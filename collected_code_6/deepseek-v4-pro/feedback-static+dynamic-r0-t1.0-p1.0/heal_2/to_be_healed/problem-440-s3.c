#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[128];
    size_t position;
} AdverbInfo;

static int is_adverb(const char *word, size_t len) {
    if (len < 2) {
        return 0;
    }
    return strcmp(word + len - 2, "ly") == 0;
}

static int find_all_adverbs(const char *sentence, AdverbInfo **adverbs, size_t *count) {
    if (sentence == NULL || adverbs == NULL || count == NULL) {
        return -1;
    }

    *adverbs = NULL;
    *count = 0;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(sentence);
    if (len == 0) {
        return 0;
    }

    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, sentence, len + 1);

    size_t capacity = 0;
    AdverbInfo *result = NULL;

    char *token = strtok(buffer, " ,.;:!?\"'()\t\n");
    while (token != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t token_len = strlen(token);
        if (is_adverb(token, token_len)) {
            if (*count >= capacity) {
                size_t new_capacity = capacity == 0 ? 4 : capacity * 2;
                if (new_capacity > SIZE_MAX / sizeof(AdverbInfo)) {
                    free(result);
                    free(buffer);
                    return -1;
                }
                AdverbInfo *new_result = (AdverbInfo *)realloc(result, new_capacity * sizeof(AdverbInfo));
                if (new_result == NULL) {
                    free(result);
                    free(buffer);
                    return -1;
                }
                result = new_result;
                capacity = new_capacity;
            }

            if (token_len >= sizeof(result[*count].word)) {
                free(result);
                free(buffer);
                return -1;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[*count].word, token, token_len + 1);

            const char *pos_ptr = sentence + (token - buffer);
            while (pos_ptr > sentence) {
                const char *prev = pos_ptr - 1;
                if (!isspace((unsigned char)*prev) &&
                    strchr(" ,.;:!?\"'()\t\n", *prev) == NULL) {
                    pos_ptr--;
                } else {
                    break;
                }
            }
            result[*count].position = (size_t)(pos_ptr - sentence);

            (*count)++;
        }
        token = strtok(NULL, " ,.;:!?\"'()\t\n");
    }

    free(buffer);

    if (*count == 0) {
        free(result);
        *adverbs = NULL;
    } else {
        *adverbs = result;
    }

    return 0;
}

int main(void) {
    const char *sentence = "The cat quickly ran very slowly and happily through the garden.";
    AdverbInfo *adverbs = NULL;
    size_t count = 0;

    int status = find_all_adverbs(sentence, &adverbs, &count);
    if (status != 0) {
        fprintf(stderr, "Error processing sentence\n");
        return EXIT_FAILURE;
    }

    printf("Adverbs found: %zu\n", count);
    for (size_t i = 0; i < count; i++) {
        printf("Position %zu: %s\n", adverbs[i].position, adverbs[i].word);
    }

    free(adverbs);
    return EXIT_SUCCESS;
}