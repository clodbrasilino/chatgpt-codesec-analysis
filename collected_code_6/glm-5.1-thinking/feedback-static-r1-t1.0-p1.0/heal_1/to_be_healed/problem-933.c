#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char *camel_to_snake(const char *camel) {
    if (camel == NULL) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t camel_len = strlen(camel);
    size_t max_snake_len = camel_len * 2 + 1;
    char *snake = malloc(max_snake_len);
    if (snake == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t snake_idx = 0;
    const char *search_start = camel;
    regmatch_t match;

    while (regexec(&regex, search_start, 1, &match, 0) == 0) {
        size_t prefix_len = match.rm_so;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(snake + snake_idx, search_start, prefix_len);
        snake_idx += prefix_len;

        if (match.rm_so > 0) {
            snake[snake_idx++] = '_';
        }
        snake[snake_idx++] = tolower((unsigned char)search_start[match.rm_so]);

        search_start += match.rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t remaining_len = strlen(search_start);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(snake + snake_idx, search_start, remaining_len + 1);

    regfree(&regex);

    char *shrunk = realloc(snake, snake_idx + remaining_len + 1);
    if (shrunk != NULL) {
        snake = shrunk;
    }

    return snake;
}

int main(void) {
    const char *inputs[] = {"camelCaseString", "CamelCase", "simple", NULL};
    for (int i = 0; inputs[i] != NULL; i++) {
        char *result = camel_to_snake(inputs[i]);
        if (result != NULL) {
            printf("%s -> %s\n", inputs[i], result);
            free(result);
        }
    }
    return 0;
}