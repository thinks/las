//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef LAS_PACK_HPP_INCLUDED
#define LAS_PACK_HPP_INCLUDED

#ifdef _MSC_VER
#define BEGIN_PACK_TIGHT \
    __pragma(pack(push)) \
    __pragma(pack(1))		// Alignment 1 byte
#define END_PACK_TIGHT __pragma(pack(pop))
#else
#define BEGIN_PACK_TIGHT // TODO
#define END_PACK_TIGHT // TODO
#endif // _MSC_VER

#endif  // LAS_PACK_HPP_INCLUDED
