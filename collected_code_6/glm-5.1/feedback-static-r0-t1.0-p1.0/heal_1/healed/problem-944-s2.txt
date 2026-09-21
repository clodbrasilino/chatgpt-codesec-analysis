#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void print_numbers_and_positions(const char *str, size_t max_len) {
    size_t i = 0;

    while (i < max_len) {
        if (str[i] == '\0') {
            break;
        }

        if (isdigit((unsigned char)str[i])) {
            size_t start = i;
            while (i < max_len && str[i] != '\0' && isdigit((unsigned char)str[i])) {
                i++;
            }

            size_t num_len = i - start;
            char num_str[32];
            if (num_len >= sizeof(num_str)) {
                continue;
            }

            memcpy(num_str, str + start, num_len);
            num_str[num_len] = '\0';

            long number = strtol(num_str, NULL, 10);
            printf("Number: %ld, Position: %zu\n", number, start);
        } else {
            i++;
        }
    }
}

int main(void) {
    const char *input = "abc123def4567gh89i0";
    print_numbers_and_positions(input, 256);
    return 0;
}