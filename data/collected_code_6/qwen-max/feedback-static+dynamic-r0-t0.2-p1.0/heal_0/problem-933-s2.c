#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* camel_to_snake(const char *camel) {
    regex_t regex;
    regmatch_t matches[2];
    char *snake, *p, *result;
    int len, match_len;

    if (regcomp(&regex, "([a-z0-9])([A-Z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        return NULL;
    }

    len = strlen(camel);
    snake = malloc(len * 2 + 1);
    if (snake == NULL) {
        regfree(&regex);
        return NULL;
    }
    strcpy(snake, camel);

    p = snake;
    while (regexec(&regex, p, 2, matches, 0) == 0) {
        match_len = matches[0].rm_eo - matches[0].rm_so;
        memmove(p + matches[0].rm_so + 1, p + matches[0].rm_so, match_len + 1);
        p[matches[0].rm_so] = '_';
        p += matches[0].rm_so + 1;
    }

    result = realloc(snake, strlen(snake) + 1);
    if (result == NULL) {
        free(snake);
        regfree(&regex);
        return NULL;
    }

    regfree(&regex);
    return result;
}

int main() {
    const char *camel = "ThisIsCamelCase";
    char *snake = camel_to_snake(camel);
    if (snake != NULL) {
        printf("%s\n", snake);
        free(snake);
    } else {
        printf("Error converting to snake case.\n");
    }
    return 0;
}