//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef LAS10_PUBLIC_HEADER_BLOCK_HPP_INCLUDED
#define LAS10_PUBLIC_HEADER_BLOCK_HPP_INCLUDED

#include "las10_namespace.hpp"
#include "las10_types.hpp"
#include "las10_point_data_record_format.hpp"
#include "las_namespace.hpp"
#include "las_pack.hpp"
#include "las_exception.hpp"
#include "las_static_assert.hpp"
#include <cstring>
#include <algorithm>
#include <iosfwd>

//------------------------------------------------------------------------------

BEGIN_LAS10_NAMESPACE

BEGIN_PACK_TIGHT

//! POD
struct public_header_block
{
    static const int32 file_signature_length	   = 4;
    static const int32 guid_data_4_length		   = 8;
    static const int32 sys_identifier_length	   = 32;
    static const int32 gen_software_length		   = 32;
    static const int32 num_points_by_return_length = 5;

    static const int32 size = 227;	// [bytes]

    //static uint16 
    //point_data_record_length(const uint8 id)
    //{
    //    switch (id) {
    //    case 0:
    //        return point_data_record_format0::length;
    //    case 1:
    //        return point_data_record_format1::length;
    //    default:
    //        LAS_THROW("las10::PHB: invalid PDRF id: " << 
    //                  static_cast<int32>(id));
    //    }
    //}

    // Data. Don't change the ordering!

    int8    file_signature[file_signature_length];  // 4 [bytes] 
    uint32  reserved;							    // 4 [bytes]
    uint32  guid_data_1;						    // 4 [bytes]
    uint16  guid_data_2;						    // 2 [bytes]
    uint16  guid_data_3;						    // 2 [bytes]
    uint8   guid_data_4[guid_data_4_length];	    // 8 [bytes] 
    uint8   version_major;						    // 1 [bytes]
    uint8   version_minor;						    // 1 [bytes]
    int8    sys_identifier[sys_identifier_length];  // 32 [bytes]
    int8    gen_software[gen_software_length];	    // 32 [bytes]
    uint16  flight_date_julian;				        // 2 [bytes]
    uint16  year;								    // 2 [bytes]
    uint16  header_size;						    // 2 [bytes]
    uint32  offset_to_data;					        // 4 [bytes]
    uint32  num_variable_length_records;		    // 4 [bytes]
    uint8   point_data_format_id;				    // 1 [bytes]
    uint16  point_data_record_length;			    // 2 [bytes]
    uint32  num_point_records;					    // 4 [bytes]
    uint32  num_points_by_return[num_points_by_return_length]; // 20 [bytes]
    float64 x_scale_factor;					        // 8 [bytes]
    float64 y_scale_factor;					        // 8 [bytes]
    float64 z_scale_factor;					        // 8 [bytes]
    float64 x_offset;							    // 8 [bytes]
    float64 y_offset;							    // 8 [bytes]
    float64 z_offset;							    // 8 [bytes]
    float64 max_x;								    // 8 [bytes]
    float64 min_x;								    // 8 [bytes]
    float64 max_y;								    // 8 [bytes]
    float64 min_y;								    // 8 [bytes]
    float64 max_z;								    // 8 [bytes]
    float64 min_z;								    // 8 [bytes]
};

END_PACK_TIGHT

END_LAS10_NAMESPACE

//------------------------------------------------------------------------------

BEGIN_STD_NAMESPACE

//------------------------------------------------------------------------------

