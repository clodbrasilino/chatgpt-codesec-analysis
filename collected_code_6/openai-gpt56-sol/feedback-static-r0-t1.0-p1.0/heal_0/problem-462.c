#include <stdio.h>
#include <stdlib.h>

static int print_combinations(const int *values, size_t count)
{
    if (count >= sizeof(size_t) * 8U) {
        return -1;
    }

    const size_t combination_count = ((size_t)1U << count);

    for (size_t mask = 0; mask < combination_count; ++mask) {
        if (putchar('{') == EOF) {
            return -1;
        }

        int first = 1;

        for (size_t index = 0; index < count; ++index) {
            if ((mask & ((size_t)1U << index)) != 0U) {
                if (!first && printf(", ") < 0) {
                    return -1;
                }

                if (printf("%d", values[index]) < 0) {
                    return -1;
                }

                first = 0;
            }
        }

        if (puts("}") == EOF) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    const int values[] = {1, 2, 3, 4};
    const size_t count = sizeof(values) / sizeof(values[0]);

    if (print_combinations(values, count) != 0) {
        fputs("Failed to generate combinations.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}