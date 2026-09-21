#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static void find_words(const char *text) {
    regex_t regex;
    regmatch_t match;
    const char *p;
    int ret;
    size_t text_len;

    if (!text) {
        return;
    }

    text_len = strnlen(text, 8192);
    if (text_len >= 8192) {
        return;
    }

    ret = regcomp(&regex, "\\b[A-Za-z]{4,}\\b", REG_EXTENDED);
    if (ret) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf) - 1);
        errbuf[sizeof(errbuf) - 1] = '\0';
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return;
    }

    p = text;

    while (regexec(&regex, p, 1, &match, 0) == 0) {
        if (match.rm_so < 0 || match.rm_eo < 0 || match.rm_so >= match.rm_eo) {
            break;
        }

        size_t offset = (size_t)(p - text);
        if (offset >= text_len) {
            break;
        }

        size_t remaining = text_len - offset;

        if ((size_t)match.rm_so >= remaining || (size_t)match.rm_eo > remaining) {
            break;
        }

        size_t len = (size_t)(match.rm_eo - match.rm_so);

        if (len > remaining - (size_t)match.rm_so) {
            break;
        }

        if (len == 0) {
            break;
        }

        if (offset + (size_t)match.rm_so + len > text_len) {
            break;
        }

        char *result = (char *)malloc(len + 1);
        if (!result) {
            regfree(&regex);
            return;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, p + match.rm_so, len);
        result[len] = '\0';
        printf("%s\n", result);

        free(result);

        p += match.rm_eo;
        if ((size_t)(p - text) >= text_len) break;
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