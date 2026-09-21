#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 1024

char* camel_to_snake(const char *input) {
    if (!input) return NULL;

    size_t in_len = strnlen(input, MAX_INPUT);
    size_t out_size = in_len * 2 + 1;
    char *result = (char*)malloc(out_size);
    if (!result) return NULL;

    size_t j = 0;
    for (size_t i = 0; i < in_len; i++) {
        char c = input[i];
        if (isupper((unsigned char)c)) {
            if (i > 0) {
                result[j++] = '_';
            }
            result[j++] = tolower((unsigned char)c);
        } else {
            result[j++] = c;
        }
    }
    result[j] = '\0';

    char *final_result = (char*)realloc(result, j + 1);
    return final_result ? final_result : result;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT];

    if (fgets(buffer, sizeof(buffer), stdin)) {
        size_t len = strnlen(buffer, sizeof(buffer));
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        char *snake_str = camel_to_snake(buffer);
        if (snake_str) {
            printf("%s\n", snake_str);
            free(snake_str);
        }
    }
    return 0;
}