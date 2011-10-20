//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef LAS_POINT_DATA_RECORD_FORMAT_HPP_INCLUDED
#define LAS_POINT_DATA_RECORD_FORMAT_HPP_INCLUDED

//#include "salsa_exception.hpp"
//#include "salsa_las_public_header_block.hpp"

#include <limits>
#include <exception>
#include <fstream>
#include <iostream>

//------------------------------------------------------------------------------

namespace las {

//------------------------------------------------------------------------------

#ifdef WIN32 
#pragma pack(push)
#pragma pack(1)     // 1 byte alignment.		
#endif  // WIN32

//------------------------------------------------------------------------------

// point_data_record_format0
// -------------------------
//! DOCS

class point_data_record_format0
{
public:

    static const int size = 20;		//! [bytes]

    //! CTOR.
    explicit
    point_data_record_format0(const double         scale_x,
                              const double         scale_y,
                              const double         scale_z,
                              const double         offset_x,
                              const double         offset_y,
                              const double         offset_z,
                              const double         pos_x,
                              const double         pos_y,
                              const double         pos_z,
                              const unsigned short intensity,
                              const unsigned char  num_returns,
                              const unsigned char  return_num,
                              const unsigned char  scan_direction_flag,
                              const unsigned char  edge_flag,
                              const char	       scan_angle_rank,
                              const unsigned char  classification,
                              const unsigned char  file_marker,	
                              const unsigned short user_bit_field)
        : _x(_compute_coord(pos_x, offset_x, scale_x))
        , _y(_compute_coord(pos_y, offset_y, scale_y))
        , _z(_compute_coord(pos_z, offset_z, scale_z))
        , _intensity(i)
        , _bit_buffer(_compute_bit_buffer(return_num,
                                          num_returns,
                                          scan_direction_flag,
                                          edge_flag))
        , _classification(classification)
        , _scan_angle_rank(scan_angle_rank)
        , _file_marker(file_marker)
        , _user_bit_field(user_bit_field)
    {}

    //! DTOR.
    ~point_data_record_format0()
    {
        //SALSA_STATIC_ASSERT(
        //    size == sizeof(las_point_data_record_format0), invalid_size);
    }
    
    // Default copy & assign.

    int  
    x() const 
    { return _x; }

    int  
    y() const 
    { return _y; }

    int
    z() const 
    { return _z; }

    unsigned short 
    intensity() const 
    { return _intensity; }

    unsigned char  
    classification() const 
    { return _classification; }

    char   
    scan_angle_rank() const	
    { return _scan_angle_rank; }

    unsigned char  
    file_marker() const	
    { return _file_marker; }

    unsigned short
    user_bit_field() const 
    { return _user_bit_field;  }

public:     // Bit buffer.

    unsigned char 
    return_num() const 
    { return _buf_return_num(_bit_buffer); }

    unsigned char  
    num_returns() const
    { return _buf_num_returns(_bit_buffer); }

    char
    scan_direction_flag() const
    { return _buf_scan_dir_flag(_bit_buffer); }

    thx::uint8  
    edge_of_flight_line() const
    { return _buf_edge_flag(_bit_buffer); }

private:

    point_data_record_format0();	//! Empty CTOR - disabled.

private:    // Constants.
    
    static const unsigned char _min_num_returns = 1;
    static const unsigned char _min_return_num  = 1;
    static const unsigned char _max_scan_dir    = 1;
    static const unsigned char _max_edge_flag   = 1;

private:    // Helper functions.
    
    static unsigned char 
    _valid_num_returns(const unsigned char nr)
    {
        if( nr < _min_num_returns ||
            nr > public_header_block::num_points_by_return_length ) {	
            LAS_THROW(
                "las::PDRF0: invalid num_returns: " 
                    << static_cast<int>(nr) << " [min: "
                    << static_cast<int>(min_num_returns)
                    << ", max:"
                    << static_cast<int>(
                        las_public_header_block::num_points_by_return_length)
                    << "]");
        }

        return nr;
    }

    static unsigned char 
    _valid_return_num(const unsigned char rn, const unsigned char nr)
    {
        if( rn < _min_return_num || rn > nr ) {	
            LAS_THROW(
                "las::PDRF0: invalid return_num: " 
                    << static_cast<int>(rn) << " [min:" 
                    << static_cast<int>(min_return_num) 
                    << ", max:" << static_cast<int>(nr) << "]");
        }

        return rn;
    }

