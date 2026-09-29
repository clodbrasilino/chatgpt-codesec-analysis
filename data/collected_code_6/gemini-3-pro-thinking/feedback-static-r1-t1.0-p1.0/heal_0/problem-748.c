#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *insert_spaces_before_caps(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "([^ \t\n\r])([A-Z])", REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t max_len = (strlen(input) * 2) + 1;
    char *result = (char *)malloc(max_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *cursor = input;
    char *res_cursor = result;
    regmatch_t pmatch[3];

    while (regexec(&regex, cursor, 3, pmatch, 0) == 0) {
        size_t copy_len = (size_t)pmatch[1].rm_eo;
        memcpy(res_cursor, cursor, copy_len);
        res_cursor += copy_len;

        *res_cursor = ' ';
        res_cursor++;

        cursor += pmatch[2].rm_so;
    }

    strcpy(res_cursor, cursor);
    regfree(&regex);

    return result;
}

int main(void) {
    const char *test_strings[] = {
        "HelloWorld",
        "ThisIsATest",
        "Already Has Spaces",
        "startsLowercase",
        "ParseURL",
        NULL
    };

    for (size_t i = 0; test_strings[i] != NULL; i++) {
        char *formatted = insert_spaces_before_caps(test_strings[i]);
        if (formatted != NULL) {
            printf("%s\n", formatted);
            free(formatted);
        } else {
            fprintf(stderr, "Error processing string: %s\n", test_strings[i]);
        }
    }

    return 0;
}