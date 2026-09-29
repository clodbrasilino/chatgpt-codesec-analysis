#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void print_numbers_and_positions(const char *str) {
    if (str == NULL) return;

    size_t max_len = 1024;
    size_t len = strnlen(str, max_len);
    size_t i = 0;
    size_t max_num_len = 256;
    char *buffer = malloc(max_num_len + 1);

    if (buffer == NULL) return;

    while (i < len) {
        if (isdigit((unsigned char)str[i])) {
            size_t start = i;
            while (i < len && isdigit((unsigned char)str[i])) {
                i++;
            }

            size_t num_len = i - start;
            if (num_len >= max_num_len) {
                continue;
            }

            snprintf(buffer, max_num_len + 1, "%.*s", (int)num_len, str + start);

            char *endptr;
            long number = strtol(buffer, &endptr, 10);
            if (endptr != buffer) {
                printf("Number: %ld, Position: %zu\n", number, start);
            }
        } else {
            i++;
        }
    }

    free(buffer);
}

int main(void) {
    const char *input = "abc123def4567gh89i0";
    print_numbers_and_positions(input);
    return 0;
}