    static unsigned char 
    _valid_scan_dir(const unsigned char scan_dir)
    {
        if( scan_dir > max_scan_dir ) {	
            SALSA_THROW(
                "las::PDRF0: invalid scan_dir: " 
                    << static_cast<int64>(scan_dir) << " [max: "
                    << static_cast<int64>(max_scan_dir) << "]");
        }

        return scan_dir;
    }

    static unsigned char 
    _valid_edge_flag(const unsigned char edge)
    {
        if (edge > max_edge_flag) {	
            SALSA_THROW(
                "las::PDRF0: invalid edge_flag: " 
                    << static_cast<int>(edge) << " [max: "
                    << static_cast<int>(max_edge_flag) << "]");	
        }

        return edge;
    }
    
    //! Simple rounding.
    static int
    _compute_coord(const double pos, 
                   const double offset, 
                   const double scale)
    { return std::floor((pos - offset)/scale + 0.5); }

    static char
    _compute_bit_buffer(const unsigned char return_num,
                        const unsigned char num_returns,
                        const unsigned char scan_dir,
                        const unsigned char edge_flag)
    { 
        const unsigned char vnum_returns(valid_num_returns(num_returns));
        char buf(0);
        buf += (vnum_returns							    << 5);
        buf += (valid_return_num(return_num, vnum_returns)	<< 2);
        buf += (valid_scan_dir(scan_dir)					<< 1);
        buf += (valid_edge_flag(edge_flag)						);
        return buf;
    }

    static unsigned char 
    _buf_return_num(const char buf) 
    { return ((buf & 224) >> 5); }

    static unsigned char 
    _buf_num_returns(const char buf)
    { return ((buf & 28)  >> 2); }

    static unsigned char 
    _buf_scan_dir_flag(const char buf)
    { return ((buf & 2) >> 1); }

    static unsigned char
    _buf_edge_flag(const char buf)
    { return  (buf & 1); }

private:	// Member variables.

    int            _x;					// 4 bytes, required.
    int            _y;					// 4 bytes, required.
    int            _z;					// 4 bytes, required.
    unsigned short _intensity;			// 2 bytes.
    char           _bit_buffer;			// 1 byte.
    unsigned char  _classification;		// 1 byte.
    char           _scan_angle_rank;	// 1 byte, required.
    unsigned char  _file_marker;		// 1 byte.
    unsigned short _user_bit_field;		// 2 bytes.
};

//------------------------------------------------------------------------------

// point_data_record_format1
// -------------------------
//! DOCS

class point_data_record_format1
{
public:

    static const thx::int64 size = 28;		// [bytes]

    //! CTOR.
    explicit
    point_data_record_format1(const double         scale_x,
                              const double         scale_y,
                              const double         scale_z,
                              const double         offset_x,
                              const double         offset_y,
                              const double         offset_z,
                              const double         pos_x,
                              const double         pos_y,
                              const double         pos_z,
                              const unsigned short intensity,
                              const unsigned char  num_returns,
                              const unsigned char  return_num,
                              const unsigned char  scan_direction_flag,
                              const unsigned char  edge_flag,
                              const char	       scan_angle_rank,
                              const unsigned char  classification,
                              const unsigned char  file_marker,	
                              const unsigned short user_bit_field,
                              const double         gps_time)
        : _x(_compute_coord(pos_x, offset_x, scale_x))
        , _y(_compute_coord(pos_y, offset_y, scale_y))
        , _z(_compute_coord(pos_z, offset_z, scale_z))
        , _intensity(i)
        , _bit_buffer(_compute_bit_buffer(return_num,
                                          num_returns,
                                          scan_direction_flag,
                                          edge_flag))
        , _classification(classification)
        , _scan_angle_rank(scan_angle_rank)
        , _file_marker(file_marker)
        , _user_bit_field(user_bit_field)
        , _valid_gps_time(gps_time)
    {}


    //! DTOR.
    ~point_data_record_format1()
    {
        //SALSA_STATIC_ASSERT(
        //    size == sizeof(las_point_data_record_format1), invalid_size);
    }

    // Default copy & assign.

    int  
    x() const 
    { return _x; }

    int  
    y() const 
    { return _y; }

    int
    z() const 
    { return _z; }

    unsigned short 
    intensity() const 
    { return _intensity; }

    unsigned char  
    classification() const 
    { return _classification; }

