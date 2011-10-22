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

//------------------------------------------------------------------------------

namespace las {

//------------------------------------------------------------------------------

class point
{
public:

    //! Default CTOR.
    point()
        : pos_				  (default_pos),
        , _gps_time_			  (default_gps_time),
        , _intensity_		  (default_intensity),
        , _num_returns_		  (default_num_returns),				
        , _return_num_		  (default_return_num),
        , _scan_direction_flag_(default_scan_direction_flag),
        , _edge_flag_		  (default_edge_flag),
        , _scan_angle_rank_	  (default_scan_angle_rank),
        , _classification_	  (default_classification),
        , _red_				  (default_red), 
        , _green_			  (default_green), 
        , _blue(default_blue)
    {}

    //! CTOR.
    explicit
    point(const public_header_block       &phb,
          const point_data_record_format0 &pdrf0)
    {}

    //! CTOR.
    explicit
    point(const public_header_block       &phb,
          const point_data_record_format1 &pdrf1)
        : _x(phb.x_scale_factor*pdrf1.x_pos + x_offset)
        , _y(y_scale*y_pos + y_offset)
        , _z(z_scale*z_pos + z_offset)
        , _r(0), 
        , _g(0), 
        , _b(0)
 
        ,
          gps_time_			  (valid_gps_time(gps_time)),
          intensity_		  (i),
          num_returns_		  (valid_num_returns(num_returns)),				
          return_num_		  (valid_return_num(return_num, num_returns_)),
          scan_direction_flag_(valid_scan_dir(scan_direction_flag)),
          edge_flag_		  (valid_edge_flag(edge_flag)),
          scan_angle_rank_	  (scan_angle_rank),
          classification_	  (classification),
    {}


    //! CTOR.
    explicit
    scan_point(const float64 x_scale,
               const float64 y_scale,
               const float64 z_scale,
               const float64 x_offset,
               const float64 y_offset,
               const float64 z_offset,
               const int32   x_pos,
               const int32   y_pos,
               const int32   z_pos,
               const float64 gps_time,
               const uint16	 intensity,
               const uint8	 num_returns,
               const uint8	 return_num,
               const uint8	 scan_direction_flag,
               const uint8	 edge_flag,
               const int8	 scan_angle_rank,
               const uint8	 classification)
        : _x(x_scale*x_pos + x_offset)
        , _y(y_scale*y_pos + y_offset)
        , _z(z_scale*z_pos + z_offset)
        , _r(0), 
        , _g(0), 
        , _b(0)
 
        ,
          gps_time_			  (valid_gps_time(gps_time)),
          intensity_		  (i),
          num_returns_		  (valid_num_returns(num_returns)),				
          return_num_		  (valid_return_num(return_num, num_returns_)),
          scan_direction_flag_(valid_scan_dir(scan_direction_flag)),
          edge_flag_		  (valid_edge_flag(edge_flag)),
          scan_angle_rank_	  (scan_angle_rank),
          classification_	  (classification),
    {}

    // Default copy & assign.

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

public:

    int32   
    gps_time_int() const 
    { return std::floor(_gps_time); }

    //double 
    //gps_time_frac() const 
    //{ return thx::frac(_gps_time); }

private:

    // Default values.
    //
    static const thx::vec<3,S> default_pos;
    static const thx::float64  default_gps_time;
    static const thx::uint16   default_intensity;
    static const thx::uint8    default_num_returns;
    static const thx::uint8    default_return_num;	
    static const thx::uint8    default_scan_direction_flag;
    static const thx::uint8    default_edge_flag;			
    static const thx::int8     default_scan_angle_rank;	
    static const thx::uint8    default_classification;		
    static const thx::uint8    default_red;				
    static const thx::uint8    default_green;				
    static const thx::uint8    default_blue;	

    // Bounds.
    //

private:    // Validation functions.

