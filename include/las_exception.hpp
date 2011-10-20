//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef LAS_EXCEPTION_HPP_INCLUDED
#define LAS_EXCEPTION_HPP_INCLUDED

#include <sstream>
#include <exception>

//------------------------------------------------------------------------------

// Useful macro.

#define LAS_THROW(MSG) \
{std::stringstream ss; ss << "las: "; ss << MSG; throw las::base(ss.str());}

//------------------------------------------------------------------------------

namespace las  {

//------------------------------------------------------------------------------

class base : public std::exception
{
public:

    //! CTOR.
	explicit
	base(const std::string &msg) throw()
		: std::exception()
        , _msg(msg) 
    {}

    //! Copy CTOR.
    base(const base &rhs) throw()
        : std::exception(rhs)
        , _msg(rhs._msg)
    {}

    //! Assign.
    base&
    operator=(const base &rhs)
    {
        std::exception::operator=(rhs);
        _msg = rhs._msg;
        return *this;
    }

    //! DTOR.
	virtual 
    ~base() throw()
    {}

	virtual const char* 
    what() const throw() 
    { return _msg.c_str(); }

private:    // Member variables.

	std::string _msg;
};

//------------------------------------------------------------------------------

}  // Namespace: las.

//------------------------------------------------------------------------------

#endif	// LAS_EXCEPTION_HPP_INCLUDED
