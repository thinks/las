//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef LAS_SCAN_POINT_HPP_INCLUDED
#define LAS_SCAN_POINT_HPP_INCLUDED

#include "salsa_exception.hpp"
#include <limits>
#include <iostream>

//------------------------------------------------------------------------------

namespace las {

//------------------------------------------------------------------------------

class scan_point
{
public:

    // Assume default values are all valid.
    //
    scan_point()
        : pos_				  (default_pos),
          gps_time_			  (default_gps_time),
          intensity_		  (default_intensity),
          num_returns_		  (default_num_returns),				
          return_num_		  (default_return_num),
          scan_direction_flag_(default_scan_direction_flag),
          edge_flag_		  (default_edge_flag),
          scan_angle_rank_	  (default_scan_angle_rank),
          classification_	  (default_classification),
          red_				  (default_red), 
          green_			  (default_green), 
          blue_				  (default_blue)
    {}

    explicit
    scan_point(const S x, const S y, const S z)
        : pos_				  (x, y, z),
          gps_time_			  (valid_gps_time(default_gps_time)),
          intensity_		  (default_intensity),
          num_returns_		  (valid_num_returns(default_num_returns)),				
          return_num_	(valid_return_num(default_return_num, num_returns_)),
          scan_direction_flag_(valid_scan_dir(default_scan_direction_flag)),
          edge_flag_		  (valid_edge_flag(default_edge_flag)),
          scan_angle_rank_	  (default_scan_angle_rank),
          classification_	  (default_classification),
          red_				  (default_red), 
          green_			  (default_green), 
          blue_				  (default_blue)
    {}

    explicit
    scan_point(const S           x, 
               const S           y, 
               const S           z, 
               const thx::uint16 i)
        : pos_				  (x, y, z),
          gps_time_			  (valid_gps_time(default_gps_time)),
          intensity_		  (i),
          num_returns_		  (valid_num_returns(default_num_returns)),				
          return_num_	(valid_return_num(default_return_num, num_returns_)),
          scan_direction_flag_(valid_scan_dir(default_scan_direction_flag)),
          edge_flag_		  (valid_edge_flag(default_edge_flag)),
          scan_angle_rank_	  (default_scan_angle_rank),
          classification_	  (default_classification),
          red_				  (default_red), 
          green_			  (default_green), 
          blue_				  (default_blue)
    {}

    explicit
    scan_point(const S	         x, 
               const S	         y, 
               const S	         z, 
               const thx::uint16 i,
               const thx::uint8  r, 
               const thx::uint8  g, 
               const thx::uint8  b)
        : pos_				  (x, y, z),
          gps_time_			  (valid_gps_time(default_gps_time)),
          intensity_		  (i),
          num_returns_		  (valid_num_returns(default_num_returns)),				
          return_num_	(valid_return_num(default_return_num, num_returns_)),
          scan_direction_flag_(valid_scan_dir(default_scan_direction_flag)),
          edge_flag_		  (valid_edge_flag(default_edge_flag)),
          scan_angle_rank_	  (default_scan_angle_rank),
          classification_	  (default_classification),
          red_				  (r), 
          green_			  (g), 
          blue_				  (b)
    {}

    explicit
    scan_point(const thx::vec<3,S>&	pos,
               const thx::float64	gps_time,
               const thx::uint16	i)
        : pos_				  (pos),
          gps_time_			  (valid_gps_time(gps_time)),
          intensity_		  (i),
          num_returns_		  (valid_num_returns(default_num_returns)),				
          return_num_	(valid_return_num(default_return_num, num_returns_)),
          scan_direction_flag_(valid_scan_dir(default_scan_direction_flag)),
          edge_flag_		  (valid_edge_flag(default_edge_flag)),
          scan_angle_rank_	  (default_scan_angle_rank),
          classification_	  (default_classification),
          red_				  (default_red), 
          green_			  (default_green), 
          blue_				  (default_blue)
    {}

    explicit
    scan_point(const thx::vec<3,S>&	pos,
               const thx::float64	gps_time,
               const thx::uint16	i,
               const thx::uint8		num_returns,
               const thx::uint8		return_num,
               const thx::uint8		scan_direction_flag,
               const thx::uint8		edge_flag,
               const thx::int8		scan_angle_rank,
               const thx::uint8		classification)
        : pos_				  (pos),
          gps_time_			  (valid_gps_time(gps_time)),
          intensity_		  (i),
          num_returns_		  (valid_num_returns(num_returns)),				
          return_num_		  (valid_return_num(return_num, num_returns_)),
          scan_direction_flag_(valid_scan_dir(scan_direction_flag)),
          edge_flag_		  (valid_edge_flag(edge_flag)),
          scan_angle_rank_	  (scan_angle_rank),
          classification_	  (classification),
          red_				  (default_red), 
          green_			  (default_green), 
          blue_				  (default_blue)
    {}

    explicit
    scan_point(const thx::vec<3,S>& scale,
               const thx::vec<3,S>& offset,
               const thx::vec3i32&  pos,
               const thx::float64	gps_time,
               const thx::uint16	i,
               const thx::uint8		num_returns,
               const thx::uint8		return_num,
               const thx::uint8		scan_direction_flag,
               const thx::uint8		edge_flag,
               const thx::int8		scan_angle_rank,
               const thx::uint8		classification)
        : pos_(scale.x*pos.x + offset.x, 
               scale.y*pos.y + offset.y, 
               scale.z*pos.z + offset.z),
          gps_time_			  (valid_gps_time(gps_time)),
          intensity_		  (i),
          num_returns_		  (valid_num_returns(num_returns)),				
          return_num_		  (valid_return_num(return_num, num_returns_)),
          scan_direction_flag_(valid_scan_dir(scan_direction_flag)),
          edge_flag_		  (valid_edge_flag(edge_flag)),
          scan_angle_rank_	  (scan_angle_rank),
          classification_	  (classification),
          red_				  (default_red), 
          green_			  (default_green), 
          blue_				  (default_blue)
    {}

