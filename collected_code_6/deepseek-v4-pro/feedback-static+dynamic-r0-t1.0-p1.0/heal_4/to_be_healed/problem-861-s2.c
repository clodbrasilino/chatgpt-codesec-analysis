#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char **anagrams;
    int count;
} AnagramList;

static int compare_chars(const void *a, const void *b) {
    return (*(const unsigned char *)a - *(const unsigned char *)b);
}

static char *sort_string(const char *str) {
    if (!str) return NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len >= 4096) return NULL;

    /* Possible weaknesses found:
     *  alloc_size is assigned 'len+1' here.
     */
    size_t alloc_size = len + 1;
    /* Possible weaknesses found:
     *  Condition 'alloc_size<=len' is always false [knownConditionTrueFalse]
     *  Condition 'alloc_size<=len' is always false
     */
    if (alloc_size <= len) return NULL;

    char *sorted = malloc(alloc_size);
    if (!sorted) return NULL;

    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(sorted, str, len);
    }
    sorted[len] = '\0';

    qsort(sorted, len, sizeof(char), compare_chars);
    return sorted;
}

AnagramList *find_anagrams(const char *target, char **word_list, int word_count) {
    if (!target || !word_list || word_count <= 0) return NULL;

    AnagramList *result = malloc(sizeof(AnagramList));
    if (!result) return NULL;

    result->anagrams = NULL;
    result->count = 0;

    result->anagrams = malloc((size_t)word_count * sizeof(char *));
    if (!result->anagrams) {
        free(result);
        return NULL;
    }

    char *sorted_target = sort_string(target);
    if (!sorted_target) {
        free(result->anagrams);
        free(result);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t target_len = strlen(target);
    if (target_len >= 4096) {
        free(sorted_target);
        free(result->anagrams);
        free(result);
        return NULL;
    }

    for (int i = 0; i < word_count; i++) {
        if (!word_list[i]) continue;

        /* Possible weaknesses found:
         *  Return index of string to the first element that is 0
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t word_len = strlen(word_list[i]);
        if (word_len >= 4096) continue;
        /* Possible weaknesses found:
         *  Assuming that condition 'word_len!=target_len' is not redundant
         */
        if (word_len != target_len) continue;
        /* Possible weaknesses found:
         *  Condition 'word_list[i][target_len]=='\0'' is always true [knownConditionTrueFalse]
         *  Condition 'word_list[i][target_len]=='\0'' is always true
         */
        if (memcmp(word_list[i], target, target_len) == 0 && word_list[i][target_len] == '\0') continue;

        char *sorted_word = sort_string(word_list[i]);
        if (!sorted_word) continue;

        if (strcmp(sorted_target, sorted_word) == 0) {
            result->anagrams[result->count] = word_list[i];
            result->count++;
        }

        free(sorted_word);
    }

    free(sorted_target);

    if (result->count == 0) {
        free(result->anagrams);
        free(result);
        return NULL;
    }

    char **temp = realloc(result->anagrams, (size_t)result->count * sizeof(char *));
    if (!temp) {
        free(result->anagrams);
        free(result);
        return NULL;
    }
    result->anagrams = temp;

    return result;
}

void free_anagram_list(AnagramList *list) {
    if (!list) return;
    free(list->anagrams);
    free(list);
}

int main(void) {
    char *words[] = {
        "listen", "enlist", "google", "inlets", "banana",
        "silent", "tinsel", "list", "stilen", "cat"
    };
    int word_count = sizeof(words) / sizeof(words[0]);
    const char *target = "listen";

    AnagramList *result = find_anagrams(target, words, word_count);

    if (result) {
        printf("Anagrams of '%s':\n", target);
        for (int i = 0; i < result->count; i++) {
            printf("  %s\n", result->anagrams[i]);
        }
        free_anagram_list(result);
    } else {
        printf("No anagrams found for '%s'.\n", target);
    }

    return 0;
}