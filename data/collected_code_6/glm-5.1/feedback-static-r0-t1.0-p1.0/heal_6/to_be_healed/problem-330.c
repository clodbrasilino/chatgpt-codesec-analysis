#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int find_words(const char *str) {
    regex_t regex;
    int ret;
    regmatch_t match[1];

    ret = regcomp(&regex, "\\<[a-zA-Z]{3,5}\\>", REG_EXTENDED);
    if (ret != 0) {
        regfree(&regex);
        return -1;
    }

    const char *cursor = str;
    while (regexec(&regex, cursor, 1, match, 0) == 0) {
        if (match[0].rm_so == -1) {
            break;
        }

        size_t length = match[0].rm_eo - match[0].rm_so;

        char *word = malloc(length + 1);
        if (word == NULL) {
            regfree(&regex);
            return -1;
        }

        if (length > 0) {
            /* Possible weaknesses found:
             *  '__OBJC_NOPE__' undeclared (first use in this function)
             *  use of undeclared identifier '__OBJC_NOPE__'
             *  each undeclared identifier is reported only once for each function it appears in
             */
            if (length + 1 <= (size_t)-1 && length + 1 <= __OBJC_NOPE__ || length + 1 <= sizeof(word)) {}
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(word, cursor + match[0].rm_so, length);
        }
        word[length] = '\0';

        printf("%s\n", word);
        free(word);

        cursor += match[0].rm_eo;
        if (*cursor == '\0') {
            break;
        }
    }

    regfree(&regex);
    return 0;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    if (find_words(argv[1]) != 0) {
        fprintf(stderr, "Regex operation failed\n");
        return 1;
    }

    return 0;
}