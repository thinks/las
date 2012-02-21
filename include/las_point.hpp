//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef LAS_POINT_HPP_INCLUDED
#define LAS_POINT_HPP_INCLUDED

#include "las_namespace.hpp"
#include <iosfwd>
#include <iomanip>

//------------------------------------------------------------------------------

BEGIN_LAS_NAMESPACE

//! POD
struct point
{
    double          x;                // 8 bytes.
    double          y;                // 8 bytes.
    double          z;                // 8 bytes.
    unsigned char   r;                // 1 byte.
    unsigned char   g;                // 1 byte.
    unsigned char   b; 	              // 1 byte.
    double          gps_time;		  // 8 bytes, [LAS].
    unsigned short  intensity;		  // 2 bytes, [LAS].
    unsigned char   num_returns;	  // 1 byte,  [LAS].
    unsigned char   return_num;		  // 1 byte,  [LAS].
    unsigned char   scan_dir_flag;    // 1 byte,  [LAS].
    unsigned char   edge_flag;		  // 1 byte,  [LAS].
    char            scan_angle_rank;  // 1 byte,  [LAS].
    unsigned char   classification;	  // 1 byte,  [LAS].
};

END_LAS_NAMESPACE

//------------------------------------------------------------------------------

BEGIN_STD_NAMESPACE

//! DOCS
template<class CharT, class Traits>
basic_ostream<CharT,Traits>&
operator<<(basic_ostream<CharT,Traits> &os,
           const las::point            &rhs)
{
    os	<< fixed << setprecision(3)
        << "las::point[0x" << &rhs << "]:\n"
        << "sizeof(las::point)    : " << sizeof(las::point) << " [bytes]\n"
        << "[X,Y,Z]               : [" 
            << rhs.x << ", " << rhs.y << ", " << rhs.z << "]\n"
        << "[R,G,B,I]             : [" 
            << static_cast<int>(rhs.r) << ", " 
            << static_cast<int>(rhs.g) << ", " 
            << static_cast<int>(rhs.b) << ", "
            << rhs.intensity << "]\n"
        << "GPS Time              : " << rhs.gps_time << "\n"  
        << "Return Number         : " 
            << static_cast<int>(rhs.return_num) 
            << " | " << static_cast<int>(rhs.num_returns) << "\n"
        << "Edge Flag             : " 
            << static_cast<int>(rhs.edge_flag) << "\n"
        << "Scan Direction Flag   : " 
            << static_cast<int>(rhs.scan_dir_flag) << "\n"
        << "Scan Angle Rank       : " 
            << static_cast<int>(rhs.scan_angle_rank) <<"\n"
        << "Classification        : " 
            << static_cast<int>(rhs.classification) << "\n";
    return os;
}

END_STD_NAMESPACE

//------------------------------------------------------------------------------

#endif	// LAS_POINT_HPP_INCLUDED
