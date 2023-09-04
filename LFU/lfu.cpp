#include "lfu.hpp"

int slow_get_page (int key) {return key;}

int main()
{
    size_t my_capacity  = 0;
    size_t values_count = 0;

    std::cin >> my_capacity >> values_count;

    lfu::cache_t<int> my_cache(my_capacity);

    for (size_t i = 0; i < values_count; i++)
    {
        int elem = 0;
        std::cin >> elem;

        my_cache.LookUpUpdate(elem, slow_get_page);
        my_cache.Dump();
    }

    std::cout << "Total hits are " << my_cache.GetHits() << std::endl;
    

    return 0;
}