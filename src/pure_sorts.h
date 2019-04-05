
# ifndef SORTS_H
# define SORTS_H


# ifndef TYPEDEF_ARR_ELEMENT
# define TYPEDEF_ARR_ELEMENT
typedef int arr_element;
# endif // TYPEDEF_ARR_ELEMENT

# ifndef TYPEDEF_ARR_ELEMENT
# define TYPEDEF_ARR_ELEMENT
arr_element tmp_space[10000005];
# endif // TYPEDEF_ARR_ELEMENT


#include <algorithm>
#include "tools.h"
#include <queue>
#include <utility>

/* 通用排序函数指针 */
typedef void (*SORT_FUNCP)(arr_element[], const int);


namespace sorts
{
    // 朴素插入排序
    void primitive_insertion_sort (arr_element arr[], const int len)
    {
        int tmp, j;

        for (int i = 1; i < len; i++) {
            tmp = arr[i];
            j = i - 1;
            while (j >= 0 && tmp < arr[j]) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = tmp;
        }

        return ;
    }

    // 朴素归并排序
    void primitive_merge_sort (arr_element arr[], const int len)
    {
        /* 为了方便使用了全局变量,可以改回 new 模式的临时空间 */
        static arr_element *tmp_arr = tmp_space;

        if (len < 2) {
            return ;
        }
        

        int m = len >> 1, l = 0, r = m, pi =0;

        primitive_merge_sort(arr, m);
        primitive_merge_sort(arr + m, len - m);

        while (l < m && r < len) {
            tmp_arr[pi++] = (arr[l] < arr[r]) ? arr[l++] : arr[r++];
        }
        while (l < m) {
            tmp_arr[pi++] = arr[l++];
        }
        while (r < len) {
            tmp_arr[pi++] = arr[r++];
        }

        for (int i = 0; i < len; i++) {
            arr[i] = tmp_arr[i];
        }

        return ;
    }

    // 混合归并排序
    void mixed_merge_sort (arr_element arr[], const int len)
    {
        /* 为了方便使用了全局变量,可以改回 new 模式的临时空间 */
        static arr_element *tmp_arr = tmp_space;

        /* 减少小规模数据下mergesort的函数栈开销 */
        if (len < 20){
            primitive_insertion_sort(arr, len);
            return ;
        }

        int m = len >> 1, l = 0, r = m, pi =0;

        /* split */
        primitive_merge_sort(arr, m);
        primitive_merge_sort(arr + m, len - m);

        /* merge */
        while (l < m && r < len) {
            tmp_arr[pi++] = (arr[l] < arr[r]) ? arr[l++] : arr[r++];
        }
        while (l < m) {
            tmp_arr[pi++] = arr[l++];
        }
        while (r < len) {
            tmp_arr[pi++] = arr[r++];
        }

        /* copy */
        for (int i = 0; i < len; i++) {
            arr[i] = tmp_arr[i];
        }

        return ;
    }

