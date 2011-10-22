//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef LAS_IO_HPP_INCLUDED
#define LAS_IO_HPP_INCLUDED

#include "las_ifstream.hpp"
#include "las_ofstream.hpp"
#include "las_public_header_block.hpp"
#include "las_variable_length_record.hpp"
#include "las_scan_point.hpp"
#include <vector>
#include <string>

//------------------------------------------------------------------------------

namespace las {

//------------------------------------------------------------------------------

class io {
public:

    static const uint16 valid_point_data_start_signature = 52445; // 0xCCDD

public:

    static void
    read(const std::string                   &file_name,
         public_header_block                 &phb,
         std::vector<scan_point>             &points,
         std::vector<variable_length_record> *vlr = 0)
    {
        ifstream ifs(file_name);                        // May throw.
        _read_public_header_block(ifs, phb);            // May throw.
        _read_variable_length_records(ifs, phb, vlr);   // May throw.
        _read_point_start_signature(ifs);               // May throw.
        _read_points(ifs, phb, points);                 // May throw.
    }

    static void
    write(const std::string &file_name,
          const public_header_block                 &phb,
          const std::vector<variable_length_record> &vlr, 
          const std::vector<scan_point>             &points)
    {
        // TODO

        LAS_THROW("las::io::write() not implemented yet!!"); // TODO!!

        ofstream ofs(file_name);                        // May throw.
        _write_public_header_block(ifs, phb);            // May throw.
        _write_variable_length_records(ifs, phb, vlr);   // May throw.
        _write_point_start_signature(ifs);               // May throw.
        _write_points(ifs, phb, points);                 // May throw.
    }

private:

    static void
    _read_public_header_block(ifstream &ifs, public_header_block &phb)
    {
        ifs.stream().read(reinterpret_cast<char*>(&phb),
                          sizeof(public_header_block));
        // TODO: validate PHB!
    }

    static void
    _write_public_header_block(ofstream &ofs, const public_header_block &phb)
    {
        // TODO: validate PHB!
        ofs.stream().write(reinterpret_cast<const char*>(&phb),
                           sizeof(public_header_block));
    }

private:    // Variable length records.

    static void
    _read_variable_length_records(ifstream                            &ifs,
                                  const public_header_block           &phb,
                                  std::vector<variable_length_record> *vlr)
    {
        if (0 != vlr) {
        }
        else {
            // Skip past VLR data.

            ifs.stream().seekg(
                phb.offset_to_data() - 
                sizeof(public_header_block) - 
                sizeof(uint16),
                std::ios_base::cur);
        }
    }

    static void
    _write_variable_length_records()
    {}

private:    // Point data start signature.

    static void
    _read_point_data_start_signature(ifstream &ifs)
    {
        uint16 point_data_start_signature(0);
        ifs.stream().read(reinterpret_cast<char*>(&point_data_start_signature),
                          sizeof(uint16));

        if (point_data_start_signature != 
            valid_point_data_start_signature) {
            LAS_THROW("Invalid point data start signature: "
                      << std::hex 
                      << "0x" << point_data_start_signature
                      << " | Valid: " 
                      << "0x" << valid_point_data_start_signature;
        }
    }

    static void
    _write_point_data_start_signature(ofstream &ofs)
    {
        ifs.stream().write(
            reinterpret_cast<const char*>(&valid_point_data_start_signature),
            sizeof(uint16));
    }

private:

    static void
    _read_points(ifstream                  &ifs,
                 const public_header_block &phb,
                 std::vector<scan_point>   &points)
    {
    }

    static void
    _write_points(ofstream &ofs)
    {}
};

//------------------------------------------------------------------------------

}   // Namespace: las.

//------------------------------------------------------------------------------

#endif  // LAS_IO_HPP_INCLUDED
