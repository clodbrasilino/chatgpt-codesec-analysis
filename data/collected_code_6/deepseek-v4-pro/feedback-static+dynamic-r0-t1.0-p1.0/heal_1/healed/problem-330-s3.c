#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_words(const char *str, int min_len, int max_len) {
    regex_t regex;
    regmatch_t match;
    const char *p = str;
    char pattern[128];
    int ret;

    if (min_len < 1 || max_len < min_len || max_len > 99) {
        fprintf(stderr, "Invalid length parameters\n");
        return;
    }

    ret = snprintf(pattern, sizeof(pattern), "\\b[A-Za-z]{%d,%d}\\b", min_len, max_len);
    if (ret < 0 || (size_t)ret >= sizeof(pattern)) {
        fprintf(stderr, "Pattern buffer too small\n");
        return;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Could not compile regex: %s\n", errbuf);
        return;
    }

    while (regexec(&regex, p, 1, &match, 0) == 0) {
        int len = match.rm_eo - match.rm_so;
        if (len <= 0) {
            break;
        }
        char *word = malloc(len + 1);
        if (!word) {
            regfree(&regex);
            return;
        }
        memcpy(word, p + match.rm_so, len);
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
    size_t len = 0;
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

    find_words(input, 3, 3);
    find_words(input, 4, 4);
    find_words(input, 5, 5);

    if (argc == 1) {
        free(input);
    }

    return 0;
}