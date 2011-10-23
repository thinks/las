//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef LAS_IO_HPP_INCLUDED
#define LAS_IO_HPP_INCLUDED

#include "las_ifstream.hpp"
#include "las_ofstream.hpp"
#include "las_public_header_block.hpp"
#include "las_variable_length_record.hpp"
#include "las_point.hpp"
#include <vector>
#include <string>

//------------------------------------------------------------------------------

namespace las {

//------------------------------------------------------------------------------

class io {
public:

    static const uint16 valid_point_data_start_signature = 52445; // 0xCCDD

public:

    static void
    read(const std::string                   &file_name,
         public_header_block                 &phb,
         std::vector<point>                  &points,
         std::vector<variable_length_record> *vlr = 0)
    {
        ifstream ifs(file_name);                        // May throw.
        _read_public_header_block(ifs, phb);            // May throw.
        _read_variable_length_records(ifs, phb, vlr);   // May throw.
        _read_point_data_start_signature(ifs);          // May throw.
        _read_points(ifs, phb, points);                 // May throw.
    }

    static void
    write(const std::string                         &file_name,
          const public_header_block                 &phb,
          const std::vector<variable_length_record> &vlr, 
          const std::vector<point>                  &points)
    {
        // TODO

        LAS_THROW("las::io::write() not implemented yet!!");

        ofstream ofs(file_name);                        // May throw.
        _write_public_header_block(ofs, phb);           // May throw.
        //_write_variable_length_records(ofs, phb, vlr);  // May throw.
        _write_point_data_start_signature(ofs);         // May throw.
        //_write_points(ofs, phb, points);                // May throw.
    }

private:

    static void
    _read_public_header_block(ifstream &ifs, public_header_block &phb)
    {
        ifs.stream().read(reinterpret_cast<char*>(&phb),
                          sizeof(public_header_block));
        // TODO: validate PHB!
    }

    static void
    _write_public_header_block(ofstream &ofs, const public_header_block &phb)
    {
        // TODO: validate PHB!
        ofs.stream().write(reinterpret_cast<const char*>(&phb),
                           sizeof(public_header_block));
    }

private:    // Variable length records.

    static void
    _read_variable_length_records(ifstream                            &ifs,
                                  const public_header_block           &phb,
                                  std::vector<variable_length_record> *vlr)
    {
        if (0 != vlr) {
        }
        else {
            // Skip past VLR data.

            ifs.stream().seekg(
                phb.offset_to_data() - 
                sizeof(public_header_block) - 
                sizeof(uint16),
                std::ios_base::cur);
        }
    }

    static void
    _write_variable_length_records(ofstream &ofs)
    {}

private:    // Point data start signature.

    static void
    _read_point_data_start_signature(ifstream &ifs)
    {
        uint16 point_data_start_signature(0);
        ifs.stream().read(reinterpret_cast<char*>(&point_data_start_signature),
                          sizeof(uint16));

        if (point_data_start_signature != 
            valid_point_data_start_signature) {
            LAS_THROW("Invalid point data start signature: "
                      << std::hex 
                      << "0x" << point_data_start_signature
                      << " | Valid: " 
                      << "0x" << valid_point_data_start_signature);
        }
    }

    static void
    _write_point_data_start_signature(ofstream &ofs)
    {
        ofs.stream().write(
            reinterpret_cast<const char*>(&valid_point_data_start_signature),
            sizeof(uint16));
    }

private:

    static void
    _read_points(ifstream                  &ifs,
                 const public_header_block &phb,
                 std::vector<point>        &points)
    {
        //assert(ifs.is_open());
        //assert(0 < phb.point_data_record_length());

        const int currg(ifs.stream().tellg());	// Current get position in file.
        ifs.stream().seekg(0, std::ios::end);	// Seek end-of-file.
        const int file_size(ifs.stream().tellg());       // Bytes in file.
        ifs.stream().seekg(currg, std::ios::beg); // Move back to current get pos.
        const int remain_size(file_size - currg);	// Remaining bytes.

        //assert(0 == remain_size%phb.point_data_record_length());
        /*
        if( 0 >= remain_size ) {	
            // End of file reached.

            num_buf_ = 0;
            return 0; 
        }
        */

        const int remain_pdr(remain_size/phb.point_data_record_length());
        //const std::size_t nread(std::min<std::size_t>(remain_pdr, capacity()));

        // Allocate enough memory to read one PDRF for each scan point.
        //
        std::vector<char> pdr(remain_size);
        ifs.stream().read(&pdr[0], static_cast<std::streamsize>(pdr.size())); 
        
        points.clear();
        points.reserve(remain_pdr);

        switch(phb.point_data_format_id())
        {
        case 0:
            for(std::size_t i(0); i < points.capacity(); ++i) {
            	// Convert and assign.
                try {
                    typedef point_data_record_format0 pdrf0_type;
                    points.push_back(
                        point(
                            phb, 
                            reinterpret_cast<const pdrf0_type*>(&pdr[0])[i]));
                }
                catch( const std::exception& ex ) {	
                    std::cerr << ex.what() << "\n";
                }
            }
            break;
        case 1:
            for(std::size_t i(0); i < points.capacity(); ++i) {
            	// Convert and assign.
                try {
                    typedef point_data_record_format1 pdrf1_type;
                    points.push_back(
                        point(
                            phb, 
                            reinterpret_cast<const pdrf1_type*>(&pdr[0])[i]));
                }
                catch (const std::exception& ex) {
                    std::cerr << ex.what() << "\n";
                }
            }
            break;
            /*
        default:
            SALSA_THROW("las::io_buffer: invalid point data format id: " 
                                        << phb.point_data_format_id());
                                        */
        }

        //return remain_pdr;
    }

    static void
    _write_points(ofstream &ofs)
    {}
};

//------------------------------------------------------------------------------

}   // Namespace: las.

//------------------------------------------------------------------------------

#endif  // LAS_IO_HPP_INCLUDED
