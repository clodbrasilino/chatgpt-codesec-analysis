#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int is_in_list(const char *word, char **list, int list_size) {
    if (!word || !list) return 0;
    for (int i = 0; i < list_size; i++) {
        if (list[i] && strcmp(word, list[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int remove_words(char **words, int count, char **to_remove, int remove_count) {
    if (!words || !to_remove) return count;
    int new_count = 0;
    for (int i = 0; i < count; i++) {
        if (words[i] && is_in_list(words[i], to_remove, remove_count)) {
            free(words[i]);
        } else {
            words[new_count++] = words[i];
        }
    }
    for (int i = new_count; i < count; i++) {
        words[i] = NULL;
    }
    return new_count;
}

char *allocate_string(const char *str) {
    if (!str) return NULL;
    const char *end = memchr(str, '\0', SIZE_MAX);
    if (!end) return NULL;
    size_t len = end - str;
    if (len == SIZE_MAX) return NULL;
    len++;
    char *new_str = malloc(len);
    if (new_str) {
        snprintf(new_str, len, "%s", str);
    }
    return new_str;
}

int main(void) {
    int count = 5;
    char **words = malloc(count * sizeof(char *));
    if (!words) return EXIT_FAILURE;
    for (int i = 0; i < count; i++) words[i] = NULL;

    words[0] = allocate_string("apple");
    words[1] = allocate_string("banana");
    words[2] = allocate_string("cherry");
    words[3] = allocate_string("date");
    words[4] = allocate_string("elderberry");

    if (!words[0] || !words[1] || !words[2] || !words[3] || !words[4]) {
        for (int i = 0; i < count; i++) free(words[i]);
        free(words);
        return EXIT_FAILURE;
    }

    int remove_count = 2;
    char **to_remove = malloc(remove_count * sizeof(char *));
    if (!to_remove) {
        for (int i = 0; i < count; i++) free(words[i]);
        free(words);
        return EXIT_FAILURE;
    }
    for (int i = 0; i < remove_count; i++) to_remove[i] = NULL;

    to_remove[0] = allocate_string("banana");
    to_remove[1] = allocate_string("date");

    if (!to_remove[0] || !to_remove[1]) {
        for (int i = 0; i < count; i++) free(words[i]);
        free(words);
        for (int i = 0; i < remove_count; i++) free(to_remove[i]);
        free(to_remove);
        return EXIT_FAILURE;
    }

    count = remove_words(words, count, to_remove, remove_count);

    for (int i = 0; i < count; i++) {
        printf("%s\n", words[i]);
    }

    for (int i = 0; i < count; i++) free(words[i]);
    free(words);

    for (int i = 0; i < remove_count; i++) free(to_remove[i]);
    free(to_remove);

    return EXIT_SUCCESS;
}