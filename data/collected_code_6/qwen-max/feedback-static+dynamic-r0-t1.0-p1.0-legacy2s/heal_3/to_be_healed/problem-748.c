#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void add_spaces_to_capitalized_words(char *str) {
    regex_t regex;
    regmatch_t match[1];
    int offset = 0;

    const char *pattern = "([A-Z][a-zA-Z]*)";

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return;
    }

    /* Possible weaknesses found:
     *  Value stored to 'str_len' during its initialization is never read [deadcode.DeadStores]
     *  Variable 'str_len' is assigned a value that is never used. [unreadVariable]
     */
    size_t str_len = strlen(str);
    char *new_str = malloc(strlen(str) * 2 + 1);
    if (new_str == NULL) {
        regfree(&regex);
        return;
    }

    char *pos = new_str;
    while (regexec(&regex, str + offset, 1, match, 0) == 0) {
        size_t match_len = match[0].rm_eo - match[0].rm_so;
        if (offset > 0 && pos > new_str && *(pos - 1) != ' ') {
            *pos++ = ' ';
        }
        /* Possible weaknesses found:
         * ASan: memcpy-param-overlap:
         */
        memcpy(pos, str + offset, match_len);
        pos += match_len;
        offset += match_len;
    }
    *pos = '\0';

    strcpy(str, new_str);
    free(new_str);
    regfree(&regex);
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    add_spaces_to_capitalized_words(str);
    printf("%s\n", str);
    return 0;
}