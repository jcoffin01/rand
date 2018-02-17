### easy-rand

This is a wrapper for the random number generation classes that C++11 
(and later) provide in `<random>`. It attempts to make it relatively 
easy to generate decent random numbers. To that end, it used mt19937_64,
and seeds it with numbers from `std::random_device`. Contrary to the way 
many people do this, however, it extracts a number of random numbers, 
and uses them to initialize the entire state of the generator, instead
of using a single call, which will tpyically seed the generator with
only 32 bits of data, severly limiting the randomness it can provide.

This also includes a wrapper for a uniform_integer range, so it's easy 
to get integers within a specified range.
