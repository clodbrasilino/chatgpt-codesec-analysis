#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char* camel_to_snake(const char *camel) {
    regex_t regex;
    regmatch_t matches[2];
    int len = strlen(camel);
    char *snake = (char *)malloc(len * 2 + 1);
    if (!snake) return NULL;
    snake[0] = '\0';

    if (regcomp(&regex, "([a-z0-9])([A-Z])", REG_EXTENDED | REG_NEWLINE) != 0) {
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

    for (int i = 1; i < len; i++) {
        if (snake[i - 1] == '_' && isupper(snake[i])) {
            snake[i] = tolower(snake[i]);
        }
    }

    regfree(&regex);
    return snake;
}

int main() {
    const char *test_cases[] = {"ThisIsCamelCase", "chrome_cast", "quad_core", "google_assistant"};
    for (size_t i = 0; i < 4; i++) {
        char *snake = camel_to_snake(test_cases[i]);
        if (snake) {
            printf("%s\n", snake);
            free(snake);
        } else {
            fprintf(stderr, "Error converting to snake case.\n");
        }
    }
    return 0;
}