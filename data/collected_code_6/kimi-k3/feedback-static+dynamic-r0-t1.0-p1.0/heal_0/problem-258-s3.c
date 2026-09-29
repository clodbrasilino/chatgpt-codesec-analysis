#include <stdio.h>
#include <stddef.h>

int count_odd_elements(const int *list, size_t size)
{
    int count = 0;
    size_t i;

    if (list == NULL) {
        return -1;
    }

    for (i = 0; i < size; i++) {
        if (list[i] % 2 != 0) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = sizeof(list) / sizeof(list[0]);
    int result;

    result = count_odd_elements(list, size);

    if (result >= 0) {
        printf("Number of odd elements: %d\n", result);
    } else {
        printf("Error: Invalid input.\n");
    }

    return 0;
}