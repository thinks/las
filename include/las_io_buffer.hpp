//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef LAS_IO_BUFFER_HPP_INCLUDED
#define LAS_IO_BUFFER_HPP_INCLUDED

#include "salsa_scan_point.hpp"
#include <thx.hpp>
#include <iosfwd>
#include <vector>
#include <cassert>

//------------------------------------------------------------------------------

namespace salsa {

//------------------------------------------------------------------------------

// Stream IO buffer size.
//
// 2^16 = 65536
// 2^20 = 1048576
// 2^21 = 2097152
// 2^22 = 4194304
// 2^23 = 8388608
// 2^24 = 16777216


class las_public_header_block;	// Fwd

template<typename S>
class io_buffer
{
public:

    //! CTOR.
    explicit 
    io_buffer(const std::size_t max_size = 4194304)
    {
        _sp_buf.reserve(max_size);
        _pdr_buf.reserve(max_size);
    }

    // Default copy, assign and DTOR.

    const scan_point& 
    operator[](const int i) const
    {
        assert(0 <= i && i < size());
        return _sp_buf[i];
    }

    const std::vector<scan_point>& 
    sp_buf() const 
    { return _sp_buf; }
    
    const std::vector<char>&	   
    pdr_buf() const 
    { return _pdr_buf; }

    std::size_t
    capacity() const 
    { return _sp_buf.capacity(); }
    
    std::size_t 
    size() const 
    { return _sp_buf.size(); }
    
    std::size_t
    mem_used() const
    {
        return (sizeof(io_buffer) + 
                sizeof(scan_point)*_sp_buf.capacity() +
                sizeof(char)*_pdr_buf.capacity());
    }

    // Return number of remaining records in file.
    //
    int 
    fill(std::ifstream &ifs, const public_header_block &phb)
    {
        assert(ifs.is_open());
        assert(0 < phb.point_data_record_length());

        const int currg(ifs.tellg());	        // Current get position in file.
        ifs.seekg(0, std::ios::end);			// Seek end-of-file.
        const int file_size(ifs.tellg());       // Bytes in file.
        ifs.seekg(currg, std::ios::beg);		// Move back to current get pos.
        const int remain_size(file_size - currg);	// Remaining bytes.
        assert(0 == remain_size%phb.point_data_record_length());

        if( 0 >= remain_size ) {	
            // End of file reached.

            num_buf_ = 0;
            return 0; 
        }

        const thx::int64 remain_pdr(remain_size/phb.point_data_record_length());
        const std::size_t nread(std::min<std::size_t>(remain_pdr, capacity()));

        // Allocate enough memory to read one PDRF for each scan point.
        //
        pdr_buf_.resize(
            static_cast<std::size_t>(nread*phb.point_data_record_length()));
        ifs.read(&pdr_buf_[0], static_cast<std::streamsize>(_pdr_buf.size())); 
        
        sp_buf_.reserve(static_cast<std::size_t>(nread));	
        sp_buf_.clear();

        switch(phb.point_data_format_id())
        {
        case 0:
            for(std::size_t i(0); i < nread; ++i) {
            	// Convert and assign.
                try 
                {
                    typedef point_data_record_format0 pdrf0;
                    const pdrf0 p(reinterpret_cast<pdrf0*>(&_pdr_buf[0])[i]);
                    _sp_buf.push_back(
                        scan_point(
                            phb.x_scale_factor(), 
                            phb.y_scale_factor(), 
                            phb.z_scale_factor()),
                            phb.x_offset(),
                            phb.y_offset(),
                            phb.z_offset()),
                            p.x(), p.y(), p.z(),
                            0.0,    // GPS time.
                            p.intensity(),
                            p.num_returns(),
                            p.return_num(),
                            p.scan_direction_flag(),
                            p.edge_of_flight_line(),
                            p.scan_angle_rank(),
                            p.classification()));
                }
                catch( const std::exception& ex ) {	
                    std::cerr << ex.what() << "\n";
                }
            }
            break;
        case 1:
            for(std::size_t i(0); i < nread; ++i) {
            	// Convert and assign.
                
                try 
                {
                    typedef point_data_record_format1 pdrf1;
                    const pdrf1 p(reinterpret_cast<pdrf1*>(&_pdr_buf[0])[i]);
                    sp_buf_.push_back(
                        scan_point(
                            phb.x_scale_factor(), 
                            phb.y_scale_factor(), 
                            phb.z_scale_factor(),
                            phb.x_offset(),
                            phb.y_offset(),
                            phb.z_offset(),
                            p.x(), p.y(), p.z(),
                            p.gps_time(),
                            p.intensity(),
                            p.num_returns(),
                            p.return_num(),
                            p.scan_direction_flag(),
                            p.edge_of_flight_line(),
                            p.scan_angle_rank(),
                            p.classification());
                }
                catch (const std::exception& ex) {
                    std::cerr << ex.what() << "\n";
                }
            }
            break;
        default:
            SALSA_THROW("las::io_buffer: invalid point data format id: " 
                                        << phb.point_data_format_id());
        }

