#include <stdio.h>
#include <stddef.h>

static int find_median(const int first[], const int second[], size_t size, double *median)
{
    size_t low = 0;
    size_t high = size;

    if (first == NULL || second == NULL || median == NULL || size == 0) {
        return -1;
    }

    while (low <= high) {
        size_t partition_first = low + (high - low) / 2;
        size_t partition_second = size - partition_first;

        if (partition_first > 0 &&
            partition_second < size &&
            first[partition_first - 1] > second[partition_second]) {
            high = partition_first - 1;
        } else if (partition_second > 0 &&
                   partition_first < size &&
                   second[partition_second - 1] > first[partition_first]) {
            low = partition_first + 1;
        } else {
            int left_max;
            int right_min;

            if (partition_first == 0) {
                left_max = second[partition_second - 1];
            } else if (partition_second == 0) {
                left_max = first[partition_first - 1];
            } else {
                left_max = first[partition_first - 1] > second[partition_second - 1]
                               ? first[partition_first - 1]
                               : second[partition_second - 1];
            }

            if (partition_first == size) {
                right_min = second[partition_second];
            } else if (partition_second == size) {
                right_min = first[partition_first];
            } else {
                right_min = first[partition_first] < second[partition_second]
                                ? first[partition_first]
                                : second[partition_second];
            }

            *median = (double)left_max / 2.0 + (double)right_min / 2.0;
            return 0;
        }
    }

    return -1;
}

int main(void)
{
    const int first[] = {1, 12, 15, 26, 38};
    const int second[] = {2, 13, 17, 30, 45};
    const size_t size = sizeof(first) / sizeof(first[0]);
    double median = 0.0;

    if (size != sizeof(second) / sizeof(second[0])) {
        fputs("Arrays must have the same size.\n", stderr);
        return 1;
    }

    if (find_median(first, second, size, &median) != 0) {
        fputs("Unable to calculate the median.\n", stderr);
        return 1;
    }

    if (printf("Median: %.2f\n", median) < 0) {
        return 1;
    }

    return 0;
}