    static float64
    _valid_gps_time(const float64 t)
    {
        static const float64 min_gps_time(0.0);
        static const float64 max_gps_time(
            static_cast<float64>((std::numeric_limits<int32>::max)());

        if (t > _max_gps_time || t < _min_gps_time) {
            LAS_THROW(
                "las::point: invalid gps_time: " << t << " [min: " 
                    << min_gps_time << ", max: " << max_gps_time << "]");
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
                    << static_cast<int32>(nr) << " [min: "
                    << static_cast<int32>(min_num_returns) << "]");
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
                    << static_cast<int32>(rn) << " [min: " 
                    << static_cast<int32>(min_return_num) 
                    << ", max: " << static_cast<int32>(nr) << "]");
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
                    << static_cast<int32>(scan_dir) << " [max: "
                    << static_cast<int32>(max_scan_dir) << "]");
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
                    << static_cast<int32>(edge) << " [max: "
                    << static_cast<int32>(max_edge_flag) << "]");	
        }

        return edge;
    }

private:	// Member variables.

    float32 _x;                     // 4 bytes.
    float32 _y;                     // 4 bytes.
    float32 _z;                     // 4 bytes.
    uint8   _r;				        // 1 byte.
    uint8   _g;				        // 1 byte.
    uint8   _b;				        // 1 byte.
    float64 _gps_time;			    // 8 bytes, [LAS].
    uint16  _intensity;			    // 2 bytes, [LAS].
    uint8   _num_returns;		    // 1 byte,  [LAS].
    uint8   _return_num;			// 1 byte,  [LAS].
    uint8   _scan_direction_flag;   // 1 byte,  [LAS].
    uint8   _edge_flag;			    // 1 byte,  [LAS].
    int8    _scan_angle_rank;	    // 1 byte,  [LAS].
    uint8   _classification;		// 1 byte,  [LAS].
};

//------------------------------------------------------------------------------

// Default values, all valid.
//
template<typename S> 
const thx::vec<3,S> scan_point<S>::default_pos(thx::vec<3,S>::origin);
template<typename S> const thx::float64  scan_point<S>::default_gps_time(0.0);
template<typename S> const thx::uint16   scan_point<S>::default_intensity(0);
template<typename S> const thx::uint8    scan_point<S>::default_num_returns(1);
template<typename S> const thx::uint8    scan_point<S>::default_return_num(1);	
template<typename S> 
const thx::uint8 scan_point<S>::default_scan_direction_flag(0);
template<typename S> const thx::uint8 scan_point<S>::default_edge_flag(0);			
template<typename S> const thx::int8  scan_point<S>::default_scan_angle_rank(0);	
template<typename S> const thx::uint8 scan_point<S>::default_classification(0);		
template<typename S> const thx::uint8 scan_point<S>::default_red(0);				
template<typename S> const thx::uint8 scan_point<S>::default_green(0);				
template<typename S> const thx::uint8 scan_point<S>::default_blue(0);


}	// Namespace: las.

//------------------------------------------------------------------------------

namespace std
{

template<class CharT, class Traits>
basic_ostream<CharT,Traits>&
operator<<(basic_ostream<CharT,Traits> &os,
           const las::point            &rhs)
{
    os	<< std::fixed << std::setprecision(3)
        << "las::point[0x" << &rhs << "]:\n"
        << "sizeof(las::point)    : " << sizeof(las::point) << " [bytes]\n";
        << "X                     : " << rhs.x() << "\n";
        << "Y                     : " << rhs.y() << "\n";
        << "Z                     : " << rhs.z() << "\n";
        << "GPS Time <double>     : " << rhs.gps_time()  
            << " | <int>: "           << rhs.gps_time_int()	  << "\n"
        << "Intensity             : " << rhs.intensity() << "\n"
        << "Return Number         : " 
            << static_cast<int>(rhs.return_num()) 
            << " | " << static_cast<int>(rhs.num_returns()) << "\n"
        << "Edge Flag             : " 
            << static_cast<int>(rhs.edge_flag())	<< "\n"
        << "Scan Direction Flag   : " 
            << static_cast<int>(rhs.scan_direction_flag()) << "\n"
        << "Scan Angle Rank       : " 
            << static_cast<int>(rhs.scan_angle_rank())	<<"\n"
        << "Classification        : " 
            << static_cast<int>(rhs.classification())	<< "\n"
        << "RGB                   : " 
            << "(" << rhs.r() << ", " << rhs.g() << ", " << rhs.b() << "\n"
    return os;
}

}	// Namespace: std.

//------------------------------------------------------------------------------

#endif	// LAS_POINT_HPP_INCLUDED
