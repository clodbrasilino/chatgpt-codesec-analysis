#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *duplicate_string(const char *s) {
    if (s == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(s);
    if (len == SIZE_MAX) {
        return NULL;
    }
    /* Possible weaknesses found:
     *  alloc_size is assigned 'len+1' here.
     */
    size_t alloc_size = len + 1;
    /* Possible weaknesses found:
     *  Condition 'alloc_size<=len' is always false [knownConditionTrueFalse]
     *  Condition 'alloc_size<=len' is always false
     */
    if (alloc_size <= len) {
        return NULL;
    }
    char *copy = malloc(alloc_size);
    if (copy == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, s, alloc_size);
    return copy;
}

void remove_words_containing(char **words, size_t *count, const char *substr) {
    if (words == NULL || count == NULL || substr == NULL) {
        return;
    }

    size_t write = 0;

    for (size_t i = 0; i < *count; i++) {
        if (words[i] != NULL && strstr(words[i], substr) != NULL) {
            free(words[i]);
            words[i] = NULL;
        } else {
            if (write != i) {
                words[write] = words[i];
                words[i] = NULL;
            }
            write++;
        }
    }

    for (size_t i = write; i < *count; i++) {
        words[i] = NULL;
    }

    *count = write;
}

int main(void) {
    size_t count = 5;
    char **words = malloc(count * sizeof(char *));
    if (words == NULL) {
        return EXIT_FAILURE;
    }

    const char *initial[] = {"apple", "banana", "cherry", "date", "elderberry"};

    for (size_t i = 0; i < count; i++) {
        words[i] = duplicate_string(initial[i]);
        if (words[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(words[j]);
            }
            free(words);
            return EXIT_FAILURE;
        }
    }

    printf("Before:\n");
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", words[i]);
    }

    remove_words_containing(words, &count, "a");

    printf("After:\n");
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", words[i]);
    }

    for (size_t i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);

    return EXIT_SUCCESS;
}