#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 1, got 5
  *  test case 0 failed: expected 2, got 4
  *  test case 2 failed: expected 1, got 3
  */

int find_max_occurrences(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        return INT_MIN;
    }

    int min_val = list[0];
    int max_val = list[0];

    for (size_t i = 1; i < size; i++) {
        if (list[i] < min_val) {
            min_val = list[i];
        }
        if (list[i] > max_val) {
            max_val = list[i];
        }
    }

    size_t range = (size_t)(max_val - min_val + 1);

    int *counts = (int *)calloc(range, sizeof(int));
    if (counts == NULL) {
        return INT_MIN;
    }

    int max_count = 0;
    /* Possible weaknesses found:
     *  Value stored to 'max_item' during its initialization is never read [deadcode.DeadStores]
     *  Variable 'max_item' is assigned a value that is never used. [unreadVariable]
     */
    int max_item = list[0];

    for (size_t i = 0; i < size; i++) {
        size_t index = (size_t)(list[i] - min_val);
        counts[index]++;
        if (counts[index] > max_count) {
            max_count = counts[index];
            /* Possible weaknesses found:
             *  Value stored to 'max_item' is never read [deadcode.DeadStores]
             *  Variable 'max_item' is assigned a value that is never used. [unreadVariable]
             */
            max_item = list[i];
        }
    }

    free(counts);

    return max_count;
}

int main(void) {
    int list0[] = {1, 2, 2, 3};
    size_t size0 = sizeof(list0) / sizeof(list0[0]);
    int result0 = find_max_occurrences(list0, size0);
    if (result0 != INT_MIN) {
        printf("%d\n", result0);
    } else {
        printf("Invalid input or memory allocation failed\n");
    }

    int list1[] = {5, 5, 5, 5};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    int result1 = find_max_occurrences(list1, size1);
    if (result1 != INT_MIN) {
        printf("%d\n", result1);
    } else {
        printf("Invalid input or memory allocation failed\n");
    }

    int list2[] = {1, 2, 3, 4, 5};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    int result2 = find_max_occurrences(list2, size2);
    if (result2 != INT_MIN) {
        printf("%d\n", result2);
    } else {
        printf("Invalid input or memory allocation failed\n");
    }

    return 0;
}