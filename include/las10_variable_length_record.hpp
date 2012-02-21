//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef LAS10_VARIABLE_LENGTH_RECORD_HPP_INCLUDED
#define LAS10_VARIABLE_LENGTH_RECORD_HPP_INCLUDED

#include "las_namespace.hpp"
#include "las10_types.hpp"
#include "las10_variable_length_record_header.hpp"
#include <vector>
#include <iosfwd>

//------------------------------------------------------------------------------

BEGIN_LAS10_NAMESPACE

//------------------------------------------------------------------------------

//! POD
struct variable_length_record
{
    variable_length_record_header header;
    std::vector<int8>             data;  
};

//------------------------------------------------------------------------------

END_LAS10_NAMESPACE

//------------------------------------------------------------------------------

BEGIN_STD_NAMESPACE

//------------------------------------------------------------------------------

template<class CharT, class Traits>
basic_ostream<CharT,Traits>&
operator<<(basic_ostream<CharT,Traits>         &os, 
           const las10::variable_length_record &rhs)
{
    os	<< "las10::variable_length_record[0x" << &rhs << "]\n"
        << rhs.header 
        << "Data : '";
    for (size_t i = 0, i < rhs.data.size(); ++i) {
        os << static_cast<int>(rhs.data[i]);
    }
    os << "'\n"; 
    return os;
}

//------------------------------------------------------------------------------

END_STD_NAMESPACE

//------------------------------------------------------------------------------

#endif  // LAS10_VARIABLE_LENGTH_RECORD_HPP_INCLUDED


//class variable_length_record
//{
//public:
//
//    const variable_length_record_header&
//    header() const
//    { return _header; }
//
//    const std::string&
//    data() const
//    { return _data; }
//
//public:
//
//    void
//    read(ifstream &ifs)
//    { 
//        ifs.stream().read(reinterpret_cast<char*>(&_header), 
//                          sizeof(variable_length_record_header));
//
//        _data.resize(_header.record_length_after_header() - 
//                     sizeof(variable_length_record_header) - 2);
//
//        ifs.stream().read(reinterpret_cast<char*>(&_data[0]),
//                          _data.size());
//    }
//
//    void
//    write(ofstream &ofs)
//    {
//        ofs.stream().write(reinterpret_cast<const char*>(&_header),
//                           sizeof(variable_length_record_header));
//        ofs.stream().write(reinterpret_cast<const char*>(&_data[0]),
//                           _data.size());
//    }
//
//private:    // Member variables.
//
//    variable_length_record_header _header;
//    std::vector<int8>             _data;  
//};

