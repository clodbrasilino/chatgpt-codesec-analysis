#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* camel_to_snake(const char* camel_case) {
    if (camel_case == NULL) {
        return NULL;
    }

    size_t length = 0;
    size_t snake_length = 0;
    for (size_t i = 0; camel_case[i] != '\0'; i++) {
        length++;
        snake_length++;
        if (isupper((unsigned char)camel_case[i]) && i > 0) {
            snake_length++;
        }
    }

    if (length == 0) {
        char* empty_str = (char*)malloc(1);
        if (empty_str != NULL) {
            empty_str[0] = '\0';
        }
        return empty_str;
    }

    char* snake_case = (char*)malloc(snake_length + 1);
    if (snake_case == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < length; i++) {
        if (isupper((unsigned char)camel_case[i])) {
            if (i > 0 && camel_case[i-1] != '_') {
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
    char buffer[1024];
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%1023s", buffer) == 1) {
        char* result = camel_to_snake(buffer);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        }
    }
    return EXIT_SUCCESS;
}