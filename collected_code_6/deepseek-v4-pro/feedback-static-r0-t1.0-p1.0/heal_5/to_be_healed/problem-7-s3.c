#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define ERR_BUF_SIZE 512
#define MAX_WORD_LEN 1024

void find_words(const char *text) {
    regex_t regex;
    regmatch_t match;
    const char *p = text;
    int ret;

    ret = regcomp(&regex, "\\b[A-Za-z]{4,}\\b", REG_EXTENDED);
    if (ret) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char errbuf[ERR_BUF_SIZE];
        regerror(ret, &regex, errbuf, ERR_BUF_SIZE);
        errbuf[ERR_BUF_SIZE - 1] = '\0';
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return;
    }

    while (regexec(&regex, p, 1, &match, 0) == 0) {
        if (match.rm_so < 0 || match.rm_eo < 0) {
            break;
        }

        size_t len = (size_t)(match.rm_eo - match.rm_so);
        if (len == 0 || len > MAX_WORD_LEN) {
            p++;
            continue;
        }

        char *result = (char *)malloc(len + 1);
        if (!result) {
            regfree(&regex);
            return;
        }

        const char *src = p + match.rm_so;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t remaining = strlen(p);
        if ((size_t)match.rm_so >= remaining) {
            free(result);
            p++;
            continue;
        }

        size_t src_len = remaining - (size_t)match.rm_so;
        if (src_len < len) {
            len = src_len;
        }

        if (len > MAX_WORD_LEN) {
            len = MAX_WORD_LEN;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, src, len);
        result[len] = '\0';
        printf("%s\n", result);
        free(result);

        p += match.rm_eo;
    }

    regfree(&regex);
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    find_words(argv[1]);
    return EXIT_SUCCESS;
}