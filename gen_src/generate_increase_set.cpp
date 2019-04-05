
#include <iostream>
#include <chrono>

#include "../src/tools.h"
#include "../src/generate.h"

const int TEST_SIZE = 100050;

int main ()
{
    /* build instance */
    auto random_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    Generate gen(TEST_SIZE, random_seed);
    IntSet dbset("./increase_testset", "test");
    
    /* build dataset directory and prepare */
    dbset.build_set();
    int *generate_space = new int[TEST_SIZE];
    
    for (int scale = 1000; scale <= 100000; scale += 1000) {

        generate_space[0] = scale;
        gen.increase(generate_space + 1, scale);

        dbset.new_testcase();
        dbset.batch_ints(generate_space, scale + 1);
    }

    delete[] generate_space;
    dbset.close_testcase();
    dbset.dump_info();

    return 0;
}