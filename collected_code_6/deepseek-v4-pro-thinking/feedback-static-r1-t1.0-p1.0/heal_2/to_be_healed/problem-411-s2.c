#define _POSIX_C_SOURCE 200809L
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

char *snake_to_camel(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "_([[:alnum:]])", REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t capacity = 64;
    char *output = malloc(capacity);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t dst = 0;
    const char *cursor = input;
    regmatch_t matches[2];

    while (regexec(&regex, cursor, 2, matches, 0) == 0) {
        size_t prefix = (size_t)matches[0].rm_so;

        if (dst + prefix + 2 > capacity) {
            capacity = capacity * 2 > dst + prefix + 2 ? capacity * 2 : dst + prefix + 2;
            char *new_output = realloc(output, capacity);
            if (new_output == NULL) {
                free(output);
                regfree(&regex);
                return NULL;
            }
            output = new_output;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(output + dst, cursor, prefix);
        dst += prefix;

        unsigned char next = (unsigned char)cursor[matches[1].rm_so];
        output[dst++] = (char)toupper(next);

        cursor += matches[0].rm_eo;
    }

    const char *rest = cursor;
    size_t rest_len = 0;
    while (*rest != '\0') {
        rest_len++;
        rest++;
    }

    if (dst + rest_len + 1 > capacity) {
        capacity = dst + rest_len + 1;
        char *new_output = realloc(output, capacity);
        if (new_output == NULL) {
            free(output);
            regfree(&regex);
            return NULL;
        }
        output = new_output;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(output + dst, cursor, rest_len);
    dst += rest_len;
    output[dst] = '\0';

    regfree(&regex);
    return output;
}

int main(void) {
    const char *snake = "hello_world_from_regex";
    char *camel = snake_to_camel(snake);

    if (camel == NULL) {
        return 1;
    }

    printf("%s\n", camel);
    free(camel);

    return 0;
}