    char   
    scan_angle_rank() const	
    { return _scan_angle_rank; }

    unsigned char  
    file_marker() const	
    { return _file_marker; }

    unsigned short
    user_bit_field() const 
    { return _user_bit_field;  }

    double 
    gps_time() const 
    { return _gps_time; }

    int   
    gps_time_int() const 
    { return std::floor(_gps_time); }

private:

    point_data_record_format1();	// Empty CTOR - disabled.

private:    // Constants.
    
    static const unsigned char _min_num_returns = 1;
    static const unsigned char _min_return_num  = 1;
    static const unsigned char _max_scan_dir    = 1;
    static const unsigned char _max_edge_flag   = 1;

private:    // Helper functions.
    
    static unsigned char 
    _valid_num_returns(const unsigned char nr)
    {
        if( nr < min_num_returns ||
            nr > las_public_header_block::num_points_by_return_length ) {	
            SALSA_THROW(
                "las::PDRF1: invalid num_returns: " 
                    << static_cast<int>(nr) << " [min: "
                    << static_cast<int>(min_num_returns)
                    << ", max:"
                    << static_cast<int>(
                        las_public_header_block::num_points_by_return_length)
                    << "]");
        }

        return nr;
    }

    static unsigned char 
    _valid_return_num(const unsigned char rn, const unsigned char nr)
    {
        if( rn < min_return_num || rn > nr ) {	
            SALSA_THROW(
                "LAS_PDRF1: invalid return_num: " 
                    << static_cast<int>(rn) << " [min:" 
                    << static_cast<int>(min_return_num) 
                    << ", max:" << static_cast<int>(nr) << "]");
        }

        return rn;
    }

    static unsigned char 
    _valid_scan_dir(const unsigned char scan_dir)
    {
        if( scan_dir > max_scan_dir ) {	
            SALSA_THROW(
                "las::PDRF1: invalid scan_dir: " 
                    << static_cast<int64>(scan_dir) << " [max: "
                    << static_cast<int64>(max_scan_dir) << "]");
        }

        return scan_dir;
    }

    static unsigned char 
    _valid_edge_flag(const unsigned char edge)
    {
        if (edge > max_edge_flag) {	
            SALSA_THROW(
                "las::PDRF1: invalid edge_flag: " 
                    << static_cast<int>(edge) << " [max: "
                    << static_cast<int>(max_edge_flag) << "]");	
        }

        return edge;
    }
    
    //! Simple nearest integer rounding.
    static int
    _compute_coord(const double pos, 
                   const double offset, 
                   const double scale)
    { return std::floor((pos - offset)/scale + 0.5); }

    static char
    _compute_bit_buffer(const unsigned char return_num,
                        const unsigned char num_returns,
                        const unsigned char scan_dir,
                        const unsigned char edge_flag)
    { 
        const unsigned char vnum_returns(valid_num_returns(num_returns));
        char buf(0);
        buf += (vnum_returns							    << 5);
        buf += (valid_return_num(return_num, vnum_returns)	<< 2);
        buf += (valid_scan_dir(scan_dir)					<< 1);
        buf += (valid_edge_flag(edge_flag)						);
        return buf;
    }

    static unsigned char 
    _buf_return_num(const char buf) 
    { return ((buf & 224) >> 5); }

    static unsigned char 
    _buf_num_returns(const char buf)
    { return ((buf & 28)  >> 2); }

    static unsigned char 
    _buf_scan_dir_flag(const char buf)
    { return ((buf & 2) >> 1); }

    static unsigned char
    _buf_edge_flag(const char buf)
    { return  (buf & 1); }

    static double 
    _valid_gps_time(const double t)
    {
        static const double min_gps_time(0.0);
        static const double max_gps_time((std::numeric_limits<int>::max)());

        if(	t > max_gps_time || t < min_gps_time ) {
            SALSA_THROW(
                "las::PDRF1: invalid gps_time: " << t << 
                    " [min: " << min_gps_time << ", max:" << max_gps_time << "]"
                       );
        }

        return t;
    }

private:	// Member variables.

