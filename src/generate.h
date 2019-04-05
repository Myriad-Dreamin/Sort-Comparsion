
# ifndef GENERATE_SORT_DATA
# define GENERATE_SORT_DATA

# ifndef TYPEDEF_ARR_ELEMENT
# define TYPEDEF_ARR_ELEMENT
typedef int arr_element;
# endif

#include <iostream>
#include <stdexcept>

#include <functional>
#include <random>
#include <ctime>

#include "std_distribution_desc.h"

/*
 * 生成器
 *
 * random_init: 随机生成, constant_array: 常值数列
 * increase: 升序数列, decrease: 降序数列
 * increase_step: 分段升序数列, decrease_step: 分段降序数列
 * distribute: 生成带分布的数列
 * 其他和standard random library中同名的函数为对应的分布生成函数.
 */
class Generate
{
protected:
    int protect_size;
    unsigned long long random_seed;
public:
    Generate (const int test_size, unsigned long long your_seed=0)
    {
        protect_size = test_size;
        random_seed = your_seed;
    }

    inline void random_init(arr_element load_arr[], const int len)
    {
        static std::mt19937 mt_rand(random_seed);
        if (len > protect_size) {
            throw std::invalid_argument("length to initialize is out of range");
        }
        for (int i = 0; i < len; i++) {
            load_arr[i] = mt_rand();
        }
    }

    inline void constant_array(arr_element load_arr[], const int len)
    {
        if (len > protect_size) {
            throw std::invalid_argument("length to initialize is out of range");
        }
        for (int i = 0; i < len; i++) {
            load_arr[i] = 1;
        }
    }

    inline void increase(arr_element load_arr[], const int len)
    {
        if (len > protect_size) {
            throw std::invalid_argument("length to initialize is out of range");
        }
        for (int i = 0; i < len; i++) {
            load_arr[i] = i;
        }
    }

    inline void increase_step(arr_element load_arr[], const int len, const int step)
    {
        if (len > protect_size) {
            throw std::invalid_argument("length to initialize is out of range");
        }
        int elem=0;
        for (int i = 0; i < len; i+=step) {
            for (int j = std::min(step, len - i - 1); ~j; j--) {
                load_arr[i + j] = elem;
            }
        }
    }

    inline void decrease(arr_element load_arr[], const int len)
    {
        if (len > protect_size) {
            throw std::invalid_argument("length to initialize is out of range");
        }
        for (int i = 0; i < len; i++) {
            load_arr[i] = len - i;
        }
    }

    inline void decrease_step(arr_element load_arr[], const int len, const int step)
    {
        if (len > protect_size) {
            throw std::invalid_argument("length to initialize is out of range");
        }
        int elem = (1LL << 31) - 1;
        for (int i = 0; i < len; i+=step) {
            for (int j = std::min(step, len - i - 1); ~j; j--) {
                load_arr[i + j] = elem;
            }
        }
    }

    inline void uniform_int_distribution(
        arr_element load_arr[],
        const int len,
        const int Interval_l,
        const int Interval_r
    ) {
        static std::mt19937 mt_rand((random_seed * 23333 + 6049));
        if (len > protect_size) {
            throw std::invalid_argument("length to initialize is out of range");
        }
        auto distribution_generator = std::bind(
            std::uniform_int_distribution<arr_element>(Interval_l, Interval_r),
            mt_rand
        );
        for (int i = 0; i < len; i++) {
            load_arr[i] = distribution_generator();
        }
    }

    inline void normal_distribution(
        arr_element load_arr[],
        const int len,
        const double mu,
        const double varx
    ) {
        static std::mt19937 mt_rand((random_seed * 23333 + 9999));
        if (len > protect_size) {
            throw std::invalid_argument("length to initialize is out of range");
        }
        auto distribution_generator = std::bind(
            std::normal_distribution<double>(mu, varx),
            mt_rand
        );
        for (int i = 0; i < len; i++) {
            load_arr[i] = arr_element(distribution_generator());
        }
    }

    inline void student_t_distribution(arr_element load_arr[], const int len, const double nt)
    {
        static std::mt19937 mt_rand((random_seed * 23333 + 12366));
        if (len > protect_size) {
            throw std::invalid_argument("length to initialize is out of range");
        }
        auto distribution_generator = std::bind(
            std::student_t_distribution<double>(nt),
            mt_rand
        );
        for (int i = 0; i < len; i++) {
            load_arr[i] = arr_element(distribution_generator());
        }
    }

    inline void exponential_distribution(arr_element load_arr[], const int len, const double lambda)
    {
        static std::mt19937 mt_rand((random_seed * 23333 + 19923));
        if (len > protect_size) {
            throw std::invalid_argument("length to initialize is out of range");
        }
        auto distribution_generator = std::bind(
            std::exponential_distribution<double>(lambda),
            mt_rand
        );
        for (int i = 0; i < len; i++) {
            load_arr[i] = arr_element(distribution_generator());
        }
    }

    inline void negative_binomial_distribution(
        arr_element load_arr[],
        const int len,
        const int nt,
        const double p
    ) {
        static std::mt19937 mt_rand((random_seed * 23333 + 3535));
        if (len > protect_size) {
            throw std::invalid_argument("length to initialize is out of range");
        }
        auto distribution_generator = std::bind(
            std::negative_binomial_distribution<arr_element>(nt, p),
            mt_rand
        );
        for (int i = 0; i < len; i++) {
            load_arr[i] = distribution_generator();
        }
    }

    void distribution(arr_element load_arr[], const int len, std_distribution input_distribution)
    {
        static std::mt19937 mt_rand((random_seed * 23333 + 1234567));
        if (len > protect_size) {
            throw std::invalid_argument("length to initialize is out of range");
        }
        switch(input_distribution)
        {
            case std_distribution::uniform_int_distribution: {
                auto distribution_generator = std::bind(
                    std::uniform_int_distribution<arr_element>(0, 20),
                    mt_rand
                );
                for (int i = 0; i < len; i++) {
                    load_arr[i] = distribution_generator();
                }
                break;
            }

            case std_distribution::normal_distribution: {
                auto distribution_generator = std::bind(
                    std::normal_distribution<double>(0, 1),
                    mt_rand
                );
                for (int i = 0; i < len; i++) {
                    load_arr[i] = arr_element(distribution_generator());
                }
                break;
            }

            case std_distribution::student_t_distribution: {
                auto distribution_generator = std::bind(
                    std::student_t_distribution<double>(20),
                    mt_rand
                );
                for (int i = 0; i < len; i++) {
                    load_arr[i] = arr_element(distribution_generator());
                }
                break;
            }

            case std_distribution::negative_binomial_distribution: {
                auto distribution_generator = std::bind(
                    std::negative_binomial_distribution<arr_element>(20, 0.5),
                    mt_rand
                );
                for (int i = 0; i < len; i++) {
                    load_arr[i] = distribution_generator();
                }
                break;
            }

            case std_distribution::exponential_distribution: {
                auto distribution_generator = std::bind(
                    std::exponential_distribution<double>(1),
                    mt_rand
                );
                for (int i = 0; i < len; i++) {
                    load_arr[i] = arr_element(distribution_generator());
                }
                break;
            }
            default: {
                throw("no such distribution supported" + distribute_desc(input_distribution));
            }
        }
    }
};

# endif // GENERATE_SORT_DATA