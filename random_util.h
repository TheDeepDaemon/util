#ifndef RANDOM_UTIL_H
#define RANDOM_UTIL_H
#include<cstdint>
#include<random>
#include<array>
#include<vector>
#include<list>
#include<string>

using std::vector;
using std::string;

class Random {
private:
	inline static Random* instance = nullptr;

	std::mt19937_64 gen;
	std::normal_distribution<double> normalDist;

	Random() : normalDist(0.0, 1.0) {
		std::random_device rd;
		std::array<unsigned, std::mt19937::state_size> seed;
		std::generate_n(seed.data(), seed.size(), std::ref(rd));
		std::seed_seq seeds(std::begin(seed), std::end(seed));
		gen.seed(seeds);
	}

public:

	static void init() {
		instance = new Random();
	}

	static void destroy() {
		if (instance != nullptr) {
			delete instance;
		}
	}

	static uint64_t randInt(const uint64_t ceil_) {
		return instance->gen() % ceil_;
	}

	static uint64_t randInt(const uint64_t floor_, const uint64_t ceil_) {
		return floor_ + (instance->gen() % (ceil_ - floor_));
	}

	static double randDouble() {
		return (double)instance->gen() / (double)instance->gen.max();
	}

	static double randDouble(const double floor_, const double ceil_) {
		return floor_ + (randDouble() * (ceil_ - floor_));
	}

	static double randNormal() {
		return instance->normalDist(instance->gen);
	}

	template<typename T>
	static void shuffle(std::vector<T>& vec) {
		std::shuffle(vec.begin(), vec.end(), instance->gen);
	}

	template<typename T>
	static void shuffle(std::list<T>& ls) {
		std::shuffle(ls.begin(), ls.end(), instance->gen);
	}

	static void shuffle(std::string& str) {
		std::shuffle(str.begin(), str.end(), instance->gen);
	}

	template<typename T>
	static std::vector<T> randVec(const size_t size, const uint64_t floor_, const uint64_t ceil_) {
		_ASSERT(ceil_ > floor_);
		std::vector<T> vec;
		vec.reserve(size);
		for (size_t i = 0; i < size; i++) {
			vec.emplace_back(T(floor_ + randInt(ceil_ - floor_)));
		}
	}

	template<typename T>
	static std::vector<T> randVec(const size_t size, const uint64_t ceil_) {
		std::vector<T> vec;
		vec.reserve(size);
		for (size_t i = 0; i < size; i++) {
			vec.emplace_back(T(randInt(ceil_)));
		}
	}

	template<typename T>
	static std::string randStr(const size_t size, const char floor_, const char ceil_) {
		_ASSERT(ceil_ > floor_);
		std::string str;
		str.reserve(size);
		for (size_t i = 0; i < size; i++) {
			str.push_back(T(floor_ + randInt(ceil_ - floor_)));
		}
		return str;
	}

	template<typename T>
	static T randomChoice(const std::vector<T>& vec) {
		return vec[randInt(vec.size())];
	}

	static vector<uint8_t> genRandBytes(const uint64_t numBytes) {
		vector<uint8_t> bytes;
		bytes.reserve(numBytes);
		for (uint64_t i = 0; i < numBytes; i++) {
			const uint8_t byte = (uint8_t)Random::randInt(UINT8_MAX + 1);
			bytes.emplace_back(byte);
		}
		return bytes;
	}

};


#endif // !RANDOM_UTIL_H