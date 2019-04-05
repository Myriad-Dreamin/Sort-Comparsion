
# ifndef SORT_TEST_H
# define SORT_TEST_H


# ifndef TYPEDEF_ARR_ELEMENT
# define TYPEDEF_ARR_ELEMENT
typedef int arr_element;
# endif


#include "tools.h"
#include "sorts.h"
#include <iostream>
#include <algorithm>

/*
 * 排序测试框架类
 * 
 * @constructor: constructor(space, size, [option]path)
 * @method: prepare(arr, len), run(arr, len, func), virtual primitive()
 * @method: begin_clock(), end_clock(), settle_clock(), show(unit), used_time(unit)
 * @method: open(), close(), write_open(), write_close(), block(out), newline()
 */
class Sort
{
protected:

    arr_element *arr;
    int arr_size;

    stop_watch self_watch;

    FileHandle self_file;
    bool write_allowed;

    void prepare (arr_element const input_arr[], const int len)
    {
        if (len > arr_size) {
            throw std::invalid_argument("length to copy is out of range");
        }
        memcpy(arr, input_arr, sizeof(arr_element) * len);
    }

    void run (arr_element const input_arr[], const int len, SORT_FUNCP sort_func)
    {
        try {
            prepare(input_arr, len);
        } catch (...) {
            throw ;
        }

        begin_clock();
        sort_func(arr, len);
        end_clock();

        # ifdef DEBUG
        print_arr(arr, len);
        assert_equal(test_space, std_space, len);
        # endif
    }
public:

    Sort (arr_element *your_space, const int space_size)
    {
        arr = your_space;
        arr_size = space_size;
        write_allowed = false;
    }

    Sort (arr_element *your_space, const int space_size, const std::string &file_path)
    {
        arr = your_space;
        arr_size = space_size;
        open(file_path);
    }

    virtual ~Sort ()
    {
        close();
    }

    inline void begin_clock ()
    {
        self_watch.start();
    }

    inline void end_clock ()
    {
        self_watch.stop();
    }

    inline void settle_clock ()
    {
        self_watch.clear();
    }

    virtual void primitive (arr_element const input_arr[], const int len) = 0;

    void show (const time_unit t_unit=time_unit::musec)
    {
        using std::cout;
        using std::endl;
        switch(t_unit) {
            case time_unit::musec: {
                cout << "used " << self_watch.microsec() << " musec" << endl;
                break ;
            }
            case time_unit::misec: {
                cout << "used " << self_watch.millisec() << " misec" << endl;
                break ;
            }
            case time_unit::sec: {
                cout << "used " << self_watch.sec() << " sec" << endl;
                break ;
            }
            default: {
                throw std::invalid_argument(
                    "It is impossible reached? Did you input a wrong time_unit to show?"
                );
                break ;
            }
        }
    }

    double used_time (const time_unit t_unit=time_unit::musec)
    {
        switch(t_unit) {
            case time_unit::musec: {
                return self_watch.microsec();
                break ;
            }
            case time_unit::misec: {
                return self_watch.millisec();
                break ;
            }
            case time_unit::sec: {
                return self_watch.sec();
                break ;
            }
            default: {
                throw std::invalid_argument(
                    "It is impossible reached? Did you input a wrong time_unit to show?"
                );
                break ;
            }
        }
    }

    void open(const std::string &file_path)
    {
        self_file.open(file_path, std::ios::out | std::ios::app);
        write_allowed = true;
    }

    void close()
    {
        self_file.close();
        write_allowed = false;
    }

    void write_open()
    {
        write_allowed = true;
    }

    void write_close()
    {
        write_allowed = false;
    }

    void newline ()
    {
        self_file.newline();
    }

    template<typename T>
    void block(const T &out_element)
    {
        self_file.block(out_element);
    }
};


class InsertionSort: public Sort
{
public:
    InsertionSort(arr_element *your_space, const int space_size): Sort(your_space, space_size) {}

    InsertionSort(
        arr_element *your_space,
        const int space_size,
        const std::string &file_path
    ): Sort(your_space, space_size, file_path) {}

    void primitive (arr_element const input_arr[], const int len)
    {
        run(input_arr, len, sorts::primitive_insertion_sort);
    }
};


class MergeSort: public Sort
{
private:
public:
    MergeSort(arr_element *your_space, const int space_size): Sort(your_space, space_size) {}

    MergeSort(
        arr_element *your_space,
        const int space_size,
        const std::string &file_path
    ): Sort(your_space, space_size, file_path) {}

    void primitive (arr_element const input_arr[], const int len)
    {
        run(input_arr, len, sorts::primitive_merge_sort);
    }

    void mixed (arr_element const input_arr[], const int len)
    {
        run(input_arr, len, sorts::mixed_merge_sort);
    }

    void multi (arr_element const input_arr[], const int len)
    {
        run(input_arr, len, sorts::multi_merge_sort);
    }
};

