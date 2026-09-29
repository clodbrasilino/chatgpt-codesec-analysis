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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char errbuf[ERRBUF_SIZE];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Could not compile regex: %s\n", errbuf);
        regfree(&regex);
        return;
    }

    memset(&match, 0, sizeof(match));
    while (regexec(&regex, p, 1, &match, 0) == 0) {
        /* Possible weaknesses found:
         *  Assuming that condition 'match.rm_so>=match.rm_eo' is not redundant
         */
        if (match.rm_so < 0 || match.rm_eo < 0 || match.rm_so >= match.rm_eo) {
            break;
        }

        /* Possible weaknesses found:
         *  Assignment 'len=match.rm_eo-match.rm_so', assigned value is greater than 0
         */
        int len = match.rm_eo - match.rm_so;
        /* Possible weaknesses found:
         *  Condition 'len<=0' is always false [knownConditionTrueFalse]
         *  Condition 'len<=0' is always false
         */
        if (len <= 0 || len > MAX_WORD_LEN) {
            break;
        }

        char *word = malloc((size_t)len + 1);
        if (!word) {
            regfree(&regex);
            return;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t remaining = strlen(p);
        if ((size_t)match.rm_so > remaining || (size_t)len > remaining - (size_t)match.rm_so) {
            free(word);
            break;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
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