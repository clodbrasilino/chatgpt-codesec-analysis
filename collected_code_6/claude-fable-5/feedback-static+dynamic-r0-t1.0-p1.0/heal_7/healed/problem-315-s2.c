#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SENTENCE_LEN 4096
#define RESULT_BUF_SIZE 256

int find_first_max_even_word(const char *sentence, char *result, size_t result_size)
{
    size_t i = 0;
    size_t len = 0;
    size_t max_len = 0;
    size_t best_start = 0;
    int found = 0;

    if (sentence == NULL || result == NULL || result_size == 0) {
        return -1;
    }

    len = strnlen(sentence, MAX_SENTENCE_LEN);
    if (len == MAX_SENTENCE_LEN) {
        return -1;
    }

    while (i < len) {
        while (i < len && sentence[i] == ' ') {
            i++;
        }
        if (i < len) {
            size_t start = i;
            size_t word_len = 0;
            while (i < len && sentence[i] != ' ') {
                i++;
            }
            word_len = i - start;
            if ((word_len % 2 == 0) && (word_len > max_len)) {
                max_len = word_len;
                best_start = start;
                found = 1;
            }
        }
    }

    if (!found) {
        return -1;
    }

    if (max_len >= result_size) {
        return -1;
    }

    if (best_start >= len || max_len > len - best_start) {
        return -1;
    }

    {
        size_t j;
        for (j = 0; j < max_len && j < result_size - 1; j++) {
            result[j] = sentence[best_start + j];
        }
        result[j] = '\0';
    }

    return 0;
}

int main(void)
{
    const char *sentence = "It is a pleasant day today";
    char result[RESULT_BUF_SIZE];

    memset(result, 0, sizeof(result));

    if (find_first_max_even_word(sentence, result, sizeof(result)) == 0) {
        result[sizeof(result) - 1] = '\0';
        if (printf("First maximum length even word: %s\n", result) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No even length word found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}