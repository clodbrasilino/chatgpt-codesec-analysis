#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void print_numbers_and_positions(const char *str, size_t max_len) {
    size_t i = 0;
    char num_str[32];

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

size_t safe_strlen(const char *str, size_t max_len) {
    const char *p = str;
    size_t remaining = max_len;
    while (remaining-- && *p != '\0') {
        p++;
    }
    return (size_t)(p - str);
}

int main(void) {
    const char *input = "abc123def4567gh89i0";
    size_t len = safe_strlen(input, 1024);
    print_numbers_and_positions(input, len + 1);
    return 0;
}