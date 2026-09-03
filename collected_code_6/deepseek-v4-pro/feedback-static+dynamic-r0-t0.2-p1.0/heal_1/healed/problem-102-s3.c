#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake) {
    if (snake == NULL) {
        return NULL;
    }

    size_t len = strlen(snake);
    char *camel = (char *)malloc(len + 1);
    if (camel == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;
    int capitalize_next = 0;
    int first_char = 1;

    while (snake[i] != '\0') {
        if (snake[i] == '_') {
            capitalize_next = 1;
            i++;
            continue;
        }

        if (capitalize_next) {
            camel[j++] = toupper((unsigned char)snake[i]);
            capitalize_next = 0;
        } else if (first_char) {
            camel[j++] = toupper((unsigned char)snake[i]);
            first_char = 0;
        } else {
            camel[j++] = snake[i];
        }
        i++;
    }

    camel[j] = '\0';
    return camel;
}

int main(void) {
    const char *test1 = "hello_world";
    const char *test2 = "snake_case_string";
    const char *test3 = "alreadyCamel";
    const char *test4 = "multiple__underscores";
    const char *test5 = "_leading_underscore";
    const char *test6 = "trailing_underscore_";
    const char *test7 = "";

    char *result;

    result = snake_to_camel(test1);
    printf("%s -> %s\n", test1, result ? result : "NULL");
    free(result);

    result = snake_to_camel(test2);
    printf("%s -> %s\n", test2, result ? result : "NULL");
    free(result);

    result = snake_to_camel(test3);
    printf("%s -> %s\n", test3, result ? result : "NULL");
    free(result);

    result = snake_to_camel(test4);
    printf("%s -> %s\n", test4, result ? result : "NULL");
    free(result);

    result = snake_to_camel(test5);
    printf("%s -> %s\n", test5, result ? result : "NULL");
    free(result);

    result = snake_to_camel(test6);
    printf("%s -> %s\n", test6, result ? result : "NULL");
    free(result);

    result = snake_to_camel(test7);
    printf("\"%s\" -> \"%s\"\n", test7, result ? result : "NULL");
    free(result);

    result = snake_to_camel(NULL);
    printf("NULL -> %s\n", result ? result : "NULL");
    free(result);

    return 0;
}