#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

int starts_with_substring(const char *str, const char *prefix) {
    if (str == NULL || prefix == NULL) {
        return 0;
    }

    size_t prefix_len = strnlen(prefix, 255);
    if (prefix_len >= 255) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char pattern[256];
    snprintf(pattern, sizeof(pattern), "^%.*s", (int)prefix_len, prefix);

    regex_t reg;
    int ret = regcomp(&reg, pattern, REG_EXTENDED | REG_NOSUB);
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