#ifndef TESTS_HPP_
#define TESTS_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <format>

int TestGenerator(const size_t capacity, const size_t input_size, const int tests_count)
{
    std::ofstream test_files[input_size];

    for (size_t index = 0; index < tests_count; index++)
    {
        std::string file_name = "test" + std::to_string(index) + ".txt";
        
        test_files[index].open(file_name);

        test_files[index] << capacity << " " << input_size << std::endl;

        for (size_t count = 0; count < input_size; count++)
        {
            size_t elem = std::rand() % 100;

            test_files[index] << elem << " ";
        }

        test_files[index].close();
    }

    return 0;
}

#endif