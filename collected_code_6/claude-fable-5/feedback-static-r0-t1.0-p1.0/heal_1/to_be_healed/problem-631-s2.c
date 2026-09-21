#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int swap_whitespace_underscore(char *str);

int swap_whitespace_underscore(char *str)
{
    regex_t re;
    regmatch_t match;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char errbuf[128];
    size_t offset;
    size_t len;
    /* Possible weaknesses found:
     *  The scope of the variable 'pos' can be reduced. [variableScope]
     */
    size_t pos;
    int rc;

    if (str == NULL) {
        return -1;
    }

    rc = regcomp(&re, "[ \t_]", REG_EXTENDED);
    if (rc != 0) {
        (void)regerror(rc, &re, errbuf, sizeof(errbuf));
        (void)fprintf(stderr, "regcomp failed: %s\n", errbuf);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    offset = 0;

    while (offset < len) {
        rc = regexec(&re, str + offset, 1, &match, 0);
        if (rc == REG_NOMATCH) {
            break;
        }
        if (rc != 0) {
            (void)regerror(rc, &re, errbuf, sizeof(errbuf));
            (void)fprintf(stderr, "regexec failed: %s\n", errbuf);
            regfree(&re);
            return -1;
        }
        pos = offset + (size_t)match.rm_so;
        if (pos >= len) {
            break;
        }
        if (str[pos] == '_') {
            str[pos] = ' ';
        } else {
            str[pos] = '_';
        }
        offset = pos + 1;
    }

    regfree(&re);
    return 0;
}

int main(void)
{
    char text[] = "hello world_example text_with mixed_content";

    if (swap_whitespace_underscore(text) != 0) {
        (void)fprintf(stderr, "conversion failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", text) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}