    // 多路归并
    void multi_merge_sort (arr_element arr[], const int len)
    {
        /* 为了方便使用了全局变量,可以改回 new 模式的临时空间 */
        static arr_element *tmp_arr = tmp_space;
        /* heap */
        static std::priority_queue<
            std::pair<arr_element, int>,
            std::vector<std::pair<arr_element, int> >,
            std::greater<std::pair<arr_element, int> >
        > merge_heap;
        static std::pair<arr_element, int> tmp_element;
        
        /* split_number is the k of k-way mergesort */
        static int split_number = 4;

        /* 减少小规模数据下mergesort的函数栈开销 */
        if (len <= 20){
            primitive_insertion_sort(arr, len);
            return ;
        }
        
        /* 复制一遍作为本地临时变量 */
        int tmp_number = split_number;
        
        /* segment_size: 段长, start_pointer, end_pointer为双指针指向段的首和末元素[start, end) */
        int segment_size = len >> 2;
        int end_pointer[tmp_number], start_pointer[tmp_number];
        
        /* split */
        end_pointer[0] = segment_size;
        start_pointer[0] = 0;
        tmp_number--;
        for (int i = 0; i < tmp_number; i++) {
            multi_merge_sort(arr + start_pointer[i], segment_size);
            end_pointer[i + 1] = end_pointer[i] + segment_size;
            start_pointer[i + 1] = end_pointer[i];
        }
        end_pointer[tmp_number] = len;
        tmp_number++;

        /* merge */
        multi_merge_sort(arr + start_pointer[tmp_number - 1], len - start_pointer[tmp_number - 1]);
        for (int i = 0; i < tmp_number; i++) {
            merge_heap.push(std::make_pair(arr[start_pointer[i]], i));
        }
        for (int i = 0; i < len; i++) {
            tmp_element = merge_heap.top();
            merge_heap.pop();
            tmp_arr[i] = tmp_element.first;
            start_pointer[tmp_element.second]++;
            if (start_pointer[tmp_element.second] < end_pointer[tmp_element.second]) {
                tmp_element.first = arr[start_pointer[tmp_element.second]];
                merge_heap.push(tmp_element);
            }
        }

        /* copy */
        for (int i = 0; i < len; i++) {
            arr[i] = tmp_arr[i];
        }

        return ;
    }

    // hoare划分
    int hoare_partition (arr_element arr[], const int len)
    {
        arr_element pivot = arr[0];
        for(int l = 0,r = len - 1;;) {
            
            while (l < r && arr[r] > pivot)r--;
            while (l < r && arr[l] <= pivot)l++;
            
            if (l >= r) {
                arr[0] = arr[l];
                arr[l] = pivot;
                return l;
            }
            
            std::swap(arr[l], arr[r]);
        }

        return -1;
    }

    // lomuto划分
    int lomuto_partition (arr_element arr[], const int len)
    {
        arr_element pivot = arr[0];
        int l = 0;

        for(int i = 1; i < len; i++) {
            if (arr[i] <= pivot) {
                l++;
                std::swap(arr[l], arr[i]);
            }
        }

        std::swap(arr[0], arr[l]);

        return l;
    }

    // Median3划分
    int hoare_partition_with_median_of_three (arr_element arr[], const int len)
    {
        int m = len >> 1;

        /* select the median of three */
        if (arr[len - 1] < arr[0]) {
            std::swap(arr[len - 1], arr[0]);
        }
        if (arr[len - 1] < arr[m]) {
            std::swap(arr[len - 1], arr[m]);
        }
        if (arr[m] < arr[0]) {
            std::swap(arr[m], arr[0]);
        }

        arr_element pivot = arr[0];

        for(int l = 0,r = len - 1;;) {

            while (l < r && arr[r] > pivot)r--;
            while (l < r && arr[l] <= pivot)l++;

            if (l >= r) {
                arr[0] = arr[l];
                arr[l] = pivot;
                return l;
            }

            std::swap(arr[l], arr[r]);
        }

        return -1;
    }

    // hoare快速排序
    void hoare_quick_sort (arr_element arr[], const int len)
    {
        if (len < 2) {
            return ;
        }
        
        int pivot = hoare_partition(arr, len);

        hoare_quick_sort(arr, pivot);
        hoare_quick_sort(arr + pivot + 1, len - pivot - 1);

        return ;
    }

    // hoare-median3快速排序
    void hoare_quick_sort_with_median_of_three (arr_element arr[], const int len)
    {
        if (len < 2) {
            return ;
        }

        int pivot = hoare_partition_with_median_of_three(arr, len);

        hoare_quick_sort_with_median_of_three(arr, pivot);
        hoare_quick_sort_with_median_of_three(arr + pivot + 1, len - pivot - 1);

        return ;
    }

