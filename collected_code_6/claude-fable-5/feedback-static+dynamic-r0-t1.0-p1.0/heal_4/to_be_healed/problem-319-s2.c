#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define ERRBUF_SIZE 128U
#define WORD_LEN 5U

int find_five_letter_words(const char *text)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char errbuf[ERRBUF_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[WORD_LEN + 1U];
    int ret;

    if (text == NULL) {
        fprintf(stderr, "Error: input string is NULL\n");
        return -1;
    }

    ret = regcomp(&regex, "[[:alpha:]]+", REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        errbuf[sizeof(errbuf) - 1U] = '\0';
        fprintf(stderr, "Error: regcomp failed: %s\n", errbuf);
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
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(word, cursor + match.rm_so, len);
            word[len] = '\0';
            printf("%s\n", word);
        }

        if (match.rm_eo <= match.rm_so) {
            break;
        }

        cursor += match.rm_eo;
    }

    if (ret != 0 && ret != REG_NOMATCH) {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        errbuf[sizeof(errbuf) - 1U] = '\0';
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