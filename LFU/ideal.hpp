#ifndef IDEAL_HPP_
#define IDEAL_HPP_

#include <iostream>
#include <list>
#include <unordered_map>
#include <iterator>
#include <vector>
#include <fstream>
#include <ctime>

//==========================================================================================//

namespace ideal_cache
{

template <typename PageT, typename KeyT = int>
class ideal_cache_t
{
    private:
        size_t capacity_;

        size_t hits_;
        
        struct UniqueCacheNode {
            KeyT                key;
            std::list<size_t>   location;
        };

        std::list<UniqueCacheNode> unique_array_;

        using UniqueKeyIterator = typename std::list<UniqueCacheNode>::iterator;

        std::unordered_map<KeyT, UniqueKeyIterator> unique_hash_;

    public:
        ideal_cache_t(const std::vector<KeyT>& array, size_t capacity) : capacity_{capacity}, hits_{0}
        {
            size_t array_index = 0;
            for (auto array_element = array.begin(); array_element != array.end(); array_element++)
            {
                auto find_element = unique_hash_.find(*array_element);
                if (find_element == unique_hash_.end())
                {
                    std::list<size_t> key_location = {array_index};

                    unique_array_.push_back({*array_element, key_location});

                    auto end_list = unique_array_.end();

                    end_list--;
                    
                    unique_hash_.emplace(*array_element, end_list);
                }

                else
                    find_element->second->location.push_back(size_t(std::distance(array.begin(), array_element)));

                array_index++;
            }
        }

    private:
        struct CacheNode {
            PageT   page;
            KeyT    key;
            size_t  distance;
        };

        std::list<CacheNode> cache_;

        using ListIterator = typename std::list<CacheNode>::iterator;

        std::unordered_map<KeyT, ListIterator> hash_;

        using HashIterator = typename std::unordered_map<KeyT, ListIterator>::iterator;

    public:
        size_t GetHits() const
        {
            return hits_;
        }

        bool IsFull() const
        {
            return (capacity_ == cache_.size());
        }

        template<typename F>
        bool LookUpUpdate(KeyT key, F slow_get_page)
        {
            auto hit = hash_.find(key);

            if (hit == hash_.end())
            {
                if (IsFull())
                {
                    DeleteMostFar();
                }

                PushNewElement(key, slow_get_page);

                return false;
            }

            else
            {
                AddNewHit(hit);

                UpdateDistance(hit, key);

                SortCache();

                return true;
            }
        }

        void DeleteMostFar()
        {
            hash_.erase(cache_.back().key);

            cache_.pop_back();
        }

        template<typename F>
        void PushNewElement(KeyT key, F slow_get_page)
        {   
            auto inserting_elem_iterator = unique_hash_.find(key);

            size_t distance = 0;

            if (inserting_elem_iterator->second->location.size() == 1)
            {
                cache_.push_back({slow_get_page(key), key, distance});

                ListIterator back_of_cache = cache_.end();

                back_of_cache--;

                hash_.emplace(key, back_of_cache);
            }

            else
            {
                inserting_elem_iterator->second->location.pop_front();

                distance = *inserting_elem_iterator->second->location.begin();    

                cache_.push_front({slow_get_page(key), key, distance});
            
                hash_.emplace(key, cache_.begin());

                SortCache();
            }
        }

        void AddNewHit(HashIterator hit)
        {
            hits_++;
        }

        void UpdateDistance(HashIterator hit, KeyT key)
        {
            auto old_element = unique_hash_.find(key);

            if (old_element->second->location.size() == 1)
            {
                cache_.erase(hit->second);
                
                hash_.erase(key);
            }

            else
            {
                old_element->second->location.pop_front();

                hit->second->distance = *old_element->second->location.begin();
            }
        }

        void SortCache()
        {
            for (ListIterator i = cache_.begin(); i != std::prev(cache_.end()); i++)
            {
                if ((i->distance > std::next(i)->distance) && (std::prev(cache_.end())->distance != 0))
                {
                    hash_[i->key] = std::next(i);

                    hash_[std::next(i)->key] = i;

                    std::swap(*i, *std::next(i));
                }
            }
        }

        void DumpArray()
        {
            for (auto elem : unique_array_)
            {
                std::cout << "Element is " << elem.key << std::endl;
                for (auto i : elem.location)
                {
                    std::cout << "Index in it's list " << i << std::endl;
                }
            }
        }

        void DumpCache()
        {
            std::cout << "\n//====================LFU Dump====================//\n";
            
            std::cout << "\t\tCapacity is: " << capacity_     << "\n";
            
            std::cout << "\t\tSize is: "     << cache_.size() << "\n";

            std::cout << "\t\tCache: \n";

            int i = 0;
            
            for (auto x: cache_){
                std::cout << "\t\t" << i++ <<": key = " << x.key << ", next element index = " << x.distance << ", hit count = " << x.hit_count << std::endl;
            }

            std::cout << "//====================End Dump====================//\n\n";
        }
};

}

//==========================================================================================//

#endif