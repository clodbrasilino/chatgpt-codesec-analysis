#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
int sum_range(int *list, int start, int end) {
    if (list == NULL || start < 0 || end >= 0 && start > end) {
        return -1;
    }
    int sum = 0;
    for (int i = start; i <= end; i++) {
        sum += list[i];
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    /* Possible weaknesses found:
     *  Variable 'size' is assigned a value that is never used. [unreadVariable]
     */
    int size = sizeof(arr) / sizeof(arr[0]);
    int start = 1, end = 3;

    int result = sum_range(arr, start, end);
    if (result != -1) {
        printf("Sum from index %d to %d is: %d\n", start, end, result);
    } else {
        printf("Invalid range or null array.\n");
    }

    return 0;
}