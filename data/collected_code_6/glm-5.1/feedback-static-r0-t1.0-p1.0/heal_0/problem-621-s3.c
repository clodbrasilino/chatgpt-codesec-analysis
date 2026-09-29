#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *increment_string_numbers(const char *input, int k) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t res_idx = 0;
    size_t i = 0;

    while (i < len) {
        if (isdigit((unsigned char)input[i])) {
            long num = 0;
            while (i < len && isdigit((unsigned char)input[i])) {
                num = num * 10 + (input[i] - '0');
                i++;
            }

            num += k;

            if (num < 0) {
                num = 0;
            }

            char num_buf[32];
            int num_len = snprintf(num_buf, sizeof(num_buf), "%ld", num);

            size_t new_size = res_idx + num_len + len - i + 1;
            char *temp = realloc(result, new_size);
            if (temp == NULL) {
                free(result);
                return NULL;
            }
            result = temp;

            memcpy(result + res_idx, num_buf, num_len);
            res_idx += num_len;
        } else {
            result[res_idx++] = input[i++];
        }
    }

    result[res_idx] = '\0';

    char *final_result = realloc(result, res_idx + 1);
    if (final_result != NULL) {
        result = final_result;
    }

    return result;
}

int main(void) {
    const char *str = "abc123def45gh6";
    int k = 7;

    char *incremented = increment_string_numbers(str, k);
    if (incremented != NULL) {
        printf("Original: %s\n", str);
        printf("Incremented: %s\n", incremented);
        free(incremented);
    }

    return 0;
}