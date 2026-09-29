#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** find_anagrams(const char* target, char** list, int list_size, int* result_size) {
    if (target == NULL || list == NULL || result_size == NULL) {
        return NULL;
    }

    *result_size = 0;
    if (list_size <= 0) {
        return NULL;
    }

    int target_len = strlen(target);
    int target_counts[256] = {0};

    for (int i = 0; i < target_len; i++) {
        unsigned char c = target[i];
        target_counts[c]++;
    }

    char** result = malloc(list_size * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < list_size; i++) {
        if (list[i] == NULL) {
            continue;
        }

        int current_len = strlen(list[i]);
        if (current_len != target_len) {
            continue;
        }

        int current_counts[256] = {0};
        int is_anagram = 1;

        for (int j = 0; j < current_len; j++) {
            unsigned char c = list[i][j];
            current_counts[c]++;
            if (current_counts[c] > target_counts[c]) {
                is_anagram = 0;
                break;
            }
        }

        if (is_anagram) {
            for (int k = 0; k < 256; k++) {
                if (current_counts[k] != target_counts[k]) {
                    is_anagram = 0;
                    break;
                }
            }
        }

        if (is_anagram) {
            result[*result_size] = list[i];
            (*result_size)++;
        }
    }

    if (*result_size == 0) {
        free(result);
        return NULL;
    }

    char** trimmed_result = realloc(result, (*result_size) * sizeof(char*));
    if (trimmed_result != NULL) {
        return trimmed_result;
    }

    return result;
}

int main() {
    char* words[] = {"listen", "silent", "enlist", "google", "inlets", "banana"};
    int size = sizeof(words) / sizeof(words[0]);
    int result_size = 0;

    char** anagrams = find_anagrams("listen", words, size, &result_size);

    if (anagrams != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("%s\n", anagrams[i]);
        }
        free(anagrams);
    }

    return 0;
}