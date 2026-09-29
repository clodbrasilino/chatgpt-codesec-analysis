#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int starts_with_vowel(const char *str) {
    if (str == NULL) {
        return 0;
    }

    regex_t regex;
    int reti;
    int result = 0;

    reti = regcomp(&regex, "^[AEIOUaeiou]", REG_EXTENDED);
    if (reti) {
        return 0;
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    if (!reti) {
        result = 1;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_strings[] = {
        "Apple",
        "Banana",
        "elephant",
        "Cat",
        "Igloo",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; ++i) {
        if (starts_with_vowel(test_strings[i])) {
            printf("\"%s\" starts with a vowel.\n", test_strings[i]);
        } else {
            printf("\"%s\" does not start with a vowel.\n", test_strings[i]);
        }
    }

    return 0;
}