#include "lfu.hpp"

double slow_get_page (double key) {return key;}

//==========================================================================================//

int main(int argc, char **argv)
{
    size_t my_capacity  = 0;
    size_t values_count = 0;

    std::cin >> my_capacity >> values_count;

    lfu::cache_t<double, double> my_cache(my_capacity);

    const std::clock_t start = std::clock();

    for (size_t i = 0; i < values_count; i++)
    {
        double elem = 0;
        std::cin >> elem;

        my_cache.LookUpUpdate(elem, slow_get_page);
        // my_cache.Dump();
    }

    std::cout << "Total hits are " << my_cache.GetHits() << std::endl;

    std::cout << "Time is " << (std::clock() - start) / (double) CLOCKS_PER_SEC << std::endl;

    return 0;
}

//==========================================================================================//

// int main(int argc, char**argv)
// {
//     if (argc != 2)
//     {
//         std::cerr << "Incorrect number of command line arguments" << std::endl;
//         return -1;
//     }
    
//     std::ifstream test_file;

//     test_file.open(argv[1]);

//     size_t my_capacity  = 0;
//     size_t values_count = 0;

//     test_file >> my_capacity >> values_count;

//     lfu::cache_t<double, double> my_cache(my_capacity);

//     const std::clock_t start = std::clock();

//     for (size_t i = 0; i < values_count; i++)
//     {
//         double elem = 0;
//         test_file >> elem;

//         my_cache.LookUpUpdate(elem, slow_get_page);
//         // my_cache.Dump();
//     }

//     std::cout << "Total hits are " << my_cache.GetHits() << std::endl;

//     std::cout << "Time is " << (std::clock() - start) / (double) CLOCKS_PER_SEC << std::endl;
    
//     test_file.close();

//     return 0;
// }

//==========================================================================================//