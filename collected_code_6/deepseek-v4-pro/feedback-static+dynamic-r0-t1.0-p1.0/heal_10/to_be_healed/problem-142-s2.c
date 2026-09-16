#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 3, got 2
  *  test case 1 failed: expected 4, got 2
  *  test case 2 failed: expected 5, got 2
  */

int count_same_pairs(const int *list1, int size1, const int *list2, int size2, const int *list3, int size3) {
    int count = 0;
    int i = 0, j = 0, k = 0;

    while (i < size1 && j < size2 && k < size3) {
        if (list1[i] == list2[j] && list1[i] == list3[k]) {
            count++;
            i++;
            j++;
            k++;
        } else {
            int min_val = list1[i];
            if (list2[j] < min_val) min_val = list2[j];
            if (list3[k] < min_val) min_val = list3[k];

            if (list1[i] == min_val) i++;
            if (list2[j] == min_val) j++;
            if (list3[k] == min_val) k++;
        }
    }

    return count;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {2, 3, 4, 5, 6};
    int list3[] = {3, 4, 5, 6, 7};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);
    int size3 = sizeof(list3) / sizeof(list3[0]);

    int result = count_same_pairs(list1, size1, list2, size2, list3, size3);
    printf("%d\n", result);

    return 0;
}