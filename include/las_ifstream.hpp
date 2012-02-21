//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef LAS_IFSTREAM_HPP_INCLUDED
#define LAS_IFSTREAM_HPP_INCLUDED

#include "las_namespace.hpp"
#include "las_exception.hpp"
#include <fstream>
#include <string>
#include <iosfwd>

//------------------------------------------------------------------------------

BEGIN_LAS_NAMESPACE

class ifstream
{
public:

    //! Default CTOR.
    ifstream() 
    { _init(); }

    //! CTOR.
    explicit
    ifstream(const std::string        &file_name, 
             const std::ios::openmode  mode = std::ios::in | std::ios::binary)
    {	
        _init();
        open(file_name, mode);
    }

    //! DTOR.
    ~ifstream() 
    { close(); }

    void
    open(const std::string        &file_name, 
         const std::ios::openmode  mode = std::ios::in | std::ios::binary)
    {
        try {
            close();
            _ifs.open(file_name.c_str(), mode);
            _file_name = file_name;
            //_ifs.clear();
        }
        catch (...) {
            LAS_THROW("las::ifstream: failure opening: '" << file_name << "'");
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
            _file_name = std::string("");
        } 
    }

    const std::string&
    file_name() const
    { return _file_name; }

    //! Expose std::ifstream for operators, etc.
    std::ifstream& 
    stream() 
    { return _ifs; }

private:

    static const std::ios_base::iostate default_exceptions = 
        std::ofstream::eofbit | std::ofstream::failbit | std::ofstream::badbit;

    void
    _init()
    { _ifs.exceptions(default_exceptions); }

private:

    ifstream(const ifstream&);
    ifstream& operator=(const ifstream&);

private:    // Member variables.

    std::ifstream _ifs;
    std::string   _file_name;
};

END_LAS_NAMESPACE

//------------------------------------------------------------------------------

BEGIN_STD_NAMESPACE

template<class CharT, class Traits>
basic_ostream<CharT,Traits>&
operator<<(basic_ostream<CharT,Traits> &os, 
           const las::ifstream         &rhs)
{
    os	<< "las::ifstream[0x" << &rhs << "]\n"
        << "Open      : " << (rhs.is_open() ? "true" : "false") << "\n"
        << "File name : '" << rhs.file_name() << "'\n";
    return os;
}

END_STD_NAMESPACE

//------------------------------------------------------------------------------

#endif	// LAS_IFSTREAM_HPP_INCLUDED
