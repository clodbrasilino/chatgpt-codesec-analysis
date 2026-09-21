#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *camel_to_snake(const char *camel_str);

char *camel_to_snake(const char *camel_str) {
    if (camel_str == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; camel_str[i] != '\0'; i++) {
        if (isupper((unsigned char)camel_str[i]) && i > 0) {
            count += 2;
        } else {
            count += 1;
        }
    }

    char *snake_str = (char *)malloc(count + 1);
    if (snake_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; camel_str[i] != '\0'; i++) {
        if (isupper((unsigned char)camel_str[i])) {
            if (i > 0) {
                snake_str[j++] = '_';
            }
            snake_str[j++] = (char)tolower((unsigned char)camel_str[i]);
        } else {
            snake_str[j++] = camel_str[i];
        }
    }
    snake_str[j] = '\0';

    return snake_str;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            char *snake = camel_to_snake(argv[i]);
            if (snake != NULL) {
                printf("%s\n", snake);
                free(snake);
            }
        }
    } else {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buffer[4096];
        /* Possible weaknesses found:
         * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
         */
        while (scanf("%4095s", buffer) == 1) {
            char *snake_case = camel_to_snake(buffer);
            if (snake_case != NULL) {
                printf("%s\n", snake_case);
                free(snake_case);
            }
        }
    }
    return 0;
}