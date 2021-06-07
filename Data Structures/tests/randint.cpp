#include<random>

// Returns random integers between 0 and 100
int randint() { 
	static const size_t seed { 15122000 };
	static const size_t upper{ 100 }, lower{ 0 }; 
	static std::mt19937 rand_gen {seed};
	static std::uniform_int_distribution<int> range {lower , upper} ;
	return range( rand_gen );
}
