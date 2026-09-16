#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *remove_pattern_from_word(const char *word, const char *pattern)
{
    size_t word_len = strlen(word);
    size_t pattern_len = strlen(pattern);
    char *buffer;
    char *trimmed;
    size_t pos = 0;
    const char *src = word;
    const char *match;
    size_t start;
    size_t end;
    size_t final_len;

    buffer = malloc(word_len + 1);
    if (buffer == NULL) {
        return NULL;
    }

    if (pattern_len == 0) {
        memcpy(buffer, word, word_len + 1);
    } else {
        while ((match = strstr(src, pattern)) != NULL) {
            size_t chunk = (size_t)(match - src);
            memcpy(buffer + pos, src, chunk);
            pos += chunk;
            src = match + pattern_len;
        }
        strcpy(buffer + pos, src);
    }

    start = 0;
    end = strlen(buffer);
    while (start < end && buffer[start] == ' ') {
        start++;
    }
    while (end > start && buffer[end - 1] == ' ') {
        end--;
    }
    final_len = end - start;

    trimmed = malloc(final_len + 1);
    if (trimmed == NULL) {
        free(buffer);
        return NULL;
    }
    memcpy(trimmed, buffer + start, final_len);
    trimmed[final_len] = '\0';
    free(buffer);

    return trimmed;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  *  test case 0 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  *  test case 2 failed: expected ['Red &', 'Orange+', 'Green', 'Orange', 'White'], got <no output>
  */

char **remove_words(const char **words, size_t count, const char *pattern, size_t *out_count)
{
    char **result;
    size_t kept = 0;
    size_t i;

    if (words == NULL || pattern == NULL || out_count == NULL) {
        return NULL;
    }

    result = malloc((count > 0 ? count : 1) * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        char *processed;

        if (words[i] == NULL) {
            continue;
        }

        processed = remove_pattern_from_word(words[i], pattern);
        if (processed == NULL) {
            size_t j;
            for (j = 0; j < kept; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        result[kept] = processed;
        kept++;
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
    const char *words[] = { "Red color", "color", "Green", "Orange", "White" };
    size_t count = sizeof(words) / sizeof(words[0]);
    const char *pattern = "color";
    size_t result_count = 0;
    char **filtered;
    size_t i;

    filtered = remove_words(words, count, pattern, &result_count);
    if (filtered == NULL) {
        fprintf(stderr, "Failed to filter word list\n");
        return EXIT_FAILURE;
    }

    printf("[");
    for (i = 0; i < result_count; i++) {
        printf("'%s'%s", filtered[i], (i + 1 < result_count) ? ", " : "");
    }
    printf("]\n");
    fflush(stdout);

    free_word_list(filtered, result_count);

    return EXIT_SUCCESS;
}