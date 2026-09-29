#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *camel_to_snake(const char *camel_case) {
    if (camel_case == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (camel_case[len] != '\0') {
        len++;
    }

    char *snake_case = malloc((len * 2) + 1);
    
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
    char buffer[4096];
    
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    while (scanf("%4095s", buffer) == 1) {
        char *result = camel_to_snake(buffer);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        } else {
            fprintf(stderr, "Memory allocation failed.\n");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}