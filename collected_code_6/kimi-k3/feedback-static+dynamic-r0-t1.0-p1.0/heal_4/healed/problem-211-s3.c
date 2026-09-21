#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int count_bits_set(int start, int end, int oth, int nth, int *result)
{
    int count;
    int i;
    int oth_bit;
    int nth_bit;

    if (result == NULL) {
        return -1;
    }
    if (start < 0 || end < 0 || start > end) {
        return -1;
    }
    if (oth < 0 || nth < 0 || oth >= (int)(sizeof(int) * CHAR_BIT) || 
        nth >= (int)(sizeof(int) * CHAR_BIT)) {
        return -1;
    }

    oth_bit = 1 << oth;
    nth_bit = 1 << nth;
    count = 0;

    for (i = start; i <= end; i++) {
        if ((i & oth_bit) && (i & nth_bit)) {
            count++;
        }
        if (i == INT_MAX) {
            break;
        }
    }

    *result = count;
    return 0;
}

int main(void)
{
    char buffer[256];
    char *endptr;
    long val;
    int start;
    int end;
    int oth;
    int nth;
    int result;
    int status;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    errno = 0;
    val = strtol(buffer, &endptr, 10);
    if (errno != 0 || endptr == buffer || val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    start = (int)val;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    errno = 0;
    val = strtol(buffer, &endptr, 10);
    if (errno != 0 || endptr == buffer || val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    end = (int)val;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    errno = 0;
    val = strtol(buffer, &endptr, 10);
    if (errno != 0 || endptr == buffer || val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    oth = (int)val;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    errno = 0;
    val = strtol(buffer, &endptr, 10);
    if (errno != 0 || endptr == buffer || val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    nth = (int)val;

    status = count_bits_set(start, end, oth, nth, &result);
    if (status != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}