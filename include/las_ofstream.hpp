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

    //! Default CTOR.
    ofstream()
    { _init(); }

    //! CTOR.
    explicit
    ofstream(const std::string        &file_name, 
             const std::ios::openmode  mode = std::ios::out | std::ios::binary)
    {
        _init();
        open(file_name, mode);
        _file_name = file_name;
    }

    //! DTOR.
    ~ofstream() 
    { close(); }

    void
    open(const std::string  &file_name, 
         const std::ios::openmode  mode = std::ios::out | std::ios::binary)
    {
        try {
            close();
            _ofs.open(file_name.c_str(), mode);
            _file_name = file_name;
            //ofs_.clear();
        }
        catch(const std::ofstream::failure&) {
            LAS_THROW("las::ofstream: failure opening: '" << file_name << "'");
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
            _file_name = std::string("");
        }
    }

    const std::string&
    file_name() const
    { return _file_name; }

    std::ofstream& 
    stream() 
    { return _ofs; }

private:

    static const std::ios_base::iostate default_exceptions = 
        std::ofstream::eofbit | 
        std::ofstream::failbit | 
        std::ofstream::badbit;

    void
    _init()
    { _ofs.exceptions(default_exceptions); }

private:

    ofstream(const ofstream&);
    ofstream& operator=(const ofstream&);

private:    // Member variables.

    std::ofstream _ofs;
    std::string   _file_name;
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
        << "Open      : " << (rhs.is_open() ? "true" : "false") << "\n"
        << "File name : '" << rhs.file_name() << "'\n";
    return os;
}

}   // Namespace: std.

//------------------------------------------------------------------------------

#endif	// LAS_OFSTREAM_HPP_INCLUDED
