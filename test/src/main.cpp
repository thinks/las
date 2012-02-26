//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#include <las.hpp>
#include <vector>
#include <iostream>

//------------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
    using std::cerr;

    try {
        const std::string ft[] = {
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856085600-856085657_corridor.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856085992-856086070_corridor.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856086261-856086321_corridor.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856086674-856086754_corridor.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856086934-856086971.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856087073-856087074.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856087076-856087142.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856087221-856087287.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856087387-856087470.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856087577-856087642.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856087786-856087874.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856087989-856088055.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856088166-856088257.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856088379-856088442.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856088527-856088621.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856088624-856088628.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856088727-856088787.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856088866-856088949.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856089019-856089071.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856089167-856089243.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856089352-856089404.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856089512-856089591.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856089678-856089731.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856089823-856089900.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856089990-856090026.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856090058-856090097.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856094688-856094717.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856094803-856094857.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856094925-856094977.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856095097-856095169.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856095232-856095317.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856095407-856095489.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856095595-856095684.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856095784-856095862.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856095980-856096056.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856096144-856096214.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856096328-856096399.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856096508-856096571.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856096712-856096790.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856096909-856096986.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856097081-856097144.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856097262-856097268.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856097270-856097320.las",
"D:/Dropbox/lidar/dublin-2007/tracks/las/ft/FT_856097413-856097447.las"
        };

        for (int i = 0; i < 1; ++i) {
            las10::public_header_block phb;
            las10::read::header(ft[i], phb);
            std::cerr << phb << "\n";
            //std::cerr << "[" << i + 1 << "|44]: '" << ft[i] << "'\n";
        }


        for (int i = 0; i < 44; ++i) {
            std::vector<las::point> points;
            las10::read::points(ft[i], points);
            std::cerr << "[" << i + 1 << "|44]: '" << ft[i] << "'\n";
        }


        //cerr << points[126];

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
    catch (...) {
        cerr << "Unknown exception. Aborting...\n";
        std::abort();
    }

    return 0;
}
