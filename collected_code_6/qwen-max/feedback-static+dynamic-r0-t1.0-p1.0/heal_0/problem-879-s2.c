#include <stdio.h>
#include <regex.h>

int match_pattern(const char *str) {
    int ret;
    regex_t preg;

    ret = regcomp(&preg, "^a.*b$", 0);
    if (ret) {
        return 1;
    }

    ret = regexec(&preg, str, 0, NULL, 0);
    regfree(&preg);

    return !ret;
}

int main() {
    const char *test_strings[] = {"ab", "a123b", "axxb", "acb", "a b", "b"};
    int i;

    for (i = 0; i < 6; i++) {
        if (match_pattern(test_strings[i])) {
            printf("'%s' matches the pattern\n", test_strings[i]);
        } else {
            printf("'%s' does not match the pattern\n", test_strings[i]);
        }
    }

    return 0;
}