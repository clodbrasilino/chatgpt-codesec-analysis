#include <stdio.h>
#include <stddef.h>

static double median_of_two_sorted_arrays(const int a[], const int b[], size_t size)
{
    size_t i = 0;
    size_t j = 0;
    size_t merged_index = 0;
    int previous = 0;
    int current = 0;

    while (merged_index <= size) {
        previous = current;

        if (i < size && (j >= size || a[i] <= b[j])) {
            current = a[i++];
        } else {
            current = b[j++];
        }

        ++merged_index;
    }

    return ((double)previous + (double)current) / 2.0;
}

int main(void)
{
    const int first[] = {1, 12, 15, 26, 38};
    const int second[] = {2, 13, 17, 30, 45};
    const size_t first_size = sizeof(first) / sizeof(first[0]);
    const size_t second_size = sizeof(second) / sizeof(second[0]);

    if (first_size == 0 || first_size != second_size) {
        fputs("Arrays must be nonempty and have the same size.\n", stderr);
        return 1;
    }

    printf("Median: %.2f\n",
           median_of_two_sorted_arrays(first, second, first_size));

    return 0;
}