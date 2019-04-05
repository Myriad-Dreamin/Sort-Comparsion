
#include <iostream>
#include <chrono>

#include "../src/tools.h"
#include "../src/generate.h"

const int TEST_SIZE = 30050, scale = 30000;

int main ()
{
    /* build instance */
    auto random_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    Generate gen(TEST_SIZE, random_seed);
    IntSet dbset("./uniform_distribution_testset", "test");
    
    /* build dataset directory and prepare */
    dbset.build_set();
    int *generate_space = new int[TEST_SIZE];
    
    for (int r = 1; r <= 100; r ++) {

        generate_space[0] = scale;
        gen.uniform_int_distribution(generate_space + 1, scale, 0, r);

        dbset.new_testcase();
        dbset.batch_ints(generate_space, scale + 1);
    }

    delete[] generate_space;
    dbset.close_testcase();
    dbset.dump_info();
    
    return 0;
}
