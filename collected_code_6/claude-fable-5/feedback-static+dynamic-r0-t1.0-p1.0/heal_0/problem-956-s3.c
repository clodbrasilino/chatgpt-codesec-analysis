#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static int split_at_uppercase(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char errbuf[256];
    const char *cursor;
    int ret;

    if (input == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "[A-Z][^A-Z]*", REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return -1;
    }

    cursor = input;
    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            if (printf("%s\n", cursor) < 0) {
                regfree(&regex);
                return -1;
            }
            break;
        }
        if (ret != 0) {
            regerror(ret, &regex, errbuf, sizeof(errbuf));
            fprintf(stderr, "Regex execution failed: %s\n", errbuf);
            regfree(&regex);
            return -1;
        }
        if (match.rm_so > 0) {
            if (printf("%.*s\n", (int)match.rm_so, cursor) < 0) {
                regfree(&regex);
                return -1;
            }
        }
        if (match.rm_eo <= match.rm_so) {
            regfree(&regex);
            return -1;
        }
        if (printf("%.*s\n", (int)(match.rm_eo - match.rm_so),
                   cursor + match.rm_so) < 0) {
            regfree(&regex);
            return -1;
        }
        cursor += match.rm_eo;
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *text = "splitThisStringAtUppercaseLetters";

    if (split_at_uppercase(text) != 0) {
        fprintf(stderr, "Failed to split the string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}