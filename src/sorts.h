
/* pure_sort.h 为带注释版, 内容与本文件一样 */

# ifndef SORTS_H
# define SORTS_H


# ifndef TYPEDEF_ARR_ELEMENT
# define TYPEDEF_ARR_ELEMENT
typedef int arr_element;
# endif


# ifndef TYPEDEF_ARR_ELEMENT
# define TYPEDEF_ARR_ELEMENT
arr_element tmp_space[10000005];
# endif

# ifdef COUNTER_FLAG
int assign_count=0;
int swap_count=0;
# endif

#include <algorithm>
#include "tools.h"
#include <queue>
#include <utility>

typedef void (*SORT_FUNCP)(arr_element[], const int);


namespace sorts
{
    void primitive_insertion_sort (arr_element arr[], const int len)
    {
        int tmp, j;
        for (int i = 1; i < len; i++) {
            tmp = arr[i];
            # ifdef COUNTER_FLAG
            assign_count++;
            # endif
            j = i - 1;
            while (j >= 0 && tmp < arr[j]) {
                arr[j + 1] = arr[j];
                # ifdef COUNTER_FLAG
                assign_count++;
                # endif
                j--;
            }
            arr[j + 1] = tmp;
            # ifdef COUNTER_FLAG
            assign_count++;
            # endif
        }
        return ;
    }

    void primitive_merge_sort (arr_element arr[], const int len)
    {
        static arr_element *tmp_arr = tmp_space;

        if (len < 2)
            return ;

        int m = len >> 1, l = 0, r = m, pi =0;

        primitive_merge_sort(arr, m);
        primitive_merge_sort(arr + m, len - m);

        while (l < m && r < len) {
            tmp_arr[pi++] = (arr[l] < arr[r]) ? arr[l++] : arr[r++];
            # ifdef COUNTER_FLAG
            assign_count++;
            # endif
        }
        while (l < m) {
            tmp_arr[pi++] = arr[l++];
            # ifdef COUNTER_FLAG
            assign_count++;
            # endif
        }
        while (r < len) {
            tmp_arr[pi++] = arr[r++];
            # ifdef COUNTER_FLAG
            assign_count++;
            # endif
        }

        for (int i = 0; i < len; i++) {
            arr[i] = tmp_arr[i];
            # ifdef COUNTER_FLAG
            assign_count++;
            # endif
        }
        return ;
    }

    void mixed_merge_sort (arr_element arr[], const int len)
    {
        static arr_element *tmp_arr = tmp_space;

        if (len < 20){
            primitive_insertion_sort(arr, len);
            return ;
        }

        int m = len >> 1, l = 0, r = m, pi =0;

        primitive_merge_sort(arr, m);
        primitive_merge_sort(arr + m, len - m);

        while (l < m && r < len) {
            tmp_arr[pi++] = (arr[l] < arr[r]) ? arr[l++] : arr[r++];
            # ifdef COUNTER_FLAG
            assign_count++;
            # endif
        }
        while (l < m) {
            tmp_arr[pi++] = arr[l++];
            # ifdef COUNTER_FLAG
            assign_count++;
            # endif
        }
        while (r < len) {
            tmp_arr[pi++] = arr[r++];
            # ifdef COUNTER_FLAG
            assign_count++;
            # endif
        }

        for (int i = 0; i < len; i++) {
            arr[i] = tmp_arr[i];
            # ifdef COUNTER_FLAG
            assign_count++;
            # endif
        }
        return ;
    }

    void multi_merge_sort (arr_element arr[], const int len)
    {
        static arr_element *tmp_arr = tmp_space;
        static std::priority_queue<
            std::pair<arr_element, int>,
            std::vector<std::pair<arr_element, int> >,
            std::greater<std::pair<arr_element, int> >
        > merge_heap;
        static std::pair<arr_element, int> tmp_element;
        static int split_number = 4;
        int tmp_number = split_number;
        if (len <= 20){
            primitive_insertion_sort(arr, len);
            return ;
        }
        int segment_size = len >> 2;
        int end_pointer[tmp_number], start_pointer[tmp_number];
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

        multi_merge_sort(arr + start_pointer[tmp_number - 1], len - start_pointer[tmp_number - 1]);
        for (int i = 0; i < tmp_number; i++) {
            merge_heap.push(std::make_pair(arr[start_pointer[i]], i));
        }
        for (int i = 0; i < len; i++) {
            tmp_element = merge_heap.top();
            # ifdef COUNTER_FLAG
            assign_count++;
            # endif
            merge_heap.pop();
            tmp_arr[i] = tmp_element.first;
            # ifdef COUNTER_FLAG
            assign_count++;
            # endif
            start_pointer[tmp_element.second]++;
            if (start_pointer[tmp_element.second] < end_pointer[tmp_element.second]) {
                tmp_element.first = arr[start_pointer[tmp_element.second]];

                // O(log N)...
                # ifdef COUNTER_FLAG
                assign_count++;
                # endif
                merge_heap.push(tmp_element);
            }
        }
        for (int i = 0; i < len; i++) {
            arr[i] = tmp_arr[i];
            # ifdef COUNTER_FLAG
            assign_count++;
            # endif
        }
        return ;
    }

    int hoare_partition (arr_element arr[], const int len)
    {
        arr_element pivot = arr[0];
        # ifdef COUNTER_FLAG
        assign_count++;
        # endif
        for(int l = 0,r = len - 1;;) {
            while (l < r && arr[r] > pivot)r--;
            while (l < r && arr[l] <= pivot)l++;
            if (l >= r) {
                arr[0] = arr[l];
                arr[l] = pivot;
                # ifdef COUNTER_FLAG
                assign_count+=2;
                # endif
                return l;
            }
            std::swap(arr[l], arr[r]);
            # ifdef COUNTER_FLAG
            swap_count++;
            # endif
        }
        return -1;
    }

