#include <stdio.h>
#include <stddef.h>

void print_positive_numbers(const int *list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        if (list[i] > 0) {
            printf("%d\n", list[i]);
        }
    }
}

int main(void)
{
    int numbers[] = { -5, 12, 0, 7, -3, 42, -1, 9 };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);

    print_positive_numbers(numbers, count);

    return 0;
}