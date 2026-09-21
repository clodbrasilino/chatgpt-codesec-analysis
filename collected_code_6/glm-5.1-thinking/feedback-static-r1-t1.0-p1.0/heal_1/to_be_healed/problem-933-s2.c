#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char *camel_to_snake(const char *camel) {
    if (camel == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(camel);
    char *snake = malloc(len * 2 + 1);
    if (snake == NULL) {
        return NULL;
    }

    regex_t regex;
    int reti = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (reti != 0) {
        free(snake);
        return NULL;
    }

    regmatch_t match;
    size_t in_idx = 0;
    size_t out_idx = 0;

    while (1) {
        reti = regexec(&regex, camel + in_idx, 1, &match, 0);
        if (reti == REG_NOMATCH) {
            size_t rem = len - in_idx;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(snake + out_idx, camel + in_idx, rem);
            out_idx += rem;
            break;
        }

        if (reti != 0) {
            free(snake);
            regfree(&regex);
            return NULL;
        }

        size_t pre_match_len = match.rm_so;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(snake + out_idx, camel + in_idx, pre_match_len);
        out_idx += pre_match_len;
        in_idx += pre_match_len;

        if (in_idx > 0) {
            snake[out_idx++] = '_';
        }

        snake[out_idx++] = tolower((unsigned char)camel[in_idx]);
        in_idx += match.rm_eo - match.rm_so;
    }

    snake[out_idx] = '\0';
    regfree(&regex);

    char *shrunk = realloc(snake, out_idx + 1);
    if (shrunk != NULL) {
        return shrunk;
    }

    return snake;
}

int main(void) {
    const char *inputs[] = {"camelCase", "CamelCase", "getHTTPResponse", "simple", "aB", NULL};
    for (int i = 0; inputs[i] != NULL; i++) {
        char *result = camel_to_snake(inputs[i]);
        if (result != NULL) {
            printf("%s -> %s\n", inputs[i], result);
            free(result);
        }
    }
    return 0;
}