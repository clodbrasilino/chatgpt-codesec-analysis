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
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char num_str[32];
            if (num_len >= sizeof(num_str)) {
                continue;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
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
    size_t len = 0;
    /* Possible weaknesses found:
     *  Either the condition 'len<max_len' is redundant or the array 'str[20]' is accessed at index 1023, which is out of bounds. [arrayIndexOutOfBoundsCond]
     *  Assuming that condition 'len<max_len' is not redundant
     *  Array index out of bounds
     */
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

int main(void) {
    const char *input = "abc123def4567gh89i0";
    /* Possible weaknesses found:
     *  Calling function 'safe_strlen', 2nd argument '1024' value is 1024
     */
    print_numbers_and_positions(input, safe_strlen(input, 1024) + 1);
    return 0;
}