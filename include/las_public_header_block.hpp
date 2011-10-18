//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef LAS_PUBLIC_HEADER_BLOCK_HPP_INCLUDED
#define LAS_PUBLIC_HEADER_BLOCK_HPP_INCLUDED

//#include "salsa_static_assert.hpp"
#include <iosfwd>

//------------------------------------------------------------------------------

namespace las {

//------------------------------------------------------------------------------

class public_header_block
{
public:
    
    // Easier access than from phb_header.
    //
    static const thx::int64 file_signature_length		= 4;
    static const thx::int64 guid_data_4_length			= 8;
    static const thx::int64 sys_identifier_length		= 32;
    static const thx::int64 gen_software_length			= 32;
    static const thx::int64 num_points_by_return_length = 5;

    static int 
    point_data_record_length(const int id)
    {
        switch (id) {
        case 0:
            return 20;
        case 1:
            return 28;
        default:
            SALSA_THROW("las::PHB: invalid PDRF id: " << static_cast<int>(id));
        }
    }

private:    // Header.

#ifdef WIN32
#pragma pack(push)
#pragma pack(1)		// Alignment 1 byte
#endif // WIN32

    class _header
    {
    public:

        static const int size = 227;	// [bytes]

    public:

        _header()
            : reserved     (0),
              guid_data_1  (0), 
              guid_data_2  (0), 
              guid_data_3  (0),
              version_major(1),				// NB: Always 1
              version_minor(0),				// NB: Always 0
              flight_date_julian(1),		// NB: 1st Jan.
              year(0),						// NB: Default values.
              header_size(static_cast<unsigned short>(size)),
              offset_to_data(
                  static_cast<unsigned short>(size + sizeof(unsigned short))),	
              num_variable_length_records(0),
              point_data_format_id(0), 
              point_data_record_length(	// NB: Only ID supplied.
                  static_cast<unsigned short>(
                      point_data_record_length(point_data_format_id))),	
              num_point_records(0),
              x_scale_factor   (1.0), 
              y_scale_factor   (1.0), 
              z_scale_factor   (1.0),
              x_offset		   (0.0), 
              y_offset		   (0.0), 
              z_offset		   (0.0),
              max_x			   (0.0), 
              min_x			   (0.0),
              max_y			   (0.0), 
              min_y			   (0.0),
              max_z			   (0.0), 
              min_z			   (0.0)
        {	
            file_signature[0] = 'L';
            file_signature[1] = 'A';
            file_signature[2] = 'S';
            file_signature[3] = 'F';
            
            // Fill arrays with zeros.
            //
            memset(guid_data_4   , 0, guid_data_4_length*sizeof(unsigned char));
            memset(sys_identifier, 0, sys_identifier_length*sizeof(unsigned char));
            memset(gen_software  , 0, gen_software_length*sizeof(unsigned char));
            memset(num_points_by_return, 0, 
                   num_points_by_return_length*sizeof(int));
        }

        //! Copy CTOR.
        _header(const _header &rhs) 
        { 
            *this = rhs; 
        }

        //! DTOR.
        ~_header() 
        { 
            //SALSA_STATIC_ASSERT(size == sizeof(header), invalid_size); 
        }

        header& 
        operator=(const header& rhs)
        {	// Bit-wise copy.
            //
            memcpy(this, &rhs, size);
            return *this;
        }

    public:		// The data is the interface!

        thx::int8    file_signature[file_signature_length];  
        thx::uint32  reserved;							  
        thx::uint32  guid_data_1;						  
        thx::uint16  guid_data_2;						  
        thx::uint16  guid_data_3;						  
        thx::uint8   guid_data_4[guid_data_4_length];	  
        thx::uint8   version_major;						  
        thx::uint8   version_minor;						  
        thx::int8    sys_identifier[sys_identifier_length];
        thx::int8    gen_software[gen_software_length];	
        thx::uint16  flight_date_julian;				 
        thx::uint16  year;								 
        thx::uint16  header_size;						 
        thx::uint32  offset_to_data;					  
        thx::uint32  num_variable_length_records;		  
        thx::uint8   point_data_format_id;				  
        thx::uint16  point_data_record_length;			  
        thx::uint32  num_point_records;					  
        thx::uint32  num_points_by_return[num_points_by_return_length];
        thx::float64 x_scale_factor;					  
        thx::float64 y_scale_factor;					  
        thx::float64 z_scale_factor;					  
        thx::float64 x_offset;							  
        thx::float64 y_offset;							  
        thx::float64 z_offset;							  
        thx::float64 max_x;								  
        thx::float64 min_x;								  
        thx::float64 max_y;								  
        thx::float64 min_y;								  
        thx::float64 max_z;								  
        thx::float64 min_z;								  
    };

#ifdef WIN32
#pragma pack(pop)	// pack(1)
#endif  // WIN32

public:

