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

	template<typename T>
	static void swap(T* arr, const size_t i1, const size_t i2) {
		const T temp = arr[i1];
		arr[i1] = arr[i2];
		arr[i2] = temp;
	}

	template<typename T>
	static void swap(vector<T>& vec, const size_t i1, const size_t i2) {
		const T temp = vec[i1];
		vec[i1] = vec[i2];
		vec[i2] = temp;
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

	static uint64_t randInt() {
		return instance->gen();
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

	// the Fisher�Yates shuffle
	template<typename T>
	static void shuffle(T* arr, const uint64_t size) {
		if (size > 0) {
			for (size_t i = size - 1; i > 0; i--) {
				size_t r = instance->gen() % (i + 1);
				swap(arr, i, r);
			}
		}
	}

	template<typename T>
	static void shuffle(std::vector<T>& vec) {
		shuffle(vec.data(), vec.size());
	}

	static void shuffle(std::string& str) {
		std::shuffle(str.begin(), str.end(), instance->gen);
	}

	template<typename T>
	static std::vector<T> randIntVec(const size_t size, const uint64_t floor_, const uint64_t ceil_) {
		_ASSERT(ceil_ > floor_);
		std::vector<T> vec;
		vec.reserve(size);
		for (size_t i = 0; i < size; i++) {
			vec.emplace_back(T(randInt(floor_, ceil_)));
		}
	}

	template<typename T>
	static std::vector<T> randIntVec(const size_t size, const uint64_t ceil_) {
		std::vector<T> vec;
		vec.reserve(size);
		for (size_t i = 0; i < size; i++) {
			vec.emplace_back(T(randInt(ceil_)));
		}
		return vec;
	}

	template<typename T>
	static std::vector<T> randFloatVec(const size_t size, const double ceil_) {
		std::vector<T> vec;
		vec.reserve(size);
		for (size_t i = 0; i < size; i++) {
			vec.emplace_back(T(randDouble() * ceil_));
		}
		return vec;
	}

	template<typename T>
	static std::vector<T> randFloatVec(const size_t size, const double floor_, const double ceil_) {
		std::vector<T> vec;
		vec.reserve(size);
		for (size_t i = 0; i < size; i++) {
			vec.emplace_back(T(randDouble(floor_, ceil_)));
		}
		return vec;
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