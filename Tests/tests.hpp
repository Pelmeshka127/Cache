#ifndef TESTS_HPP_
#define TESTS_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <format>

namespace testgen
{

class testgen_t
{
    private:

        size_t capacity_;

        size_t input_size_;

        size_t tests_count_;

    public:

        testgen_t(const size_t capacity, const size_t input_size, const size_t tests_count)
        {
            capacity_       = capacity;

            input_size_     = input_size;

            tests_count_    = tests_count;

            std::ofstream test_files[input_size];

            for (size_t index = 0; index < tests_count; index++)
            {
                std::string file_name = "Tests/test" + std::to_string(index) + ".txt";
                
                test_files[index].open(file_name);

                test_files[index] << capacity << " " << input_size << std::endl;

                for (size_t count = 0; count < input_size; count++)
                {
                    size_t elem = size_t (std::rand() % 10);

                    test_files[index] << elem << " ";
                }

                test_files[index].close();
            }

    }

};

}
#endif