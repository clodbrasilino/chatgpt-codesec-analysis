#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_ERR_LEN 256

int find_adverbs(const char *sentence)
{
    regex_t regex;
    regmatch_t match;
    const char *pattern = "[A-Za-z]+ly\\b";
    char errbuf[MAX_ERR_LEN];
    int ret;
    size_t offset = 0;
    size_t len;
    int count = 0;

    if (sentence == NULL) {
        fprintf(stderr, "Error: sentence is NULL\n");
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return -1;
    }

    len = strlen(sentence);

    while (offset < len) {
        ret = regexec(&regex, sentence + offset, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            regerror(ret, &regex, errbuf, sizeof(errbuf));
            fprintf(stderr, "Regex execution failed: %s\n", errbuf);
            regfree(&regex);
            return -1;
        }

        size_t start = offset + (size_t)match.rm_so;
        size_t end = offset + (size_t)match.rm_eo;
        size_t word_len = end - start;

        char *word = malloc(word_len + 1);
        if (word == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            regfree(&regex);
            return -1;
        }

        memcpy(word, sentence + start, word_len);
        word[word_len] = '\0';

        printf("Adverb: %-15s Position: %zu-%zu\n", word, start, end - 1);
        count++;

        free(word);

        if (match.rm_eo == match.rm_so) {
            offset += 1;
        } else {
            offset = end;
        }
    }

    regfree(&regex);
    return count;
}

int main(void)
{
    const char *sentence = "She quickly ran to the store and quietly bought some milk, then happily walked home.";
    int result;

    printf("Sentence: %s\n\n", sentence);

    result = find_adverbs(sentence);
    if (result < 0) {
        fprintf(stderr, "Failed to search for adverbs\n");
        return EXIT_FAILURE;
    }

    if (result == 0) {
        printf("No adverbs found.\n");
    } else {
        printf("\nTotal adverbs found: %d\n", result);
    }

    return EXIT_SUCCESS;
}