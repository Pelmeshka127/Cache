#include "ideal.hpp"
#include "lfu.hpp"

using KeyT = int;
KeyT slow_get_page(KeyT key) {return key;}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Incorrect number of command line arguments" << std::endl;
        return -1;
    }
    
    std::ifstream test_file;

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

    lfu::cache_t<int, int> lfu_cache(my_capacity);

    for (auto i : array)
    {
        lfu_cache.LookUpUpdate(i, slow_get_page);
    }

    std::cout << "Total hit in lfu is " << lfu_cache.GetHits() << std::endl;

    ideal_cache::cache_t<int, int> ideal_cache(my_capacity, array);

    for (auto elem : array)
    {
        ideal_cache.LookUpUpdate(elem, slow_get_page);
    }

    std::cout << "Total hit in ideal is " << ideal_cache.GetHits() << std::endl;

    return 0;
}