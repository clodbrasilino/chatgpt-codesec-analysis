#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
int count_in_range(int *list, size_t size, int lower, int upper) {
    if (list == NULL) {
        return 0;
    }

    if (lower > upper) {
        int temp = lower;
        lower = upper;
        upper = temp;
    }

    int count = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] >= lower && list[i] <= upper) {
            count++;
        }
    }

    return count;
}

int main(void) {
    int data[] = {1, 5, 12, 15, 8, 3, 20, 7};
    size_t data_size = sizeof(data) / sizeof(data[0]);

    int lower = 5;
    int upper = 15;

    int result = count_in_range(data, data_size, lower, upper);

    printf("%d\n", result);

    return 0;
}