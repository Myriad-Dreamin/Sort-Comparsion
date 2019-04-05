
#include <iostream>
#include <chrono>

#include "../src/tools.h"
#include "../src/generate.h"

const int TEST_SIZE = 10000050;

int main ()
{
    /* build instance */
    auto random_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    Generate gen(TEST_SIZE, random_seed);
    IntSet dbset("./big_const_5e5_1e7", "test");

    /* build dataset directory and prepare */
    dbset.build_set();
    int *generate_space = new int[TEST_SIZE];
    
    for (int scale = 500000; scale <= 10000000; scale += 500000) {

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