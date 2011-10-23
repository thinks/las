//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef LAS_POINT_HPP_INCLUDED
#define LAS_POINT_HPP_INCLUDED

#include "las_types.hpp"
#include "las_exception.hpp"
#include "las_public_header_block.hpp"
#include "las_point_data_record_format.hpp"
#include <limits>
#include <iostream>
#include <iomanip>

//------------------------------------------------------------------------------

namespace las {

//------------------------------------------------------------------------------

class point
{
public:

    //! PDRF0 CTOR.
    explicit
    point(const public_header_block       &phb,
          const point_data_record_format0 &pdrf0)
        : _x(_coord_float32(phb.x_scale_factor(), pdrf0.x(), phb.x_offset()))
        , _y(_coord_float32(phb.y_scale_factor(), pdrf0.y(), phb.y_offset()))
        , _z(_coord_float32(phb.z_scale_factor(), pdrf0.z(), phb.z_offset()))
        , _r(0)
        , _g(0) 
        , _b(0)
        , _gps_time(_valid_gps_time(0.))
        , _intensity(pdrf0.intensity())
        , _num_returns(_valid_num_returns(pdrf0.num_returns()))
        , _return_num(_valid_return_num(pdrf0.return_num(),pdrf0.num_returns()))
        , _scan_direction_flag(_valid_scan_dir(pdrf0.scan_direction_flag()))
        , _edge_flag(_valid_edge_flag(pdrf0.edge_flag()))
        , _scan_angle_rank(pdrf0.scan_angle_rank())
        , _classification(pdrf0.classification())
    {}

    //! PDRF1 CTOR.
    explicit
    point(const public_header_block       &phb,
          const point_data_record_format1 &pdrf1)
        : _x(_coord_float32(phb.x_scale_factor(), pdrf1.x(), phb.x_offset()))
        , _y(_coord_float32(phb.y_scale_factor(), pdrf1.y(), phb.y_offset()))
        , _z(_coord_float32(phb.z_scale_factor(), pdrf1.z(), phb.z_offset()))
        , _r(0)
        , _g(0) 
        , _b(0)
        , _gps_time(_valid_gps_time(pdrf1.gps_time()))
        , _intensity(pdrf1.intensity())
        , _num_returns(_valid_num_returns(pdrf1.num_returns()))
        , _return_num(_valid_return_num(pdrf1.return_num(),pdrf1.num_returns()))
        , _scan_direction_flag(_valid_scan_dir(pdrf1.scan_direction_flag()))
        , _edge_flag(_valid_edge_flag(pdrf1.edge_flag()))
        , _scan_angle_rank(pdrf1.scan_angle_rank())
        , _classification(pdrf1.classification())
    {}

public:

    float32 x() const { return _x; }
    float32 y() const { return _y; }
    float32 z() const { return _z; }

    uint8 r() const { return _r; }
    uint8 g() const { return _g; }
    uint8 b() const { return _b; }

    float64	
    gps_time() const 
    { return _gps_time; }

    uint16		
    intensity() const 
    { return _intensity; }

    uint8		
    num_returns() const 
    { return _num_returns; }
    
    uint8		
    return_num() const 
    { return _return_num; }
    
    uint8		
    scan_direction_flag() const 
    { return _scan_direction_flag; }
  
    uint8		
    edge_flag()	const 
    { return _edge_flag; }
    
    int8		
    scan_angle_rank() const 
    { return _scan_angle_rank; }
    
    uint8		
    classification() const 
    { return _classification; }

private:    // Validation.

    static float64
    _valid_gps_time(const float64 t)
    {
        static const float64 min_gps_time(0.);
        static const float64 max_gps_time((std::numeric_limits<int32>::max)());

        if (t > max_gps_time || t < min_gps_time) {
            LAS_THROW(
                "las::point: invalid GPS time: " << t << 
                " [min: " << min_gps_time << ", max: " << max_gps_time << "]");
        }

        return t;
    }

