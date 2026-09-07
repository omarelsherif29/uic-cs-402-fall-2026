


#include <iostream>
#include <algorithm>
#include <chrono>
#include <concepts>
#include <type_traits>

#include "testing.h"
#include "Omar_Elsherif_project1.h"

using namespace std;

/****************
 * INSTRUCTIONS *
 ****************
 *
 * - Replace all instances of "Firstname_Lastname" with your firstname and
 *   your last name. This include the .h and .cpp files, along with the
 *   header guards at the top of the .h file.
 *
 * - Implement the appropriate algorithms as described below.
 *   You must follow the specifications as written
 *   below (e.g., stability, in-place, etc.).
 *
 * - DO NOT MODIFY THE FUNCTION SIGNATURES!!!
 *
 * - You are allowed to add helper functions. Be sure to add the appropriate
 *   function prototypes in "Fistname_Lastname_project1.h".
 *
 * - The file "testing.cpp" has various functions you can utilize to test
 *   your code. You can also add your own tests!
 *
 * - If you are working in a group, please modify the comments directly below.
 *
 */


/** This please add your name here as well **/
const std::string who_am_i() {
    return "Omar_Elsherif";
}


/* Bubble Sort 
 *
 * 5 points
 * 
 * Algorithm: Continuously compare adjacent elements and swap them if necessary.
 *            This is a stable, in-place sorting algorithm. Your implementation must be in-place.
 *
 * Parameters:
 *  vector<T> &list: reference to a list of type T. You can assume this type
 *                   has all of the normal binary comparison operators such
 *                   as <, >, ==, !=, etc.
 *  bool decending:  if true, then sort in descending order; otherwise sort
 *                   in ascending order (the default)
 * */
