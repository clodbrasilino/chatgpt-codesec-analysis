#include <stdio.h>
#include <stdbool.h>

bool find_largest_negative(const int *arr, size_t size, int *result)
{
    if (arr == NULL || result == NULL || size == 0U) {
        return false;
    }

    bool found = false;
    int largest = 0;

    for (size_t i = 0U; i < size; i++) {
        if (arr[i] < 0) {
            if (!found || arr[i] > largest) {
                largest = arr[i];
                found = true;
            }
        }
    }

    if (found) {
        *result = largest;
    }

    return found;
}

int main(void)
{
    int numbers[] = { 3, -7, 2, -1, -15, 8, 0 };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int largest_negative = 0;

    if (find_largest_negative(numbers, count, &largest_negative)) {
        if (printf("Largest negative number: %d\n", largest_negative) < 0) {
            return 1;
        }
    } else {
        if (printf("No negative numbers found.\n") < 0) {
            return 1;
        }
    }

    return 0;
}