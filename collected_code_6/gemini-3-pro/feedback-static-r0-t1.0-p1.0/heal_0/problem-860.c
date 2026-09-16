#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

int ends_with_alphanumeric(const char *str) {
    if (str == NULL) {
        return 0;
    }

    regex_t regex;
    int reti;
    int result = 0;

    reti = regcomp(&regex, "[a-zA-Z0-9]$", REG_EXTENDED);
    if (reti != 0) {
        return 0;
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    if (reti == 0) {
        result = 1;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_strings[] = {
        "HelloWorld123",
        "Hello World!",
        "EndingWithSpace ",
        "JustLetters",
        "Numbers99",
        "",
        NULL
    };

    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; i++) {
        if (test_strings[i] != NULL) {
            int result = ends_with_alphanumeric(test_strings[i]);
            printf("String: '%s' - Ends with alphanumeric: %s\n", 
                   test_strings[i], result ? "Yes" : "No");
        }
    }

    return 0;
}