#include "ideal.hpp"

//==========================================================================================//

using KeyT = int;
KeyT slow_get_page(KeyT key) {return key;}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Incorrect number of command line arguments" << std::endl;
        return -1;
    }

    std::ifstream test_file{};

    test_file.open(argv[1]);

    size_t my_capacity  = 0;
    size_t values_count = 0;

    test_file >> my_capacity >> values_count;

    std::vector<KeyT> array;
    for (size_t i = 0; i != values_count; i++)
    {
        int key = 0;

        test_file >> key;
        
        array.push_back(key);
    }

    for (auto elem : array)
    {
        std::cout << elem << " ";
    }

    std::cout << std::endl;

    ideal_cache::ideal_cache_t<int> my_cache(array, my_capacity);

    my_cache.DumpArray();

    for (auto elem : array)
    {
        my_cache.LookUpUpdate(elem, slow_get_page(elem));

        my_cache.DumpCache();
    }

    return 0;
}

//==========================================================================================//