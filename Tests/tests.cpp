#include "tests.hpp"

//==========================================================================================//

int main()
{
    size_t capacity     = 0;
    size_t values_count = 0;
    size_t tests_count  = 0;

    std::cout << "Enter size of cache" << std::endl;

    std::cin >> capacity;

    std::cout << "Enter count of numbers" << std::endl;

    std::cin >> values_count;

    std::cout << "Enter the count of unit tests" << std::endl;

    std::cin >> tests_count;

    testgen::testgen_t tests(capacity, values_count, tests_count);

    return 0;
}

//==========================================================================================//