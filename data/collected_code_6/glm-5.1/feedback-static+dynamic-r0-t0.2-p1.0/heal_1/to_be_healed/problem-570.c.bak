#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contains_match(const char *word, const char *match) {
    if (word == NULL || match == NULL) {
        return 0;
    }
    if (strlen(match) == 1) {
        return strchr(word, match[0]) != NULL;
    }
    return strstr(word, match) != NULL;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['Red &', 'Orange+', 'Green', 'Orange', 'White'], got <no output>
  *  test case 1 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  *  test case 0 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  */

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
        if (list[i] != NULL && !contains_match(list[i], match)) {
            result[count] = list[i];
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
    char *words[] = {"apple", "banana", "cherry", "date", "elderberry"};
    size_t size = sizeof(words) / sizeof(words[0]);
    const char *match = "a";
    size_t out_size = 0;

    char **filtered = remove_words(words, size, match, &out_size);

    if (filtered != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%s\n", filtered[i]);
        }
        free(filtered);
    }

    return 0;
}