template<typename T>
void bubble_sort(vector<T> &list, bool descending) {
   size_t n = list.size();
    if (n < 2) return;

    for (size_t i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (size_t j = 0; j < n - 1 - i; ++j) {
            bool should_swap = descending ? (list[j] < list[j + 1]) 
                                          : (list[j] > list[j + 1]);
            if (should_swap) {
                std::swap(list[j], list[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

/* Selection Sort 
 *
 * 5 points
 * 
 * Algorithm: Continuously finds the minimium (or maximum) element in the list, 
 *            then swaps it with the first non-sorted element of the list.
 *            This is an unstable, in-place sorting algorithm. 
 *            Your implementation must be in-place.
 *
 * Parameters:
 *  vector<T> &list: reference to a list of type T. You can assume this type
 *                   has all of the normal binary comparison operators such
 *                   as <, >, ==, !=, etc.
 *  bool decending:  if true, then sort in descending order; otherwise sort
 *                   in ascending order (the default)
 * */
template<typename T>
void selection_sort(vector<T> &list, bool descending) {
    size_t n = list.size();
    if (n < 2) return;

    for (size_t i = 0; i < n - 1; ++i) {
        size_t target_idx = i;
        for (size_t j = i + 1; j < n; ++j) {
            bool is_better = descending ? (list[j] > list[target_idx])
                                        : (list[j] < list[target_idx]);
            if (is_better) {
                target_idx = j;
            }
        }
        if (target_idx != i) {
            std::swap(list[i], list[target_idx]);
        }
    }
}

/* Insertion Sort 
 *
 * 5 points
 * 
 * Algorithm: Iterates through the list and inserts the current element into
 *            the correct sorted position of the prefix of the list.
 *            This is a stable, in-place sorting algorithm. Your implementation
 *            does not need to be in-place.
 *
 * Parameters:
 *  vector<T> &list: reference to a list of type T. You can assume this type
 *                   has all of the normal binary comparison operators such
 *                   as <, >, ==, !=, etc.
 *  bool decending:  if true, then sort in descending order; otherwise sort
 *                   in ascending order (the default)
 * */
template<typename T>
void insertion_sort(vector<T> &list, bool descending) {
    size_t n = list.size();
    if (n < 2) return;

    for (size_t i = 1; i < n; ++i) {
        T key = list[i];
        int j = static_cast<int>(i) - 1;

        if (descending) {
            while (j >= 0 && list[j] < key) {
                list[j + 1] = list[j];
                --j;
            }
        } else {
            while (j >= 0 && list[j] > key) {
                list[j + 1] = list[j];
                --j;
            }
        }
        list[j + 1] = key;
    }
}


/* Quicksort 
 *
 * 10 points
 * 
 * Algorithm: Sorts by first choosing a random pivot from the list, then 
 *            partitioning the list into two halves with respect to the 
 *            pivot, then recursing on each half.
 *            This is an unstable sorting algorithm. Not required to be
 *            implemented as an in-place sort.
 *            
 *
 * Parameters:
 *  vector<T> &list: reference to a list of type T. You can assume this type
 *                   has all of the normal binary comparison operators such
 *                   as <, >, ==, !=, etc.
 *  bool decending:  if true, then sort in descending order; otherwise sort
 *                   in ascending order (the default)
 *
 * */
template<typename T>
void quicksort_helper(vector<T> &list, int low, int high, bool descending) {
    if (low >= high) return;

    T pivot = list[low + (high - low) / 2];
    int i = low;
    int j = high;

    while (i <= j) {
        if (descending) {
            while (list[i] > pivot) ++i;
            while (list[j] < pivot) --j;
        } else {
            while (list[i] < pivot) ++i;
            while (list[j] > pivot) --j;
        }

        if (i <= j) {
            std::swap(list[i], list[j]);
            ++i;
            --j;
        }
    }

    if (low < j) quicksort_helper(list, low, j, descending);
    if (i < high) quicksort_helper(list, i, high, descending);
}

template<typename T>
void quicksort(vector<T> &list, bool descending) {
    if (list.size() < 2) return;
    quicksort_helper(list, 0, static_cast<int>(list.size()) - 1, descending);
}



/* Merge Sort 
 *
 * 10 points
 * 
 * Algorithm: Sorts the list by recursively sorting the left and right
 *            halves, then merging the two left and right halves together.
 *            This is a stable sorting algorithm. Not required to be implemented
 *            as an in-place sort.
 *
 * Parameters:
 *  vector<T> &list: reference to a list of type T. You can assume this type
 *                   has all of the normal binary comparison operators such
 *                   as <, >, ==, !=, etc.
 *  bool decending:  if true, then sort in descending order; otherwise sort
 *                   in ascending order (the default)
 *
 * */
template<typename T>
void merge_sublists(vector<T> &list, size_t l_idx, size_t m_idx, size_t r_idx, bool descending) {
    vector<T> temp;
    temp.reserve(r_idx - l_idx + 1);

    size_t i = l_idx;
    size_t j = m_idx + 1;

    while (i <= m_idx && j <= r_idx) {
        bool take_left = descending ? (list[i] >= list[j]) 
                                    : (list[i] <= list[j]);
        if (take_left) {
            temp.push_back(list[i++]);
        } else {
            temp.push_back(list[j++]);
        }
    }

    while (i <= m_idx) temp.push_back(list[i++]);
    while (j <= r_idx) temp.push_back(list[j++]);

    for (size_t k = 0; k < temp.size(); ++k) {
        list[l_idx + k] = temp[k];
    }
}

template<typename T>
void merge_sort_helper(vector<T> &list, size_t l_idx, size_t r_idx, bool descending) {
    if (l_idx >= r_idx) return;
    size_t m_idx = l_idx + (r_idx - l_idx) / 2;

    merge_sort_helper(list, l_idx, m_idx, descending);
    merge_sort_helper(list, m_idx + 1, r_idx, descending);
    merge_sublists(list, l_idx, m_idx, r_idx, descending);
}

template<typename T>
void merge_sort(vector<T> &list, bool descending) {
    if (list.size() < 2) return;
    merge_sort_helper(list, 0, list.size() - 1, descending);
}


/* Your Hybrid Sort
 *
 * 20 points
 *
 * Algorithm: Your own custom Hybrid Sorting algorithm! Remember, a hybrid
 *            sort tries to take advantage of two (or more) sorting algorithms
 *            to speed up data processing.
 *
 * Parameters:
 *  vector<T> &list: reference to a list of type T. You can assume this type
 *                   has all of the normal binary comparison operators such
 *                   as <, >, ==, !=, etc.
 *  bool decending:  if true, then sort in descending order; otherwise sort
 *                   in ascending order (the default)
 *
 */
template<typename T>
void hybrid_sort_helper(vector<T> &list, int low, int high, bool descending) {
    while (low < high) {
        if (high - low < 16) {
            // Insertion sort for small sub-arrays
            for (int i = low + 1; i <= high; ++i) {
                T key = list[i];
                int j = i - 1;
                if (descending) {
                    while (j >= low && list[j] < key) {
                        list[j + 1] = list[j];
                        --j;
                    }
                } else {
                    while (j >= low && list[j] > key) {
                        list[j + 1] = list[j];
                        --j;
                    }
                }
                list[j + 1] = key;
            }
            break;
        } else {
            // Partition step
            T pivot = list[low + (high - low) / 2];
            int i = low;
            int j = high;

            while (i <= j) {
                if (descending) {
                    while (list[i] > pivot) ++i;
                    while (list[j] < pivot) --j;
                } else {
                    while (list[i] < pivot) ++i;
                    while (list[j] > pivot) --j;
                }

                if (i <= j) {
                    std::swap(list[i], list[j]);
                    ++i;
                    --j;
                }
            }

            if (j - low < high - i) {
                if (low < j) hybrid_sort_helper(list, low, j, descending);
                low = i;
            } else {
                if (i < high) hybrid_sort_helper(list, i, high, descending);
                high = j;
            }
        }
    }
}

template<typename T>
void my_hybrid_sort(vector<T> &list, bool descending) {
    if (list.size() < 2) return;
    hybrid_sort_helper(list, 0, static_cast<int>(list.size()) - 1, descending);
}


/* Binary Radix Sort
 *
 * 20 points, EXTRA CREDIT
 *
 * Algorithm:
 *
 * Parameters: 
 *   vector<T> &list: reference to a list of type T.
 *                    IMPORTANT: this type T is assumed to be *integral*. It
 *                    can be any of the following integral types in C++:
 *                      - (unsigned) short int
 *                      - (unsigned) int
 *                      - (unsigned) long int
 *
 * Additional Information:
 *   - If you are enrolled in the undergraduate section of this course, this
 *     function is optional and worth extra credit.
 */
template<Integral T> 
void binary_radix_sort(vector<T> &list, bool descending) {
    if (list.size() < 2) return;

    T max_val = list[0];
    for (size_t i = 1; i < list.size(); ++i) {
        if (list[i] > max_val) max_val = list[i];
    }

    size_t num_bits = sizeof(T) * 8;
    vector<T> output(list.size());

    for (size_t bit = 0; bit < num_bits; ++bit) {
        if ((static_cast<uint64_t>(max_val) >> bit) == 0 && bit > 0) break;

        vector<int> count(2, 0);
        for (const auto &item : list) {
            int bit_val = (static_cast<uint64_t>(item) >> bit) & 1;
            count[bit_val]++;
        }

        if (descending) {
            count[0] += count[1];
        } else {
            count[1] += count[0];
        }

        for (int i = static_cast<int>(list.size()) - 1; i >= 0; --i) {
            int bit_val = (static_cast<uint64_t>(list[i]) >> bit) & 1;
            if (descending) {
                int idx = (bit_val == 1) ? count[1] - 1 : count[0] - 1;
                output[idx] = list[i];
                if (bit_val == 1) count[1]--;
                else count[0]--;
            } else {
                int idx = (bit_val == 0) ? count[0] - 1 : count[1] - 1;
                output[idx] = list[i];
                if (bit_val == 0) count[0]--;
                else count[1]--;
            }
        }

        list = output;
    }
}

/* Base B Radix Sort 
 *
 * 25 Points
 *
 * Algorithm: Implement Radix Sort as discussed in class, but with
 *            respect to any unspecified base.
 *
 * Parameters: 
 *   vector<T> &list: reference to a list of type T.
 *                    IMPORTANT: this type T is assumed to be *integral*. It
 *                    can be any of the following integral types in C++:
 *                      - (unsigned) short int
 *                      - (unsigned) int
 *                      - (unsigned) long int
 *
 *   unsigned int base: the base with which to implement the radix sort. 
 *                      Note that base should be at least 2. The default
 *                      base is 10.
 *
 *   bool decending: if true, then sort in descending order; otherwise sort
 *                   in ascending order (the default).
 *
 */
template<Integral T>
void radix_sort(vector<T> &list, unsigned int base, bool descending) {
    if (list.size() < 2 || base < 2) return;

    T max_val = list[0];
    for (size_t i = 1; i < list.size(); ++i) {
        if (list[i] > max_val) max_val = list[i];
    }

    vector<T> output(list.size());
    for (uint64_t exp = 1; static_cast<uint64_t>(max_val) / exp > 0; exp *= base) {
        vector<int> count(base, 0);

        for (const auto &item : list) {
            int digit = (static_cast<uint64_t>(item) / exp) % base;
            count[digit]++;
        }

        if (descending) {
            for (int i = static_cast<int>(base) - 2; i >= 0; --i) {
                count[i] += count[i + 1];
            }
        } else {
            for (size_t i = 1; i < base; ++i) {
                count[i] += count[i - 1];
            }
        }

        for (int i = static_cast<int>(list.size()) - 1; i >= 0; --i) {
            int digit = (static_cast<uint64_t>(list[i]) / exp) % base;
            output[count[digit] - 1] = list[i];
            count[digit]--;
        }

        list = output;
    }
}

int main() {
    /**** STUDENT CODE HERE ****/
 
    /**** END STUDENT CODE ****/

    /***** DO NOT MODIFY BELOW THIS LINE *****/
    /*** INSTRUCTIONS ***
     *
     * Before submitting your code: 
     *   - remove all code within the main function that you have written above the `do-not-modify` line;
     *   - uncomment all lines below that begin with "//".
     *   - NOTE: you can uncomment the code below if you are testing your code with the autograder. The 
     *     autograder will throw an error if you run it without uncommenting the code.
     */

    vector<int> test_list {1, 2, 3, 4, 5};
    vector<unsigned int> test_list2 {1, 2, 3, 4, 5};
    vector<StableChar> test_list3  {};
    vector<StableInt> test_list4 {};
    vector<StableString> test_list5 {};
    vector<short> test_list6  {};
    vector<unsigned short> test_list7  {};
    vector<long> test_list8  {};
    vector<unsigned long> test_list9  {};


    insertion_sort(test_list);
    insertion_sort(test_list2);
    insertion_sort(test_list3);
    insertion_sort(test_list4);
    insertion_sort(test_list5);
    insertion_sort(test_list6);
    insertion_sort(test_list7);
    insertion_sort(test_list8);
    insertion_sort(test_list9);


    selection_sort(test_list);
    selection_sort(test_list2);
    selection_sort(test_list3);
    selection_sort(test_list4);
    selection_sort(test_list5);
    selection_sort(test_list6);
    selection_sort(test_list7);
    selection_sort(test_list8);
    selection_sort(test_list9);

    bubble_sort(test_list);
    bubble_sort(test_list2);
    bubble_sort(test_list3);
    bubble_sort(test_list4);
    bubble_sort(test_list5);
    bubble_sort(test_list6);
    bubble_sort(test_list7);
    bubble_sort(test_list8);
    bubble_sort(test_list9);


    merge_sort(test_list);
    merge_sort(test_list2);
    merge_sort(test_list3);
    merge_sort(test_list4);
    merge_sort(test_list5);
    merge_sort(test_list6);
    merge_sort(test_list7);
    merge_sort(test_list8);
    merge_sort(test_list9);

    quicksort(test_list);
    quicksort(test_list2);
    quicksort(test_list3);
    quicksort(test_list4);
    quicksort(test_list5);
    quicksort(test_list6);
    quicksort(test_list7);
    quicksort(test_list8);
    quicksort(test_list9);

    my_hybrid_sort(test_list);
    my_hybrid_sort(test_list2);
    my_hybrid_sort(test_list3);
    my_hybrid_sort(test_list4);
    my_hybrid_sort(test_list5);
    my_hybrid_sort(test_list6);
    my_hybrid_sort(test_list7);
    my_hybrid_sort(test_list8);
    my_hybrid_sort(test_list9);

    binary_radix_sort(test_list);
    binary_radix_sort(test_list2);
    binary_radix_sort(test_list6);
    binary_radix_sort(test_list7);
    binary_radix_sort(test_list8);
    binary_radix_sort(test_list9);

    radix_sort(test_list);
    radix_sort(test_list2);
    radix_sort(test_list6);
    radix_sort(test_list7);
    radix_sort(test_list8);
    radix_sort(test_list9);


    return 0;
}