template<class CharT, class Traits>
basic_ostream<CharT,Traits>&
operator<<(basic_ostream<CharT,Traits>      &os, 
           const las10::public_header_block &rhs)
{
    typedef las10::public_header_block phb_type;
    os	<< "las10::public_header_block[0x" << &rhs << "]\n"
        << "sizeof(las10::public_header_block)  : " << sizeof(phb_type) << "\n"
        << "File Signature ('LASF')           : '" 
            << string(rhs.file_signature, phb_type::file_signature_length) 
            << "'\n"
        << "Reserved                          : " 
            << static_cast<int>(rhs.reserved) << "\n"
        << "GUID data 1                       : " 
            << static_cast<int>(rhs.guid_data_1) << "\n"
        << "GUID data 2                       : " 
            << static_cast<int>(rhs.guid_data_2) << "\n"
        << "GUID data 3                       : " 
            << static_cast<int>(rhs.guid_data_3) << "\n";
    os  << "GUID data 4                       : '";
    for (int i = 0; i < phb_type::guid_data_4_length; ++i) {
        os << static_cast<int>(rhs.guid_data_4[i]);
    }
    os	<< "'\n"
    os  << "Version Major                     : " 
            << static_cast<int>(rhs.version_major) << "\n"
        << "Version Minor                     : " 
            << static_cast<int>(rhs.version_minor) << "\n"
        << "System Identifier                 : '" 
            << string(rhs.sys_identifier, phb_type::sys_identifier_length) 
            << "'\n"
        << "Generating Software               : '" 
            << string(rhs.gen_software, phb_type::gen_sotware_length) << "'\n"
        << "Flight Date Julian                : " 
            << rhs.flight_date_julian << "\n"
        << "Year                              : " 
            << rhs.year << "\n"
        << "Header Size                       : " 
            << rhs.header_size << " [bytes]\n"
        << "Offset to Data                    : " 
            << rhs.offset_to_data /*<< " | " << rhs.size_on_disk()*/ 
            << " [bytes]\n"
        << "Number of Variable Length Records : " 
            << rhs.num_variable_length_records << "\n"
        << "Point Data Format ID              : " 
            << static_cast<int>(rhs.point_data_format_id) << "\n"
        << "Point Data Record Length          : " 
            << rhs.point_data_record_length << "\n"
        << "Number of Point Records           : " 
            << rhs.num_point_records << "\n"
        << "Number of Points by Return:\n";
    for (int i = 0; i < phb_type::num_points_by_return_length; ++i) {
        os	<< "Return[" << i + 1 << "]                         : "
                << rhs.num_points_by_return[i] << "\n";
    }
    os	<< "X Scale Factor                    : " << rhs.x_scale_factor <<"\n"
        << "Y Scale Factor                    : " << rhs.y_scale_factor <<"\n"
        << "Z Scale Factor                    : " << rhs.z_scale_factor <<"\n"
        << "X Offset                          : " << rhs.x_offset << "\n"
        << "Y Offset                          : " << rhs.y_offset << "\n"
        << "Z Offset                          : " << rhs.z_offset << "\n"
        << "Max X                             : " << rhs.max_x << "\n"
        << "Min X                             : " << rhs.min_x << "\n"
        << "Max Y                             : " << rhs.max_y << "\n"
        << "Min Y                             : " << rhs.min_y << "\n"
        << "Max Z                             : " << rhs.max_z << "\n"
        << "Min Z                             : " << rhs.min_z << "\n";
    return os;
}

END_STD_NAMESPACE

//------------------------------------------------------------------------------

#endif	// LAS10_PUBLIC_HEADER_BLOCK_HPP_INCLUDED








