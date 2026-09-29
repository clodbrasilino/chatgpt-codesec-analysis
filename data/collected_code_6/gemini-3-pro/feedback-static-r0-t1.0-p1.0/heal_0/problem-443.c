#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int find_largest_negative(const int *list, size_t size, int *error) {
    if (list == NULL || size == 0 || error == NULL) {
        if (error != NULL) {
            *error = 1;
        }
        return 0;
    }

    int largest_negative = INT_MIN;
    int found_negative = 0;
    *error = 0;

    for (size_t i = 0; i < size; ++i) {
        if (list[i] < 0) {
            if (!found_negative || list[i] > largest_negative) {
                largest_negative = list[i];
                found_negative = 1;
            }
        }
    }

    if (!found_negative) {
        *error = 2;
        return 0;
    }

    return largest_negative;
}

int main(void) {
    int numbers[] = {3, -5, 7, -2, -9, 0, 1};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int error = 0;

    int largest_negative = find_largest_negative(numbers, size, &error);

    if (error == 0) {
        printf("Largest negative number: %d\n", largest_negative);
    } else if (error == 1) {
        printf("Invalid input.\n");
    } else if (error == 2) {
        printf("No negative numbers found.\n");
    }

    return 0;
}