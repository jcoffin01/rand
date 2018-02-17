#pragma once
#include <array>
#include <random>
#include <algorithm>

template <class Int>
class generator {
    template <class Rand> 
    class Seed {
        class seeder {
            std::array < std::random_device::result_type, Rand::state_size > rand_data;
        public:
            seeder() {
                std::random_device rd;
                std::generate(rand_data.begin(), rand_data.end(), std::ref(rd));
            }
    
            typename std::array < std::random_device::result_type, Rand::state_size >::iterator begin() { return rand_data.begin(); }
            typename std::array < std::random_device::result_type, Rand::state_size >::iterator end() { return rand_data.end(); }
        } seed;
    
        std::seed_seq s;
    
    public:
        Seed() : s(seed.begin(), seed.end()) { }
    
        template <class I>
        auto generate(I a, I b) { return s.generate(std::forward<I>(a), std::forward<I>(b)); }
    };

    using Rand = std::mt19937_64;
	Seed<Rand> seed;
    Rand rng;
    std::uniform_int_distribution<Int> uni;
public:
	explicit generator(Int high) : rng(seed), uni(0, high) {}
    generator(Int low, Int high) : rng(seed), uni(low, high) { }
    int operator()() { return uni(rng); }
};

