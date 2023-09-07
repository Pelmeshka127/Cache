#include "ideal.hpp"

using KeyT = int;
KeyT slow_get_page(KeyT key) {return key;}

int main()
{
    size_t my_capacity  = 0;
    size_t values_count = 0;

    std::cin >> my_capacity >> values_count;

    std::vector<KeyT> array;
    for (size_t i = 0; i != values_count; i++)
    {
        int key = 0;

        std::cin >> key;
        
        array.push_back(key);
    }

    ideal_cache::ideal_cache_t<int> my_cache(array, my_capacity);

    my_cache.Dump();

    return 0;
}