

#include <iostream>
#include "../test_src/collect.h"
#include "../src/tools.h"

int main() {
    // or ./Dataset_Test/testtest
	IntSet dbset("E:\\project\\cpp\\work\\Cpp-basic\\SortCompare\\test\\Dataset_Test", "test");
    std::cout << dbset.build_set() << std::endl;
    dbset.open_testcase(1);
    int batchs[20] = {5, 1, 2, 3, 4, 5};
    dbset.batch_ints(batchs, 6);

    dbset.close_testcase();

}