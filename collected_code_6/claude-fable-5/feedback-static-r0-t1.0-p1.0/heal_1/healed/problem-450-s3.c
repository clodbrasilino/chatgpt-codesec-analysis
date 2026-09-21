#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

static size_t safe_string_length(const char *s, size_t max_len)
{
    size_t len = 0;

    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

char **extract_strings_by_size(const char **list, size_t list_count, size_t target_size, size_t *result_count)
{
    char **result = NULL;
    size_t count = 0;
    size_t i;

    if (result_count == NULL) {
        return NULL;
    }
    *result_count = 0;

    if (list == NULL || target_size >= MAX_STRING_LENGTH) {
        return NULL;
    }

    for (i = 0; i < list_count; i++) {
        if (list[i] != NULL) {
            size_t len = safe_string_length(list[i], MAX_STRING_LENGTH);
            if (len < MAX_STRING_LENGTH && len == target_size) {
                count++;
            }
        }
    }

    if (count == 0) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    result = malloc(count * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    count = 0;
    for (i = 0; i < list_count; i++) {
        if (list[i] != NULL) {
            size_t len = safe_string_length(list[i], MAX_STRING_LENGTH);
            if (len < MAX_STRING_LENGTH && len == target_size) {
                result[count] = malloc(len + 1);
                if (result[count] == NULL) {
                    size_t j;
                    for (j = 0; j < count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                memcpy(result[count], list[i], len);
                result[count][len] = '\0';
                count++;
            }
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