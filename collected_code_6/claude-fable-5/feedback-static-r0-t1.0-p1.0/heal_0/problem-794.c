#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int match_pattern(const char *text)
{
    regex_t regex;
    int result;
    int match;

    if (text == NULL) {
        return 0;
    }

    result = regcomp(&regex, "^a.*b$", REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        char error_buffer[256];
        regerror(result, &regex, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "Regex compilation failed: %s\n", error_buffer);
        return -1;
    }

    result = regexec(&regex, text, 0, NULL, 0);
    regfree(&regex);

    if (result == 0) {
        match = 1;
    } else if (result == REG_NOMATCH) {
        match = 0;
    } else {
        fprintf(stderr, "Regex execution failed\n");
        match = -1;
    }

    return match;
}

int main(void)
{
    const char *test_strings[] = {
        "ab",
        "acb",
        "a123b",
        "abc",
        "xab",
        "a",
        "b",
        "aXXXXb"
    };
    size_t count = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        int result = match_pattern(test_strings[i]);
        if (result < 0) {
            fprintf(stderr, "Error matching string: %s\n", test_strings[i]);
            return EXIT_FAILURE;
        }
        printf("\"%s\" -> %s\n", test_strings[i],
               (result == 1) ? "match" : "no match");
    }

    return EXIT_SUCCESS;
}