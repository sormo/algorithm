#pragma once

#include <vector>
#include <string>

template <class T>
void Mergesort(std::vector<T> & data);

template <class T>
void Quicksort(std::vector<T> & data);

// explicit instantiation
template void Mergesort<int>(std::vector<int> & data);
template void Quicksort<int>(std::vector<int> & data);
template void Quicksort<unsigned int>(std::vector<unsigned int> & data);

std::string KaratsubaMultiply(const std::string& a, const std::string & b);

unsigned int CountNumberOfInversions(const std::vector<unsigned int> & arr);
