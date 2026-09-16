#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
int calculate_range_sum(int *list, size_t size, size_t start, size_t end) {
    if (list == NULL) {
        return 0;
    }

    if (start > end || start >= size) {
        return 0;
    }

    if (end >= size) {
        end = size - 1;
    }

    int sum = 0;
    for (size_t i = start; i <= end; i++) {
        sum += list[i];
    }

    return sum;
}

int main(void) {
    int data[] = {1, 2, 3, 4, 5};
    size_t data_size = sizeof(data) / sizeof(data[0]);

    int result = calculate_range_sum(data, data_size, 1, 3);

    printf("%d\n", result);

    return 0;
}