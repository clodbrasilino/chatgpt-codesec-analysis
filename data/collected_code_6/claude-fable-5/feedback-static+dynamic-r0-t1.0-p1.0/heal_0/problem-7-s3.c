#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

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
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
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
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex execution failed: %s\n", errbuf);
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