#include <stdio.h>
#include <regex.h>

int check_same_start_end(const char *str) {
    regex_t regex;
    int reti;

    if (regcomp(&regex, "^(.).*\\1$", REG_EXTENDED|REG_NOSUB) != 0) {
        return -1;
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    if (reti == 0)
        return 1;
    else if (reti == REG_NOMATCH)
        return 0;
    else
        return -1;
}

int main() {
    const char *test_strings[] = {"radar", "hello", "a", "abba", ""};
    for (const char *s : test_strings) {
        int result = check_same_start_end(s);
        if (result == 1) {
            printf("The string \"%s\" starts and ends with the same character.\n", s);
        } else if (result == 0) {
            printf("The string \"%s\" does not start and end with the same character.\n", s);
        } else {
            printf("Error checking the string \"%s\".\n", s);
        }
    }
    return 0;
}