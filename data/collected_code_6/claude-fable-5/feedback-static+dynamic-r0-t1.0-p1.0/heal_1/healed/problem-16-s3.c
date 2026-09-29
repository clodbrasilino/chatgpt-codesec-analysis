#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

static void print_regex_error(int rc, const regex_t *re, const char *prefix)
{
    size_t needed;
    char *errbuf;

    needed = regerror(rc, re, NULL, 0);
    errbuf = malloc(needed);
    if (errbuf == NULL) {
        fprintf(stderr, "%s: unknown error (allocation failure)\n", prefix);
        return;
    }
    regerror(rc, re, errbuf, needed);
    fprintf(stderr, "%s: %s\n", prefix, errbuf);
    free(errbuf);
}

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
        print_regex_error(rc, &re, "regcomp failed");
        return -1;
    }

    rc = regexec(&re, text, 0, NULL, 0);
    if (rc == 0) {
        result = 1;
    } else if (rc == REG_NOMATCH) {
        result = 0;
    } else {
        print_regex_error(rc, &re, "regexec failed");
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