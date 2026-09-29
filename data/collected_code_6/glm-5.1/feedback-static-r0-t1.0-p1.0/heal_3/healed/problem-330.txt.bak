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

        int start = match[0].rm_so;
        int end = match[0].rm_eo;
        int length = end - start;

        char *word = malloc(length + 1);
        if (word == NULL) {
            regfree(&regex);
            return -1;
        }

        memcpy(word, cursor + start, length);
        word[length] = '\0';

        printf("%s\n", word);
        free(word);

        cursor += end;
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