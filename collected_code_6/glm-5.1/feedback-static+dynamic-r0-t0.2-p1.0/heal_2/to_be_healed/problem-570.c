#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contains_match(const char *word, const char *match) {
    if (word == NULL || match == NULL) {
        return 0;
    }
    size_t match_len = 0;
    while (match[match_len] != '\0') {
        match_len++;
        if (match_len == 0 && match[0] == '\0') break;
    }
    if (match_len == 1) {
        const char *p = word;
        while (*p != '\0') {
            if (*p == match[0]) return 1;
            p++;
        }
        return 0;
    }
    const char *p = word;
    while (*p != '\0') {
        const char *w = p;
        const char *m = match;
        while (*w != '\0' && *m != '\0' && *w == *m) {
            w++;
            m++;
        }
        if (*m == '\0') return 1;
        p++;
    }
    return 0;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  *  test case 1 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  *  test case 2 failed: expected ['Red &', 'Orange+', 'Green', 'Orange', 'White'], got <no output>
  */

char **remove_words(char **list, size_t size, const char *match, size_t *out_size) {
    if (list == NULL || match == NULL || out_size == NULL) {
        return NULL;
    }
    char **result = malloc(size * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }
    char **copy_list = malloc(size * sizeof(char *));
    if (copy_list == NULL) {
        free(result);
        return NULL;
    }
    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t len = 0;
            while (list[i][len] != '\0') len++;
            copy_list[i] = malloc(len + 1);
            if (copy_list[i] != NULL) {
                for (size_t j = 0; j <= len; j++) {
                    copy_list[i][j] = list[i][j];
                }
            } else {
                copy_list[i] = NULL;
            }
        } else {
            copy_list[i] = NULL;
        }
        if (copy_list[i] != NULL && !contains_match(copy_list[i], match)) {
            result[count] = copy_list[i];
            count++;
        } else if (copy_list[i] != NULL) {
            free(copy_list[i]);
        }
    }
    free(copy_list);
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
    char *words[] = {"Red", "", "Green", "Orange", "White"};
    size_t size = sizeof(words) / sizeof(words[0]);
    const char *match = "a";
    size_t out_size = 0;
    char **filtered = remove_words(words, size, match, &out_size);
    if (filtered != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            if (i > 0) printf(", ");
            printf("'%s'", filtered[i]);
            free(filtered[i]);
        }
        free(filtered);
        printf("\n");
    }
    return 0;
}