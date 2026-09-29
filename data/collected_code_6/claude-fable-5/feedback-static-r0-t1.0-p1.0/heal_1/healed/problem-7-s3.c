#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static void print_regex_error(int errcode, const regex_t *regex, const char *context)
{
    size_t needed;
    char *errbuf;

    needed = regerror(errcode, regex, NULL, 0);
    errbuf = malloc(needed);
    if (errbuf == NULL) {
        fprintf(stderr, "%s: unable to allocate error buffer\n", context);
        return;
    }

    regerror(errcode, regex, errbuf, needed);
    fprintf(stderr, "%s: %s\n", context, errbuf);
    free(errbuf);
}

int find_long_words(const char *text)
{
    regex_t regex;
    regmatch_t match;
    const char *pattern = "[[:alpha:]]{4,}";
    const char *cursor;
    int ret;

    if (text == NULL) {
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        print_regex_error(ret, &regex, "Regex compilation failed");
        return -1;
    }

    cursor = text;
    while ((ret = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        regoff_t start = match.rm_so;
        regoff_t end = match.rm_eo;
        regoff_t length = end - start;

        if (length <= 0) {
            break;
        }

        if (printf("%.*s\n", (int)length, cursor + start) < 0) {
            regfree(&regex);
            return -1;
        }

        cursor += end;
        if (*cursor == '\0') {
            break;
        }
    }

    if (ret != 0 && ret != REG_NOMATCH) {
        print_regex_error(ret, &regex, "Regex execution failed");
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *text = "The quick brown fox jumps over a lazy dog near the riverbank";

    if (find_long_words(text) != 0) {
        fprintf(stderr, "Failed to process text\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}