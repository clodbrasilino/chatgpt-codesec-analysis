#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contains_match(const char *word, const char *match) {
    if (word == NULL || match == NULL || match[0] == '\0') {
        return 0;
    }
    for (size_t i = 0; match[i] != '\0'; i++) {
        if (strchr(word, match[i]) != NULL) {
            return 1;
        }
    }
    return 0;
}

char *my_strdup(const char *s) {
    if (s == NULL) return NULL;
    size_t len = strlen(s) + 1;
    char *d = malloc(len);
    if (d) memcpy(d, s, len);
    return d;
}

char **remove_words(char **list, size_t size, const char *match, size_t *out_size) {
    if (list == NULL || match == NULL || out_size == NULL) {
        return NULL;
    }

    if (size == 0) {
        *out_size = 0;
        return NULL;
    }

    char **result = malloc(size * sizeof(char *));
    if (result == NULL) {
        *out_size = 0;
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (contains_match(list[i], match)) {
            continue;
        }
        result[count] = my_strdup(list[i] ? list[i] : "");
        if (result[count] == NULL) {
            for (size_t j = 0; j < count; j++) free(result[j]);
            free(result);
            *out_size = 0;
            return NULL;
        }
        count++;
    }

    if (count == 0) {
        free(result);
        *out_size = 0;
        return NULL;
    }

    char **shrunk = realloc(result, count * sizeof(char *));
    if (shrunk != NULL) {
        result = shrunk;
    }

    *out_size = count;
    return result;
}

int main(void) {
    char *words1[] = {"Red", "", "Green", "Orange", "White"};
    size_t size1 = sizeof(words1) / sizeof(words1[0]);
    const char *match1 = "+&";
    size_t out_size1 = 0;

    char **filtered1 = remove_words(words1, size1, match1, &out_size1);

    printf("[");
    for (size_t i = 0; i < out_size1; i++) {
        printf("'%s'", filtered1[i] ? filtered1[i] : "");
        if (i < out_size1 - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    for (size_t i = 0; i < out_size1; i++) {
        free(filtered1[i]);
    }
    free(filtered1);

    char *words2[] = {"Red &", "Orange+", "Green", "Orange", "White"};
    size_t size2 = sizeof(words2) / sizeof(words2[0]);
    const char *match2 = "+&";
    size_t out_size2 = 0;

    char **filtered2 = remove_words(words2, size2, match2, &out_size2);

    printf("[");
    for (size_t i = 0; i < out_size2; i++) {
        printf("'%s'", filtered2[i] ? filtered2[i] : "");
        if (i < out_size2 - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    for (size_t i = 0; i < out_size2; i++) {
        free(filtered2[i]);
    }
    free(filtered2);

    return 0;
}