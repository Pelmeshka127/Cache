#ifndef IDEAL_HPP_
#define IDEAL_HPP_

#include <iostream>
#include <list>
#include <unordered_map>
#include <iterator>
#include <vector>
#include <unordered_set>
#include <fstream>
#include <ctime>

//==========================================================================================//

namespace ideal
{

template <typename PageT, typename KeyT = int>
class cache_t
{
    private:
        const size_t capacity_;

        size_t hits_;

        struct CacheNode {
            KeyT    key;
            PageT   page;
        };

        std::list<CacheNode> cache_;

        using ListIterator = typename std::list<CacheNode>::iterator;

        std::unordered_map<KeyT, std::list<size_t>> hash_;

        std::unordered_set<KeyT> data_set_;

    public:
        cache_t(const size_t capacity, std::vector<int> &data) : capacity_{capacity}, hits_{0}
        {
            size_t index = 0;

            for (auto element: data)
                hash_[element].push_back(index++);
        }

        bool IsFull() const
        {
            return (capacity_ == cache_.size());
        }

        size_t GetHits() const
        {
            return hits_;
        }

        template<typename F>
        bool LookUpUpdate(KeyT key, F slow_get_page)
        {
            auto hit = data_set_.find(key);

            if (hit == data_set_.end())
            {
                if (hash_[key].size() == 1)
                    return false;

                if (IsFull())
                    DeleteMostFar();

                PushNewElement(key, slow_get_page);

                UpdateElementDistance(key);

                return false;
            }

            else
            {
                hits_++;

                UpdateElementDistance(key);

                return true;
            }
        }

        void DeleteMostFar()
        {
            size_t max_distance = 0;

            ListIterator erasing_element {};

            for (auto cache_elem = cache_.begin(); cache_elem != cache_.end(); cache_elem++)
            {
                auto nearest_element_position = hash_[cache_elem->key].begin();

                if (*nearest_element_position > max_distance)
                {
                    max_distance    = *nearest_element_position;

                    erasing_element = cache_elem;
                }    
            }

            if (max_distance)
            {
                data_set_.erase(erasing_element->key);

                cache_.erase(erasing_element);
            }

            else
            {
                data_set_.erase(cache_.begin()->key);

                cache_.pop_front();
            }


        }

        template<typename F>
        void PushNewElement(KeyT key, F slow_get_page)
        {
            cache_.push_back({slow_get_page(key), key});

            data_set_.insert(key);
        }

        void UpdateElementDistance(KeyT key)
        {
            hash_[key].pop_front();
        }

        void Dump() const
        {
            std::cout << "\n//====================LFU Dump====================//\n";
            
            std::cout << "\t\tCapacity is: " << capacity_     << "\n";
            
            std::cout << "\t\tSize is: "     << cache_.size() << "\n";

            std::cout << "\t\tCache: \n";

            for (auto x: cache_)
                auto hit = hash_.find(x.key);

            std::cout << "\t\t" << "Total hits " << hits_ << std::endl;

            std::cout << "//====================End Dump====================//\n\n";
        }
};

}

//==========================================================================================//

#endif