        return remain_pdr;
    }

    // Write buffered points to file.
    //
    void 
    write(std::ofstream& ofs, const las_public_header_block& phb)
    {
        assert(ofs.is_open());

        if( 0 == num_buf_ ) { return; }	// Nothing to write.

        switch(phb.point_data_format_id())
        {
        case 0:
            {
            typedef las_point_data_record_format0 lpdrf0;

            std::vector<lpdrf0> lpdrf_buf;
            lpdrf_buf.reserve(static_cast<std::size_t>(num_buf_));
            for(thx::int64 i = 0; i < num_buf_; ++i)
            {	// Convert and insert.
                //
                try
                {
                    const lpdrf0 pd(
                        thx::vec3f64(phb.x_scale_factor(),
                                     phb.y_scale_factor(),
                                     phb.z_scale_factor()),
                        thx::vec3f64(phb.x_offset(),
                                     phb.y_offset(),
                                     phb.z_offset()),
                        (*this)[i].pos(),
                        (*this)[i].intensity(),
                        (*this)[i].num_returns(),
                        (*this)[i].return_num(),
                        (*this)[i].scan_direction_flag(),
                        (*this)[i].edge_flag(),
                        (*this)[i].scan_angle_rank(),
                        (*this)[i].classification(),
                        0,
                        0);

                    lpdrf_buf.push_back(pd);
                }
                catch( const std::exception& ex )
                {
                    log::instance().msg() << ex.what() << "\n";
                    log::instance().flush();
                }
            }

            // Write chunk to file.
            //
            ofs.write(reinterpret_cast<const char*>(&lpdrf_buf[0]),
                      static_cast<std::streamsize>(
                        num_buf_*phb.point_data_record_length()));
            }
            break;
        case 1:
            {
            typedef las_point_data_record_format1 lpdrf1;

            std::vector<lpdrf1> lpdrf_buf;
            lpdrf_buf.reserve(static_cast<std::size_t>(num_buf_));
            for(thx::int64 i = 0; i < num_buf_; ++i)
            {	// Convert and insert.
                //
                try
                {
                    const lpdrf1 pd(
                        thx::vec3f64(phb.x_scale_factor(),
                                     phb.y_scale_factor(),
                                     phb.z_scale_factor()),
                        thx::vec3f64(phb.x_offset(),
                                     phb.y_offset(),
                                     phb.z_offset()),
                        (*this)[i].pos(),
                        (*this)[i].intensity(),
                        (*this)[i].num_returns(),
                        (*this)[i].return_num(),
                        (*this)[i].scan_direction_flag(),
                        (*this)[i].edge_flag(),
                        (*this)[i].scan_angle_rank(),
                        (*this)[i].classification(),
                        0,
                        0,
                        (*this)[i].gps_time());

                    lpdrf_buf.push_back(pd);
                }
                catch( const std::exception& ex )
                {
                    log::instance().msg() << ex.what() << "\n";
                    log::instance().flush();
                }
            }

            // Write chunk to file.
            //
            ofs.write(reinterpret_cast<const char*>(&lpdrf_buf[0]),
                      static_cast<std::streamsize>(
                        num_buf_*phb.point_data_record_length()));
            }
            break;
        default:
            SALSA_THROW("las::io_buffer: invalid point data format id: " 
                                        << phb.point_data_format_id());
        }
    }

private:    // Member variables.

    std::vector<scan_point> _sp_buf;
    std::vector<char>       _pdr_buf;
    int                     _num_buf;
};

//------------------------------------------------------------------------------

}	// Namespace: las.

//------------------------------------------------------------------------------

namespace std
{

template<class CharT, class Traits>
basic_ostream<CharT,Traits>&
operator<<(basic_ostream<CharT,Traits> &os,
           const las::io_buffer        &rhs)
{
    os	<< "las::io_buffer[0x" << &rhs << "]:\n"
        << "Capacity  : " << rhs.capacity()	<< " [scan points]\n"
        << "Size      : " << rhs.size()		<< " [scan points]\n"
        << "Mem used  : " << 0.000001*rhs.mem_used() 
            << " [MB] (SP: " 
            << 0.000001*sizeof(las::scan_point)*rhs.sp_buf().capacity() 
            << " [MB] + PDR: "
            << 0.000001*sizeof(char)*rhs.pdr_buf().capacity() << " [MB])\n";
    return os;
}

}	// Namespace: std.

//------------------------------------------------------------------------------

#endif	// SALSA_LAS_IO_BUFFER_HPP_INCLUDED
