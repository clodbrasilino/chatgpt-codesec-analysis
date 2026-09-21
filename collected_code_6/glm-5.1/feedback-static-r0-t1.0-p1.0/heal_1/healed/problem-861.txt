#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_anagram(const char *s1, const char *s2, size_t max_len) {
    size_t len1 = strnlen(s1, max_len);
    size_t len2 = strnlen(s2, max_len);
    if (len1 != len2 || (len1 == max_len && s1[len1] != '\0') || (len2 == max_len && s2[len2] != '\0')) {
        return 0;
    }
    int count[256] = {0};
    for (size_t i = 0; i < len1; i++) {
        unsigned char c1 = (unsigned char)s1[i];
        unsigned char c2 = (unsigned char)s2[i];
        count[c1]++;
        count[c2]--;
    }
    for (int i = 0; i < 256; i++) {
        if (count[i] != 0) {
            return 0;
        }
    }
    return 1;
}

char **find_anagrams(const char *target, char **list, size_t list_size, size_t *result_size) {
    if (target == NULL || list == NULL || result_size == NULL) {
        return NULL;
    }
    *result_size = 0;
    char **result = malloc(list_size * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < list_size; i++) {
        if (list[i] != NULL && is_anagram(target, list[i], 1024)) {
            result[*result_size] = list[i];
            (*result_size)++;
        }
    }
    if (*result_size == 0) {
        free(result);
        return NULL;
    }
    char **trimmed_result = realloc(result, (*result_size) * sizeof(char *));
    if (trimmed_result != NULL) {
        return trimmed_result;
    }
    return result;
}

int main() {
    const char *target = "listen";
    char *list[] = {"enlist", "google", "inlets", "banana", "silent", "tinsel"};
    size_t list_size = sizeof(list) / sizeof(list[0]);
    size_t result_size = 0;
    char **anagrams = find_anagrams(target, list, list_size, &result_size);
    if (anagrams != NULL) {
        for (size_t i = 0; i < result_size; i++) {
            printf("%s\n", anagrams[i]);
        }
        free(anagrams);
    } else {
        printf("No anagrams found.\n");
    }
    return 0;
}