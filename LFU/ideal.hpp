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

namespace ideal_cache
{

template <typename PageT, typename KeyT>
class cache_t
{
    private:
        const size_t capacity_;

        size_t hits_;

        struct CacheNode {
            PageT   page;
            KeyT    key;
        };

        std::list<CacheNode> cache_;

        using CacheIterator = typename std::list<CacheNode>::iterator;

        std::unordered_map<KeyT, std::list<size_t>> hash_;

        using HashIterator = typename std::unordered_map<KeyT, std::list<size_t>>::iterator;

        std::unordered_set<KeyT> data_set_;

        using SetIterator  = typename std::unordered_set<KeyT>::iterator;

    public:
        cache_t(const size_t capacity, const std::vector<KeyT>& data) : capacity_{capacity}, hits_{0}
        {
            size_t position = 0;

            for (auto elem : data)
                hash_[elem].push_back(position++);
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
        void LookUpUpdate(KeyT key, F slow_get_page)
        {
            auto set_hit = data_set_.find(key);

            if (set_hit == data_set_.end())
            {
                if (hash_[key].size() == 1)
                    return;

                data_set_.insert(key);

                if (IsFull())
                {
                    CacheIterator erasing_elem = GetDeletingElement();

                    data_set_.erase(erasing_elem->key);

                    *erasing_elem = {slow_get_page(key), key};
                }

                else
                    PushNewElement(slow_get_page, key);
            }

            else
                hits_++;

            UpdateElementDistance(key);
        }

        CacheIterator GetDeletingElement()
        {
            size_t max_distance = 0;

            CacheIterator erasing_elem {};

            for (auto cache_elem = cache_.begin(); cache_elem != cache_.end(); cache_elem++)
            {
                if (hash_.find(cache_elem->key) != hash_.end())
                {
                    auto nearest_element_position = hash_[cache_elem->key].begin();

                    if (*nearest_element_position > max_distance)
                    {
                        max_distance = *nearest_element_position;

                        erasing_elem = cache_elem;
                    }
                }

                else
                {
                    erasing_elem = cache_elem;

                    break;
                }
            }

            return erasing_elem;
        }

        void UpdateElementDistance(KeyT key)
        {
            hash_[key].pop_front();

            if (hash_[key].size() == 0)
                hash_.erase(key);
        }

        template<typename F>
        void PushNewElement(F slow_get_page, KeyT key)
        {
            cache_.push_back({slow_get_page(key), key});
        }

        void Dump() const
        {
            std::cout << "\n//====================LFU Dump====================//\n";
            
            std::cout << "\t\tCapacity is: " << capacity_     << "\n";
            
            std::cout << "\t\tSize is: "     << cache_.size() << "\n";

            std::cout << "\t\tCache: \n";

            for (auto x: cache_)
            {
                auto hit = hash_.find(x.key);
                std::cout << "Element is " << x.key << std::endl;
            }

            std::cout << "\t\t" << "Total hits " << hits_ << std::endl;

            std::cout << "//====================End Dump====================//\n\n";
        }
};

}

//==========================================================================================//

#endif