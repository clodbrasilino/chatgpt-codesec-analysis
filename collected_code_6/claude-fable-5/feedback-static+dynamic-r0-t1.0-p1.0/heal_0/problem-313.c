#include <stdio.h>
#include <stddef.h>

void print_positive_numbers(const int *list, size_t length)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < length; i++) {
        if (list[i] > 0) {
            if (printf("%d\n", list[i]) < 0) {
                return;
            }
        }
    }
}

int main(void)
{
    int numbers[] = { -5, 3, 0, 12, -7, 8, 1, -2 };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);

    print_positive_numbers(numbers, count);

    return 0;
}