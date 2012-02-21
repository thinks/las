//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef LAS10_POINT_DATA_RECORD_FORMAT_HPP_INCLUDED
#define LAS10_POINT_DATA_RECORD_FORMAT_HPP_INCLUDED

#include "las10_namespace.hpp"
#include "las10_types.hpp"
#include "las_namespace.hpp"
#include "las_exception.hpp"
#include "las_pack.hpp"
#include <iosfwd>

//------------------------------------------------------------------------------

BEGIN_LAS10_NAMESPACE

BEGIN_PACK_TIGHT

//! POD
struct point_data_record_format0
{
    static const uint16 length = 20;    //! [bytes]

    int32  x;				// 4 bytes, required.
    int32  y;				// 4 bytes, required.
    int32  z;				// 4 bytes, required.
    uint16 intensity;		// 2 bytes.
    int8   bit_buffer;		// 1 byte.
    uint8  classification;	// 1 byte.
    int8   scan_angle_rank;	// 1 byte, required.
    uint8  file_marker;		// 1 byte.
    uint16 user_bit_field;	// 2 bytes.
};


//! POD
struct point_data_record_format1
{
    static const uint16 length = 28;   // [bytes]

    int32   x;					// 4 bytes, required.
    int32   y;					// 4 bytes, required.
    int32   z;					// 4 bytes, required.
    uint16  intensity;			// 2 bytes.
    int8    bit_buffer;		    // 1 byte.
    uint8   classification;	    // 1 byte.
    int8    scan_angle_rank;	// 1 byte, required.
    uint8   file_marker;		// 1 byte.
    uint16  user_bit_field;	    // 2 bytes.
    float64 gps_time;           // 8 bytes.
};

END_PACK_TIGHT

//------------------------------------------------------------------------------

template<class PDRF> uint8
return_num(const PDRF &pdrf) 
{ return static_cast<uint8>((pdrf.bit_buffer & 224) >> 5); }

template<class PDRF> uint8 
num_returns(const PDRF pdrf)
{ return static_cast<uint8>((pdrf.bit_buffer & 28)  >> 2); }

template<class PDRF> uint8 
scan_dir_flag(const PDRF pdrf)
{ return static_cast<uint8>((pdrf.bit_buffer & 2) >> 1); }

template<class PDRF> uint8
edge_flag(const PDRF pdrf)
{ return static_cast<uint8>(pdrf.bit_buffer & 1); }

//    static int8
//    _create_bit_buffer(const uint8 return_num,
//                       const uint8 num_returns,
//                       const uint8 scan_dir,
//                       const uint8 edge_flag)
//    { 
//        const uint8 vnum_returns(_valid_num_returns(num_returns));
//        int8 buf(0);
//        buf += (vnum_returns							    << 5);
//        buf += (_valid_return_num(return_num, vnum_returns)	<< 2);
//        buf += (_valid_scan_dir(scan_dir)					<< 1);
//        buf += (_valid_edge_flag(edge_flag)						);
//        return buf;
//    }

END_LAS10_NAMESPACE

//------------------------------------------------------------------------------

BEGIN_STD_NAMESPACE

template<class CharT, class Traits>
basic_ostream<CharT,Traits>&
operator<<(basic_ostream<CharT,Traits>            &os, 
           const las10::point_data_record_format0 &rhs)
{
    typedef las10::point_data_record_format0 pdrf0_type;
    os	<< "las10::point_data_record_format0[0x" << &rhs << "]:\n"
        << "Length                : " << pdrf0_type::length << " | " 
            << sizeof(pdrf0_type) << " [bytes]\n";
        << "X                     : " << rhs.x << "\n"
        << "Y                     : " << rhs.y << "\n"
        << "Z                     : " << rhs.z << "\n"
        << "Intensity             : " << rhs.intensity << "\n"
        << "Return Number         : " 
            << static_cast<int>(return_num(rhs)) << "\n"
        << "Number of Returns     : " 
            << static_cast<int>(num_returns(rhs)) << "\n"
        << "Scan Direction Flag   : {" 
            << static_cast<int>(scan_dir_flag(rhs)) << "}\n"
        << "Edge of Flight Line   : {" 
            << static_cast<int>(edge_flag(rhs)) << "}\n"
        << "Classification        : " 
            << static_cast<int>(rhs.classification) << "\n"
        << "Scan Angle Rank       : " 
            << static_cast<int>(rhs.scan_angle_rank) << "\n"
        << "File Marker           : " 
            << static_cast<int>(rhs.file_marker) << "\n"
        << "User Bit Field        : " << rhs.user_bit_field << "\n";
    return os;
}

