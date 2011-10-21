//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef LAS_VARIABLE_LENGTH_RECORD_HPP_INCLUDED
#define LAS_VARIABLE_LENGTH_RECORD_HPP_INCLUDED

#include "las_variable_length_record_header.hpp"
#include "las_ifstream.hpp"
#include "las_ofstream.hpp"
#include <vector>

//------------------------------------------------------------------------------

namespace las {

//------------------------------------------------------------------------------

class variable_length_record
{
public:

    const variable_length_record_header&
    header() const
    { return _header; }

    const std::string&
    data() const
    { return _data; }

public:

    void
    read(ifstream &ifs)
    { 
        ifs.stream().read(reinterpret_cast<char*>(&_header), 
                          sizeof(variable_length_record_header));

        _data.resize(_header.record_length_after_header() - 
                     sizeof(variable_length_record_header) - 2);

        ifs.stream().read(reinterpret_cast<char*>(&_data[0]),
                          _data.size());
    }

    void
    write(ofstream &ofs)
    {
        ofs.stream().write(reinterpret_cast<const char*>(&_header),
                           sizeof(variable_length_record_header));
        ofs.stream().write(reinterpret_cast<const char*>(&_data[0]),
                           _data.size());
    }

private:    // Member variables.

    variable_length_record_header _header;
    std::string                   _data;
};

//------------------------------------------------------------------------------

}   // Namespace: las.

//------------------------------------------------------------------------------

namespace std
{

template<class CharT, class Traits>
basic_ostream<CharT,Traits>&
operator<<(basic_ostream<CharT,Traits>       &os, 
           const las::variable_length_record &rhs)
{
    os	<< "las::variable_length_record[0x" << &rhs << "]\n"
        << rhs.header() 
        << "Data : '" << rhs.data() << "'\n"; 
    return os;
}

}	// Namespace: std.

#endif  // LAS_VARIABLE_LENGTH_RECORD_HPP_INCLUDED