class MixedMergeSort: public MergeSort
{
private:
public:
    MixedMergeSort(arr_element *your_space, const int space_size): MergeSort(your_space, space_size) {}

    MixedMergeSort(
        arr_element *your_space,
        const int space_size,
        const std::string &file_path
    ): MergeSort(your_space, space_size, file_path) {}

    void primitive (arr_element const input_arr[], const int len)
    {
        mixed(input_arr, len);
    }

    void multi (arr_element const input_arr[], const int len)
    {
        run(input_arr, len, sorts::multi_merge_sort);
    }
};

class MultiMergeSort: public MergeSort
{
private:
public:
    MultiMergeSort(arr_element *your_space, const int space_size): MergeSort(your_space, space_size) {}

    MultiMergeSort(
        arr_element *your_space,
        const int space_size,
        const std::string &file_path
    ): MergeSort(your_space, space_size, file_path) {}

    void primitive (arr_element const input_arr[], const int len)
    {
        multi(input_arr, len);
    }
};


class QuickSort: public Sort
{
public:
    QuickSort(arr_element *your_space, const int space_size): Sort(your_space, space_size) {}

    QuickSort(
        arr_element *your_space,
        const int space_size,
        const std::string &file_path
    ): Sort(your_space, space_size, file_path) {}

    void primitive (arr_element const input_arr[], const int len)
    {
        hoare(input_arr, len);
    }

    void hoare (arr_element const input_arr[], const int len)
    {
        run(input_arr, len, sorts::hoare_quick_sort);
    }

    void random_hoare (arr_element const input_arr[], const int len)
    {
        run(input_arr, len, sorts::random_hoare_quick_sort);
    }

    void hoare_with_median_of_three (arr_element const input_arr[], const int len)
    {
        run(input_arr, len, sorts::hoare_quick_sort_with_median_of_three);
    }

    void stable_hoare (arr_element const input_arr[], const int len)
    {
        run(input_arr, len, sorts::stable_hoare_quick_sort);
    }

    void lomuto (arr_element const input_arr[], const int len)
    {
        run(input_arr, len, sorts::lomuto_quick_sort);
    }
};

class HoareQuickSort: public QuickSort
{
public:
    HoareQuickSort(arr_element *your_space, const int space_size): QuickSort(your_space, space_size) {}

    HoareQuickSort(
        arr_element *your_space,
        const int space_size,
        const std::string &file_path
    ): QuickSort(your_space, space_size, file_path) {}

    void primitive (arr_element const input_arr[], const int len)
    {
        hoare(input_arr, len);
    }
};

class RandomQuickSort: public QuickSort
{
public:
    RandomQuickSort(arr_element *your_space, const int space_size): QuickSort(your_space, space_size) {}

    RandomQuickSort(
        arr_element *your_space,
        const int space_size,
        const std::string &file_path
    ): QuickSort(your_space, space_size, file_path) {}

    void primitive (arr_element const input_arr[], const int len)
    {
        random_hoare(input_arr, len);
    }
};

class HoareQuickSortWithMedianofThree: public QuickSort
{
public:
    HoareQuickSortWithMedianofThree(arr_element *your_space, const int space_size): QuickSort(your_space, space_size) {}

    HoareQuickSortWithMedianofThree(
        arr_element *your_space,
        const int space_size,
        const std::string &file_path
    ): QuickSort(your_space, space_size, file_path) {}

    void primitive (arr_element const input_arr[], const int len)
    {
        hoare_with_median_of_three(input_arr, len);
    }
};

class StableHoareQuickSort: public QuickSort
{
public:
    StableHoareQuickSort(arr_element *your_space, const int space_size): QuickSort(your_space, space_size) {}

    StableHoareQuickSort(
        arr_element *your_space,
        const int space_size,
        const std::string &file_path
    ): QuickSort(your_space, space_size, file_path) {}

    void primitive (arr_element const input_arr[], const int len)
    {
        stable_hoare(input_arr, len);
    }

    void lomuto (arr_element const input_arr[], const int len)
    {
        run(input_arr, len, sorts::lomuto_quick_sort);
    }
};

class LomutoQuickSort: public QuickSort
{
public:
    LomutoQuickSort(arr_element *your_space, const int space_size): QuickSort(your_space, space_size) {}

    LomutoQuickSort(
        arr_element *your_space,
        const int space_size,
        const std::string &file_path
    ): QuickSort(your_space, space_size, file_path) {}

    void primitive (arr_element const input_arr[], const int len)
    {
        lomuto(input_arr, len);
    }
};


class STDSort: public Sort
{
public:
    STDSort(arr_element *your_space, const int space_size): Sort(your_space, space_size) {}

    STDSort(
        arr_element *your_space,
        const int space_size,
        const std::string &file_path
    ): Sort(your_space, space_size, file_path) {}

    void primitive (arr_element const input_arr[], const int len)
    {
        try {
            prepare(input_arr, len);
        } catch (...) {
            throw ;
        }

        begin_clock();
        std::sort(arr, arr + len);
        end_clock();
    }
};
# endif
