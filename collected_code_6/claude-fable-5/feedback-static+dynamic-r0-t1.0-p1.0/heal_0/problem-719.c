#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int match_a_followed_by_bs(const char *text)
{
    regex_t regex;
    int compile_result;
    int exec_result;

    if (text == NULL) {
        return 0;
    }

    compile_result = regcomp(&regex, "ab*", REG_EXTENDED);
    if (compile_result != 0) {
        char error_buffer[128];
        regerror(compile_result, &regex, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "Regex compilation failed: %s\n", error_buffer);
        return -1;
    }

    exec_result = regexec(&regex, text, 0, NULL, 0);
    regfree(&regex);

    if (exec_result == 0) {
        return 1;
    }
    if (exec_result == REG_NOMATCH) {
        return 0;
    }

    fprintf(stderr, "Regex execution failed\n");
    return -1;
}

int main(void)
{
    const char *test_strings[] = {
        "a",
        "ab",
        "abbb",
        "b",
        "ac",
        "xyz",
        "bba",
        ""
    };
    size_t count = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        int result = match_a_followed_by_bs(test_strings[i]);
        if (result < 0) {
            return EXIT_FAILURE;
        }
        printf("\"%s\" -> %s\n", test_strings[i],
               (result == 1) ? "Match" : "No match");
    }

    return EXIT_SUCCESS;
}