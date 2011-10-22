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

    try {
        las::ifstream ifs("D:/las.git/test/data/test.las");
        cerr << ifs << "\n";

        las::public_header_block phb;
        std::vector<las::point> points;
        las::io::read("D:/las.git/test/data/test.las",
                      phb,
                      points);

        las::header header;
        header.read(ifs);
        cerr << header << "\n";


        las::ofstream ofs;
        cerr << ofs << "\n";

    }
    catch (std::exception& ex) {
        cerr << ex.what() << "\n";
        std::abort();
    }

    return 0;
}