    int lomuto_partition (arr_element arr[], const int len)
    {
        arr_element pivot = arr[0];
        # ifdef COUNTER_FLAG
        assign_count++;
        # endif
        int l = 0;
        for(int i = 1; i < len; i++) {
            if (arr[i] <= pivot) {
                l++;
                std::swap(arr[l], arr[i]);
                # ifdef COUNTER_FLAG
                swap_count++;
                # endif
            }
        }
        std::swap(arr[0], arr[l]);
        # ifdef COUNTER_FLAG
        swap_count++;
        # endif
        return l;
    }

    int hoare_partition_with_median_of_three (arr_element arr[], const int len)
    {
        int m = len >> 1;
        if (arr[len - 1] < arr[0]) {
            std::swap(arr[len - 1], arr[0]);
            # ifdef COUNTER_FLAG
            swap_count++;
            # endif
        }
        if (arr[len - 1] < arr[m]) {
            std::swap(arr[len - 1], arr[m]);
            # ifdef COUNTER_FLAG
            swap_count++;
            # endif
        }
        if (arr[m] < arr[0]) {
            std::swap(arr[m], arr[0]);
            # ifdef COUNTER_FLAG
            swap_count++;
            # endif
        }

        arr_element pivot = arr[0];
        # ifdef COUNTER_FLAG
        assign_count++;
        # endif
        for(int l = 0,r = len - 1;;) {
            while (l < r && arr[r] > pivot)r--;
            while (l < r && arr[l] <= pivot)l++;
            if (l >= r) {
                arr[0] = arr[l];
                arr[l] = pivot;
                # ifdef COUNTER_FLAG
                assign_count+=2;
                # endif
                return l;
            }
            std::swap(arr[l], arr[r]);
            # ifdef COUNTER_FLAG
            swap_count++;
            # endif
        }
        return -1;
    }

    void hoare_quick_sort (arr_element arr[], const int len)
    {
        if (len < 2)
            return ;
        int pivot = hoare_partition(arr, len);
        hoare_quick_sort(arr, pivot);
        hoare_quick_sort(arr + pivot + 1, len - pivot - 1);
        return ;
    }

    void hoare_quick_sort_with_median_of_three (arr_element arr[], const int len)
    {
        if (len < 2)
            return ;
        int pivot = hoare_partition_with_median_of_three(arr, len);
        hoare_quick_sort_with_median_of_three(arr, pivot);
        hoare_quick_sort_with_median_of_three(arr + pivot + 1, len - pivot - 1);
        return ;
    }

    void lomuto_quick_sort (arr_element arr[], const int len)
    {
        if (len < 2)
            return ;
        int pivot = lomuto_partition(arr, len);
        lomuto_quick_sort(arr, pivot);
        lomuto_quick_sort(arr + pivot + 1, len - pivot - 1);
        return ;
    }

    void random_hoare_quick_sort (arr_element arr[], const int len)
    {
        if (len < 2)
            return ;
        std::random_shuffle(arr, arr+len);
        # ifdef COUNTER_FLAG
        swap_count+=len;
        # endif
        hoare_quick_sort(arr, len);
        return ;
    }

    inline int compare_func(
        const arr_element &first_key_x,const int second_key_x,
        const arr_element &first_key_y,const int second_key_y
    )
    {
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

    int stable_partition (arr_element arr[], int idx_arr[], const int len)
    {
        int cnt = 0;
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
                # ifdef COUNTER_FLAG
                swap_count++;
                # endif
                break;
            }
        }
        arr_element pivot_element = arr[0];
        # ifdef COUNTER_FLAG
        assign_count++;
        # endif
        int pivot_idx = idx_arr[0];
        for (int l = 0,r = len - 1;;) {
            while (l < r && compare_func(arr[r], idx_arr[r] , pivot_element, pivot_idx) > 0)r--;
            while (l < r && compare_func(arr[l], idx_arr[l] , pivot_element, pivot_idx) <= 0)l++;
            if (l >= r) {
                arr[0] = arr[l];
                arr[l] = pivot_element;
                # ifdef COUNTER_FLAG
                assign_count+=2;
                # endif
                idx_arr[0] = idx_arr[l];
                idx_arr[l] = pivot_idx;

                return l;
            }
            std::swap(arr[l], arr[r]);
            std::swap(idx_arr[l], idx_arr[r]);
            # ifdef COUNTER_FLAG
            swap_count++;
            # endif
        }
        return -1;
    }

    void sub_stable_hoare_quick_sort (arr_element arr[], int idx_arr[], const int len)
    {
        if (len < 2)
            return ;
        int pivot = stable_partition(arr, idx_arr, len);
        // printf("[%d %d] %d [%d %d]\n",0,pivot-1, pivot, pivot+1, len-1);
        sub_stable_hoare_quick_sort(arr, idx_arr, pivot);
        sub_stable_hoare_quick_sort(arr + pivot + 1, idx_arr + pivot + 1, len - pivot - 1);
        return ;
    }

    void stable_hoare_quick_sort (arr_element arr[], const int len)
    {
        if (len < 2)
            return ;

        int *idx_arr = new int[len], rand_aim, len_mod = len;
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
            # ifdef COUNTER_FLAG
            swap_count++;
            # endif
        }
        int pivot = stable_partition(arr, idx_arr, len);
        // printf("[%d %d] %d [%d %d]\n",0,pivot-1, pivot, pivot+1, len-1);
        sub_stable_hoare_quick_sort(arr, idx_arr, pivot);
        sub_stable_hoare_quick_sort(arr + pivot + 1, idx_arr + pivot + 1, len - pivot - 1);

        delete[] idx_arr;
        return ;
    }

}

# endif