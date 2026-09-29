#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void split_at_uppercase(const char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (ret != 0) {
        return;
    }

    regmatch_t match;
    const char *cursor = str;
    
    if (*cursor != '\0' && *cursor >= 'A' && *cursor <= 'Z') {
        putchar(*cursor);
        cursor++;
    }

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        int match_pos = match.rm_so;
        
        for (int i = 0; i < match_pos; i++) {
            putchar(cursor[i]);
        }
        
        printf(" ");
        putchar(cursor[match_pos]);
        
        cursor += match.rm_so + 1;
    }

    while (*cursor != '\0') {
        putchar(*cursor);
        cursor++;
    }
    printf("\n");

    regfree(&regex);
}

int main(void) {
    const char *test_str = "SplitThisStringAtUppercaseLetters";
    split_at_uppercase(test_str);
    return 0;
}