    static const unsigned short valid_pre_point_value = 52445;// 0xCCDD = 52445.

public:

    //! CTOR.
    public_header_block()
        : _hdr()
        , _pre_point_data(pre_point_value)
    {}

    explicit
    public_header_block(const _header &hdr)
        : hdr_(hdr),
          pre_point_data_(las_public_header_block::pre_point_value)
    {}

    explicit
    public_header_block(const std::string&              sys_id,
                        const std::string&              gen_sw,
                        const thx::uint8                pd_format,
                        const thx::uint32               num_points,
                        const std::vector<thx::uint32>& num_points_n,
                        const thx::float64              scale_x,
                        const thx::float64              scale_y,
                        const thx::float64              scale_z,
                        const thx::float64              offset_x,
                        const thx::float64              offset_y,
                        const thx::float64              offset_z,
                        const thx::float64              max_x,
                        const thx::float64              min_x,
                        const thx::float64              max_y,
                        const thx::float64              min_y,
                        const thx::float64              max_z,
                        const thx::float64              min_z)
        : hdr_(),
          pre_point_data_(las_public_header_block::pre_point_value)
    {
        memcpy(hdr_.sys_identifier, 
               &sys_id[0], 
               std::min<std::size_t>(sys_identifier_length, sys_id.size()));
        hdr_.sys_identifier[sys_identifier_length - 1] = '\0';

        memcpy(hdr_.gen_software,
               &gen_sw[0], 
               std::min<std::size_t>(gen_software_length, gen_sw.size()));
        hdr_.gen_software[gen_software_length - 1] = '\0';

        hdr_.point_data_format_id = pd_format;
        hdr_.point_data_record_length 
            = static_cast<thx::uint16>(point_data_record_lengths(pd_format));

        hdr_.num_point_records = num_points;
        for(size_t n(0); n < num_points_n.size(); ++n)
        {
            if( n < 5 )
            {
                hdr_.num_points_by_return[n] = num_points_n[n];
            }
        }

        hdr_.x_scale_factor = scale_x;
        hdr_.y_scale_factor = scale_y;
        hdr_.z_scale_factor = scale_z;
        hdr_.x_offset = offset_x;
        hdr_.y_offset = offset_y;
        hdr_.z_offset = offset_z;
        hdr_.max_x = max_x;
        hdr_.min_x = min_x;
        hdr_.max_y = max_y;
        hdr_.min_y = min_y;
        hdr_.max_z = max_z;
        hdr_.min_z = min_z;
    }


    // TODO!
    //las_public_header_block(const std::vector<scan_point>& sp_vec);

    // Default copy & assign.


    thx::int64 
    size_on_disk() const 
    { 
        return static_cast<thx::int64>(header::size + sizeof(thx::uint16)); 
    }

    thx::uint16 pre_point_data() const { return pre_point_data_; }

    const thx::int8*  file_signature() const { return hdr_.file_signature; }
    thx::uint32       reserved()       const { return hdr_.reserved;	   }
    thx::uint32		  guid_data_1()    const { return hdr_.guid_data_1;    }
    thx::uint16		  guid_data_2()    const { return hdr_.guid_data_2;    }
    thx::uint16		  guid_data_3()    const { return hdr_.guid_data_3;    }
    const thx::uint8* guid_data_4()    const { return hdr_.guid_data_4;	   }
    thx::uint8		  version_major()  const { return hdr_.version_major;  }
    thx::uint8		  version_minor()  const { return hdr_.version_minor;  }
    const thx::int8*  sys_identifier() const { return hdr_.sys_identifier; }
    const thx::int8*  gen_software()   const { return hdr_.gen_software;   }
    thx::uint16       year()		   const { return hdr_.year;		   }
    thx::uint16       header_size()    const { return hdr_.header_size;    }
    thx::uint32       offset_to_data() const { return hdr_.offset_to_data; }
    thx::float64	  x_scale_factor() const { return hdr_.x_scale_factor; }
    thx::float64	  y_scale_factor() const { return hdr_.y_scale_factor; }
    thx::float64	  z_scale_factor() const { return hdr_.z_scale_factor; }
    thx::float64	  x_offset()       const { return hdr_.x_offset;	   }
    thx::float64	  y_offset()	   const { return hdr_.y_offset;	   }
    thx::float64	  z_offset()	   const { return hdr_.z_offset;	   }
    thx::float64	  max_x()		   const { return hdr_.max_x;		   }
    thx::float64	  min_x()		   const { return hdr_.min_x;		   }
    thx::float64	  max_y()		   const { return hdr_.max_y;		   }
    thx::float64	  min_y()		   const { return hdr_.min_y;		   }
    thx::float64	  max_z()		   const { return hdr_.max_z;		   }
    thx::float64	  min_z()		   const { return hdr_.min_z;		   }



