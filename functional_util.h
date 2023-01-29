#ifndef FUNCTIONAL_UTIL_H
#define FUNCTIONAL_UTIL_H
#include<vector>
#include<algorithm>
#include<random>


// return vin after transforming it using mapping
template<typename T, typename U>
inline std::vector<T> vmap(const std::vector<U>& vin, T(*mapping)(const U&)) {
	std::vector<T> vout;
	vout.reserve(vin.size());
	for (size_t i = 0; i < vin.size(); i++) {
		vout.push_back(mapping(vin[i]));
	}
	return vout;
}


// return vin after transforming it using mapping
template<typename T, typename U>
inline std::vector<T> vmap(const std::vector<U>& vin, T(*mapping)(U)) {
	std::vector<T> vout;
	vout.reserve(vin.size());
	for (size_t i = 0; i < vin.size(); i++) {
		vout.push_back(mapping(vin[i]));
	}
	return vout;
}


// transform vin using mapping and store the result in vout
template<typename T, typename U>
inline void vmap(std::vector<T>& vout, const std::vector<U>& vin, T(*mapping)(const U&)) {
	_ASSERT(vout.size() == vin.size());
	for (size_t i = 0; i < vin.size(); i++) {
		vout[i] = mapping(vin[i]);
	}
}


template<typename T, typename U>
inline std::vector<std::pair<T, U>> zip(const std::vector<T>& vec1, const std::vector<U>& vec2) {
	uint64_t size = std::min(vec1.size(), vec2.size());
	std::vector<std::pair<T, U>> vout;
	vout.reserve(vec1.size());
	for (uint64_t i = 0; i < size; i++) {
		vout.push_back(std::pair<T, U>(vec1[i], vec2[i]));
	}
	return vout;
}



template<typename T>
inline void concat(std::vector<T>& v1, const std::vector<T>& v2) {
	v1.insert(v1.end(), v2.begin(), v2.end());
}



template<typename T>
inline std::vector<T> filter(const std::vector<T>& vin, bool(*filterFunc)(const T&)) {
	std::vector<T> vout;
	vout.reserve(vin.size());
	for (size_t i = 0; i < vin.size(); i++) {
		if (filterFunc(vin[i])) {
			vout.push_back(vin[i]);
		}
	}
	return vout;
}


template<typename T>
inline std::vector<T> filter(const std::vector<T>& vin, bool(*filterFunc)(T)) {
	std::vector<T> vout;
	vout.reserve(vin.size());
	for (size_t i = 0; i < vin.size(); i++) {
		if (filterFunc(vin[i])) {
			vout.push_back(vin[i]);
		}
	}
	return vout;
}


inline std::vector<uint64_t> getPermutationVector(const uint64_t size) {
	std::vector<uint64_t> permutation(size);
	for (uint64_t i = 0; i < size; i++) {
		permutation[i] = i;
	}
	return permutation;
}


template<typename T>
inline std::vector<T> getPermutationVector(const uint64_t size) {
	std::vector<T> permutation(size);
	for (uint64_t i = 0; i < size; i++) {
		permutation[i] = T(i);
	}
	return permutation;
}


inline std::vector<uint64_t> getRandomPermutation(uint64_t size) {
	std::vector<uint64_t> permutation = getPermutationVector(size);
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::shuffle(permutation.begin(), permutation.end(), gen);
	return permutation;
}


template<typename T>
inline bool areEqual(const std::vector<T>& vec1, const std::vector<T>& vec2) {
	if (vec1.size() != vec2.size()) {
		return false;
	}

	for (uint i = 0; i < vec1.size(); i++) {
		if (vec1[i] != vec2[i]) {
			return false;
		}
	}

	return true;
}


#endif