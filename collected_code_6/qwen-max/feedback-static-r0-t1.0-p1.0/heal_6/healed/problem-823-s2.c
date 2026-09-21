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

    int ret;
    regex_t reg;

    ret = regcomp(&reg, "^\\Q", REG_EXTENDED | REG_NOSUB);
    if (ret) {
        return 0;
    }

    for (size_t i = 0; i < prefix_len; ++i) {
        switch (prefix[i]) {
            case '\\':
                ret = regcomp(&reg, "\\E\\\\\\Q", REG_EXTENDED | REG_NOSUB);
                break;
            case '[':
                ret = regcomp(&reg, "\\E[\\Q", REG_EXTENDED | REG_NOSUB);
                break;
            case ']':
                ret = regcomp(&reg, "\\E]\\Q", REG_EXTENDED | REG_NOSUB);
                break;
            case '^':
                ret = regcomp(&reg, "\\E^\\Q", REG_EXTENDED | REG_NOSUB);
                break;
            case '$':
                ret = regcomp(&reg, "\\E$\\Q", REG_EXTENDED | REG_NOSUB);
                break;
            case '.':
                ret = regcomp(&reg, "\\E.\\Q", REG_EXTENDED | REG_NOSUB);
                break;
            case '*':
                ret = regcomp(&reg, "\\E*\\Q", REG_EXTENDED | REG_NOSUB);
                break;
            case '+':
                ret = regcomp(&reg, "\\E+\\Q", REG_EXTENDED | REG_NOSUB);
                break;
            case '?':
                ret = regcomp(&reg, "\\E?\\Q", REG_EXTENDED | REG_NOSUB);
                break;
            case '(':
                ret = regcomp(&reg, "\\E(\\Q", REG_EXTENDED | REG_NOSUB);
                break;
            case ')':
                ret = regcomp(&reg, "\\E)\\Q", REG_EXTENDED | REG_NOSUB);
                break;
            case '{':
                ret = regcomp(&reg, "\\E{\\Q", REG_EXTENDED | REG_NOSUB);
                break;
            case '}':
                ret = regcomp(&reg, "\\E}\\Q", REG_EXTENDED | REG_NOSUB);
                break;
            case '|':
                ret = regcomp(&reg, "\\E|\\Q", REG_EXTENDED | REG_NOSUB);
                break;
            default:
                ret = regcomp(&reg, &prefix[i], REG_EXTENDED | REG_NOSUB);
        }
        if (ret) {
            regfree(&reg);
            return 0;
        }
    }

    ret = regcomp(&reg, "\\E", REG_EXTENDED | REG_NOSUB);
    if (ret) {
        regfree(&reg);
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