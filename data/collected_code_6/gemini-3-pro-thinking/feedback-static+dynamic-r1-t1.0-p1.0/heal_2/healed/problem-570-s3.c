#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *duplicate_string(const char *src) {
    if (!src) {
        return NULL;
    }

    size_t len = 0;
    size_t max_len = 8192;

    while (len < max_len && src[len] != '\0') {
        len++;
    }

    char *dest = malloc(len + 1);
    if (dest) {
        memcpy(dest, src, len);
        dest[len] = '\0';
    }
    return dest;
}

int remove_words_with_substring(char ***word_list, size_t *count, const char *target) {
    if (!word_list || !*word_list || !count || !target) {
        return -1;
    }

    size_t new_count = 0;
    char **list = *word_list;

    for (size_t i = 0; i < *count; i++) {
        if (list[i] == NULL) {
            continue;
        }
        if (strstr(list[i], target) != NULL) {
            free(list[i]);
            list[i] = NULL;
        } else {
            list[new_count] = list[i];
            new_count++;
        }
    }

    if (new_count == 0) {
        free(*word_list);
        *word_list = NULL;
        *count = 0;
        return 0;
    }

    if (new_count < *count) {
        char **temp = realloc(*word_list, new_count * sizeof(char *));
        if (temp) {
            *word_list = temp;
        }
    }

    *count = new_count;
    return 0;
}

int main(void) {
    size_t count = 5;
    char **words = malloc(count * sizeof(char *));
    if (!words) {
        return 1;
    }

    const char *initial_words[] = {"apple", "banana", "cherry", "date", "grape"};
    for (size_t i = 0; i < count; i++) {
        words[i] = duplicate_string(initial_words[i]);
        if (!words[i]) {
            for (size_t j = 0; j < i; j++) {
                free(words[j]);
            }
            free(words);
            return 1;
        }
    }

    const char *target = "a";

    if (remove_words_with_substring(&words, &count, target) != 0) {
        if (words) {
            for (size_t i = 0; i < count; i++) {
                free(words[i]);
            }
            free(words);
        }
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", words[i]);
    }

    if (words) {
        for (size_t i = 0; i < count; i++) {
            free(words[i]);
        }
        free(words);
    }

    return 0;
}