    static uint8
    _valid_num_returns(const uint8 nr)
    {
        static const uint8 min_num_returns(1);

        if (nr < min_num_returns) {	
            LAS_THROW(
                "las::point: invalid number of returns: " 
                    << static_cast<int>(nr) << " [min: "
                    << static_cast<int>(min_num_returns) << "]");
        }

        return nr;
    }

    static uint8
    _valid_return_num(const uint8 rn, const uint8 nr)
    {	
        static const uint8 min_return_num(1);

        if (rn < min_return_num || rn > nr) {	
            LAS_THROW(
                "las::point: invalid return number: " 
                    << static_cast<int>(rn) << " [min: " 
                    << static_cast<int>(min_return_num) 
                    << ", max: " << static_cast<int>(nr) << "]");
        }

        return rn;
    }

    static uint8
    _valid_scan_dir(const uint8 scan_dir)
    {	
        static const uint8 max_scan_dir(1);

        if (scan_dir > max_scan_dir) {	
            LAS_THROW(
                "las::point: invalid scan direction: " 
                    << static_cast<int>(scan_dir) << " [max: "
                    << static_cast<int>(max_scan_dir) << "]");
        }

        return scan_dir;
    }

    static uint8
    _valid_edge_flag(const uint8 edge)
    {
        static const uint8 max_edge_flag(1);
        
        if (edge > max_edge_flag) {	
            LAS_THROW(
                "las::point: invalid edge_flag: " 
                    << static_cast<int>(edge) << " [max: "
                    << static_cast<int>(max_edge_flag) << "]");	
        }

        return edge;
    }

private:    // Position.

    static float32
    _coord_float32(const float64 scale,
                   const int32   pos,
                   const float64 offset)
    { return static_cast<float32>(scale*pos + offset); }

private:	// Member variables.

    float32 _x, _y, _z;             // 12 bytes.
    uint8   _r, _g, _b; 	        // 3 byte.
    float64 _gps_time;			    // 8 bytes, [LAS].
    uint16  _intensity;			    // 2 bytes, [LAS].
    uint8   _num_returns;		    // 1 byte,  [LAS].
    uint8   _return_num;			// 1 byte,  [LAS].
    uint8   _scan_direction_flag;   // 1 byte,  [LAS].
    uint8   _edge_flag;			    // 1 byte,  [LAS].
    int8    _scan_angle_rank;	    // 1 byte,  [LAS].
    uint8   _classification;		// 1 byte,  [LAS].
};

}	// Namespace: las.

//------------------------------------------------------------------------------

namespace std
{

template<class CharT, class Traits>
basic_ostream<CharT,Traits>&
operator<<(basic_ostream<CharT,Traits> &os,
           const las::point            &rhs)
{
    os	<< fixed << setprecision(3)
        << "las::point[0x" << &rhs << "]:\n"
        << "sizeof(las::point)    : " << sizeof(las::point) << " [bytes]\n"
        << "[X,Y,Z]               : [" 
            << rhs.x() << ", " << rhs.y() << ", " << rhs.z() << "]\n"
        << "[R,G,B,I]             : [" 
            << static_cast<int>(rhs.r()) << ", " 
            << static_cast<int>(rhs.g()) << ", " 
            << static_cast<int>(rhs.b()) << ", "
            << rhs.intensity() << "]\n"
        << "GPS Time              : " << rhs.gps_time() << "\n"  
        << "Return Number         : " 
            << static_cast<int>(rhs.return_num()) 
            << " | " << static_cast<int>(rhs.num_returns()) << "\n"
        << "Edge Flag             : " 
            << static_cast<int>(rhs.edge_flag()) << "\n"
        << "Scan Direction Flag   : " 
            << static_cast<int>(rhs.scan_direction_flag()) << "\n"
        << "Scan Angle Rank       : " 
            << static_cast<int>(rhs.scan_angle_rank()) <<"\n"
        << "Classification        : " 
            << static_cast<int>(rhs.classification()) << "\n";
    return os;
}

}	// Namespace: std.

//------------------------------------------------------------------------------

#endif	// LAS_POINT_HPP_INCLUDED