//------------------------------------------------------------------------------

template<class CharT, class Traits>
basic_ostream<CharT,Traits>&
operator<<(basic_ostream<CharT,Traits>            &os, 
           const las10::point_data_record_format1 &rhs)
{
    typedef las10::point_data_record_format0 pdrf1_type;
    os	<< "las10::point_data_record_format1[0x" << &rhs << "]:\n"
        << "Length                : " << pdrf1_type::length << " | " 
            << sizeof(pdrf1_type) << " [bytes]\n";
        << "X                     : " << rhs.x << "\n"
        << "Y                     : " << rhs.y << "\n"
        << "Z                     : " << rhs.z << "\n"
        << "Intensity             : " << rhs.intensity << "\n"
        << "Return Number         : " 
            << static_cast<int>(return_num(rhs)) << "\n"
        << "Number of Returns     : " 
            << static_cast<int>(num_returns(rhs)) << "\n"
        << "Scan Direction Flag   : {" 
            << static_cast<int>(scan_dir_flag(rhs)) << "}\n"
        << "Edge of Flight Line   : {" 
            << static_cast<int>(edge_flag(rhs)) << "}\n"
        << "Classification        : " 
            << static_cast<int>(rhs.classification) << "\n"
        << "Scan Angle Rank       : " 
            << static_cast<int>(rhs.scan_angle_rank) << "\n"
        << "File Marker           : " 
            << static_cast<int>(rhs.file_marker) << "\n"
        << "User Bit Field        : " << rhs.user_bit_field << "\n"
        << "GPS Time <double>	  : " << rhs.gps_time << "\n";
    return os;
}

END_STD_NAMESPACE

//------------------------------------------------------------------------------

#endif	// LAS10_POINT_DATA_RECORD_FORMAT_HPP_INCLUDED












