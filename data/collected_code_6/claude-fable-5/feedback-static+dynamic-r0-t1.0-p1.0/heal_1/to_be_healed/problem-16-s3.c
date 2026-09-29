#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int match_lowercase_underscore(const char *text)
{
    regex_t re;
    int rc;
    int result;

    if (text == NULL) {
        return -1;
    }

    rc = regcomp(&re, "^[a-z]+_[a-z]+$", REG_EXTENDED | REG_NOSUB);
    if (rc != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char errbuf[256];
        regerror(rc, &re, errbuf, sizeof(errbuf));
        fprintf(stderr, "regcomp failed: %s\n", errbuf);
        return -1;
    }

    rc = regexec(&re, text, 0, NULL, 0);
    if (rc == 0) {
        result = 1;
    } else if (rc == REG_NOMATCH) {
        result = 0;
    } else {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char errbuf[256];
        regerror(rc, &re, errbuf, sizeof(errbuf));
        fprintf(stderr, "regexec failed: %s\n", errbuf);
        result = -1;
    }

    regfree(&re);
    return result;
}

int main(void)
{
    const char *tests[] = {
        "aab_cbbbc",
        "aab_Abbbc",
        "Aaab_abbbc",
        "hello_world",
        "hello",
        "abc_def_ghi"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        int res = match_lowercase_underscore(tests[i]);
        if (res < 0) {
            fprintf(stderr, "Error processing string: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        if (res == 1) {
            printf("\"%s\": Found a match!\n", tests[i]);
        } else {
            printf("\"%s\": Not matched!\n", tests[i]);
        }
    }

    return EXIT_SUCCESS;
}