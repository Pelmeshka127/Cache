#ifndef LFU_HPP_
#define LFU_HPP_

#include <list>
#include <unordered_map>
#include <iterator>
#include <iostream>
#include <fstream>

//==========================================================================================//

namespace lfu
{

template<typename PageT, typename KeyT = int>
class cache_t 
{
    private:
        std::size_t capacity_;

        std::size_t hits_;
        
        struct CacheNode
        {
            PageT   data;
            size_t  hit_count;
            KeyT    key;
        };

        std::list<CacheNode> cache_;

        using ListIterator = typename std::list<CacheNode>::iterator;
        
        std::unordered_map<KeyT, ListIterator> hash_;

        using HashIterator = typename std::unordered_map<KeyT, ListIterator>::iterator;
    
    public:
        cache_t(size_t sz): capacity_{sz},  hits_{0} {};

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
                    DeleteMinCounting();

                PushFront(key, slow_get_page);

                SortCache();

                return false;

            }

            else
            {
                AddNewHit(hit);

                SortCache();

                return true;
            }
        }

        void DeleteMinCounting()
        {
            hash_.erase(cache_.back().key);

            cache_.pop_back();
        }

        template<typename F>
        void PushFront(KeyT key, F slow_get_page)
        {
            cache_.push_front({slow_get_page(key), 0, key});

            hash_.emplace(key, cache_.begin());
        }

        void AddNewHit(HashIterator hit)
        {
            hits_++;

            hit->second->hit_count++;
        }

        void SortCache()
        {
            for(ListIterator i = cache_.begin(); i != std::prev(cache_.end()); i++)
            {
                if (i->hit_count < std::next(i)->hit_count)
                {
                    hash_[i->key] = std::next(i);

                    hash_[std::next(i)->key] = i;

                    std::swap(*i, *std::next(i));
                }
            }
        }

        void Dump() const
        {
            std::cout << "\n//====================LFU Dump====================//\n";
            
            std::cout << "\t\tCapacity is: " << capacity_     << "\n";
            
            std::cout << "\t\tSize is: "     << cache_.size() << "\n";

            std::cout << "\t\tCache: \n";

            int i = 0;
            
            for (auto x: cache_){
                std::cout << "\t\t" << i++ <<": key = " << x.key << ", hit_count = " << x.hit_count << "\n";
            }

            std::cout << "//====================End Dump====================//\n\n";
        }
};

}

//==========================================================================================//

#endif