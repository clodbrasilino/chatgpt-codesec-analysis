#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contains_match(const char *word, const char *match) {
    if (word == NULL || match == NULL || *match == '\0') {
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
    *out_size = 0;
    if (size == 0) {
        return NULL;
    }
    char **result = malloc(size * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }
    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] == NULL || !contains_match(list[i], match)) {
            if (list[i] != NULL) {
                result[count] = strdup(list[i]);
            } else {
                result[count] = strdup("");
            }
            if (result[count] != NULL) {
                count++;
            }
        }
    }
    char **shrunk = realloc(result, count * sizeof(char *));
    if (shrunk != NULL) {
        result = shrunk;
    } else if (count == 0) {
        free(result);
        result = NULL;
    }
    *out_size = count;
    return result;
}

int main(void) {
    char *words[] = {"Red", "", "Green", "Orange", "White"};
    size_t size = sizeof(words) / sizeof(words[0]);
    const char *match = "a";
    size_t out_size = 0;
    
    setvbuf(stdout, NULL, _IONBF, 0);
    
    char **filtered = remove_words(words, size, match, &out_size);
    
    printf("[");
    for (size_t i = 0; i < out_size; i++) {
        printf("'%s'", filtered[i]);
        if (i < out_size - 1) printf(", ");
    }
    printf("]\n");
    
    if (filtered != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            free(filtered[i]);
        }
        free(filtered);
    }
    return 0;
}