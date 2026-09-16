#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  *  test case 0 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  *  test case 2 failed: expected ['Red &', 'Orange+', 'Green', 'Orange', 'White'], got <no output>
  */

char **remove_words(const char **words, size_t count, const char *pattern, size_t *out_count)
{
    char **result = NULL;
    size_t kept = 0;
    size_t i;

    if (words == NULL || pattern == NULL || out_count == NULL) {
        return NULL;
    }

    result = malloc(count * sizeof(char *));
    if (result == NULL && count > 0) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (words[i] == NULL) {
            continue;
        }
        if (strstr(words[i], pattern) == NULL) {
            size_t len = strlen(words[i]) + 1;
            char *copy = malloc(len);
            if (copy == NULL) {
                size_t j;
                for (j = 0; j < kept; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            memcpy(copy, words[i], len);
            result[kept] = copy;
            kept++;
        }
    }

    *out_count = kept;
    return result;
}

void free_word_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void)
{
    const char *words[] = { "apple", "banana", "cherry", "grape", "apricot" };
    size_t count = sizeof(words) / sizeof(words[0]);
    const char *pattern = "ap";
    size_t result_count = 0;
    char **filtered;
    size_t i;

    filtered = remove_words(words, count, pattern, &result_count);
    if (filtered == NULL && result_count == 0 && count > 0) {
        fprintf(stderr, "Failed to filter word list\n");
        return EXIT_FAILURE;
    }

    printf("Words not containing \"%s\":\n", pattern);
    for (i = 0; i < result_count; i++) {
        printf("%s\n", filtered[i]);
    }

    free_word_list(filtered, result_count);

    return EXIT_SUCCESS;
}