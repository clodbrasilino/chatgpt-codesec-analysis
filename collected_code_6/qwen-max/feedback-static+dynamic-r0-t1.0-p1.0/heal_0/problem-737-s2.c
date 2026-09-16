#include <stdio.h>
#include <regex.h>

int is_string_starting_with_vowel(const char *str) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    if (regcomp(&regex, "^[aeiouAEIOU]", REG_EXTENDED|REG_NOSUB) != 0) {
        return -1;
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        return 1;
    } else if (reti == REG_NOMATCH) {
        return 0;
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return -1;
    }
}

int main() {
    const char *test_str = "example";
    int result = is_string_starting_with_vowel(test_str);

    if (result == 1) {
        printf("The string '%s' starts with a vowel.\n", test_str);
    } else if (result == 0) {
        printf("The string '%s' does not start with a vowel.\n", test_str);
    } else {
        printf("An error occurred while checking the string.\n");
    }

    return 0;
}