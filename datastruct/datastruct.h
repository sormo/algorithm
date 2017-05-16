#pragma once
#include <vector>

template <class T>
std::vector<T> MedianMaintenance(const std::vector<T> & data);

// explicit instantiation
template std::vector<int> MedianMaintenance<int>(const std::vector<int> & data);
