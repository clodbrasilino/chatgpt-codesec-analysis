#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_LEN 4096

void to_lowercase(char *str) {
    while (*str) {
        *str = (char)tolower((unsigned char)*str);
        str++;
    }
}

size_t get_safe_length(const char *str) {
    size_t len = 0;
    /* Possible weaknesses found:
     *  Array index 'len' is used before limits check. [arrayIndexThenCheck]
     */
    while (str[len] != '\0' && len < MAX_STR_LEN) {
        len++;
    }
    return len;
}

void sort_string(char *str, size_t length) {
    if (length == 0) return;
    for (size_t i = 0; i < length - 1; i++) {
        for (size_t j = i + 1; j < length; j++) {
            if (str[i] > str[j]) {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

int is_anagram(const char *str1, const char *str2) {
    size_t len1 = get_safe_length(str1);
    size_t len2 = get_safe_length(str2);

    if (len1 != len2 || len1 == MAX_STR_LEN || len2 == MAX_STR_LEN) {
        return 0;
    }

    char *copy1 = strdup(str1);
    char *copy2 = strdup(str2);

    if (!copy1 || !copy2) {
        free(copy1);
        free(copy2);
        return 0;
    }

    to_lowercase(copy1);
    to_lowercase(copy2);

    sort_string(copy1, len1);
    sort_string(copy2, len2);

    int result = strcmp(copy1, copy2) == 0;

    free(copy1);
    free(copy2);

    return result;
}

char **find_anagrams(const char *target, const char **list, int list_size, int *result_size) {
    if (!target || !list || !result_size) {
        return NULL;
    }

    char **anagrams = malloc(list_size * sizeof(char *));
    if (!anagrams) {
        *result_size = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < list_size; i++) {
        if (list[i] && is_anagram(target, list[i])) {
            anagrams[count] = strdup(list[i]);
            if (anagrams[count]) {
                count++;
            }
        }
    }

    *result_size = count;
    return anagrams;
}

int main(void) {
    const char *target = "Listen";
    const char *list[] = {"enlists", "google", "inlets", "banana", "Silent"};
    int list_size = sizeof(list) / sizeof(list[0]);
    int result_size = 0;

    char **anagrams = find_anagrams(target, list, list_size, &result_size);

    if (anagrams) {
        for (int i = 0; i < result_size; i++) {
            printf("%s\n", anagrams[i]);
            free(anagrams[i]);
        }
        free(anagrams);
    }

    return 0;
}