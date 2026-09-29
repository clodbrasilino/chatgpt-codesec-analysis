#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contains_match(const char *word, const char *match) {
    if (word == NULL || match == NULL || match[0] == '\0') {
        return 0;
    }
    if (match[1] == '\0') {
        return strchr(word, match[0]) != NULL;
    }
    return strstr(word, match) != NULL;
}

char *strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *d = malloc(len);
    if (d) memcpy(d, s, len);
    return d;
}

char **remove_words(char **list, size_t size, const char *match, size_t *out_size) {
    if (list == NULL || match == NULL || out_size == NULL) {
        return NULL;
    }

    char **result = malloc(size * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] == NULL) {
            result[count] = NULL;
            count++;
        } else if (!contains_match(list[i], match)) {
            result[count] = strdup(list[i]);
            if (result[count] == NULL) {
                for (size_t j = 0; j < count; j++) free(result[j]);
                free(result);
                return NULL;
            }
            count++;
        }
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
    char *words[] = {"Red &", "", "Green", "Orange+", "White"};
    size_t size = sizeof(words) / sizeof(words[0]);
    const char *match = "+&";
    size_t out_size = 0;

    char **filtered = remove_words(words, size, match, &out_size);

    if (filtered != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            if (filtered[i] != NULL) {
                printf("%s", filtered[i]);
            }
            if (i < out_size - 1) {
                printf(", ");
            }
            free(filtered[i]);
        }
        printf("\n");
        free(filtered);
    }

    return 0;
}