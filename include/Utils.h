#ifndef UTILS_H
#define UTILS_H

#include <algorithm> 

template<typename T>
T clamp(T val, T minVal, T maxVal) {
    return std::max(minVal, std::min(val, maxVal));
}

#endif
