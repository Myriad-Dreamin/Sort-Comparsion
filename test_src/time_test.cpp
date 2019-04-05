
# define DONOTPRINT
# define TYPEDEF_ARR_ELEMENT

typedef int arr_element;
arr_element *test_space, *tmp_space, *load_space;
arr_element *spaces[3] = {test_space, load_space, tmp_space};


#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include "../src/tools.h"
#include "../src/generate.h"
#include "../src/sort_test.h"


using std::cout;
using std::endl;

std::string sorts_desc[20];
Sort *testing_sorts[20];
std::map<std::string, Sort* > sort_instance;

void test_sorts(
    arr_element *testing_space,
    const int testing_sorts_count,
    const int len
)
{
    for (int i = 0; i < testing_sorts_count; i++) {
        testing_sorts[i]->primitive(testing_space, len);
        testing_sorts[i]->block(len);
        testing_sorts[i]->block(testing_sorts[i]->used_time());
        testing_sorts[i]->block("mus");
        testing_sorts[i]->block(sorts_desc[i]);
        testing_sorts[i]->newline();
        testing_sorts[i]->settle_clock();
    }
    return ;
}

void close_all ()
{
    for (auto sort_pair : sort_instance) {
        Sort *instance = sort_pair.second;
        delete instance;
    }
}

void init_sort_instance (const int require_space_size, const std::string &csv_name)
{
    InsertionSort                   *ins_sort = new InsertionSort                   (test_space, require_space_size, csv_name);
    MergeSort                       *mer_sort = new MergeSort                       (test_space, require_space_size, csv_name);
    QuickSort                       *quc_sort = new QuickSort                       (test_space, require_space_size, csv_name);
    STDSort                         *std_sort = new STDSort                         (test_space, require_space_size, csv_name);
    MixedMergeSort                  *mix_sort = new MixedMergeSort                  (test_space, require_space_size, csv_name);
    MultiMergeSort                  *mul_sort = new MultiMergeSort                  (test_space, require_space_size, csv_name);
    HoareQuickSort                  *hoa_sort = new HoareQuickSort                  (test_space, require_space_size, csv_name);
    RandomQuickSort                 *ran_sort = new RandomQuickSort                 (test_space, require_space_size, csv_name);
    HoareQuickSortWithMedianofThree *wmt_sort = new HoareQuickSortWithMedianofThree (test_space, require_space_size, csv_name);
    StableHoareQuickSort            *stb_sort = new StableHoareQuickSort            (test_space, require_space_size, csv_name);
    LomutoQuickSort                 *lom_sort = new LomutoQuickSort                 (test_space, require_space_size, csv_name);

    sort_instance["ins_sort"      ] = ins_sort;
    sort_instance["merge_sort"    ] = mer_sort;
    sort_instance["quick_sort"    ] = quc_sort;
    sort_instance["std_sort"      ] = std_sort;
    sort_instance["mixed_sort"    ] = mix_sort;
    sort_instance["multi_sort"    ] = mul_sort;
    sort_instance["hoare_sort"    ] = hoa_sort;
    sort_instance["random_sort"   ] = ran_sort;
    sort_instance["hoare_sort_wmt"] = wmt_sort;
    sort_instance["stable_sort"   ] = stb_sort;
    sort_instance["lomuto_sort"   ] = lom_sort;
}

const std::string get_base_suffix(std::string path) {
    std::reverse(path.begin(), path.end());
    std::string res;
    for (unsigned int i = 0 ; i < path.length(); i++) {
        if(path[i] == '\\' || path[i] == '/') {
            break;
        }
        res.push_back(path[i]);
    }
    std::reverse(res.begin(), res.end());
    return res;
}
int main(int argc, char* argv[])
{
    if (argc == 1) {
        cout <<
            "sort-test time_test version\n"
            "\n"
            "usage: \n"
            "    time_test [int_testset_path] [option] [test sorts list]\n"
            "    eg. time_test ./Datatest_Test std_sort\n"
            "\n"
            "int_testset_path:\n"
            "    path to Generated Test Set \n"
            "\n"
            "    each element is in integer(range from -2^31 to 2^31 - 1)\n"
            "    in format of [L : len] [A: array of integer with length L] (L >= 0)\n"
            "    [A with length L] := [integer] [A with length L - 1](L > 0)\n"
            "    [A with length 0] := [null array]\n"
            "\n"
            "test sorts list:\n"
            "    in format of [S: list of sorts' name]\n"
            "    available sorts:\n"
            "        (primitive)\n"
            "        ins_sort       merge_sort     quick_sort      std_sort\n"
            "\n"
            "        (other type of merge sorts)\n"
            "        mixed_sort     multi_sort\n"
            "\n"
            "        (other type of quick sorts)\n"
            "        hoare_sort     random_sort    hoare_sort_wmt  stable_sort     lomuto_sort\n"
            "\n"
            "use time_test --help [sort's name or command] for more information\n";
        return 0;
    }

    std::string dataset_path = std::string(argv[1]);

    IntSet test_sets(dataset_path, "test");
    test_sets.load_info();
    int require_space_size = test_sets.possible_space_size() + 50;

    test_space = new arr_element[require_space_size];
    init_sort_instance(require_space_size, get_base_suffix(dataset_path) + ".csv");

    int test_count = argc - 2;
    for(int i = 2 , j = 0; i < argc; i++, j++)
    {
        if(!sort_instance.count(argv[i])) {
            delete[] test_space;
            throw std::invalid_argument(std::string("unknown sort type named ") + argv[i]);
        }
        testing_sorts[j] = sort_instance[argv[i]];
        sorts_desc[j] = argv[i];
    }

    load_space = new arr_element[require_space_size];
    tmp_space = new arr_element[require_space_size];

    for(int i = 1; i <= test_sets.size(); i++)
    {
        test_sets.load_testcase_ints(load_space, i);
        test_sorts(load_space + 1, test_count, load_space[0]);
        cout << "test point " << i << " finished" << endl;
    }

    delete[] test_space;
    delete[] load_space;
    delete[] tmp_space;
    close_all();
    // Sort *test_sort;
    // // arr_element *your_space, const int space_size
    // STDSort std_sort = STDSort();
    return 0;
}