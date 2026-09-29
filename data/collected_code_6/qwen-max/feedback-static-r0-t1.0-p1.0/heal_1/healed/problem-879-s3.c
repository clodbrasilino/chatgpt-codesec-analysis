#include <stdio.h>
#include <regex.h>

int match_string(const char *str) {
    regex_t regex;
    int ret;

    if (regcomp(&regex, "^a.*b$", REG_EXTENDED) != 0) {
        return 0;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    return !ret;
}

int main() {
    const char *test_strings[] = {"a2b", "abc", "acb", "a123b", "ab", "b"};
    for (int i = 0; i < 6; ++i) {
        if (match_string(test_strings[i])) {
            printf("Match: %s\n", test_strings[i]);
        } else {
            printf("No Match: %s\n", test_strings[i]);
        }
    }
    return 0;
}