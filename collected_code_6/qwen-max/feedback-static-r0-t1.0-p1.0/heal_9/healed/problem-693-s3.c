#include <stdio.h>
#include <string.h>
#include <regex.h>

void remove_multiple_spaces(char *input) {
    static const char pattern[] = "[[:space:]]+";
    regex_t reg;
    if (regcomp(&reg, pattern, REG_EXTENDED | REG_NEWLINE)) {
        return;
    }

    regmatch_t match;
    int offset = 0;

    while (regexec(&reg, input + offset, 1, &match, 0) == 0) {
        if (match.rm_so == 0) {
            offset += 1;
            continue;
        }
        size_t len_before = match.rm_so;
        size_t len_after = input[offset + match.rm_eo] ? strlen(input + offset + match.rm_eo) : 0;

        if (len_before + 1 + len_after >= 1024) {
            break;
        }

        memmove(input + offset + len_before + 1, input + offset + match.rm_eo, len_after + 1);
        input[offset + len_before] = ' ';
        offset += 1;
    }

    regfree(&reg);
}

int main() {
    char str[] = "This  is   a    test string. ";
    remove_multiple_spaces(str);
    printf("%s\n", str);
    return 0;
}