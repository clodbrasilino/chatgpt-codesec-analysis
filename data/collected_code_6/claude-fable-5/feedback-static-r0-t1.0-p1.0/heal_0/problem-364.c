#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min_flips_to_alternate(const char *s)
{
    size_t len;
    size_t i;
    int flips_start_zero;
    int flips_start_one;
    char expected_zero;
    char expected_one;

    if (s == NULL) {
        return -1;
    }

    len = strlen(s);
    if (len == 0) {
        return 0;
    }

    flips_start_zero = 0;
    flips_start_one = 0;

    for (i = 0; i < len; i++) {
        if (s[i] != '0' && s[i] != '1') {
            return -1;
        }

        if ((i % 2) == 0) {
            expected_zero = '0';
            expected_one = '1';
        } else {
            expected_zero = '1';
            expected_one = '0';
        }

        if (s[i] != expected_zero) {
            flips_start_zero++;
        }
        if (s[i] != expected_one) {
            flips_start_one++;
        }
    }

    return (flips_start_zero < flips_start_one) ? flips_start_zero : flips_start_one;
}

int main(void)
{
    char buffer[1024];
    int result;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    result = min_flips_to_alternate(buffer);
    if (result < 0) {
        fprintf(stderr, "Invalid binary string\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    return EXIT_SUCCESS;
}