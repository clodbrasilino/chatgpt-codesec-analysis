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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    text_len = strlen(text);
    if (text_len >= 8192) {
        return;
    }

    ret = regcomp(&regex, "\\b[A-Za-z]{4,}\\b", REG_EXTENDED);
    if (ret) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return;
    }

    p = text;

    while (regexec(&regex, p, 1, &match, 0) == 0) {
        /* Possible weaknesses found:
         *  Assuming that condition 'match.rm_so>=match.rm_eo' is not redundant
         */
        if (match.rm_so < 0 || match.rm_eo < 0 || match.rm_so >= match.rm_eo) {
            p++;
            if ((size_t)(p - text) >= text_len) break;
            continue;
        }

        /* Possible weaknesses found:
         *  Assignment 'len=(unsigned long)(match.rm_eo-match.rm_so)', assigned value is greater than 0
         */
        size_t len = (size_t)(match.rm_eo - match.rm_so);
        size_t offset = (size_t)(p - text);
        size_t remaining = text_len - offset;

        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (match.rm_so >= remaining || match.rm_eo > remaining) {
            p++;
            if ((size_t)(p - text) >= text_len) break;
            continue;
        }

        /* Possible weaknesses found:
         *  Condition 'len==0' is always false
         *  Condition 'len==0' is always false [knownConditionTrueFalse]
         */
        if (len == 0) {
            p++;
            if ((size_t)(p - text) >= text_len) break;
            continue;
        }

        if (len > remaining - match.rm_so) {
            len = remaining - match.rm_so;
        }

        if (len == 0) {
            p++;
            if ((size_t)(p - text) >= text_len) break;
            continue;
        }

        char *result = (char *)malloc(len + 1);
        if (!result) {
            regfree(&regex);
            return;
        }

        if (offset + match.rm_so + len <= text_len) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result, p + match.rm_so, len);
            result[len] = '\0';
            printf("%s\n", result);
        }

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