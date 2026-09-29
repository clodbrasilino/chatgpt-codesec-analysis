#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_ERROR_MSG 128
#define MAX_SENTENCE_LEN 4096

int find_adverbs(const char *sentence);

int find_adverbs(const char *sentence)
{
    regex_t regex;
    regmatch_t match;
    const char *pattern = "[A-Za-z]+ly";
    char *error_buf;
    int ret;
    size_t offset = 0;
    size_t len;

    if (sentence == NULL) {
        fprintf(stderr, "Invalid input: sentence is NULL\n");
        return -1;
    }

    len = strnlen(sentence, MAX_SENTENCE_LEN);
    if (len >= MAX_SENTENCE_LEN) {
        fprintf(stderr, "Invalid input: sentence too long or not null-terminated\n");
        return -1;
    }

    error_buf = calloc(MAX_ERROR_MSG, sizeof(char));
    if (error_buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &regex, error_buf, MAX_ERROR_MSG - 1);
        error_buf[MAX_ERROR_MSG - 1] = '\0';
        fprintf(stderr, "Regex compilation failed: %s\n", error_buf);
        free(error_buf);
        return -1;
    }

    while (offset < len) {
        ret = regexec(&regex, sentence + offset, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            regerror(ret, &regex, error_buf, MAX_ERROR_MSG - 1);
            error_buf[MAX_ERROR_MSG - 1] = '\0';
            fprintf(stderr, "Regex execution failed: %s\n", error_buf);
            regfree(&regex);
            free(error_buf);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            fprintf(stderr, "Invalid match offsets\n");
            regfree(&regex);
            free(error_buf);
            return -1;
        }

        {
            size_t start = offset + (size_t)match.rm_so;
            size_t end = offset + (size_t)match.rm_eo;
            size_t word_len;
            char *word;

            if (end > len || start > end || start > len) {
                fprintf(stderr, "Match out of bounds\n");
                regfree(&regex);
                free(error_buf);
                return -1;
            }

            word_len = end - start;
            if (word_len > len - start) {
                fprintf(stderr, "Match length exceeds available data\n");
                regfree(&regex);
                free(error_buf);
                return -1;
            }

            word = malloc(word_len + 1);
            if (word == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                regfree(&regex);
                free(error_buf);
                return -1;
            }

            if (word_len > 0) {
                if (start + word_len > len) {
                    fprintf(stderr, "Copy would exceed source bounds\n");
                    free(word);
                    regfree(&regex);
                    free(error_buf);
                    return -1;
                }
                memcpy(word, sentence + start, word_len);
            }
            word[word_len] = '\0';
            printf("Adverb: %-15s Position: %zu-%zu\n", word, start,
                   (word_len > 0) ? end - 1 : start);
            free(word);

            offset = end;
        }

        if (match.rm_eo == match.rm_so) {
            offset++;
        }
    }

    regfree(&regex);
    free(error_buf);
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