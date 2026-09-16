#include <stdio.h>
#include <regex.h>

int match_pattern(const char *str);

int main() {
    const char *test_str1 = "a";
    const char *test_str2 = "ab";
    const char *test_str3 = "abb";
    const char *test_str4 = "acb";

    if (match_pattern(test_str1)) printf("Match for '%s'\n", test_str1);
    if (match_pattern(test_str2)) printf("Match for '%s'\n", test_str2);
    if (match_pattern(test_str3)) printf("Match for '%s'\n", test_str3);
    if (!match_pattern(test_str4)) printf("No match for '%s'\n", test_str4);

    return 0;
}

int match_pattern(const char *str) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "^a(b*)$", REG_EXTENDED | REG_NOSUB);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return 0;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    return !ret;
}