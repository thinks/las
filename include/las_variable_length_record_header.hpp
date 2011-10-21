//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef LAS_VARIABLE_LENGTH_RECORD_HEADER_HPP_INCLUDED
#define LAS_VARIABLE_LENGTH_RECORD_HEADER_HPP_INCLUDED

#include "las_types.hpp"
#include "las_exception.hpp"
#include "las_static_assert.hpp"
#include "las_ifstream.hpp"
#include <cstring>
#include <algorithm>
#include <iosfwd>

//------------------------------------------------------------------------------

namespace las {

//------------------------------------------------------------------------------

#ifdef WIN32
#pragma pack(push)
#pragma pack(1)		// Alignment 1 byte
#endif // WIN32

//------------------------------------------------------------------------------

class variable_length_record_header
{
public:

    static const int32 user_id_length	  = 16;
    static const int32 description_length = 32;

    static const uint16 valid_record_signature = 43707; // Always 0xAABB.
    static const int32 size = 54;   // [bytes]

public:

    //! Default CTOR.
    variable_length_record_header()
        : _record_signature(valid_record_signature)
        , _record_id(0)
        , _record_length_after_header(0)
    {
        std::memset(_user_id, 0, user_id_length*sizeof(int8));
        std::memset(_description, 0, description_length*sizeof(int8));
    }

    //! Copy CTOR.
    variable_length_record_header(const variable_length_record_header &rhs) 
    { *this = rhs; }

    //! Assign.
    variable_length_record_header& 
    operator=(const variable_length_record_header &rhs)
    {
        std::memcpy(this, &rhs, size); // Bit-wise copy.
        return *this;
    }

    //! DTOR.
    ~variable_length_record_header() 
    { 
        LAS_STATIC_ASSERT(1 == sizeof(int8),    invalid_int8_size);
        LAS_STATIC_ASSERT(1 == sizeof(uint8),   invalid_uint8_size);
        LAS_STATIC_ASSERT(2 == sizeof(int16),   invalid_int16_size);
        LAS_STATIC_ASSERT(2 == sizeof(uint16),  invalid_uint16_size);
        LAS_STATIC_ASSERT(4 == sizeof(int32),   invalid_int32_size);
        LAS_STATIC_ASSERT(4 == sizeof(uint32),  invalid_uint32_size);
        LAS_STATIC_ASSERT(8 == sizeof(float64), invalid_float64_size);
        LAS_STATIC_ASSERT(size == sizeof(variable_length_record_header), 
                          invalid_vlr_size); 
    }

public:

    uint16
    record_signature() const
    { return _record_signature; }

    const int8*
    user_id() const
    { return _user_id; }

    uint16
    record_id() const
    { return _record_id; }

    uint16
    record_length_after_header() const
    { return _record_length_after_header; }

    const int8*
    description() const
    { return _description; }

private:    // Member variables.

    uint16 _record_signature;                // 2 [bytes]
    int8   _user_id[user_id_length];         // 16 [bytes] 
    uint16 _record_id;                       // 2 [bytes]
    uint16 _record_length_after_header;      // 2 [bytes]
    int8   _description[description_length]; // 32 [bytes]
};

//------------------------------------------------------------------------------

#ifdef WIN32
#pragma pack(pop)	// pack(1)
#endif  // WIN32

//------------------------------------------------------------------------------

}   // Namespace: las.

//------------------------------------------------------------------------------

namespace std {

template<class CharT, class Traits>
basic_ostream<CharT,Traits>&
operator<<(basic_ostream<CharT,Traits>              &os, 
           const las::variable_length_record_header &rhs)
{
    os	<< "las::variable_length_record_header[0x" << &rhs << "]\n"
        << "sizeof(las::variable_length_record_header)  : " 
            << sizeof(las::variable_length_record_header) << " | Size : "
            << las::variable_length_record_header::size << "\n"
        << "Record Signature                     : " 
            << std::hex 
            << "0x" << rhs.record_signature() << " | Valid: 0x" 
            <<  las::variable_length_record_header::valid_record_signature 
            << "\n" << std::dec
        << "User Id                              : '" 
            << std::string(rhs.user_id()) << "'\n"
        << "Record Id                            : " 
            << rhs.record_id() << "\n"
        << "Record length after header           : " 
            << rhs.record_length_after_header() << "\n"
        << "Description                          : '" 
            << std::string(rhs.description()) << "'\n";
    return os;
}

}	// Namespace: std.

//------------------------------------------------------------------------------

#endif  // LAS_VARIABLE_LENGTH_RECORD_HPP_INCLUDED
