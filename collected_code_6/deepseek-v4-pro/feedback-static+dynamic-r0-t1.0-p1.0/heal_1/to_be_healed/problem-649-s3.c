#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
int sum_in_range(int *list, int size, int start, int end, int *error) {
    if (list == NULL || size <= 0 || error == NULL) {
        if (error != NULL) {
            *error = 1;
        }
        return 0;
    }
    if (start < 0 || end < start || end >= size) {
        *error = 1;
        return 0;
    }
    *error = 0;
    int sum = 0;
    for (int i = start; i <= end; i++) {
        sum += list[i];
    }
    return sum;
}

int main(void) {
    int numbers[] = {5, 10, 15, 20, 25, 30};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int error = 0;
    int result = sum_in_range(numbers, size, 1, 3, &error);
    if (error != 0) {
        fprintf(stderr, "Error: invalid range or arguments\n");
        return EXIT_FAILURE;
    }
    printf("Sum: %d\n", result);
    return EXIT_SUCCESS;
}