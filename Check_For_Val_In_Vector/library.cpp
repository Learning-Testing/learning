#include "library.h"

#include <iostream>
#include <vector>
#include <algorithm>

template <class T>
T check_in_vector(T val, std::vector<T> vec)
{
    bool in_vector = (std::find(vec.begin(), vec.end(), val) != vec.end());
    return in_vector;
}
