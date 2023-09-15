#include "new_cache.hpp"

int slow_get_page(int key)
{
    return key;
}

int main(int argc, char **argv)
{    
    int mode = 0;

    std::cout << "Введите 1 для ввода данных с клавиатуры" << std::endl
              << "Введите 2 для ввода данных с файла"      << std::endl;

    std::cin >> mode;

    if (mode == 1)
    {
        size_t my_capacity  = 0;
        size_t values_count = 0;

        std::cin >> my_capacity >> values_count;

        new_cache::new_cache_t<int> my_cache(my_capacity);

        const std::clock_t start = std::clock();

        for (size_t i = 0; i < values_count; i++)
        {
            int elem = 0;
            std::cin >> elem;

            my_cache.LookUpUpdate(elem, slow_get_page);
            my_cache.Dump();
        }

        std::cout << "Total hits are " << my_cache.GetHits() << std::endl;

        std::cout << "Time is " << (std::clock() - start) / (double) CLOCKS_PER_SEC << std::endl;
    }

    else if (mode == 2)
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

        new_cache::new_cache_t<int> my_cache(my_capacity);

        const std::clock_t start = std::clock();

        for (size_t i = 0; i < values_count; i++)
        {
            int elem = 0;
            test_file >> elem;

            my_cache.LookUpUpdate(elem, slow_get_page);
            // my_cache.Dump();
        }

        std::cout << "Total hits are " << my_cache.GetHits() << std::endl;

        std::cout << "Time is " << (std::clock() - start) / (double) CLOCKS_PER_SEC << std::endl;
        
        test_file.close();
    }

    return 0;
}