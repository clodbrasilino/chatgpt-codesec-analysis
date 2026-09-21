#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

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

static int read_input_line(char *buffer, size_t size)
{
    size_t len;

    if (buffer == NULL || size == 0) {
        return -1;
    }
    if (fgets(buffer, size, stdin) == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == size - 1) {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return -1;
    }
    return 0;
}

static int parse_int(const char *buffer, int *out)
{
    char *endptr;
    long val;

    if (buffer == NULL || out == NULL) {
        return -1;
    }
    errno = 0;
    val = strtol(buffer, &endptr, 10);
    if (errno != 0 || endptr == buffer || *endptr != '\0' || val < 0 || val > INT_MAX) {
        return -1;
    }
    *out = (int)val;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    int start;
    int end;
    int oth;
    int nth;
    int result;
    int status;

    if (read_input_line(buffer, sizeof(buffer)) != 0) {
        return EXIT_FAILURE;
    }
    if (parse_int(buffer, &start) != 0) {
        return EXIT_FAILURE;
    }

    if (read_input_line(buffer, sizeof(buffer)) != 0) {
        return EXIT_FAILURE;
    }
    if (parse_int(buffer, &end) != 0) {
        return EXIT_FAILURE;
    }

    if (read_input_line(buffer, sizeof(buffer)) != 0) {
        return EXIT_FAILURE;
    }
    if (parse_int(buffer, &oth) != 0) {
        return EXIT_FAILURE;
    }

    if (read_input_line(buffer, sizeof(buffer)) != 0) {
        return EXIT_FAILURE;
    }
    if (parse_int(buffer, &nth) != 0) {
        return EXIT_FAILURE;
    }

    status = count_bits_set(start, end, oth, nth, &result);
    if (status != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}