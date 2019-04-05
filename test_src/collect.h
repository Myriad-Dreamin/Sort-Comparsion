

# ifndef COLLECT_H
# define COLLECT_H

#include <chrono>

# define TYPEDEF_ARR_ELEMENT
# define TMP_SPACE
# define STD_SPACE

typedef int arr_element;


const int TEST_SIZE = 500000;


auto random_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();


arr_element test_space[TEST_SIZE], generate_space[TEST_SIZE], tmp_space[TEST_SIZE];

#ifdef DEBUG
arr_element std_space[TEST_SIZE];
arr_element *spaces[4] = {test_space, generate_space, tmp_space, std_space};
#else
arr_element *spaces[4] = {test_space, generate_space, tmp_space};
#endif

enum space_index {
    test_idx = 0,
    generate_idx = 1,
    tmp_idx = 2,
    std_idx = 3
};


# endif