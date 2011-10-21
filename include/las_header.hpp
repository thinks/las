//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef LAS_HEADER_HPP_INCLUDED
#define LAS_HEADER_HPP_INCLUDED

#include "las_public_header_block.hpp"
#include "las_variable_length_record.hpp"
#include "las_ifstream.hpp"
#include "las_exception.hpp"
#include <vector>
#include <iosfwd>

//------------------------------------------------------------------------------

namespace las {

//------------------------------------------------------------------------------

class header
{
public:

    static const uint16 valid_point_data_start_signature = 52445; // 0xCCDD

public:

    //! Default CTOR.
    header()
    {}

    const public_header_block&
    phb() const
    { return _phb; }

    uint16
    point_data_start_signature() const
    { return _point_data_start_signature; }

    void
    read(ifstream &ifs)
    {
        ifs.stream().read(reinterpret_cast<char*>(&_phb),
                          sizeof(public_header_block));

        for (uint32 i(0); i < _phb.num_variable_length_records(); ++i) {
            variable_length_record vlr;
            vlr.read(ifs);
            _vlr.push_back(vlr);
        }

        ifs.stream().read(reinterpret_cast<char*>(&_point_data_start_signature),
                          sizeof(uint16));
    }

    std::size_t
    num_vlr() const
    { return _vlr.size(); }

    const variable_length_record&
    operator[](const std::size_t i) const
    {
        if (i >= _vlr.size()) {
            LAS_THROW("las::header: Invalid VLR index: " << i);
        }

        return _vlr[i];
    }

private:


private:    // Member variables.

    public_header_block _phb;
    std::vector<variable_length_record> _vlr;
    uint16 _point_data_start_signature;
};

//------------------------------------------------------------------------------

}   // Namespace: las.

//------------------------------------------------------------------------------

namespace std
{

template<class CharT, class Traits>
basic_ostream<CharT,Traits>&
operator<<(basic_ostream<CharT,Traits> &os, 
           const las::header           &rhs)
{
    os	<< "las::header[0x" << &rhs << "]\n"
        << rhs.phb();

    for (std::size_t i(0); i < rhs.num_vlr(); ++i) {
        os << rhs[i];
    }

    os  << "Point data start signature : " 
        << std::hex 
        << "0x" << rhs.point_data_start_signature() << " | Valid: 0x" 
        <<  las::header::valid_point_data_start_signature << "\n"
        << std::dec;

    return os;
}

}   // Namespace: std.

//------------------------------------------------------------------------------

#endif  // LAS_HEADER_HPP_INCLUDED
