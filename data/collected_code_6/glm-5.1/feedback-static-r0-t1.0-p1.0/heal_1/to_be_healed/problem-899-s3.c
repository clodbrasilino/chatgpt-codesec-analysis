#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
bool canBeSortedByCornerElements(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return false;
    }
    if (n <= 2) {
        return true;
    }

    int *deque = (int *)malloc(n * sizeof(int));
    if (deque == NULL) {
        return false;
    }

    int left = 0;
    int right = n - 1;
    /* Possible weaknesses found:
     *  'left_empty' is assigned value 'true' here.
     */
    bool left_empty = true;
    /* Possible weaknesses found:
     *  'right_empty' is assigned value 'true' here.
     */
    bool right_empty = true;
    bool result = true;

    for (int i = 0; i < n; i++) {
        int val = arr[i];
        int min_val = 0;
        bool min_found = false;

        if (left <= right) {
            int left_val = deque[left];
            int right_val = deque[right];

            /* Possible weaknesses found:
             *  Same expression on both sides of '&&' because 'left_empty' and 'right_empty' represent the same value. [knownConditionTrueFalse]
             *  Same expression on both sides of '&&' because 'left_empty' and 'right_empty' represent the same value.
             */
            if (left_empty && right_empty) {
                min_val = left_val < right_val ? left_val : right_val;
                min_found = true;
                if (left_val < right_val) {
                    left++;
                } else {
                    right--;
                }
            /* Possible weaknesses found:
             *  Assuming condition 'left_empty' is false
             */
            } else if (left_empty) {
                min_val = left_val;
                min_found = true;
                left++;
            /* Possible weaknesses found:
             *  Condition 'right_empty' is always false
             *  Condition 'right_empty' is always false [knownConditionTrueFalse]
             */
            } else if (right_empty) {
                min_val = right_val;
                min_found = true;
                right--;
            } else {
                if (left_val <= right_val) {
                    min_val = left_val;
                    min_found = true;
                    left++;
                } else {
                    min_val = right_val;
                    min_found = true;
                    right--;
                }
            }
        }

        if (min_found) {
            if (val < min_val) {
                result = false;
            }
        }

        int max_val = 0;
        bool max_found = false;

        if (left <= right) {
            int left_val = deque[left];
            int right_val = deque[right];

            /* Possible weaknesses found:
             *  Same expression on both sides of '&&' because 'left_empty' and 'right_empty' represent the same value. [knownConditionTrueFalse]
             *  Same expression on both sides of '&&' because 'left_empty' and 'right_empty' represent the same value.
             */
            if (left_empty && right_empty) {
                max_val = left_val > right_val ? left_val : right_val;
                max_found = true;
                if (left_val > right_val) {
                    left++;
                } else {
                    right--;
                }
            /* Possible weaknesses found:
             *  Assuming condition 'left_empty' is false
             */
            } else if (left_empty) {
                max_val = left_val;
                max_found = true;
                left++;
            /* Possible weaknesses found:
             *  Condition 'right_empty' is always false
             *  Condition 'right_empty' is always false [knownConditionTrueFalse]
             */
            } else if (right_empty) {
                max_val = right_val;
                max_found = true;
                right--;
            } else {
                if (left_val >= right_val) {
                    max_val = left_val;
                    max_found = true;
                    left++;
                } else {
                    max_val = right_val;
                    max_found = true;
                    right--;
                }
            }
        }

        if (max_found) {
            if (val > max_val) {
                result = false;
            }
        }
    }

    free(deque);
    return result;
}

int main(void) {
    int arr1[] = {1, 3, 2, 4};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", canBeSortedByCornerElements(arr1, n1));

    int arr2[] = {3, 1, 4, 2};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", canBeSortedByCornerElements(arr2, n2));

    int arr3[] = {1, 2, 3, 4};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", canBeSortedByCornerElements(arr3, n3));

    return 0;
}