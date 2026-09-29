#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_words(const char *text) {
    regex_t regex;
    regmatch_t match;
    const char *p = text;
    int ret;

    ret = regcomp(&regex, "\\b[A-Za-z]{4,}\\b", REG_EXTENDED);
    if (ret) {
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return;
    }

    while (regexec(&regex, p, 1, &match, 0) == 0) {
        size_t len = match.rm_eo - match.rm_so;

        if (len == 0) {
            p++;
            continue;
        }

        size_t remaining = strlen(p);
        if (match.rm_so >= remaining || match.rm_eo > remaining) {
            p += match.rm_eo;
            continue;
        }

        char *result = (char *)malloc(len + 1);
        if (!result) {
            regfree(&regex);
            return;
        }

        size_t copy_len = (len < remaining - match.rm_so) ? len : remaining - match.rm_so;
        memcpy(result, p + match.rm_so, copy_len);
        result[copy_len] = '\0';

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