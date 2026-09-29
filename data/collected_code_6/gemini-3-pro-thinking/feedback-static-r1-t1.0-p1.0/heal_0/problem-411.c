#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    regex_t regex;
    int reti = regcomp(&regex, "_([a-z])", REG_EXTENDED);
    if (reti != 0) {
        return NULL;
    }

    size_t len = strlen(snake_str);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *cursor = snake_str;
    char *res_cursor = result;
    regmatch_t pmatch[2];

    while ((reti = regexec(&regex, cursor, 2, pmatch, 0)) == 0) {
        size_t prefix_len = (size_t)pmatch[0].rm_so;
        memcpy(res_cursor, cursor, prefix_len);
        res_cursor += prefix_len;

        *res_cursor = (char)toupper((unsigned char)cursor[pmatch[1].rm_so]);
        res_cursor++;

        cursor += pmatch[0].rm_eo;
    }

    if (reti != REG_NOMATCH) {
        free(result);
        regfree(&regex);
        return NULL;
    }

    strcpy(res_cursor, cursor);
    regfree(&regex);

    return result;
}

int main(void) {
    const char *test_strings[] = {
        "hello_world",
        "this_is_a_test",
        "alreadyCamel",
        "multiple__underscores",
        "_leading_underscore",
        "trailing_underscore_",
        NULL
    };

    for (size_t i = 0; test_strings[i] != NULL; ++i) {
        char *camel = snake_to_camel(test_strings[i]);
        if (camel != NULL) {
            printf("%s\n", camel);
            free(camel);
        } else {
            fprintf(stderr, "Conversion failed for input at index %zu\n", i);
        }
    }

    return EXIT_SUCCESS;
}