#include <stdio.h>
#include <string.h>
#include <regex.h>

void remove_multiple_spaces(char *input, size_t input_len) {
    static const char pattern[] = "[[:space:]]+";
    regex_t reg;
    char result[input_len + 1];
    regmatch_t match;
    int offset = 0;

    if (regcomp(&reg, pattern, REG_EXTENDED | REG_NEWLINE) != 0) {
        return;
    }

    while (regexec(&reg, input + offset, 1, &match, 0) == 0) {
        if (match.rm_so == 0) {
            offset += 1;
            continue;
        }
        snprintf(result, input_len - offset + 1, "%.*s %s", 
                 match.rm_so, input + offset, 
                 input + offset + match.rm_eo);
        memmove(input + offset, result, strlen(result) + 1);
        offset += 1;
    }

    regfree(&reg);
}

int main() {
    char str[] = "This  is   a    test string. ";
    size_t str_len = sizeof(str) - 1;
    remove_multiple_spaces(str, str_len);
    printf("%s\n", str);
    return 0;
}