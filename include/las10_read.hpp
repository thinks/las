//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef LAS10_READ_HPP_INCLUDED
#define LAS10_READ_HPP_INCLUDED

#include "las10_namespace.hpp"
#include "las10_public_header_block.hpp"
#include "las10_variable_length_record.hpp"
#include "las10_point_data_record_format.hpp"
#include "las_point.hpp"
#include "las_ifstream.hpp"
#include "las_exception.hpp"
#include "las_static_assert.hpp"
#include <vector>
#include <string>

//------------------------------------------------------------------------------

BEGIN_LAS10_NAMESPACE

//! DOCS
class read {
public:

    //! Read public header block from file. May throw.
    static void
    header(const std::string &file_name, public_header_block &phb)
    {
        las::ifstream ifs(file_name); // May throw.
        _read_public_header_block(ifs.stream(), phb);
    }

    // TODO
    //static void
    //variable_length_records(const std::string &file_name, 
    //                        std::vector<variable_length_record> *vlr_ptr)
    //{}

    //! Read points from file. May throw.
    static void
    points(const std::string                   &file_name,
           std::vector<las::point>             &points,
           public_header_block                 *phb_ptr = 0,
           std::vector<variable_length_record> *vlr_ptr = 0)
    {
        las::ifstream ifs(file_name); // May throw.
        public_header_block phb;
        // TODO: set strings to null!
        _read_public_header_block(ifs.stream(), phb); // May throw.
        if (0 != phb_ptr) {
            *phb_ptr = phb;
        }

        _read_variable_length_records(ifs.stream(), phb, vlr_ptr); // May throw.
        _read_point_data_start_signature(ifs.stream());            // May throw.
        _read_points(ifs.stream(), phb, points);                   // May throw.
    }


public:     // Public header block.

    static void
    _read_public_header_block(std::ifstream &ifs, public_header_block &phb)
    {
        LAS_STATIC_ASSERT(
            sizeof(public_header_block) == public_header_block::size, 
            invalid_PHB_size);
        ifs.read(reinterpret_cast<char*>(&phb), sizeof(public_header_block)); 
    }

private:    // Variable length records.

    //! TODO
    static void
    _read_variable_length_records(std::ifstream                       &ifs,
                                  const public_header_block           &phb,
                                  std::vector<variable_length_record> *vlr)
    {
        if (0 != vlr) {
        }
        else { // Skip past VLR data.
            ifs.seekg(
                phb.offset_to_data - 
                sizeof(public_header_block) - 
                sizeof(uint16),
                std::ios_base::cur);
        }
    }

private:    // Point data start signature.

    static const uint16 _valid_point_data_start_signature = 52445; // 0xCCDD

    //! Check post-header value. May throw.
    static void
    _read_point_data_start_signature(std::ifstream &ifs)
    {
        uint16 point_data_start_signature = 0;
        ifs.read(reinterpret_cast<char*>(&point_data_start_signature),
                 sizeof(uint16));
        if (point_data_start_signature != 
            _valid_point_data_start_signature) {
            LAS_THROW("Invalid point data start signature: "
                      << std::hex 
                      << "0x" << point_data_start_signature
                      << " | Valid: " 
                      << "0x" << _valid_point_data_start_signature);
        }
    }

private:

    static void
    _read_points(std::ifstream             &ifs,
                 const public_header_block &phb,
                 std::vector<las::point>   &points)
    {
        const uint16 pdr_length = phb.point_data_record_length;
        if (pdr_length <= 0) {
            LAS_THROW("Invalid point data record length: " << pdr_length);
        }
        const std::streamoff remain_bytes = _remaining_bytes(ifs);
        if (remain_bytes%pdr_length != 0) {
            LAS_THROW("Invalid point data record alignment");
        }

        // Read!

        std::vector<int8> pdr_buf(static_cast<std::size_t>(remain_bytes));
        ifs.read(&pdr_buf[0], pdr_buf.size()); 
        switch(phb.point_data_format_id)
        {
        case 0:
            _convert_pdr<point_data_record_format0>(phb, pdr_buf, points);
            break;
        case 1:
            _convert_pdr<point_data_record_format1>(phb, pdr_buf, points);
            break;
        default:
            LAS_THROW("Invalid point data format id: " 
                      << phb.point_data_format_id);
        }
    }

