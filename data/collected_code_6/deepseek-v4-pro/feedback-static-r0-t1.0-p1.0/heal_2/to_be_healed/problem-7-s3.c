#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_words(const char *text) {
    regex_t regex;
    regmatch_t match;
    const char *p = text;
    int ret;
    /* Possible weaknesses found:
     *  The scope of the variable 'errbuf' can be reduced. [variableScope]
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char errbuf[512];

    ret = regcomp(&regex, "\\b[A-Za-z]{4,}\\b", REG_EXTENDED);
    if (ret) {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return;
    }

    while (regexec(&regex, p, 1, &match, 0) == 0) {
        size_t len = match.rm_eo - match.rm_so;
        if (len > 1024) {
            regfree(&regex);
            return;
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