#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void print_numbers_and_positions(const char *str) {
    if (str == NULL) return;

    size_t max_len = 1024;
    size_t len = strnlen(str, max_len);
    size_t i = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    while (i < len) {
        if (isdigit((unsigned char)str[i])) {
            size_t start = i;
            while (i < len && isdigit((unsigned char)str[i])) {
                i++;
            }

            size_t num_len = i - start;
            if (num_len >= sizeof(buffer)) {
                continue;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(buffer, str + start, num_len);
            buffer[num_len] = '\0';

            char *endptr;
            long number = strtol(buffer, &endptr, 10);
            if (endptr != buffer) {
                printf("Number: %ld, Position: %zu\n", number, start);
            }
        } else {
            i++;
        }
    }
}

int main(void) {
    const char *input = "abc123def4567gh89i0";
    print_numbers_and_positions(input);
    return 0;
}