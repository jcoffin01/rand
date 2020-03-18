#pragma once
#include <algorithm>
#include <array>
#include <random>

#pragma once

#include <algorithm>
#include <array>
#include <random>

namespace {

// A SeedSeq class that ignores its input, and just generates random data from
// `std::random_device`. Intended primarily for non-deterministic
// implementations of `std::random_device` (which is pretry much anything except
// MinGW < 9. If you want to just hash (or whatever) the input to get
// reproducible output, you probably want std::seed_seq instead. This is for the
// more common case of wanting a seed that's actually random.
template<class Gen>
class simple_seed
{
  std::vector<uint_least32_t> original_data;

public:
  template<class It>
  void generate(It begin, It end)
  {
    // Save original data, since `param` might be called to retrieve it later.
    std::copy(begin, end, std::back_inserter(original_data));
    std::random_device rd;
    std::generate(begin, end, std::ref(rd));
  }

  simple_seed& operator=(simple_seed const&) = delete;

  size_t size() const { return Gen::state_size; }

  template<class OutIt>
  void param(OutIt dest) const
  {
    std::copy(original_data.begin(), original_data.end(), dest);
  }
};
} // namespace

template<class Int, class Gen = std::mt19937>
class generator
{
  Gen gen;
  std::uniform_int_distribution<Int> dist;

public:
  generator(Int low, Int high)
    : gen(simple_seed<Gen>())
    , dist(low, high)
  {}
  generator(Int high)
    : gen(simple_seed<Gen>())
    , dist(0, high)
  {}
  int operator()() { return dist(gen); }
};
