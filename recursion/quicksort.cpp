#include "recursion.h"

template <class T>
void Swap(std::vector<T> & data, size_t a, size_t b)
{
    T tmp = data[a];
    data[a] = data[b];
    data[b] = tmp;
}

template <class T>
size_t Partition(std::vector<T> & data, size_t from, size_t to, size_t pivot)
{
	Swap(data, from, pivot);

    size_t i = from + 1;
    size_t j = from + 1;

    while ( i < to )
    {
        if (data[i] < data[from])
        {
			Swap(data, j, i);
            j++;
        }
        i++;
    }

    Swap(data, j-1, from);

    return j-1;
}

template <class T>
void QuicksortRec(std::vector<T> & data, size_t from, size_t to)
{
    // base case
    if (from == to)
        return;

    // choose pivot
    size_t p = rand() % (to - from) + from;

    p = Partition(data, from, to, p);

	QuicksortRec(data, from, p);
	QuicksortRec(data, p+1, to);
}

template <class T>
void Quicksort(std::vector<T> & data)
{
	QuicksortRec(data, 0, data.size());
}
