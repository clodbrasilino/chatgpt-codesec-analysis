#include <stdio.h>
#include <stddef.h>

static int square_elements(const double input[], double output[], size_t count)
{
    if ((input == NULL || output == NULL) && count != 0U) {
        return -1;
    }

    for (size_t i = 0U; i < count; ++i) {
        output[i] = input[i] * input[i];
    }

    return 0;
}

int main(void)
{
    const double numbers[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double squares[sizeof(numbers) / sizeof(numbers[0])];
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);

    if (square_elements(numbers, squares, count) != 0) {
        fputs("Failed to square elements.\n", stderr);
        return 1;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (printf("%.2f\n", squares[i]) < 0) {
            return 1;
        }
    }

    return 0;
}