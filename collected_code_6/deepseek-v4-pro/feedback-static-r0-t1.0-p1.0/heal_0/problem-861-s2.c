#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **anagrams;
    int count;
} AnagramList;

static int compare_chars(const void *a, const void *b) {
    return (*(const char *)a - *(const char *)b);
}

static char *sort_string(const char *str) {
    size_t len = strlen(str);
    char *sorted = malloc(len + 1);
    if (!sorted) return NULL;
    strcpy(sorted, str);
    qsort(sorted, len, sizeof(char), compare_chars);
    return sorted;
}

AnagramList *find_anagrams(const char *target, char **word_list, int word_count) {
    if (!target || !word_list || word_count <= 0) return NULL;

    AnagramList *result = malloc(sizeof(AnagramList));
    if (!result) return NULL;

    result->anagrams = malloc(word_count * sizeof(char *));
    if (!result->anagrams) {
        free(result);
        return NULL;
    }

    result->count = 0;

    char *sorted_target = sort_string(target);
    if (!sorted_target) {
        free(result->anagrams);
        free(result);
        return NULL;
    }

    size_t target_len = strlen(target);

    for (int i = 0; i < word_count; i++) {
        if (!word_list[i]) continue;
        if (strlen(word_list[i]) != target_len) continue;
        if (strcmp(word_list[i], target) == 0) continue;

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

    result->anagrams = realloc(result->anagrams, result->count * sizeof(char *));
    if (!result->anagrams && result->count > 0) {
        free(result);
        return NULL;
    }

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