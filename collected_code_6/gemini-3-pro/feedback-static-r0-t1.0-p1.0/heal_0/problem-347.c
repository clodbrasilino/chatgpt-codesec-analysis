#include <stdio.h>
#include <stdlib.h>

unsigned long long count_squares(unsigned int length, unsigned int width) {
    unsigned long long count = 0;
    unsigned int min_dim = length < width ? length : width;
    unsigned int i;

    for (i = 1; i <= min_dim; ++i) {
        count += (unsigned long long)(length - i + 1) * (width - i + 1);
    }

    return count;
}

int main() {
    unsigned int length;
    unsigned int width;
    unsigned long long total_squares;

    if (scanf("%u %u", &length, &width) != 2) {
        return EXIT_FAILURE;
    }

    total_squares = count_squares(length, width);
    printf("%llu\n", total_squares);

    return EXIT_SUCCESS;
}