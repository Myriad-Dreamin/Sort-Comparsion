
#include <iostream>
#include <chrono>

#include "../src/tools.h"
#include "../src/generate.h"

const int TEST_SIZE = 10050;

int main ()
{
    /* build instance */
    auto random_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    Generate gen(TEST_SIZE, random_seed);
    IntSet dbset("./big_const_10_1e4", "test");

    /* build dataset directory and prepare */
    dbset.build_set();
    int *generate_space = new int[TEST_SIZE];
    
    for (int scale = 10; scale <= 10000; scale += 10) {

        generate_space[0] = scale;
        gen.constant_array(generate_space + 1, scale);

        dbset.new_testcase();
        dbset.batch_ints(generate_space, scale + 1);
    }

    delete[] generate_space;
    dbset.close_testcase();
    dbset.dump_info();

    return 0;
}