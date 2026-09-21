#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define PATTERN_SIZE 128
#define ERRBUF_SIZE 256
#define MAX_WORD_LEN 99

void find_words(const char *str, int min_len, int max_len) {
    regex_t regex;
    regmatch_t match;
    const char *p = str;
    char pattern[PATTERN_SIZE];
    int ret;

    if (min_len < 1 || max_len < min_len || max_len > MAX_WORD_LEN) {
        fprintf(stderr, "Invalid length parameters\n");
        return;
    }

    if (str == NULL) {
        fprintf(stderr, "NULL input string\n");
        return;
    }

    ret = snprintf(pattern, sizeof(pattern), "\\b[A-Za-z]{%d,%d}\\b", min_len, max_len);
    if (ret < 0 || (size_t)ret >= sizeof(pattern)) {
        fprintf(stderr, "Pattern buffer too small\n");
        return;
    }

    memset(&regex, 0, sizeof(regex));
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        char errbuf[ERRBUF_SIZE];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Could not compile regex: %s\n", errbuf);
        regfree(&regex);
        return;
    }

    memset(&match, 0, sizeof(match));
    while (regexec(&regex, p, 1, &match, 0) == 0) {
        if (match.rm_so < 0 || match.rm_eo < 0 || match.rm_so >= match.rm_eo) {
            break;
        }

        regoff_t len = match.rm_eo - match.rm_so;
        if (len <= 0 || len > MAX_WORD_LEN) {
            break;
        }

        size_t remaining = strnlen(p, (size_t)(match.rm_eo + 1));
        if (remaining < (size_t)match.rm_eo) {
            break;
        }

        char *word = malloc((size_t)len + 1);
        if (!word) {
            regfree(&regex);
            return;
        }

        memcpy(word, p + match.rm_so, (size_t)len);
        word[len] = '\0';

        printf("%s\n", word);
        free(word);
        p += match.rm_eo;
        if (*p == '\0') break;
    }

    regfree(&regex);
}

int main(int argc, char *argv[]) {
    char *input = NULL;
    size_t input_len = 0;

    if (argc > 1) {
        input = argv[1];
    } else {
        ssize_t nread = getline(&input, &input_len, stdin);
        if (nread == -1) {
            free(input);
            return 1;
        }
        if (nread > 0 && input[nread - 1] == '\n') {
            input[nread - 1] = '\0';
        }
    }

    if (input != NULL && input[0] != '\0') {
        find_words(input, 3, 3);
        find_words(input, 4, 4);
        find_words(input, 5, 5);
    }

    if (argc == 1 && input != NULL) {
        free(input);
    }

    return 0;
}