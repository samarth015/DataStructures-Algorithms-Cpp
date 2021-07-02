#include<random>

// Returns random integers between 0 and 100
template<std::size_t lower = 0, std::size_t upper = 100, std::size_t seed = 15122000>
int randint() { 
	static std::mt19937 rand_gen {seed};
	static std::uniform_int_distribution<int> range {lower , upper} ;
	return range( rand_gen );
}
