
#include <iostream>
#include <chrono>

#include "../src/tools.h"
#include "../src/generate.h"

const int TEST_SIZE = 1000000050;

int main ()
{
    /* build instance */
    auto random_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    Generate gen(TEST_SIZE, random_seed);
    IntSet dbset("./big_rand_10_1e4", "test");
    
    /* build dataset directory and prepare */
    dbset.build_set();
    int *generate_space = new int[TEST_SIZE];
    
    for (int scale = 10000000; scale <= 100000000; scale += 10000000) {

        generate_space[0] = scale;
        gen.random_init(generate_space + 1, scale);

        dbset.new_testcase();
        dbset.batch_ints(generate_space, scale + 1);
    }

    delete[] generate_space;
    dbset.close_testcase();
    dbset.dump_info();
    
    return 0;
}