//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#include <las.hpp>
#include <iostream>

//------------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
    using std::cerr;

    las::ifstream ifs;
    cerr << ifs << "\n";

    las::ofstream ofs;
    cerr << ofs << "\n";


    las::public_header_block phb;
    cerr << phb << "\n";

    las::variable_length_record vlr;
    cerr << vlr << "\n";

    return 0;
}
