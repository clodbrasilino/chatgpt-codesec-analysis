#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* camel_to_snake(const char *camel) {
    regex_t regex;
    regmatch_t matches[2];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(camel);
    char *snake = (char *)malloc(len * 2 + 1);
    if (!snake) return NULL;
    snake[0] = '\0';

    if (regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        free(snake);
        return NULL;
    }

    const char *p = camel;
    size_t snake_len = 0;

    while (*p) {
        if (regexec(&regex, p, 2, matches, 0) == 0) {
            size_t match_len = matches[1].rm_eo - matches[1].rm_so;
            if (snake_len + match_len + 1 <= len * 2 + 1) {
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(snake + snake_len, p, match_len);
                snake[snake_len + match_len] = '\0';
                snake_len += match_len;
                if (snake_len + 1 <= len * 2 + 1) {
                    snake[snake_len++] = '_';
                }
            }
            p += matches[1].rm_eo;
        } else {
            if (snake_len + 1 <= len * 2 + 1) {
                snake[snake_len++] = *p;
            }
            p++;
        }
    }

    snake[snake_len] = '\0';
    regfree(&regex);
    return snake;
}

int main() {
    const char *camel = "ThisIsCamelCase";
    char *snake = camel_to_snake(camel);
    if (snake) {
        printf("%s\n", snake);
        free(snake);
    } else {
        fprintf(stderr, "Error converting to snake case.\n");
    }
    return 0;
}