////! DOCS
//class point_data_record_format0
//{
//public:
//
//    static const uint16 length = 20;    //! [bytes]
//
//    //! CTOR.
//    explicit
//    point_data_record_format0(const float64 inv_scale_x,
//                              const float64 inv_scale_y,
//                              const float64 inv_scale_z,
//                              const float64 offset_x,
//                              const float64 offset_y,
//                              const float64 offset_z,
//                              const float64 pos_x,
//                              const float64 pos_y,
//                              const float64 pos_z,
//                              const uint16  intensity,
//                              const uint8   num_returns,
//                              const uint8   return_num,
//                              const uint8   scan_direction_flag,
//                              const uint8   edge_flag,
//                              const int8	scan_angle_rank,
//                              const uint8   classification,
//                              const uint8   file_marker,	
//                              const uint16  user_bit_field)
//        : _x(_coord_int32(pos_x, offset_x, inv_scale_x))
//        , _y(_coord_int32(pos_y, offset_y, inv_scale_y))
//        , _z(_coord_int32(pos_z, offset_z, inv_scale_z))
//        , _intensity(intensity)
//        , _bit_buffer(_create_bit_buffer(return_num,
//                                         num_returns,
//                                         scan_direction_flag,
//                                         edge_flag))
//        , _classification(classification)
//        , _scan_angle_rank(scan_angle_rank)
//        , _file_marker(file_marker)
//        , _user_bit_field(user_bit_field)
//    {}
//
//    //! DTOR.
//    ~point_data_record_format0()
//    {
//        LAS_STATIC_ASSERT(1 == sizeof(int8),    invalid_int8_size);
//        LAS_STATIC_ASSERT(1 == sizeof(uint8),   invalid_uint8_size);
//        LAS_STATIC_ASSERT(2 == sizeof(int16),   invalid_int16_size);
//        LAS_STATIC_ASSERT(2 == sizeof(uint16),  invalid_uint16_size);
//        LAS_STATIC_ASSERT(4 == sizeof(int32),   invalid_int32_size);
//        LAS_STATIC_ASSERT(4 == sizeof(uint32),  invalid_uint32_size);
//        LAS_STATIC_ASSERT(8 == sizeof(float64), invalid_float64_size);
//        LAS_STATIC_ASSERT(length == sizeof(point_data_record_format0), 
//                          invalid_pdrf0_length); 
//    }
//    
//public:
//
//    int32 x() const { return _x; }
//    int32 y() const { return _y; }
//    int32 z() const { return _z; }
//
//    uint16
//    intensity() const 
//    { return _intensity; }
//
//    uint8  
//    classification() const 
//    { return _classification; }
//
//    int8   
//    scan_angle_rank() const	
//    { return _scan_angle_rank; }
//
//    uint8  
//    file_marker() const	
//    { return _file_marker; }
//
//    uint16
//    user_bit_field() const 
//    { return _user_bit_field;  }
//
//public:     // Bit buffer.
//
//    uint8 
//    return_num() const 
//    { return _buf_return_num(_bit_buffer); }
//
//    uint8  
//    num_returns() const
//    { return _buf_num_returns(_bit_buffer); }
//
//    int8
//    scan_direction_flag() const
//    { return _buf_scan_dir_flag(_bit_buffer); }
//
//    uint8  
//    edge_flag() const
//    { return _buf_edge_flag(_bit_buffer); }
//
//private:    // Validation.
//    
//    static uint8 
//    _valid_num_returns(const uint8 nr)
//    {
//        static const uint8 min_num_returns = 1;
//        static const uint8 max_num_returns = 5;
//
//        if (nr < min_num_returns || nr > max_num_returns) {	
//            LAS_THROW(
//                "las::PDRF0: invalid number of returns: " 
//                    << static_cast<int32>(nr) << " [min: "
//                    << static_cast<int32>(min_num_returns)
//                    << ", max:" << static_cast<int32>(max_num_returns) << "]");
//        }
//
//        return nr;
//    }
//
//    static uint8 
//    _valid_return_num(const uint8 rn, const uint8 nr)
//    {
//        static const uint8 min_return_num = 1;
//
//        if (rn < min_return_num || rn > nr) {	
//            LAS_THROW(
//                "las::PDRF0: invalid return number: " 
//                    << static_cast<int32>(rn) << " [min:" 
//                    << static_cast<int32>(min_return_num) 
//                    << ", max:" << static_cast<int32>(nr) << "]");
//        }
//
//        return rn;
//    }
//
//    static uint8 
//    _valid_scan_dir(const uint8 scan_dir)
//    {
//        static const uint8 max_scan_dir = 1;
//
//        if (scan_dir > max_scan_dir) {	
//            LAS_THROW(
//                "las::PDRF0: invalid scan direction: " 
//                    << static_cast<int32>(scan_dir) << " [max: "
//                    << static_cast<int32>(max_scan_dir) << "]");
//        }
//
//        return scan_dir;
//    }
//
//    static uint8 
//    _valid_edge_flag(const uint8 edge_flag)
//    {
//        static const uint8 max_edge_flag = 1;
//
//        if (edge_flag > max_edge_flag) {	
//            LAS_THROW(
//                "las::PDRF0: invalid edge flag: " 
//                    << static_cast<int32>(edge_flag) << " [max: "
//                    << static_cast<int32>(max_edge_flag) << "]");	
//        }
//
//        return edge_flag;
//    }
//    
//private:    // Position.
//
//    //! Simple rounding.
//    static int32
//    _coord_int32(const float64 pos, 
//                 const float64 offset, 
//                 const float64 inv_scale)
//    { return static_cast<int32>(std::floor((pos - offset)*inv_scale + 0.5)); }
//
//private:    // Bit buffer.
//
//    static int8
//    _create_bit_buffer(const uint8 return_num,
//                       const uint8 num_returns,
//                       const uint8 scan_dir,
//                       const uint8 edge_flag)
//    { 
//        const uint8 vnum_returns(_valid_num_returns(num_returns));
//        int8 buf(0);
//        buf += (vnum_returns							    << 5);
//        buf += (_valid_return_num(return_num, vnum_returns)	<< 2);
//        buf += (_valid_scan_dir(scan_dir)					<< 1);
//        buf += (_valid_edge_flag(edge_flag)						);
//        return buf;
//    }
//
//    static uint8
//    _buf_return_num(const int8 buf) 
//    { return ((buf & 224) >> 5); }
//
//    static uint8 
//    _buf_num_returns(const int8 buf)
//    { return ((buf & 28)  >> 2); }
//
//    static uint8 
//    _buf_scan_dir_flag(const int8 buf)
//    { return ((buf & 2) >> 1); }
//
//    static uint8
//    _buf_edge_flag(const int8 buf)
//    { return  (buf & 1); }
//
//private:	// Member variables.
//
//    int32  _x;					// 4 bytes, required.
//    int32  _y;					// 4 bytes, required.
//    int32  _z;					// 4 bytes, required.
//    uint16 _intensity;			// 2 bytes.
//    int8   _bit_buffer;			// 1 byte.
//    uint8  _classification;		// 1 byte.
//    int8   _scan_angle_rank;	// 1 byte, required.
//    uint8  _file_marker;		// 1 byte.
//    uint16 _user_bit_field;		// 2 bytes.
//};
//
////------------------------------------------------------------------------------
//
//// point_data_record_format1
//// -------------------------
////! DOCS
//
//class point_data_record_format1
//{
//public:
//
//    static const uint16 length = 28;   // [bytes]
//
//    //! CTOR.
//    explicit
//    point_data_record_format1(const float64 inv_scale_x,
//                              const float64 inv_scale_y,
//                              const float64 inv_scale_z,
//                              const float64 offset_x,
//                              const float64 offset_y,
//                              const float64 offset_z,
//                              const float64 pos_x,
//                              const float64 pos_y,
//                              const float64 pos_z,
//                              const uint16  intensity,
//                              const uint8   num_returns,
//                              const uint8   return_num,
//                              const uint8   scan_direction_flag,
//                              const uint8   edge_flag,
//                              const int8	scan_angle_rank,
//                              const uint8   classification,
//                              const uint8   file_marker,	
//                              const uint16  user_bit_field,
//                              const float64 gps_time)
//        : _x(_coord_int32(pos_x, offset_x, inv_scale_x))
//        , _y(_coord_int32(pos_y, offset_y, inv_scale_y))
//        , _z(_coord_int32(pos_z, offset_z, inv_scale_z))
//        , _intensity(intensity)
//        , _bit_buffer(_create_bit_buffer(return_num,
//                                         num_returns,
//                                         scan_direction_flag,
//                                         edge_flag))
//        , _classification(classification)
//        , _scan_angle_rank(scan_angle_rank)
//        , _file_marker(file_marker)
//        , _user_bit_field(user_bit_field)
//        , _gps_time(_valid_gps_time(gps_time))
//    {}
//
//    //! DTOR.
//    ~point_data_record_format1()
//    {
//        LAS_STATIC_ASSERT(1 == sizeof(int8),    invalid_int8_size);
//        LAS_STATIC_ASSERT(1 == sizeof(uint8),   invalid_uint8_size);
//        LAS_STATIC_ASSERT(2 == sizeof(int16),   invalid_int16_size);
//        LAS_STATIC_ASSERT(2 == sizeof(uint16),  invalid_uint16_size);
//        LAS_STATIC_ASSERT(4 == sizeof(int32),   invalid_int32_size);
//        LAS_STATIC_ASSERT(4 == sizeof(uint32),  invalid_uint32_size);
//        LAS_STATIC_ASSERT(8 == sizeof(float64), invalid_float64_size);
//        LAS_STATIC_ASSERT(length == sizeof(point_data_record_format1), 
//                          invalid_pdrf1_length); 
//    }
//
//public:
//
//    int32 x() const { return _x; }
//    int32 y() const { return _y; }
//    int32 z() const { return _z; }
//
//    uint16
//    intensity() const 
//    { return _intensity; }
//
//    uint8  
//    classification() const 
//    { return _classification; }
//
//    int8   
//    scan_angle_rank() const	
//    { return _scan_angle_rank; }
//
//    uint8  
//    file_marker() const	
//    { return _file_marker; }
//
//    uint16
//    user_bit_field() const 
//    { return _user_bit_field;  }
//
//    float64 
//    gps_time() const 
//    { return _gps_time; }
//
//    int32   
//    gps_time_int32() const 
//    { return static_cast<int32>(std::floor(_gps_time)); }
//
//public:     // Bit buffer.
//
//    uint8 
//    return_num() const 
//    { return _buf_return_num(_bit_buffer); }
//
//    uint8  
//    num_returns() const
//    { return _buf_num_returns(_bit_buffer); }
//
//    int8
//    scan_direction_flag() const
//    { return _buf_scan_dir_flag(_bit_buffer); }
//
//    uint8  
//    edge_flag() const
//    { return _buf_edge_flag(_bit_buffer); }
//
//private:    // Validation.
//    
//    static uint8 
//    _valid_num_returns(const uint8 nr)
//    {
//        static const uint8 min_num_returns = 1;
//        static const uint8 max_num_returns = 5;
//    
//        if (nr < min_num_returns || nr > max_num_returns) {	
//            LAS_THROW(
//                "las::PDRF1: invalid number of returns: " 
//                    << static_cast<int32>(nr) << " [min: "
//                    << static_cast<int32>(min_num_returns)
//                    << ", max:" << static_cast<int32>(max_num_returns) << "]");
//        }
//
//        return nr;
//    }
//
//    static uint8 
//    _valid_return_num(const uint8 rn, const uint8 nr)
//    {
//        static const uint8 min_return_num = 1;
//
//        if (rn < min_return_num || rn > nr) {	
//            LAS_THROW(
//                "LAS_PDRF1: invalid return number: " 
//                    << static_cast<int32>(rn) << " [min:" 
//                    << static_cast<int32>(min_return_num) 
//                    << ", max:" << static_cast<int32>(nr) << "]");
//        }
//
//        return rn;
//    }
//
//    static uint8
//    _valid_scan_dir(const uint8 scan_dir)
//    {
//        static const uint8 max_scan_dir    = 1;
//
//        if (scan_dir > max_scan_dir) {	
//            LAS_THROW(
//                "las::PDRF1: invalid scan direction: " 
//                    << static_cast<int32>(scan_dir) << " [max: "
//                    << static_cast<int32>(max_scan_dir) << "]");
//        }
//
//        return scan_dir;
//    }
//
//    static uint8 
//    _valid_edge_flag(const uint8 edge_flag)
//    {
//        static const uint8 max_edge_flag = 1;
//
//        if (edge_flag > max_edge_flag) {	
//            LAS_THROW(
//                "las::PDRF1: invalid edge flag: " 
//                    << static_cast<int32>(edge_flag) << " [max: "
//                    << static_cast<int32>(max_edge_flag) << "]");	
//        }
//
//        return edge_flag;
//    }
//
//    static float64 
//    _valid_gps_time(const float64 t)
//    {
//        static const float64 min_gps_time(0.);
//        static const float64 max_gps_time((std::numeric_limits<int32>::max)());
//
//        if (t > max_gps_time || t < min_gps_time) {
//            LAS_THROW(
//                "las::PDRF1: invalid GPS time: " << t << 
//                " [min: " << min_gps_time << ", max:" << max_gps_time << "]");
//        }
//
//        return t;
//    }
//
//private:    // Position.
//
//    //! Simple nearest integer rounding.
//    static int32
//    _coord_int32(const float64 pos, 
//                 const float64 offset, 
//                 const float64 inv_scale)
//    { return static_cast<int32>(std::floor((pos - offset)*inv_scale + 0.5)); }
//
//private:    // Bit buffer.
//
//    static int8
//    _create_bit_buffer(const uint8 return_num,
//                       const uint8 num_returns,
//                       const uint8 scan_dir,
//                       const uint8 edge_flag)
//    { 
//        const uint8 vnum_returns(_valid_num_returns(num_returns));
//        int8 buf(0);
//        buf += (vnum_returns							    << 5);
//        buf += (_valid_return_num(return_num, vnum_returns)	<< 2);
//        buf += (_valid_scan_dir(scan_dir)					<< 1);
//        buf += (_valid_edge_flag(edge_flag)						);
//        return buf;
//    }
//
//    static uint8 
//    _buf_return_num(const int8 buf) 
//    { return ((buf & 224) >> 5); }
//
//    static uint8 
//    _buf_num_returns(const int8 buf)
//    { return ((buf & 28) >> 2); }
//
//    static uint8 
//    _buf_scan_dir_flag(const int8 buf)
//    { return ((buf & 2) >> 1); }
//
//    static uint8
//    _buf_edge_flag(const int8 buf)
//    { return  (buf & 1); }
//
//private:	// Member variables.
//
//    int32   _x;					// 4 bytes, required.
//    int32   _y;					// 4 bytes, required.
//    int32   _z;					// 4 bytes, required.
//    uint16  _intensity;			// 2 bytes.
//    int8    _bit_buffer;		// 1 byte.
//    uint8   _classification;	// 1 byte.
//    int8    _scan_angle_rank;	// 1 byte, required.
//    uint8   _file_marker;		// 1 byte.
//    uint16  _user_bit_field;	// 2 bytes.
//    float64 _gps_time;          // 8 bytes.
//};





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
