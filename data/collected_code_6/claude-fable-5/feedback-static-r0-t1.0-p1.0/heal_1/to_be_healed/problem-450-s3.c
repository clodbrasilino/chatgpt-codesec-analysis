#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extract_strings_by_size(const char **list, size_t list_count, size_t target_size, size_t *result_count)
{
    char **result = NULL;
    size_t count = 0;
    size_t i;

    if (list == NULL || result_count == NULL) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    for (i = 0; i < list_count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (list[i] != NULL && strlen(list[i]) == target_size) {
            count++;
        }
    }

    if (count == 0) {
        *result_count = 0;
        return NULL;
    }

    result = malloc(count * sizeof(char *));
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }

    count = 0;
    for (i = 0; i < list_count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (list[i] != NULL && strlen(list[i]) == target_size) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(list[i]);
            result[count] = malloc(len + 1);
            if (result[count] == NULL) {
                size_t j;
                for (j = 0; j < count; j++) {
                    free(result[j]);
                }
                free(result);
                *result_count = 0;
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[count], list[i], len + 1);
            count++;
        }
    }

    *result_count = count;
    return result;
}

void free_extracted(char **strings, size_t count)
{
    size_t i;

    if (strings == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main(void)
{
    const char *words[] = { "apple", "cat", "banana", "dog", "pear", "fig", "grape" };
    size_t word_count = sizeof(words) / sizeof(words[0]);
    size_t target_size = 3;
    size_t result_count = 0;
    char **extracted;
    size_t i;

    extracted = extract_strings_by_size(words, word_count, target_size, &result_count);

    if (extracted == NULL) {
        if (result_count == 0) {
            printf("No strings of size %zu found or allocation failed.\n", target_size);
        }
        return EXIT_FAILURE;
    }

    printf("Strings of size %zu:\n", target_size);
    for (i = 0; i < result_count; i++) {
        printf("%s\n", extracted[i]);
    }

    free_extracted(extracted, result_count);

    return EXIT_SUCCESS;
}