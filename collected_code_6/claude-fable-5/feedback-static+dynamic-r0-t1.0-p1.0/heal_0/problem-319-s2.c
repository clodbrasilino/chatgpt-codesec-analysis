#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int find_five_letter_words(const char *text)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    char errbuf[128];
    char word[6];
    int ret;

    if (text == NULL) {
        fprintf(stderr, "Error: input string is NULL\n");
        return -1;
    }

    ret = regcomp(&regex, "[[:alpha:]]+", REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Error: regcomp failed: %s\n", errbuf);
        return -1;
    }

    cursor = text;
    while ((ret = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        size_t len = (size_t)(match.rm_eo - match.rm_so);

        if (len == 5U) {
            memcpy(word, cursor + match.rm_so, 5U);
            word[5] = '\0';
            printf("%s\n", word);
        }

        if (match.rm_eo <= match.rm_so) {
            break;
        }

        cursor += match.rm_eo;
    }

    if (ret != 0 && ret != REG_NOMATCH) {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Error: regexec failed: %s\n", errbuf);
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *sample = "The quick brown fox jumps over a lazy dog while birds watch above";

    if (find_five_letter_words(sample) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}