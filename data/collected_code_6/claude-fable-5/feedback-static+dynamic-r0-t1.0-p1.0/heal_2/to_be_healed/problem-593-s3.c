#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_IP_LEN 64

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t n = 0;

    while (n < max_len && s[n] != '\0') {
        n++;
    }
    return n;
}

int remove_leading_zeroes(const char *input, char *output, size_t out_size)
{
    size_t i = 0;
    size_t j = 0;
    size_t len;

    if (input == NULL || output == NULL || out_size == 0) {
        return -1;
    }

    len = bounded_strlen(input, MAX_IP_LEN);
    if (len >= MAX_IP_LEN) {
        return -1;
    }

    while (i < len) {
        if (isdigit((unsigned char)input[i])) {
            size_t start = i;
            while (i < len && isdigit((unsigned char)input[i])) {
                i++;
            }
            while (start < i - 1 && input[start] == '0') {
                start++;
            }
            while (start < i) {
                if (j + 1 >= out_size) {
                    return -1;
                }
                output[j] = input[start];
                j++;
                start++;
            }
        } else if (input[i] == '.') {
            if (j + 1 >= out_size) {
                return -1;
            }
            output[j] = input[i];
            j++;
            i++;
        } else {
            return -1;
        }
    }

    if (j >= out_size) {
        return -1;
    }
    output[j] = '\0';
    return 0;
}

int main(void)
{
    const char *tests[] = {
        "192.068.001.010",
        "010.020.030.040",
        "000.000.000.000",
        "127.0.0.1"
    };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[MAX_IP_LEN];
    size_t i;
    size_t count = sizeof(tests) / sizeof(tests[0]);

    memset(result, 0, sizeof(result));

    for (i = 0; i < count; i++) {
        if (remove_leading_zeroes(tests[i], result, sizeof(result)) == 0) {
            if (printf("%s -> %s\n", tests[i], result) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (fprintf(stderr, "Invalid input: %s\n", tests[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}