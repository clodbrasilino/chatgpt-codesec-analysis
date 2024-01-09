#include <regex.h>
#include <stdbool.h>

bool startsAndEndsWithSameChar(const char* str) {
    regex_t regex;
    regcomp(&regex, "^([a-zA-Z]).*\\1$", REG_EXTENDED);

    int result = regexec(&regex, str, 0, NULL, 0);

    regfree(&regex);

    return result == 0;
}