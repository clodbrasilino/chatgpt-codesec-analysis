#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int find_long_words(const char *text)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    int ret;

    if (text == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "[[:alpha:]]{4,}", REG_EXTENDED);
    if (ret != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char errbuf[256];
        errbuf[0] = '\0';
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        errbuf[sizeof(errbuf) - 1] = '\0';
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return -1;
    }

    cursor = text;
    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            break;
        }

        {
            size_t length = (size_t)(match.rm_eo - match.rm_so);
            char *word = malloc(length + 1);

            if (word == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                regfree(&regex);
                return -1;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(word, cursor + match.rm_so, length);
            word[length] = '\0';
            printf("%s\n", word);
            free(word);
        }

        cursor += match.rm_eo;
        if (*cursor == '\0') {
            break;
        }
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *input = "The quick brown fox jumps over a lazy dog near it";

    if (find_long_words(input) != 0) {
        fprintf(stderr, "Failed to process input string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}