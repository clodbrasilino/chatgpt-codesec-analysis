#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

static int find_range(const int *values, size_t count, int64_t *difference)
{
    int smallest;
    int largest;

    if (values == NULL || difference == NULL || count == 0U) {
        return -1;
    }

    smallest = values[0];
    largest = values[0];

    for (size_t i = 1U; i < count; ++i) {
        if (values[i] < smallest) {
            smallest = values[i];
        }
        if (values[i] > largest) {
            largest = values[i];
        }
    }

    *difference = (int64_t)largest - (int64_t)smallest;
    return 0;
}

int main(void)
{
    const int values[] = {12, -7, 25, 4, 18, -3};
    const size_t count = sizeof(values) / sizeof(values[0]);
    int64_t difference = 0;

    if (find_range(values, count, &difference) != 0) {
        (void)fprintf(stderr, "Unable to calculate the difference.\n");
        return 1;
    }

    if (printf("Difference: %" PRId64 "\n", difference) < 0) {
        return 1;
    }

    return 0;
}