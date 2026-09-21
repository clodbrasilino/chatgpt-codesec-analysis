#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_LEN 4096

char* camel_to_snake(const char* camel_case) {
    if (camel_case == NULL) {
        return NULL;
    }

    size_t len = strnlen(camel_case, MAX_STR_LEN);
    if (len == 0) {
        char* empty = (char*)malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }

    size_t new_len = len;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel_case[i]) && i > 0) {
            new_len++;
        }
    }

    char* snake_case = (char*)malloc(new_len + 1);
    if (snake_case == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel_case[i])) {
            if (i > 0) {
                snake_case[j++] = '_';
            }
            snake_case[j++] = tolower((unsigned char)camel_case[i]);
        } else {
            snake_case[j++] = camel_case[i];
        }
    }
    snake_case[j] = '\0';

    return snake_case;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_STR_LEN];
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%4095s", input) == 1) {
        char* res = camel_to_snake(input);
        if (res) {
            printf("%s\n", res);
            free(res);
        }
    }
    return 0;
}