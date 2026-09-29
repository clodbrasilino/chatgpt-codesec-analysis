#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_words(const char *str, int min_len, int max_len) {
    regex_t regex;
    regmatch_t match;
    const char *p = str;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char pattern[128];
    int ret;

    if (min_len < 1 || max_len < min_len || max_len > 99) {
        fprintf(stderr, "Invalid length parameters\n");
        return;
    }

    ret = snprintf(pattern, sizeof(pattern), "\\b[A-Za-z]{%d,%d}\\b", min_len, max_len);
    if (ret < 0 || (size_t)ret >= sizeof(pattern)) {
        fprintf(stderr, "Pattern too long\n");
        return;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    while (p && *p && regexec(&regex, p, 1, &match, 0) == 0) {
        int len = match.rm_eo - match.rm_so;
        if (len <= 0) {
            p++;
            continue;
        }
        char *word = malloc((size_t)len + 1);
        if (!word) {
            regfree(&regex);
            return;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(word, p + match.rm_so, (size_t)len);
        word[len] = '\0';
        printf("%s\n", word);
        free(word);
        p += match.rm_eo;
    }

    regfree(&regex);
}

int main(int argc, char *argv[]) {
    char *input = NULL;
    size_t len = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'nread' can be reduced. [variableScope]
     */
    ssize_t nread;

    if (argc > 1) {
        input = argv[1];
    } else {
        nread = getline(&input, &len, stdin);
        if (nread == -1) {
            free(input);
            return 1;
        }
        if (nread > 0 && input[nread - 1] == '\n') {
            input[nread - 1] = '\0';
        }
    }

    if (!input) {
        return 1;
    }

    find_words(input, 3, 3);
    find_words(input, 4, 4);
    find_words(input, 5, 5);

    if (argc == 1) {
        free(input);
    }

    return 0;
}