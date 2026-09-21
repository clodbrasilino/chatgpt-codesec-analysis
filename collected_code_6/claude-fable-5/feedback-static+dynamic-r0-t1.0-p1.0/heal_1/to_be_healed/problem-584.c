#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_ERROR_MSG 128

int find_adverbs(const char *sentence)
{
    regex_t regex;
    regmatch_t match;
    const char *pattern = "[A-Za-z]+ly";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char error_buf[MAX_ERROR_MSG];
    int ret;
    size_t offset = 0;
    size_t len;

    if (sentence == NULL) {
        fprintf(stderr, "Invalid input: sentence is NULL\n");
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &regex, error_buf, sizeof(error_buf));
        fprintf(stderr, "Regex compilation failed: %s\n", error_buf);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(sentence);

    while (offset < len) {
        ret = regexec(&regex, sentence + offset, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            regerror(ret, &regex, error_buf, sizeof(error_buf));
            fprintf(stderr, "Regex execution failed: %s\n", error_buf);
            regfree(&regex);
            return -1;
        }

        {
            size_t start = offset + (size_t)match.rm_so;
            size_t end = offset + (size_t)match.rm_eo;
            size_t word_len = end - start;
            char *word = malloc(word_len + 1);

            if (word == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                regfree(&regex);
                return -1;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(word, sentence + start, word_len);
            word[word_len] = '\0';
            printf("Adverb: %-15s Position: %zu-%zu\n", word, start, end - 1);
            free(word);

            offset = end;
        }

        if (match.rm_eo == match.rm_so) {
            offset++;
        }
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *sentence = "She quickly ran to the store and quietly bought a surprisingly cheap gift";

    printf("Sentence: %s\n\n", sentence);

    if (find_adverbs(sentence) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}