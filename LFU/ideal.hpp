#ifndef IDEAL_HPP_
#define IDEAL_HPP_

#include <iostream>
#include <list>
#include <unordered_map>
#include <iterator>
#include <vector>
#include <deque>

//==========================================================================================//

namespace ideal_cache
{

template <typename PageT, typename KeyT = int>
class ideal_cache_t
{
    private:
        size_t capacity_;

        size_t hits_;

        struct CacheNode {
            KeyT                key;
            size_t              frequency;
            std::list<size_t>   location;
        };

        std::list<CacheNode> unique_key_;

        using UniqueKeyIterator = typename std::list<CacheNode>::iterator;

        std::unordered_map<KeyT, UniqueKeyIterator> unique_hash_;

    public:
        ideal_cache_t(const std::vector<KeyT>& array, size_t capacity)
        {
            capacity_ = capacity;
            hits_     = 0;

            size_t array_index = 0;
            for (auto array_element = array.begin(); array_element != array.end(); array_element++)
            {
                auto find_element = unique_hash_.find(*array_element);
                if (find_element == unique_hash_.end())
                {
                    std::cout << "Working with " << *array_element << std::endl;
                    
                    std::cout << "Size of list is " << unique_key_.size() << std::endl;

                    std::list<size_t> key_location = {array_index};

                    unique_key_.push_back({*array_element, 1, key_location});

                    auto end_list = unique_key_.end();

                    end_list--;
                    
                    unique_hash_.emplace(*array_element, end_list);
                }

                else
                {
                    find_element->second->location.push_back(std::distance(array.begin(), array_element));
                }

                array_index++;

            }
        }

        void Dump()
        {
            for (auto elem : unique_key_)
            {
                std::cout << "Element is " << elem.key << "; It's index in array is " << elem.location.front() << std::endl;
                for (auto i : elem.location)
                {
                    std::cout << "Index in list " << i << std::endl;
                }
            }
        }
};

}

//==========================================================================================//

#endif