//class public_header_block
//{
//public:
//        
//    static const int32 file_signature_length	   = 4;
//    static const int32 guid_data_4_length		   = 8;
//    static const int32 sys_identifier_length	   = 32;
//    static const int32 gen_software_length		   = 32;
//    static const int32 num_points_by_return_length = 5;
//
//    static const int32 size = 227;	// [bytes]
//
//    static uint16 
//    point_data_record_length(const uint8 id)
//    {
//        switch (id) {
//        case 0:
//            return point_data_record_format0::length;
//        case 1:
//            return point_data_record_format1::length;
//        default:
//            LAS_THROW("las::PHB: invalid PDRF id: " << static_cast<int32>(id));
//        }
//    }
//
//public:
//
//    //! Empty CTOR.
//    public_header_block()
//        : _reserved(0)
//        , _guid_data_1(0) 
//        , _guid_data_2(0) 
//        , _guid_data_3(0)
//        , _version_major(1)				// NB: Always 1
//        , _version_minor(0)				// NB: Always 0
//        , _flight_date_julian(1)		// NB: 1st Jan.
//        , _year(0)						// NB: Default values.
//        , _header_size(static_cast<uint16>(size))
//        , _offset_to_data(static_cast<uint16>(size + sizeof(uint16)))	
//        , _num_variable_length_records(0)
//        , _point_data_format_id(0) 
//        , _point_data_record_length(	// NB: Only ID supplied.
//                static_cast<uint16>(
//                    point_data_record_length(_point_data_format_id)))	
//        , _num_point_records(0)
//        , _x_scale_factor(1.0) 
//        , _y_scale_factor(1.0) 
//        , _z_scale_factor(1.0)
//        , _x_offset(0.0) 
//        , _y_offset(0.0) 
//        , _z_offset(0.0)
//        , _max_x(1.0) 
//        , _min_x(0.0)
//        , _max_y(1.0) 
//        , _min_y(0.0)
//        , _max_z(1.0)
//        , _min_z(0.0)
//    {	
//        _file_signature[0] = 'L';
//        _file_signature[1] = 'A';
//        _file_signature[2] = 'S';
//        _file_signature[3] = 'F';
//            
//        // Fill arrays with zeros.
//            
//        std::memset(_guid_data_4, 0, guid_data_4_length*sizeof(int8));
//        std::memset(_sys_identifier, 0, sys_identifier_length*sizeof(int8));
//        std::memset(_gen_software, 0, gen_software_length*sizeof(int8));
//        std::memset(_num_points_by_return, 
//                    0, 
//                    num_points_by_return_length*sizeof(int32));
//    }
//
//    //! Copy CTOR.
//    public_header_block(const public_header_block &rhs) 
//    { *this = rhs; }
//
//
//    //! Assign.
//    public_header_block& 
//    operator=(const public_header_block &rhs)
//    {
//        std::memcpy(this, &rhs, size); // Bit-wise copy.
//        //std::copy(&rhs, &rhs + size, this); // Bit-wise copy.
//        return *this;
//    }
//
//    //! DTOR.
//    ~public_header_block() 
//    { 
//        LAS_STATIC_ASSERT(1 == sizeof(int8),    invalid_int8_size);
//        LAS_STATIC_ASSERT(1 == sizeof(uint8),   invalid_uint8_size);
//        LAS_STATIC_ASSERT(2 == sizeof(int16),   invalid_int16_size);
//        LAS_STATIC_ASSERT(2 == sizeof(uint16),  invalid_uint16_size);
//        LAS_STATIC_ASSERT(4 == sizeof(int32),   invalid_int32_size);
//        LAS_STATIC_ASSERT(4 == sizeof(uint32),  invalid_uint32_size);
//        LAS_STATIC_ASSERT(8 == sizeof(float64), invalid_float64_size);
//        LAS_STATIC_ASSERT(size == sizeof(public_header_block), 
//                          invalid_phb_size); 
//    }
//
//public:
//
//    const int8*  
//    file_signature() const 
//    { return _file_signature; }
//
//    uint32       
//    reserved() const 
//    { return _reserved; }
//
//    uint32		  
//    guid_data_1() const 
//    { return _guid_data_1; }
//
//    uint16		  
//    guid_data_2() const 
//    { return _guid_data_2; }
//
//    uint16		  
//    guid_data_3() const 
//    { return _guid_data_3; }
//
//    const uint8* 
//    guid_data_4() const 
//    { return _guid_data_4; }
//
//    uint8		  
//    version_major() const 
//    { return _version_major;  }
//
//    uint8		  
//    version_minor() const 
//    { return _version_minor; }
//
//    const int8*  
//    sys_identifier() const 
//    { return _sys_identifier; }
//    
//    const int8*  
//    gen_software() const 
//    { return _gen_software; }
//
//    uint16
//    flight_date_julian() const 
//    { return _flight_date_julian; }
//
//    uint16       
//    year() const 
//    { return _year; }
//
//    uint16       
//    header_size() const 
//    { return _header_size; }
//
//    uint32       
//    offset_to_data() const 
//    { return _offset_to_data; }
//
//    float64	  
//    x_scale_factor() const 
//    { return _x_scale_factor; }
//
//    float64  
//    y_scale_factor() const 
//    { return _y_scale_factor; }
//
//    float64	  
//    z_scale_factor() const 
//    { return _z_scale_factor; }
//    
//    float64	  
//    x_offset() const 
//    { return _x_offset;	}
//
//    float64	  
//    y_offset() const 
//    { return _y_offset; }
//
//    float64	  
//    z_offset() const 
//    { return _z_offset;	}
//    
//    float64	  
//    max_x()	const 
//    { return _max_x; }
//
//    float64	  
//    min_x()	const 
//    { return _min_x; }
//
//    float64	  
//    max_y() const 
//    { return _max_y; }
//
//    float64	  
//    min_y() const 
//    { return _min_y; }
//
//    float64	  
//    max_z() const 
//    { return _max_z; }
//
//    float64	  
//    min_z()	const 
//    { return _min_z; }
//
//    uint32
//    num_variable_length_records() const 
//    { return _num_variable_length_records; }
//    
//    uint8 
//    point_data_format_id() const 
//    { return _point_data_format_id; }
//    
//    uint16 
//    point_data_record_length() const 
//    { return _point_data_record_length; }
//    
//    uint32 
//    num_point_records() const 
//    { return _num_point_records; }
//    
//    const uint32* 
//    num_points_by_return() const 
//    { return _num_points_by_return; }
//
//private:    // Member variables. Don't change order!
//
//    int8    _file_signature[file_signature_length]; // 4 [bytes] 
//    uint32  _reserved;							    // 4 [bytes]
//    uint32  _guid_data_1;						    // 4 [bytes]
//    uint16  _guid_data_2;						    // 2 [bytes]
//    uint16  _guid_data_3;						    // 2 [bytes]
//    uint8   _guid_data_4[guid_data_4_length];	    // 8 [bytes] 
//    uint8   _version_major;						    // 1 [bytes]
//    uint8   _version_minor;						    // 1 [bytes]
//    int8    _sys_identifier[sys_identifier_length]; // 32 [bytes]
//    int8    _gen_software[gen_software_length];	    // 32 [bytes]
//    uint16  _flight_date_julian;				    // 2 [bytes]
//    uint16  _year;								    // 2 [bytes]
//    uint16  _header_size;						    // 2 [bytes]
//    uint32  _offset_to_data;					    // 4 [bytes]
//    uint32  _num_variable_length_records;		    // 4 [bytes]
//    uint8   _point_data_format_id;				    // 1 [bytes]
//    uint16  _point_data_record_length;			    // 2 [bytes]
//    uint32  _num_point_records;					    // 4 [bytes]
//    uint32  _num_points_by_return[num_points_by_return_length]; // 20 [bytes]
//    float64 _x_scale_factor;					    // 8 [bytes]
//    float64 _y_scale_factor;					    // 8 [bytes]
//    float64 _z_scale_factor;					    // 8 [bytes]
//    float64 _x_offset;							    // 8 [bytes]
//    float64 _y_offset;							    // 8 [bytes]
//    float64 _z_offset;							    // 8 [bytes]
//    float64 _max_x;								    // 8 [bytes]
//    float64 _min_x;								    // 8 [bytes]
//    float64 _max_y;								    // 8 [bytes]
//    float64 _min_y;								    // 8 [bytes]
//    float64 _max_z;								    // 8 [bytes]
//    float64 _min_z;								    // 8 [bytes]
//};










