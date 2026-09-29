#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculate_min_length(const char *str, size_t max_len) {
    size_t len = strnlen(str, max_len);
    if (len == 0) {
        return 0;
    }

    int count[256] = {0};
    for (size_t i = 0; i < len; i++) {
        unsigned char c = str[i];
        count[c]++;
    }

    int min_count = len;
    for (int i = 0; i < 256; i++) {
        if (count[i] > 0 && count[i] < min_count) {
            min_count = count[i];
        }
    }

    return len - min_count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(argv[1]) > 4096) {
        fprintf(stderr, "Error: Input string exceeds maximum allowed length\n");
        return 1;
    }

    int result = calculate_min_length(argv[1], 4096);
    printf("%d\n", result);

    return 0;
}