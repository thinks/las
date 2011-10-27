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
        std::vector<las::point> points;
        las::io::read("D:/las.git/test/data/test.las", points);

        cerr << points[0];

        /*
        las::header header;
        header.read(ifs);
        cerr << header << "\n";


        las::ofstream ofs;
        cerr << ofs << "\n";
        */
    }
    catch (std::exception& ex) {
        cerr << ex.what() << "\n";
        std::abort();
    }

    return 0;
}