    // lomuto快速排序
    void lomuto_quick_sort (arr_element arr[], const int len)
    {
        if (len < 2) {
            return ;
        }

        int pivot = lomuto_partition(arr, len);

        lomuto_quick_sort(arr, pivot);
        lomuto_quick_sort(arr + pivot + 1, len - pivot - 1);

        return ;
    }

    // random-hoare快速排序
    void random_hoare_quick_sort (arr_element arr[], const int len)
    {
        if (len < 2) {
            return ;
        }
        
        std::random_shuffle(arr, arr+len);
        hoare_quick_sort(arr, len);

        return ;
    }

    // 重载的Pair<key, position> key: input arr_element, position: int
    inline int compare_func(
        const arr_element &first_key_x,const int second_key_x,
        const arr_element &first_key_y,const int second_key_y
    ) {
        if (
            (first_key_x < first_key_y) ||
            ((first_key_x == first_key_y) && (second_key_x < second_key_y))
        ) {
            return -1;
        }
        if ((first_key_x == first_key_y) && (second_key_x == second_key_y)) {
            return 0;
        }
        return 1;
    }

    // 稳定划分
    int stable_partition (arr_element arr[], int idx_arr[], const int len)
    {
        int cnt = 0;

        /* select the middle array */
        for (int i = 0; i < len; i++) {
            if (arr[i] == arr[0]) {
                cnt++;
            }
        }
        cnt = (cnt + 1) >> 1;
        for (int i = 0; i < len; i++) {
            if (arr[i] == arr[0]) {
                cnt--;
            }
            if (cnt == 0) {
                std::swap(arr[0], arr[i]);
                std::swap(idx_arr[0], idx_arr[i]);
                break;
            }
        }

        arr_element pivot_element = arr[0];
        int pivot_idx = idx_arr[0];

        for (int l = 0,r = len - 1;;) {

            while (l < r && compare_func(arr[r], idx_arr[r] , pivot_element, pivot_idx) > 0)r--;
            while (l < r && compare_func(arr[l], idx_arr[l] , pivot_element, pivot_idx) <= 0)l++;

            if (l >= r) {
                arr[0] = arr[l];
                arr[l] = pivot_element;

                idx_arr[0] = idx_arr[l];
                idx_arr[l] = pivot_idx;

                return l;
            }

            std::swap(arr[l], arr[r]);
            std::swap(idx_arr[l], idx_arr[r]);
        }
        return -1;
    }

    // 稳定快速排序子函数
    void sub_stable_hoare_quick_sort (arr_element arr[], int idx_arr[], const int len)
    {
        if (len < 2) {
            return ;
        }
        
        int pivot = stable_partition(arr, idx_arr, len);
        
        sub_stable_hoare_quick_sort(arr, idx_arr, pivot);
        sub_stable_hoare_quick_sort(arr + pivot + 1, idx_arr + pivot + 1, len - pivot - 1);

        return ;
    }

    // 稳定快速排序
    void stable_hoare_quick_sort (arr_element arr[], const int len)
    {
        if (len < 2) {
            return ;
        }

        int *idx_arr = new int[len], rand_aim, len_mod = len;

        /* random shuffle */
        while (len_mod != (rand_aim = len_mod & (-len_mod))) {
            len_mod -= rand_aim;
        }
        len_mod--;
        for (int i = 0; i < len; i++)
        {
            idx_arr[i] = i;
        }
        for (int i = len - 1; ~i; i--)
        {
            rand_aim = rand_uint() & len_mod;
            std::swap(arr[i], arr[rand_aim]);
            std::swap(idx_arr[i], idx_arr[rand_aim]);
        }

        int pivot = stable_partition(arr, idx_arr, len);
        
        sub_stable_hoare_quick_sort(arr, idx_arr, pivot);
        sub_stable_hoare_quick_sort(arr + pivot + 1, idx_arr + pivot + 1, len - pivot - 1);

        delete[] idx_arr;

        return ;
    }

}

# endif // SORT_H