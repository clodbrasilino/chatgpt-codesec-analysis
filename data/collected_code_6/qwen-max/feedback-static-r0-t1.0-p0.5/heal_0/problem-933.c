#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* camel_to_snake(const char *camel) {
    regex_t regex;
    regmatch_t matches[2];
    char *snake = (char *)malloc(strlen(camel) * 2 + 1);
    if (!snake) return NULL;
    snake[0] = '\0';

    if (regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        free(snake);
        return NULL;
    }

    const char *p = camel;
    while (*p) {
        if (regexec(&regex, p, 2, matches, 0) == 0) {
            strncat(snake, p, matches[1].rm_eo - matches[1].rm_so);
            strncat(snake, "_", 1);
            p += matches[1].rm_eo;
        } else {
            strncat(snake, p, 1);
            p++;
        }
    }

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