    //! Return remaining bytes in file. Returns negative value if 
    //! file is not open.
    static std::streamoff
    _remaining_bytes(std::ifstream &ifs)
    {
        std::streamoff remaining = -1;
        if (ifs.is_open()) {
            const std::streampos currg = ifs.tellg();// Current get position.
            ifs.seekg(0, std::ios::end);	         // Seek end-of-file.
            remaining = ifs.tellg() - currg;         // Remaining bytes.
            ifs.seekg(currg, std::ios::beg);         // Back to current get pos.
        }
        return remaining;
    }

    //! Count number of point data records in buffer.
    template<class PDRF>
    static std::size_t
    _pdr_count(const std::vector<int8> &pdr_buf)
    {
        LAS_STATIC_ASSERT(0 != PDRF::length, invalid_PDRF_length);
        return (pdr_buf.size()/PDRF::length);
    }

    //! Convert point data records to points.
    template<class PDRF>
    static void
    _convert_pdr(const public_header_block &phb, 
                 const std::vector<int8>   &pdr_buf, 
                 std::vector<las::point>   &points)
    {
        const PDRF *pdr_ptr = reinterpret_cast<const PDRF*>(&pdr_buf[0]);
        int i;
        const int n = static_cast<int>(_pdr_count<PDRF>(pdr_buf));
        points.resize(n);
#pragma omp parallel for
        for (i = 0; i < n; ++i) {
            _make_point(phb, pdr_ptr[i], points[i]);
        }
    }

    //! Make point from PDRF0.
    static void
    _make_point(const public_header_block       &phb,
                const point_data_record_format0 &pdrf0,
                las::point                      &point)
    {
        point.x               = phb.x_scale_factor*pdrf0.x + phb.x_offset;
        point.y               = phb.y_scale_factor*pdrf0.y + phb.y_offset;
        point.z               = phb.z_scale_factor*pdrf0.z + phb.z_offset;
        point.r               = 0;
        point.g               = 0;
        point.b               = 0;
        point.gps_time        = 0.;
        point.intensity       = pdrf0.intensity;
        point.num_returns     = num_returns(pdrf0);
        point.return_num      = return_num(pdrf0);
        point.scan_dir_flag   = scan_dir_flag(pdrf0);
        point.edge_flag       = edge_flag(pdrf0);
        point.scan_angle_rank = pdrf0.scan_angle_rank;
        point.classification  = pdrf0.classification;
    }

    //! Make point from PDRF1.
    static void
    _make_point(const public_header_block       &phb,
                const point_data_record_format1 &pdrf1,
                las::point                      &point)
    {
        point.x               = phb.x_scale_factor*pdrf1.x + phb.x_offset;
        point.y               = phb.y_scale_factor*pdrf1.y + phb.y_offset;
        point.z               = phb.z_scale_factor*pdrf1.z + phb.z_offset;
        point.r               = 0;
        point.g               = 0;
        point.b               = 0;
        point.gps_time        = pdrf1.gps_time;
        point.intensity       = pdrf1.intensity;
        point.num_returns     = num_returns(pdrf1);
        point.return_num      = return_num(pdrf1);
        point.scan_dir_flag   = scan_dir_flag(pdrf1);
        point.edge_flag       = edge_flag(pdrf1);
        point.scan_angle_rank = pdrf1.scan_angle_rank;
        point.classification  = pdrf1.classification;
    }
};

END_LAS10_NAMESPACE

//------------------------------------------------------------------------------

#endif // LAS10_READ_HPP_INCLUDED
