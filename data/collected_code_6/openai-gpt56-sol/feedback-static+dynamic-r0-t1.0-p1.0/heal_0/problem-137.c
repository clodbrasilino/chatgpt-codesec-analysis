#include <stdio.h>
#include <stdlib.h>

static int zero_ratio(const int *array, size_t length, double *ratio)
{
    size_t zero_count = 0;

    if (array == NULL || ratio == NULL || length == 0) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (array[i] == 0) {
            ++zero_count;
        }
    }

    *ratio = (double)zero_count / (double)length;
    return 0;
}

int main(void)
{
    int values[] = {0, 1, 0, 2, 3, 0};
    const size_t length = sizeof(values) / sizeof(values[0]);
    double ratio = 0.0;

    if (zero_ratio(values, length, &ratio) != 0) {
        fputs("Unable to calculate the zero ratio.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.6f\n", ratio) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}