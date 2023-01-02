/// @file    pa16.cpp
/// @author  Thien Nguyen thiennguyen@.csn.edu
/// @date    5/7/22
/// @note    I pledge my word of honor that
///          I have abided by the the CSN Academic Integrity Policy
///          while completing this assignment.
///
/// @brief   This assignment measures the time it takes
///          to search and sort various sort techniques.
/// @note    People who helped: Kevin, William, and me.
/// @cite    https://www.geeksforgeeks.org/int_max-int_min-cc-applications/
/// @cite    https://www.geeksforgeeks.org/bubble-sort/
/// @cite    https://www.techiedelight.com/selection-sort-iterative-recursive/
/// @cite    https://www.techiedelight.com/insertion-sort-iterative-recursive/
/// @cite    https://www.techiedelight.com/merge-sort-singly-linked-list/
/// @cite    https://www.techiedelight.com/binary-search/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <chrono>
#include <numeric>
#include <random>
#include <iomanip>
#include <limits>
#include <climits>
#include <cassert>
#include <string>
#include <fstream>

using namespace std;
using namespace chrono;
using iterator = typename vector<int>::iterator;

ofstream fout;

/// Helper functions
template <typename Container>
void populate(Container &vec);

template <typename Container>
void again(Container &v1, Container &v2, Container &v3, Container &v4, Container &v5);

template <typename Container>
void formatted(Container &v1, Container &v2, Container &v3, Container &v4, Container &v5, int number);

/// Searching functions
template <typename Iter, typename T>
Iter linear_search(Iter first, Iter last, const T &a);

template <typename Iter, typename T>
Iter bin_search(Iter first, Iter last, const T &a);

// Wrapper functions to match signature of funct_t
template <typename Iter>
void seqsearch(Iter first, Iter last)
{
    linear_search(first, last, INT_MIN);
}

template <typename Iter>
void binsearch(Iter first, Iter last)
{
    binary_search(first, last, INT_MIN);
}

/// soring functions
template <typename Iter>
void bubble_sort(Iter first, Iter last);

template <typename Iter>
void selection_sort(Iter first, Iter last);

template <typename Iter>
void insertion_sort(Iter first, Iter last);

template <typename Iter>
void merge_sort(Iter first, Iter last);

template <typename Iter>
void quick_sort(Iter first, Iter last);

/// formatted functions
template <typename Iter>
double measure_time(Iter first, Iter last, int number);

/// Extra_functions I wrote, to see if work
template <typename Container>
void selection_sort_recursive(Container &v, int i);

template <typename Container>
void bubble_sort_recursive(Container &v, int n);

template <typename Container>
void insertion_sort_recursive(Container &v, int i);

template <typename Container>
int binary_search_recursive(Container &v, int a, int first, int last);

template <class Iter, class Container>
double sort_time(void sort_name(Iter, Iter), Container v);

/// --------------------------------------------------  END

void header();

int main()
{
    fout.open("output.txt");
    fout << std::setprecision(5) << std::fixed;
    // --------------------------------------------------  PREP

    std::vector<int> vector_1(10000);
    std::vector<int> vector_2(20000);
    std::vector<int> vector_3(40000);
    std::vector<int> vector_4(80000);
    std::vector<int> vector_5(160000);

    populate(vector_1);
    populate(vector_2);
    populate(vector_3);
    populate(vector_4);
    populate(vector_5);

    header();

    // --------------------------------------------------  START

    fout << std::left << std::setw(20) << "Linear Search";

    formatted(vector_1, vector_2, vector_3, vector_4, vector_5, 1);

    fout << std::left << std::setw(20) << "Binary Search";

    formatted(vector_1, vector_2, vector_3, vector_4, vector_5, 2);

    fout << std::left << std::setw(20) << "Bubble Sort";

    again(vector_1, vector_2, vector_3, vector_4, vector_5);
    formatted(vector_1, vector_2, vector_3, vector_4, vector_5, 3);

    fout << std::left << std::setw(20) << "Selection Sort";

    again(vector_1, vector_2, vector_3, vector_4, vector_5);
    formatted(vector_1, vector_2, vector_3, vector_4, vector_5, 4);

    fout << std::left << std::setw(20) << "Insertion Sort";

    again(vector_1, vector_2, vector_3, vector_4, vector_5);
    formatted(vector_1, vector_2, vector_3, vector_4, vector_5, 5);

    fout << std::left << std::setw(20) << "Merge Sort";

    again(vector_1, vector_2, vector_3, vector_4, vector_5);
    formatted(vector_1, vector_2, vector_3, vector_4, vector_5, 6);

    fout << std::left << std::setw(20) << "Quick Sort";

    again(vector_1, vector_2, vector_3, vector_4, vector_5);
    formatted(vector_1, vector_2, vector_3, vector_4, vector_5, 7);

    fout << std::left << std::setw(20) << "std::sort";

    again(vector_1, vector_2, vector_3, vector_4, vector_5);
    formatted(vector_1, vector_2, vector_3, vector_4, vector_5, 8);

    fout << "\nTimes reported in seconds\n";

    fout.close();
    return EXIT_SUCCESS;
}

