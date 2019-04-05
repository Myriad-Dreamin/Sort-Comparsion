
# define DONOTPRINT
# define DEBUG

#include <iostream>

#include "collect.h"
#include "../src/tools.h"
#include "../src/generate.h"
#include "../src/sort_test.h"


using std::cout;
using std::endl;


STDSort std_sort(std_space, TEST_SIZE, "./quicksort_test.csv");
LomutoQuickSort lom_sort(test_space, TEST_SIZE, "./quicksort_test.csv");
HoareQuickSort hoa_sort(test_space, TEST_SIZE, "./quicksort_test.csv");

RandomQuickSort hoa_sort_rand(test_space, TEST_SIZE, "./quicksort_test.csv");
StableHoareQuickSort hoa_sort_stable(test_space, TEST_SIZE, "./quicksort_test.csv");
HoareQuickSortWithMedianofThree hoa_sort_wmt(
    test_space,
    TEST_SIZE,
    "./quicksort_test.csv"
);

const int testing_sorts_count = 5;
Sort *testing_sorts[testing_sorts_count] = {&lom_sort, &hoa_sort, &hoa_sort_rand, &hoa_sort_stable, &hoa_sort_wmt};
std::string sorts_desc[testing_sorts_count] = {
    "lomuto quick sort",
    "hoare quick sort",
    "random hoare quick sort",
    "stable hoare quick sort",
    "hoare quick sort with median of three"
};

Generate gen(TEST_SIZE, random_seed);


enum output_mode {to_console, to_file, do_nothing};
void test_sorts(
    const int len,
    const output_mode ot_mode = output_mode::do_nothing,
    const char * test_info=""
)
{
    if (len > TEST_SIZE) {
        throw std::invalid_argument("length to initialize is out of range");
    }
    # ifdef DEBUG
    print_arr(generate_space, len);
    std_sort.primitive(generate_space, len);
    # endif

    for (int i = 0; i < testing_sorts_count; i++) {
        testing_sorts[i]->primitive(generate_space, len);
    }

    switch (ot_mode) {
        case output_mode::to_console: {
            
            cout << "std sort: " << endl;
            std_sort.show();

            for (int i = 0; i < testing_sorts_count; i++) {
                cout << sorts_desc[i] << ": " << endl;
                testing_sorts[i]->show();
            }

            break ;
        }
        case output_mode::to_file: {
            
            std_sort.block(len);
            std_sort.block(std_sort.used_time());
            std_sort.block("mus");
            std_sort.block(std::string("standard sort | ") + test_info);
            std_sort.newline();

            for (int i = 0; i < testing_sorts_count; i++) {
                testing_sorts[i]->block(len);
                testing_sorts[i]->block(testing_sorts[i]->used_time());
                testing_sorts[i]->block("mus");
                testing_sorts[i]->block(sorts_desc[i] + " | " + test_info);
                testing_sorts[i]->newline();
            }

            break ;
        }
        default: {
            break ;
        }
    }
    return ;
}

void clearclocks()
{
    std_sort.settle_clock();
    for (int i = 0; i < testing_sorts_count; i++) {
        testing_sorts[i]->settle_clock();
    }
}

void close_all()
{
    std_sort.close();
    for (int i = 0; i < testing_sorts_count; i++) {
        testing_sorts[i]->close();
    }
}

int main()
{
    int test_len = 3000;
    gen.random_init(generate_space, test_len);
    test_sorts(test_len, output_mode::to_file, "random_init");
    clearclocks();

    gen.constant_array(generate_space, test_len);
    test_sorts(test_len, output_mode::to_file, "special_test");
    clearclocks();

    gen.increase(generate_space, test_len);
    test_sorts(test_len, output_mode::to_file, "special_test2");
    clearclocks();

    gen.decreate(generate_space, test_len);
    test_sorts(test_len, output_mode::to_file, "special_test2");
    clearclocks();

    close_all();
    return 0;
}