    int            _x;					// 4 bytes, required.
    int            _y;					// 4 bytes, required.
    int            _z;					// 4 bytes, required.
    unsigned short _intensity;			// 2 bytes.
    char           _bit_buffer;			// 1 byte.
    unsigned char  _classification;		// 1 byte.
    char           _scan_angle_rank;	// 1 byte, required.
    unsigned char  _file_marker;		// 1 byte.
    unsigned short _user_bit_field;		// 2 bytes.
    double         _gps_time;           // 8 bytes.
};

//------------------------------------------------------------------------------

#ifdef WIN32
#pragma pack(pop)	// pack(1)
#endif  // WIN32 

//------------------------------------------------------------------------------

}	// Namespace: las.

//------------------------------------------------------------------------------

namespace std
{

template<class CharT, class Traits>
basic_ostream<CharT,Traits>&
operator<<(basic_ostream<CharT,Traits>          &os, 
           const las::point_data_record_format0 &rhs)
{
    os	<< "las::point_data_record_format0[0x" << &rhs << "]:\n"
        << "X                     : " << rhs.x() << "\n"
        << "Y                     : " << rhs.y() << "\n"
        << "Z                     : " << rhs.z() << "\n"
        << "Intensity             : " << rhs.intensity() << "\n"
        << "Return Number         : " 
            << static_cast<int>(rhs.return_num()) << "\n"
        << "Number of Returns     : " 
            << static_cast<int>(rhs.num_returns()) << "\n"
        << "Scan Direction Flag   : {" 
            << static_cast<int>(rhs.scan_direction_flag()) << "}\n"
        << "Edge of Flight Line   : {" 
            << static_cast<int>(rhs.edge_of_flight_line()) << "}\n"
        << "Classification        : " 
            << static_cast<int>(rhs.classification()) << "\n"
        << "Scan Angle Rank       : " 
            << static_cast<int>(rhs.scan_angle_rank()) << "\n"
        << "File Marker           : " 
            << static_cast<int>(rhs.file_marker()) << "\n"
        << "User Bit Field        : " << rhs.user_bit_field() << "\n";
    return os;
}

//------------------------------------------------------------------------------

template<class CharT, class Traits>
basic_ostream<CharT,Traits>&
operator<<(basic_ostream<CharT,Traits>          &os, 
           const las::point_data_record_format1 &rhs)
{
    os	<< "las::point_data_record_format1[0x" << &rhs << "]:\n"
        << "X                     : " << rhs.x() << "\n"
        << "Y                     : " << rhs.y() << "\n"
        << "Z                     : " << rhs.z() << "\n"
        << "Intensity             : " << rhs.intensity() << "\n"
        << "Return Number         : " 
            << static_cast<int>(rhs.return_num()) << "\n"
        << "Number of Returns     : " 
            << static_cast<int>(rhs.num_returns()) << "\n"
        << "Scan Direction Flag   : {" 
            << static_cast<int>(rhs.scan_direction_flag()) << "}\n"
        << "Edge of Flight Line   : {" 
            << static_cast<int>(rhs.edge_of_flight_line()) << "}\n"
        << "Classification        : " 
            << static_cast<int>(rhs.classification()) << "\n"
        << "Scan Angle Rank       : " 
            << static_cast<int>(rhs.scan_angle_rank()) << "\n"
        << "File Marker           : " 
            << static_cast<int>(rhs.file_marker()) << "\n"
        << "User Bit Field        : " << rhs.user_bit_field() << "\n"
        << "GPS Time <double>	  : " << rhs.gps_time() 
            << " | <int>: " << rhs.gps_time_int() << "\n";
    return os;
}

}	// Namespace: std.

#endif	// LAS_POINT_DATA_RECORD_FORMAT_HPP_INCLUDED







//void 
//read(std::ifstream& ifs)
//{
//    lpdrf0_.read(ifs);
//    ifs.read(reinterpret_cast<char*>(&gps_time_), 
//                sizeof(thx::float64));
//
//    gps_time_ = valid_gps_time(gps_time_);
//}
//    
//void 
//write(std::ofstream& ofs) const
//{
//    ofs.write(reinterpret_cast<const char*>(this), 
//                las_point_data_record_format1::size);
//}



//void 
//read(std::ifstream& ifs)
//{
//    ifs.read(reinterpret_cast<char*>(this), 
//                las_point_data_record_format0::size);
//
//    // Ensure valid values.
//    //
//    bit_buffer_ = compute_bit_buffer(return_num(),
//                                        num_returns(),
//                                        scan_direction_flag(),
//                                        edge_of_flight_line());
//}
//
//void 
//write(std::ofstream& ofs) const
//{ ofs.write(reinterpret_cast<const char*>(this), size); }


//=========================================================================
