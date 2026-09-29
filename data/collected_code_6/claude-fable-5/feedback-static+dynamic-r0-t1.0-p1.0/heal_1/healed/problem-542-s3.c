#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static void print_regex_error(int errcode, const regex_t *regex, const char *prefix);
int replace_with_colon(char *str);

static void print_regex_error(int errcode, const regex_t *regex, const char *prefix)
{
    size_t needed;
    char *errbuf;

    needed = regerror(errcode, regex, NULL, 0);
    errbuf = malloc(needed);
    if (errbuf == NULL) {
        fprintf(stderr, "%s: unable to allocate error buffer\n", prefix);
        return;
    }
    regerror(errcode, regex, errbuf, needed);
    fprintf(stderr, "%s: %s\n", prefix, errbuf);
    free(errbuf);
}

int replace_with_colon(char *str)
{
    regex_t regex;
    regmatch_t match;
    int ret;
    size_t offset = 0;

    if (str == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0) {
        print_regex_error(ret, &regex, "Regex compilation failed");
        return -1;
    }

    while (str[offset] != '\0') {
        ret = regexec(&regex, str + offset, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            print_regex_error(ret, &regex, "Regex execution failed");
            regfree(&regex);
            return -1;
        }
        str[offset + (size_t)match.rm_so] = ':';
        offset += (size_t)match.rm_eo;
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    char text[] = "Hello world, this is a.test string. Enjoy,coding today";

    printf("Original: %s\n", text);

    if (replace_with_colon(text) != 0) {
        fprintf(stderr, "Replacement failed\n");
        return EXIT_FAILURE;
    }

    printf("Modified: %s\n", text);

    return EXIT_SUCCESS;
}