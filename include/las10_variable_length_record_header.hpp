//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef LAS10_VARIABLE_LENGTH_RECORD_HEADER_HPP_INCLUDED
#define LAS10_VARIABLE_LENGTH_RECORD_HEADER_HPP_INCLUDED

#include "las_namespace.hpp"
#include "las_pack.hpp"
//#include "las_exception.hpp"
//#include "las_static_assert.hpp"
//#include "las_ifstream.hpp"
#include "las10_types.hpp"
#include <string>
#include <iosfwd>

//------------------------------------------------------------------------------

BEGIN_LAS10_NAMESPACE

//------------------------------------------------------------------------------

BEGIN_PACK_TIGHT

//------------------------------------------------------------------------------

//! POD
struct variable_length_record_header
{
    // Constants.

    static const int32 user_id_length	  = 16;
    static const int32 description_length = 32;

    static const uint16 valid_record_signature = 43707; // Always 0xAABB.
    static const int32 size = 54;   // [bytes]

    // Data.

    uint16 record_signature;                // 2 [bytes]
    int8   user_id[user_id_length];         // 16 [bytes] 
    uint16 record_id;                       // 2 [bytes]
    uint16 record_length_after_header;      // 2 [bytes]
    int8   description[description_length]; // 32 [bytes]
};

//------------------------------------------------------------------------------

END_PACK_TIGHT

//------------------------------------------------------------------------------

END_LAS10_NAMESPACE

//------------------------------------------------------------------------------

BEGIN_STD_NAMESPACE

//------------------------------------------------------------------------------

template<class CharT, class Traits>
basic_ostream<CharT,Traits>&
operator<<(basic_ostream<CharT,Traits>                &os, 
           const las10::variable_length_record_header &rhs)
{
    typedef las10::variable_length_record_header vlr_header_type;
    os	<< "las10::variable_length_record_header[0x" << &rhs << "]\n"
        << "sizeof(las10::variable_length_record_header)  : " 
            << sizeof(vlr_header_type) << " | Size : "
            << vlr_header_type::size << "\n"
        << "Record Signature                     : " 
            << hex // Print in hex.
            << "0x" << rhs.record_signature << " | Valid: 0x" 
            << vlr_header_type::valid_record_signature 
            << "\n" 
            << dec // Print in decimal.
        << "User Id                              : '" 
            << string(rhs.user_id, vlr_header_type::user_id_length) << "'\n"
        << "Record Id                            : " 
            << rhs.record_id() << "\n"
        << "Record length after header           : " 
            << rhs.record_length_after_header << "\n"
        << "Description                          : '" 
            << string(rhs.description, vlr_header_type::description_length) 
            << "'\n";
    return os;
}

//------------------------------------------------------------------------------

END_STD_NAMESPACE

//------------------------------------------------------------------------------

#endif  // LAS10_VARIABLE_LENGTH_RECORD_HEADER_HPP_INCLUDED



//class variable_length_record_header
//{
//public:
//
//    static const int32 user_id_length	  = 16;
//    static const int32 description_length = 32;
//
//
//public:
//
//    //! Default CTOR.
//    variable_length_record_header()
//        : _record_signature(valid_record_signature)
//        , _record_id(0)
//        , _record_length_after_header(0)
//    {
//        std::memset(_user_id, 0, user_id_length*sizeof(int8));
//        std::memset(_description, 0, description_length*sizeof(int8));
//    }
//
//    //! Copy CTOR.
//    variable_length_record_header(const variable_length_record_header &rhs)
//        : _record_signature(rhs._record_signature)
//        , _record_id(rhs._record_id)
//        , _record_length_after_header(rhs._record_length_after_header)
//    { 
//        std::memcpy(_user_id, 
//                    rhs._user_id, 
//                    user_id_length*sizeof(int8));
//        std::memcpy(_description, 
//                    rhs._description, 
//                    description_length*sizeof(int8));
//    }
//
//    //! Assign.
//    variable_length_record_header& 
//    operator=(const variable_length_record_header &rhs)
//    {
//        _record_signature = rhs._record_signature;
//        _record_id = rhs._record_id;
//        _record_length_after_header = rhs._record_length_after_header;
//        std::memcpy(_user_id, 
//                    rhs._user_id, 
//                    user_id_length*sizeof(int8));
//        _user_id[user_id_length - 1] = '\0';  // Null termination.
//        std::memcpy(_description, 
//                    rhs._description, 
//                    description_length*sizeof(int8));
//        _description[description_length - 1] = '\0'; // Null termination.
//        return *this;
//    }
//
//    //! DTOR.
//    ~variable_length_record_header() 
//    { 
//        LAS_STATIC_ASSERT(1 == sizeof(int8),    invalid_int8_size);
//        LAS_STATIC_ASSERT(1 == sizeof(uint8),   invalid_uint8_size);
//        LAS_STATIC_ASSERT(2 == sizeof(int16),   invalid_int16_size);
//        LAS_STATIC_ASSERT(2 == sizeof(uint16),  invalid_uint16_size);
//        LAS_STATIC_ASSERT(4 == sizeof(int32),   invalid_int32_size);
//        LAS_STATIC_ASSERT(4 == sizeof(uint32),  invalid_uint32_size);
//        LAS_STATIC_ASSERT(8 == sizeof(float64), invalid_float64_size);
//        LAS_STATIC_ASSERT(size == sizeof(variable_length_record_header), 
//                          invalid_vlr_size); 
//    }
//
//public:
//
//    uint16
//    record_signature() const
//    { return _record_signature; }
//
//    const int8*
//    user_id() const
//    { return _user_id; }
//
//    uint16
//    record_id() const
//    { return _record_id; }
//
//    uint16
//    record_length_after_header() const
//    { return _record_length_after_header; }
//
//    const int8*
//    description() const
//    { return _description; }
//
//private:    // Member variables.
//
//    uint16 _record_signature;                // 2 [bytes]
//    int8   _user_id[user_id_length];         // 16 [bytes] 
//    uint16 _record_id;                       // 2 [bytes]
//    uint16 _record_length_after_header;      // 2 [bytes]
//    int8   _description[description_length]; // 32 [bytes]
//};