void header()
{ // print the header
    fout << std::setw(27) << "10000"
         << std::setw(13) << "20000"
         << std::setw(13) << "400000"
         << std::setw(14) << "800000"
         << std::setw(13) << "1600000\n"
         << std::string(79, '-') << std::endl;
}

/// @paragraph This function populates a vector with random numbers
/// @param[in] vec is the vector to be populated
template <typename Container>
void populate(Container &vec)
{
    std::iota(vec.begin(), vec.end(), 0);
}

/// @paragraph This function resets a vector to random unosrted
/// @param[in] v is the vector to be reset
template <typename Container>
void again(Container &v1, Container &v2, Container &v3,
           Container &v4, Container &v5)
{
    std::shuffle(v1.begin(), v1.end(),
                 std::default_random_engine(std::random_device{}()));

    std::shuffle(v2.begin(), v2.end(),
                 std::default_random_engine(std::random_device{}()));

    std::shuffle(v3.begin(), v3.end(),
                 std::default_random_engine(std::random_device{}()));

    std::shuffle(v4.begin(), v4.end(),
                 std::default_random_engine(std::random_device{}()));

    std::shuffle(v5.begin(), v5.end(),
                 std::default_random_engine(std::random_device{}()));
}

template <typename Container>
void formatted(Container &v1, Container &v2, Container &v3,
               Container &v4, Container &v5, int number)
{
    fout << std::right
         << std::setw(7) << measure_time(v1.begin(), v1.end(), number)
         << std::setw(13) << measure_time(v2.begin(), v2.end(), number)
         << std::setw(13) << measure_time(v3.begin(), v3.end(), number)
         << std::setw(13) << measure_time(v4.begin(), v4.end(), number)
         << std::setw(13) << measure_time(v5.begin(), v5.end(), number)
         << std::endl
         << std::flush;
}

/// @paragraph Search the vector using a linear search.
/// @param first First element of the vector
/// @param last Last element of the vector
/// @param a The value to search for.
/// @return The index of the value in the vector.
template <typename Iter, typename T>
Iter linear_search(Iter first, Iter last, const T &a)
{ // search for the value in the vector
    auto position = last;

    for (; first != last && position == last; ++first)
    {
        if (*first == a)
        {
            position = first;
        }
    }

    return position;
}

template <typename Iter, typename T>
Iter bin_search(Iter first, Iter last, const T &a)
{ // search for the value in the vector
    assert(is_sorted(first, last));

    auto position = last;

    while (first < last && position == last)
    { // find the median value between the Iterators first and last
        const auto mid = next(first, distance(first, last) / 2);

        // divide and conquer
        if (*mid == a)
        { // found the a
            position = mid;
        }
        else if (*mid < a)
        { // search the right half
            first = mid + 1;
        }
        else
        { // search the left half
            last = mid;
        }
    }

    return position;
}

/// @paragraph Sort the vector using bubble sort.
/// @param v The vector to sort.
template <typename Iter>
void bubble_sort(Iter first, Iter last)
{ // sort the vector using bubble sort
    for (auto i = first; i != last; ++i)
    { // iterate through the range [first, last)
        for (auto j = first; j != i; ++j)
        { // iterate through the range [first, last)
            if (*j > *i)
            { // swap the elements
                swap(*j, *i);
            }
        }
    }
}

/// @paragraph Sort the vector using a selection sort
/// @param v The vector to sort.
template <typename Iter>
void selection_sort(Iter first, Iter last)
{ // sort the vector using selection sort
    for (; first != last; ++first)
    {
        swap(*first, *min_element(first, last));
    }
}

/// @paragraph Sort the vector using an insertion sort.
/// @param v The vector to sort.
template <typename Iter>
void insertion_sort(Iter first, Iter last)
{ // sort the vector using insertion sort
    if (first != last)
    {
        swap(*first, *min_element(first, last));

        for (auto i = first; ++i < last; first = i)
        {
            for (auto j = i; *j < *first; --j, --first)
            {
                swap(*j, *first);
            }
        }
    }
}

/// @paragraph Sort the vector using a merge sort.
/// @param first The index of the first element in the vector.
/// @param last The index of the last element in the vector.
template <typename Iter>
void merge_sort(Iter first, Iter last)
{ // merge the two vectors
    const auto size = distance(first, last);

    if (size > 1)
    { // divide the range [first, last) into two halves
        const auto middle = next(first, size / 2);

        merge_sort(first, middle);
        merge_sort(middle, last);
        inplace_merge(first, middle, last);
    }
}

