//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef LAS_OFSTREAM_HPP_INCLUDED
#define LAS_OFSTREAM_HPP_INCLUDED

#include "las_exception.hpp"
#include <fstream>
#include <string>
#include <iosfwd>

//------------------------------------------------------------------------------

namespace las {

//------------------------------------------------------------------------------

class ofstream
{
public:

    //! CTOR.
    ofstream()
    {
        _ofs.exceptions(std::ofstream::eofbit | 
                        std::ofstream::failbit | 
                        std::ofstream::badbit);
    }

    //! CTOR.
    explicit
    ofstream(const std::string        &fname, 
             const std::ios::openmode  mode = std::ios::out | std::ios::binary)
    {
        _ofs.exceptions(std::ofstream::eofbit | 
                        std::ofstream::failbit | 
                        std::ofstream::badbit);

        open(fname, mode);
    }

    //! DTOR.
    ~ofstream() 
    { close(); }

    void
    open(const std::string  &fname, 
         std::ios::openmode  mode = std::ios::out | std::ios::binary)
    {
        try {
            _ofs.open(fname.c_str(), mode);
            //ofs_.clear();
        }
        catch(const std::ofstream::failure&) {
            LAS_THROW("las::ofstream: failure opening: '" << fname << "'");
        }
    }

    bool 
    is_open() const 
    { return _ofs.is_open(); }

    void 
    close() 
    { 
        if (is_open()) {
            _ofs.close(); 
        }
    }

    std::ofstream& 
    stream() 
    { return _ofs; }

private:

    ofstream(const ofstream&);
    ofstream& operator=(const ofstream&);

private:    // Member variables.

    std::ofstream _ofs;
};

//------------------------------------------------------------------------------

}	// Namespace: las.

//------------------------------------------------------------------------------

namespace std {

template<class CharT, class Traits>
basic_ostream<CharT,Traits>&
operator<<(basic_ostream<CharT,Traits> &os, 
           const las::ofstream         &rhs)
{
    os	<< "las::ofstream[0x" << &rhs << "]\n"
        << "Open : " << (rhs.is_open() ? "true" : "false") << "\n";
    return os;
}

}   // Namespace: std.

//------------------------------------------------------------------------------

#endif	// LAS_OFSTREAM_HPP_INCLUDED
