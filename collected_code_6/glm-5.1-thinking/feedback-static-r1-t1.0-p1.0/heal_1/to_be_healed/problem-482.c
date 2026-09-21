#include <stdio.h>
#include <string.h>
#include <regex.h>

int find_sequences(const char *str) {
    if (str == NULL) {
        return 1;
    }

    regex_t regex;
    int ret;
    const char *pattern = "[A-Z][a-z]+";

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char errbuf[128];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "regcomp failed: %s\n", errbuf);
        return ret;
    }

    const char *p = str;
    regmatch_t match[1];

    while (1) {
        ret = regexec(&regex, p, 1, match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char errbuf[128];
            regerror(ret, &regex, errbuf, sizeof(errbuf));
            fprintf(stderr, "regexec failed: %s\n", errbuf);
            regfree(&regex);
            return ret;
        }

        if (match[0].rm_so == -1) {
            break;
        }

        int len = match[0].rm_eo - match[0].rm_so;
        printf("Found: %.*s\n", len, p + match[0].rm_so);

        if (match[0].rm_eo == 0) {
            p += 1;
        } else {
            p += match[0].rm_eo;
        }

        if (*p == '\0') {
            break;
        }
    }

    regfree(&regex);
    return 0;
}

int main(void) {
    const char *text = "Hello World, this Is a Test string with NOlowercase and SomeMatches.";
    find_sequences(text);
    return 0;
}