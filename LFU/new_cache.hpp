#ifndef NEW_CACHE_HPP_
#define NEW_CACHE_HPP_

#include <iostream>
#include <list>
#include <unordered_map>
#include <iterator>
#include <fstream>
#include <ctime>

namespace new_cache
{

template<typename PageT, typename KeyT = int>
class new_cache_t
{
    private:
        const size_t capacity_;

        size_t size_;

        size_t hits_;

        struct FrequencyNode;

        using FrequencyIterator = typename std::list<FrequencyNode>::iterator;

        struct CacheNode {
            PageT               page;
            KeyT                key;
            FrequencyIterator   freq_iter;
        };

        struct FrequencyNode {
            size_t               hit_count = 0;
            std::list<CacheNode> sublist;
        };

        std::list<FrequencyNode> cache_;

        using ListIterator = typename std::list<CacheNode>::iterator;

        std::unordered_map<KeyT, ListIterator> hash_;

    public:
        new_cache_t(size_t capacity) : capacity_{capacity}, size_{0},  hits_{0} {}

        size_t GetHits() const
        {
            return hits_;
        }

        bool IsFull() const
        {
            return (capacity_ == size_);
        }

        bool IsEmpty() const
        {
            return (cache_.size() == 0);
        }

        template<typename F>
        bool LookUpUpdate(KeyT key, F slow_get_page)
        {
            auto hit = hash_.find(key);

            if (hit == hash_.end())
            {
                if (IsFull())
                    DeleteMinCounting(key);

                if (IsEmpty())
                    cache_.push_front({});

                if (cache_.front().hit_count != 0)
                    cache_.push_front({});

                PushNewElement(key, slow_get_page);
                
                return false;
            }

            else
            {
                hits_++;

                AddNewHit(hit->second);

                return true;
            }
        }

        template<typename F>
        void PushNewElement(KeyT key, F slow_get_page)
        {
            cache_.front().sublist.push_front({slow_get_page(key), key, cache_.begin()});

            hash_.emplace(key, cache_.front().sublist.begin());

            size_++;
        }

        void DeleteMinCounting(KeyT key)
        {
            hash_.erase(cache_.front().sublist.back().key);

            cache_.front().sublist.pop_back();

            size_--;
        }

        void AddNewHit(ListIterator iterator)
        {
            auto frequency     = iterator->freq_iter->hit_count;
            
            auto freq_iterator = iterator->freq_iter;

            if (freq_iterator == std::prev(cache_.end()))
                cache_.push_back({frequency + 1, {}});

            else if(std::next(freq_iterator)->hit_count != frequency + 1)
                cache_.insert(std::next(freq_iterator), {frequency + 1, {}});

            auto next_freq_iterator = std::next(freq_iterator);

            next_freq_iterator->sublist.splice(next_freq_iterator->sublist.begin(), freq_iterator->sublist, iterator);

            if (freq_iterator->sublist.size() == 0)
                cache_.erase(freq_iterator);

            freq_iterator = next_freq_iterator;
        }

        void Dump() const
        {
            std::cout << "\n//====================LFU Dump====================//\n";
            
            std::cout << "\t\tCapacity is: " << capacity_     << "\n";
            
            std::cout << "\t\tSize is: "     << cache_.size() << "\n";

            std::cout << "\t\tCache: \n";

            for (auto x: cache_)
            {
                std::cout << "\t\t" << "Hit Count " << x.hit_count << std::endl;
                    
                int i = 0;

                for (auto y: x.sublist)
                {
                    std::cout << "\t\t" << i++ <<": key = " << y.key << std::endl;
                }
            }

            std::cout << "//====================End Dump====================//\n\n";
        }
};

}

#endif