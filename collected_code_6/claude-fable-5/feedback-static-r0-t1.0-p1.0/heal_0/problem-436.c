#include <stdio.h>
#include <stddef.h>

void print_negative_numbers(const int *list, size_t length)
{
    size_t i;

    if (list == NULL || length == 0U) {
        return;
    }

    for (i = 0U; i < length; i++) {
        if (list[i] < 0) {
            printf("%d\n", list[i]);
        }
    }
}

int main(void)
{
    int numbers[] = { 3, -7, 12, -1, 0, -45, 8, -9 };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);

    print_negative_numbers(numbers, count);

    return 0;
}