//const int vlr_size(static_cast<int>(rhs.vlr_vec().size()));
//for(int i = 0; i < vlr_size; ++i)
//{
//	os	<< "VLR[" << i << "]::Record Signature: " 
//			<< rhs.vlr_vec()[i].record_signature() 
//			<< std::hex << " | 0x" 
//			<< rhs.vlr_vec()[i].record_signature() << std::dec << "\n"
//		<< "VLR[" << i << "]::User ID: '" 
//			<< std::string(rhs.vlr_vec()[i].user_id()) << "'\n"
//		<< "VLR[" << i << "]::Record ID: " 
//			<< rhs.vlr_vec()[i].record_id() << "\n"
//		<< "VLR[" << i << "]::Record Length After Header: " 
//			<< rhs.vlr_vec()[i].record_length_after_header() << " | " 
//			<< rhs.vlr_vec()[i].size_on_disk() << " [bytes]\n"
//		<< "VLR[" << i << "]::Description: '" 
//			<< std::string(rhs.vlr_vec()[i].description()) << "'\n"
//		<< "VLR[" << i << "]::Data: '";
//	const int data_size(static_cast<int>(rhs.vlr_vec()[i].data().size()));
//	for(int j = 0; j < data_size; ++j)
//	{
//		os << rhs.vlr_vec()[i].data()[j]; 
//	}
//	os << "' [" << rhs.vlr_vec()[i].data().size() << " bytes]\n";
//}

