#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define ERRBUF_SIZE 128U
#define WORD_LEN 5U

static void print_regex_error(int errcode, const regex_t *regex, const char *context)
{
    char errbuf[ERRBUF_SIZE];

    memset(errbuf, 0, sizeof(errbuf));
    (void)regerror(errcode, regex, errbuf, sizeof(errbuf) - 1U);
    errbuf[sizeof(errbuf) - 1U] = '\0';
    fprintf(stderr, "Error: %s failed: %s\n", context, errbuf);
}

int find_five_letter_words(const char *text)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    char word[WORD_LEN + 1U];
    int ret;

    if (text == NULL) {
        fprintf(stderr, "Error: input string is NULL\n");
        return -1;
    }

    ret = regcomp(&regex, "[[:alpha:]]+", REG_EXTENDED);
    if (ret != 0) {
        print_regex_error(ret, &regex, "regcomp");
        return -1;
    }

    cursor = text;
    while ((ret = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        size_t len;

        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            break;
        }

        len = (size_t)(match.rm_eo - match.rm_so);

        if (len == WORD_LEN && len < sizeof(word)) {
            memset(word, 0, sizeof(word));
            memcpy(word, cursor + match.rm_so, len);
            word[sizeof(word) - 1U] = '\0';
            printf("%s\n", word);
        }

        if (match.rm_eo <= match.rm_so) {
            break;
        }

        cursor += match.rm_eo;
    }

    if (ret != 0 && ret != REG_NOMATCH) {
        print_regex_error(ret, &regex, "regexec");
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