    thx::uint16 flight_date_julian() const { return hdr_.flight_date_julian; }
    
    thx::uint32 num_variable_length_records() const 
    { return hdr_.num_variable_length_records; }
    
    thx::uint8 point_data_format_id() const 
    { return hdr_.point_data_format_id; }
    
    thx::uint16 point_data_record_length() const 
    { return hdr_.point_data_record_length; }
    
    thx::uint32 num_point_records() const 
    { return hdr_.num_point_records; }
    
    const thx::uint32* num_points_by_return() const 
    { return hdr_.num_points_by_return; }
    
private:	// Member variables.

    header hdr_;
    thx::uint16 pre_point_data_;
};

//------------------------------------------------------------------------------

}	// Namespace: las.

//------------------------------------------------------------------------------

namespace std
{

template<class CharT, class Traits>
basic_ostream<CharT,Traits>&
operator<<(basic_ostream<CharT,Traits>    &os, 
           const las::public_header_block &rhs)
{
    os	<< "las::public_header_block[0x" << &rhs << "]:\n"
        << "File Signature ('LASF')           : '" 
        << std::string(rhs.file_signature()) << "'\n"
        << "Reserved                          : " 
            << static_cast<int>(rhs.reserved()) << "\n"
        << "GUID data 1                       : " 
            << static_cast<int>(rhs.guid_data_1()) << "\n"
        << "GUID data 2                       : " 
            << static_cast<int>(rhs.guid_data_2()) << "\n"
        << "GUID data 3                       : " 
            << static_cast<int>(rhs.guid_data_3()) << "\n"

        << "GUID data 4                       : '";
    for(thx::int64 i = 0; 
        i < salsa::las_public_header_block::guid_data_4_length; 
        ++i)
    {
        os << static_cast<thx::int64>(rhs.guid_data_4()[i]);
    }
    os	<< "'\n"

        << "Version Major                     : " 
            << static_cast<thx::int64>(rhs.version_major()) << "\n"
        << "Version Minor                     : " 
            << static_cast<thx::int64>(rhs.version_minor()) << "\n"
        << "System Identifier                 : '" 
            << std::string(rhs.sys_identifier()) << "'\n"
        << "Generating Software               : '" 
            << std::string(rhs.gen_software()) << "'\n"
        << "Flight Date Julian                : " 
            << rhs.flight_date_julian() << "\n"
        << "Year                              : " 
            << rhs.year() << "\n"
        << "Header Size                       : " 
            << rhs.header_size() << " [bytes]\n"
        << "Offset to Data                    : " 
            << rhs.offset_to_data() << " | " << rhs.size_on_disk() 
            << " [bytes]\n"
        << "Number of Variable Length Records : " 
            << rhs.num_variable_length_records() << "\n"
        << "Point Data Format ID              : " 
            << static_cast<thx::int64>(rhs.point_data_format_id()) << "\n"
        << "Point Data Record Length          : " 
            << rhs.point_data_record_length() << "\n"
        << "Number of Point Records           : " 
            << rhs.num_point_records() << "\n"
        << "Number of Points by Return        :\n";

    for(thx::int64 i = 0; 
        i < salsa::las_public_header_block::num_points_by_return_length; 
        ++i )
    {
        os	<< "Return[" << i + 1 << "]                         : "
                << rhs.num_points_by_return()[i] << "\n";
    }

    os	<< "X Scale Factor                    : " << rhs.x_scale_factor() <<"\n"
        << "Y Scale Factor                    : " << rhs.y_scale_factor() <<"\n"
        << "Z Scale Factor                    : " << rhs.z_scale_factor() <<"\n"
        << "X Offset                          : " << rhs.x_offset() << "\n"
        << "Y Offset                          : " << rhs.y_offset() << "\n"
        << "Z Offset                          : " << rhs.z_offset() << "\n"
        << "Max X                             : " << rhs.max_x() << "\n"
        << "Min X                             : " << rhs.min_x() << "\n"
        << "Max Y                             : " << rhs.max_y() << "\n"
        << "Min Y                             : " << rhs.min_y() << "\n"
        << "Max Z                             : " << rhs.max_z() << "\n"
        << "Min Z                             : " << rhs.min_z() << "\n";
    
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

    os	<< "Pre-point value                   : " << rhs.pre_point_data() 
            << std::hex << " | 0x" << rhs.pre_point_data() << std::dec << "\n";

    return os;
}

//=========================================================================
}	// Namespace: std.

#endif	// SALSA_LAS_PUBLIC_HEADER_BLOCK_HPP_INCLUDED





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