//os	<< "Pre-point value                   : " << rhs.pre_point_data() 
//        << std::hex << " | 0x" << rhs.pre_point_data() << std::dec << "\n";


//static const unsigned short valid_pre_point_value = 52445;// 0xCCDD = 52445.



// TODO!
//las_public_header_block(const std::vector<scan_point>& sp_vec);

// Default copy & assign.


//std::size_t
//size_on_disk() const 
//{ return static_cast<std::size_t>(header::size + sizeof(unsigned short)); }

//thx::uint16 
//pre_point_data() const { return pre_point_data_; }

//};



//class variable_length_record
//{
//public:
//
//	static const int record_signature_value = 43707; // Always 0xAABB
//	static const int user_id_length = 16;
//	static const int description_length = 32;
//
//private:
//
////#pragma pack(push)
////#pragma pack(1)	
//
//	class vlr_header
//	{
//	public:
//
//	static const int size = 54;		// [bytes]
//
//	public:
//
//	vlr_header()
//		: record_signature(record_signature_value),
//		  record_id(0),
//		  record_length_after_header(vlr_header::size)
//	{	// Fill arrays with zeros.
//		//
//		memset(user_id, 
//			   0, 
//			   user_id_length*sizeof(char));
//		memset(description, 
//			   0, 
//			   description_length*sizeof(char));
//	}
//
//	vlr_header(const vlr_header& rhs) { *this = rhs; }
//
//	vlr_header& 
//	operator=(const vlr_header& rhs)
//	{	// Bit-wise copy.
//		//
//		memcpy(this, &rhs, vlr_header::size);
//		return *this;
//	}
//
//	public:
//
//	unsigned short record_signature;			// 2 bytes, required.
//	char user_id[user_id_length];				// 16 bytes, required.
//	unsigned short record_id;					// 2 bytes, required.
//	unsigned short record_length_after_header;	// 2 bytes, required.
//	char description[description_length];		// 32 bytes.
//	};
//
////#pragma pack(pop)
//
////=========================================================================
//
//public:
//
//	variable_length_record() {}
//	~variable_length_record() throw() {}
//
//	// Default copy & assign.
//
//	void read(std::ifstream& ifs, bool last);
//	void write(std::ofstream& ofs) const;
//	unsigned int size_on_disk() const;
//
//
//	unsigned short record_signature() const 
//	{ return hdr_.record_signature; }
//
//	unsigned short record_length_after_header() const 
//	{ return hdr_.record_length_after_header; }
//
//	const char* user_id() const		 { return hdr_.user_id; }
//	unsigned short record_id() const { return hdr_.record_id; }
//	const char* description() const  { return hdr_.description; }
//
//	const std::vector<char>& data() const { return data_; }
//
//private:
//
//	vlr_header hdr_;
//	std::vector<char> data_;
//};