    // Default copy & assign.

public:

    const thx::vec<3,S>& 
    pos() const 
    { return pos_; }

    double	
    gps_time() const 
    { return _gps_time; }

    unsigned short		
    intensity() const 
    { return _intensity; }


    unsigned char		
    num_returns() const 
    { return _num_returns; }
    
    unsigned char		
    return_num() const 
    { return _return_num; }
    
    unsigned char		
    scan_direction_flag() const 
    { return _scan_direction_flag; }
  
    unsigned char		
    edge_flag()	const 
    { return _edge_flag; }
    
    char		
    scan_angle_rank() const 
    { return _scan_angle_rank; }
    
    unsigned char		
    classification() const 
    { return _classification; }
    
    unsigned char		 
    r() const 
    { return _red; }

    unsigned char		
    g() const 
    { return _green; }
    
    unsigned char		
    b() const 
    { return _blue;	}

public:

    int   
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

    // Validation functions.
    //
    static double 
    _valid_gps_time(const double t)
    {
        static const double min_gps_time(0.0);
        static const double max_gps_time(
            static_cast<double>((std::numeric_limits<int>::max)());

        if(	t > _max_gps_time || t < _min_gps_time ) {
            LAS_THROW(
                "las::scan_point: invalid gps_time: " << t << " [min: " 
                    << min_gps_time << ", max: " << max_gps_time << "]");
        }

        return t;
    }

    static unsigned char
    _valid_num_returns(const unsigned char nr)
    {
        static const unsigned char min_num_returns(1);

        if( nr < min_num_returns ) {	
            LAS_THROW(
                "las::scan_point: invalid num_returns: " 
                    << static_cast<int>(nr) << " [min: "
                    << static_cast<int>(min_num_returns) << "]");
        }

        return nr;
    }

    static unsigned char
    _valid_return_num(const unsigned char rn, const unsigned char nr)
    {	
        static const unsigned char min_return_num(1);

        if( rn < min_return_num || rn > nr ) {	
            LAS_THROW(
                "las::scan_point: invalid return_num: " 
                    << static_cast<int>(rn) << " [min: " 
                    << static_cast<int>(min_return_num) 
                    << ", max: " << static_cast<int>(nr) << "]");
        }

        return rn;
    }

    static unsigned char
    _valid_scan_dir(const unsigned char scan_dir)
    {	
        static const unsigned char max_scan_dir(1);

        if( scan_dir > max_scan_dir ) {	
            LAS_THROW(
                "las::scan_point: invalid scan_dir: " 
                    << static_cast<int>(scan_dir) << " [max: "
                    << static_cast<int>(scan_point<S>::max_scan_dir) << "]");
        }

        return scan_dir;
    }

    static unsigned char
    _valid_edge_flag(const unsigned char edge)
    {
        static const unsigned char max_edge_flag(1);
        
        if( edge > max_edge_flag ) {	
            LAS_THROW(
                "scan_point: invalid edge_flag: " 
                    << static_cast<int>(edge) << " [max: "
                    << static_cast<int>(max_edge_flag) << "]");	
        }

        return edge;
    }

private:	// Member variables.

    thx::vec<3,S> pos_;					
    double         _gps_time;			    // 8 bytes, [LAS].
    unsigned short _intensity;			    // 2 bytes, [LAS].
    unsigned char  _num_returns;		    // 1 byte,  [LAS].
    unsigned char  _return_num;			    // 1 byte,  [LAS].
    unsigned char  _scan_direction_flag;    // 1 byte,  [LAS].
    unsigned char  _edge_flag;			    // 1 byte,  [LAS].
    char           _scan_angle_rank;	    // 1 byte,  [LAS].
    unsigned char  _classification;		    // 1 byte,  [LAS].
    unsigned char  _red;				    // 1 byte.
    unsigned char  _green;				    // 1 byte.
    unsigned char  _blue;				    // 1 byte.
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
           const las::io_buffer        &rhs)
{
    os	<< std::fixed << std::setprecision(3)
        << "las::scan_point<S>[0x" << &rhs << "]:\n"
        << "sizeof(las::scan_point) : " 
            << sizeof(las::scan_point) << " [bytes]\n";
        << "Pos                   : " << rhs.pos()		  << "\n"
        << "GPS Time <double>     : "  << rhs.gps_time()  
            << " | <int>: "           << rhs.gps_time_int()	  << "\n"
        << "Intensity             : " << rhs.intensity() << "\n"
        << "Return Number         : " 
            << static_cast<int>(rhs.return_num()) 
            << " | " << static_cast<int>(rhs.num_returns()) << "\n"
        << "Edge Flag             : {" 
            << static_cast<int>(rhs.edge_flag())	<< "}\n"
        << "Scan Direction Flag   : {" 
            << static_cast<int>(rhs.scan_direction_flag()) << "}\n"
        << "Scan Angle Rank       : " 
            << static_cast<int>(rhs.scan_angle_rank())	<<"\n"
        << "Classification        : " 
            << static_cast<int>(rhs.classification())	<< "\n"
        << "RGB                   : " 
            << "(" << rhs.r() << ", " << rhs.g() << ", " << rhs.b() << "\n"
            
    return os;
}

}	// Namespace: std.

#endif	// SALSA_SCAN_POINT_HPP_INCLUDED
