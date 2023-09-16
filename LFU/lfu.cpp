#include "lfu.hpp"

int slow_get_page (int key) {return key;}

int MakeConsoleInput(int argc, char**argv);

int MakeFileInput(int argc, char**argv);

//==========================================================================================//

int main(int argc, char **argv)
{
    bool interactive = true;

    while(interactive)
    {
        std::cout   << "Введите 1 для ввода данных с клавиатуры" << std::endl
                    << "Введите 2 для ввода данных с файла"      << std::endl;

        int mode = 0;

        if (scanf("%d", &mode) == 1)
        {
            switch(mode)
            {
                case 1:
                    MakeConsoleInput(argc, argv);
                    interactive = false;
                    break;

                case 2:
                    MakeFileInput(argc, argv);
                    interactive = false;
                    break;

                default:
                    std::cout << "Введено неверное число, повторите поппытку" << std::endl;
                    while(getchar() != '\n')
                        continue;
            }
        }

        else
        {
            std::cout << "Введен некорректный символ, повторите поппытку" << std::endl;
            while(getchar() != '\n')
                continue;
        }
    }

    return 0;
}

//==========================================================================================//

int MakeConsoleInput(int argc, char **argv)
{
    size_t my_capacity  = 0;
    size_t values_count = 0;

    std::cin >> my_capacity >> values_count;

    lfu::cache_t<int> my_cache(my_capacity);

    const std::clock_t start = std::clock();

    for (size_t i = 0; i < values_count; i++)
    {
        int elem = 0;
        std::cin >> elem;

        my_cache.LookUpUpdate(elem, slow_get_page);
        // my_cache.Dump();
    }

    std::cout << "Total hits are " << my_cache.GetHits() << std::endl;

    std::cout << "Time is " << (std::clock() - start) / (double) CLOCKS_PER_SEC << std::endl;

    return 0;
}

//==========================================================================================//

int MakeFileInput(int argc, char**argv)
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

    lfu::cache_t<int> my_cache(my_capacity);

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

    return 0;
}

//==========================================================================================//