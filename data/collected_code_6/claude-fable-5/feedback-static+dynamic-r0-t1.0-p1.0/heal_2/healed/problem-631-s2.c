#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096

int swap_whitespace_underscore(char *str);
static void print_regex_error(int rc, const regex_t *re);

static void print_regex_error(int rc, const regex_t *re)
{
    size_t needed;
    char *errbuf;

    needed = regerror(rc, re, NULL, 0);
    if (needed == 0) {
        (void)fprintf(stderr, "regex error: unknown\n");
        return;
    }

    errbuf = (char *)malloc(needed);
    if (errbuf == NULL) {
        (void)fprintf(stderr, "regex error: allocation failure\n");
        return;
    }

    (void)regerror(rc, re, errbuf, needed);
    errbuf[needed - 1] = '\0';
    (void)fprintf(stderr, "regex error: %s\n", errbuf);
    free(errbuf);
}

int swap_whitespace_underscore(char *str)
{
    regex_t re;
    regmatch_t match;
    size_t offset;
    size_t len;
    int rc;

    if (str == NULL) {
        return -1;
    }

    rc = regcomp(&re, "[ \t_]", REG_EXTENDED);
    if (rc != 0) {
        print_regex_error(rc, &re);
        return -1;
    }

    len = strnlen(str, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        (void)fprintf(stderr, "input too long or not terminated\n");
        regfree(&re);
        return -1;
    }

    offset = 0;

    while (offset < len) {
        rc = regexec(&re, str + offset, 1, &match, 0);
        if (rc == REG_NOMATCH) {
            break;
        }
        if (rc != 0) {
            print_regex_error(rc, &re);
            regfree(&re);
            return -1;
        }

        {
            size_t pos = offset + (size_t)match.rm_so;
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