/// @brief Quick sort the vector
/// @param first The index of the first element in the vector.
/// @param last The index of the last element in the vector.
template <typename Iter>
void quick_sort(Iter first, Iter last)
{ // sort the vector using quick sort
    if (distance(first, last) > 1)
    { // left  end   of current partition
        // right end   of current partition
        // the   pivot of the current partition
        auto left = first;
        auto right = last;
        auto pivot = left++;

        while (left < right)
        { // reorder elements in the range [first, last)
            if (*left < *pivot)
            {
                ++left;
            }
            else
            {
                while (left != right && *pivot < *right)
                {
                    --right;
                }
                swap(*left, *right);
            }
        }

        --left;

        swap(*pivot, *left);

        quick_sort(first, left);
        quick_sort(right, last);
    }
}

template <typename Iter>
double measure_time(Iter first, Iter last, int number)
{ // start the clock
    auto start = high_resolution_clock::now();

    // switch case for all sort techniques we have implemented
    switch (number)
    {
    case 1:
        seqsearch(first, last);
        // linear_search(first, last, INT_MAX);
        break;
    case 2:
        // binsearch(first, last);
        bin_search(first, last, INT_MAX);
        break;
    case 3:
        bubble_sort(first, last);
        break;
    case 4:
        selection_sort(first, last);
        break;
    case 5:
        insertion_sort(first, last);
        break;
    case 6:
        merge_sort(first, last);
        break;
    case 7:
        quick_sort(first, last);
        break;
    case 8:
        std::sort(first, last);
        break;
    default:
        break;
    }

    auto stop = high_resolution_clock::now();

    return duration_cast<microseconds>(stop - start).count() / 1'000'000.0;
}

/// @paragraph Sort the vector using a selection sort
/// @param v The vector to sort.
/// @param i The index to start from, and increment to the end
///          serve as a starting point
/// @brief   return in void is not good but I'm too lazy to even change the if
template <typename Container>
void selection_sort_recurisve(Container &v, int i)
{ // sort the vector using selection sort
    if (i == v.size() - 1)
    {
        return;
    }

    int min = i;
    for (int j = i + 1; j < v.size(); j++)
    { // find the smallest element
        if (v[j] < v[min])
        { // if the smallest element is found,
            min = j;
        }
    }
    // swap the smallest element with the current element
    // on top of the vector
    std::swap(v[i], v[min]);

    // recursively call the function
    selection_sort_recursive(v, i + 1);
}

/// @paragraph Sort the vector using buble sort recursively
/// @param v The vector to sort.
/// @param n The vector size
template <typename Container>
void bubble_sort_recursive(Container &v, int n)
{ // sort the vector using bubble sort
    for (int i = 0; i < n - 1; i++)
    { // for each element in the vector
        if (v[i] > v[i + 1])
        { // if the element is bigger than the next element
            std::swap(v[i], v[i + 1]);
        }
    }
    // recursively call the function and we move toward the base case
    if (n - 1 > 1)
    {
        bubble_sort_recursive(v, n - 1);
    }
}

/// @paragraph Sort the vector using insertion sort recursively
/// @param v The vector to sort.
/// @param i The index to start from, and increment to the end
///          serve as a breaking point, since 0 is already sorted
///          we start at 1
template <typename Container>
void insertion_sort_recursive(Container &v, int i)
{ // sort the vector using insertion sort
    int j = i;
    int temp = v[i];
    while (j > 0 && v[j - 1] > temp)
    { // while the element is smaller than the previous
        v[j] = v[j - 1];
        j--;
    }
    v[j] = temp;

    // recursively call the function
    if (i + 1 <= v.size() - 1)
    {
        insertion_sort_recursive(v, i + 1);
    }
}

/// @paragraph   Search the vector using binary search
/// @param v     The vector to search
/// @param a     The element to search for
/// @param first The first element of Container
/// @param last  The last element of Container
/// @return      The index of the element
template <typename Container>
int binary_search_recursive(Container &v, int a, int first, int last)
{ // search for the value in the vector
    int mid = (first + last) / 2;

    if (v[mid] == a)
    { // if the value is found, return the index
        return mid;
    }
    else if (v[mid] < a)
    { // if the value is greater than the midpoint
        return binary_search_recursive(v, a, mid + 1, last);
    }
    else
    { // if the value is less than the midpoint
        return binary_search_recursive(v, a, first, mid - 1);
    }

    return -1;
}

template <class Iter, class Container>
double sort_time(void sort_name(Iter, Iter), Container v)
{ // measure the time for each sort
    auto start = high_resolution_clock::now();

    // sort the vector
    sort_name(v.begin(), v.end());

    auto stop = high_resolution_clock::now();

    return duration_cast<microseconds>(stop - start).count() / 1000000.0;
}

// // TODO: add heapsort and introsort
