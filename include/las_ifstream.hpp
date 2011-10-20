//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef LAS_IFSTREAM_HPP_INCLUDED
#define LAS_IFSTREAM_HPP_INCLUDED

#include "las_exception.hpp"
#include <fstream>
#include <string>
#include <iosfwd>

//------------------------------------------------------------------------------

namespace las {

//------------------------------------------------------------------------------

class ifstream
{
public:

    //! Empty CTOR.
    ifstream() 
    {
        _ifs.exceptions(std::ifstream::eofbit | 
                        std::ifstream::failbit | 
                        std::ifstream::badbit);
    }

    //! CTOR.
    explicit
    ifstream(const std::string        &fname, 
             const std::ios::openmode  mode = std::ios::in | std::ios::binary)
    {	
        _ifs.exceptions(std::ifstream::eofbit | 
                        std::ifstream::failbit | 
                        std::ifstream::badbit);
        open(fname, mode);
    }

    //! DTOR.
    ~ifstream() 
    { close(); }

    void
    open(const std::string        &fname, 
         const std::ios::openmode  mode = std::ios::in | std::ios::binary)
    {
        try {
            _ifs.open(fname.c_str(), mode);
            //_ifs.clear();
        }
        catch(const std::ofstream::failure&) {
            LAS_THROW("las::ifstream: failure opening: '" << fname << "'");
        }
    }

    bool 
    is_open() const	
    { return _ifs.is_open(); }

    void 
    close()			
    { 
        if (_ifs.is_open()) { 
            _ifs.close(); 
        } 
    }

    //! Expose std::ifstream for operators, etc.
    std::ifstream& 
    stream() 
    { return _ifs; }

private:

    ifstream(const ifstream&);
    ifstream& operator=(const ifstream&);

private:    // Member variables.

    std::ifstream _ifs;
};

//------------------------------------------------------------------------------

}	// Namespace: las.

//------------------------------------------------------------------------------

namespace std {

template<class CharT, class Traits>
basic_ostream<CharT,Traits>&
operator<<(basic_ostream<CharT,Traits> &os, 
           const las::ifstream         &rhs)
{
    os	<< "las::ifstream[0x" << &rhs << "]\n"
        << "Open : " << (rhs.is_open() ? "true" : "false") << "\n";
    return os;
}

}   // Namespace: std.

//------------------------------------------------------------------------------

#endif	// LAS_IFSTREAM_HPP_INCLUDED
