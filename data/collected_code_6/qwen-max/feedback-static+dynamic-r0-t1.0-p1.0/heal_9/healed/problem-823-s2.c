#include <stdio.h>
#include <regex.h>
#include <string.h>

int starts_with_substring(const char *str, const char *prefix) {
    regex_t reg;
    int ret;

    size_t prefix_len = strnlen(prefix, 255);

    if (prefix_len >= 255) {
        return 0;
    }

    char pattern[256];
    snprintf(pattern, sizeof(pattern), "^%.254s", prefix);

    ret = regcomp(&reg, pattern, REG_EXTENDED | REG_NOSUB);
    if (ret) {
        return 0;
    }

    ret = regexec(&reg, str, 0, NULL, 0);
    regfree(&reg);

    return !ret;
}

int main() {
    const char *test_str = "hello world";
    const char *prefix = "he";

    if (starts_with_substring(test_str, prefix)) {
        printf("The string starts with the given prefix.\n");
    } else {
        printf("The string does not start with the given prefix.\n");
    }

    return 0;
}