//void 
//read(std::ifstream& ifs)
//{	// Convenient types.
//    //
//    typedef las_public_header_block phb_type;
//
//    // Read header from disk.
//    //
//    ifs.read(reinterpret_cast<char*>(&hdr_), header::size);
//
//    // Error checking.
//    //
//    // Signature.
//    //
//    if( hdr_.file_signature[0] != 'L' ||
//        hdr_.file_signature[1] != 'A' ||
//        hdr_.file_signature[2] != 'S' ||
//        hdr_.file_signature[3] != 'F' )
//    { 
//        SALSA_THROW(
//            "LAS PHB Error: Invalid signature: '" 
//                << hdr_.file_signature[0] 
//                << hdr_.file_signature[1] 
//                << hdr_.file_signature[2] 
//                << hdr_.file_signature[3] << "'");
//    }
//
//    // Point count.
//    //
//    unsigned long num_pts(0);
//    for(int i = 0; i < phb_type::num_points_by_return_length; ++i)
//    {	// Sum points by return.
//        //
//        num_pts += hdr_.num_points_by_return[i];
//    }
//
//    if( hdr_.num_point_records != num_pts ) 
//    { 
//        SALSA_THROW(
//            "LAS PHB Error: Invalid point count: " 
//                << hdr_.num_point_records);
//    }
//
//    // Bounds, min == max is OK.
//    //
//    if( hdr_.min_x > hdr_.max_x || 
//        hdr_.min_y > hdr_.max_y || 
//        hdr_.min_z > hdr_.max_z )
//    {
//        SALSA_THROW(
//            "LAS PHB Error: invalid bounds:\n"
//                << "[" << hdr_.min_x << ", " <<  hdr_.max_x << "]\n"
//                << "[" << hdr_.min_y << ", " <<  hdr_.max_y << "]\n"
//                << "[" << hdr_.min_z << ", " <<  hdr_.max_z << "]\n");
//    }
//
//    if( hdr_.offset_to_data < hdr_.header_size + sizeof(unsigned short) ) 
//    {
//        SALSA_THROW(
//            "LAS PHB Error: invalid offset: " << hdr_.offset_to_data);
//    }
//
//    // Null-terminate "strings".
//    //
//    hdr_.sys_identifier[phb_type::sys_identifier_length - 1] = '\0';
//    hdr_.gen_software  [phb_type::gen_software_length   - 1] = '\0';
//
//    // Ignore VLR's. Read VLR data out of the way.
//    //
//    hdr_.num_variable_length_records = 0;
//    const int vlr_size(
//        hdr_.offset_to_data - hdr_.header_size - sizeof(thx::uint16));
//    if( 0 < vlr_size )
//    {
//        std::vector<char> vlr_data(vlr_size);	// Garbage.
//        ifs.read(&vlr_data[0], static_cast<std::streamsize>(vlr_data.size()));
//    }
//
//    // Get it out of the way so that we can start reading points
//    // after reading the header.
//    //
//    pre_point_data_ = phb_type::pre_point_value - 1;	// Invalidate.
//    ifs.read(reinterpret_cast<char*>(&pre_point_data_), 
//                sizeof(thx::uint16));	// 2 bytes
//
//    if( pre_point_data_ != phb_type::pre_point_value )
//    {	// Check validity.
//        //
//        SALSA_THROW("LAS PHB Error: invalid pre-point value");
//    }
//}
//
//void 
//write(std::ofstream& ofs) const
//{	// Write header.
//    //
//    ofs.write(reinterpret_cast<const char*>(&hdr_), header::size);
//
//    // NB: Always write correct pre_point value.
//    //
//    ofs.write(
//        reinterpret_cast<const char*>(
//            &las_public_header_block::pre_point_value), 
//        sizeof(thx::uint16));	// 2 bytes
//
//}
