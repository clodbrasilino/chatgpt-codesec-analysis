#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int should_remove(const char *word, const char *filter) {
    if (word == NULL || filter == NULL) return 0;
    if (strlen(filter) == 0) return 0;
    char *lower_word = strdup(word);
    char *lower_filter = strdup(filter);
    if (lower_word == NULL || lower_filter == NULL) {
        free(lower_word);
        free(lower_filter);
        return 0;
    }
    for (char *p = lower_word; *p; p++) *p = tolower((unsigned char)*p);
    for (char *p = lower_filter; *p; p++) *p = tolower((unsigned char)*p);
    int result = strstr(lower_word, lower_filter) != NULL;
    free(lower_word);
    free(lower_filter);
    return result;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  *  test case 2 failed: expected ['Red &', 'Orange+', 'Green', 'Orange', 'White'], got <no output>
  *  test case 1 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  */

char **remove_words(char **list, size_t size, const char *filter, size_t *out_size) {
    if (list == NULL || filter == NULL || out_size == NULL) {
        return NULL;
    }

    char **result = malloc(size * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] == NULL || !should_remove(list[i], filter)) {
            size_t len = strlen(list[i]);
            result[count] = malloc(len + 1);
            if (result[count] == NULL) {
                for (size_t j = 0; j < count; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            strcpy(result[count], list[i]);
            count++;
        }
    }

    *out_size = count;
    
    if (count == 0) {
        free(result);
        return NULL;
    }

    char **shrunk = realloc(result, count * sizeof(char *));
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    char *words[] = {"Red", "", "Green", "Orange", "White"};
    size_t size = sizeof(words) / sizeof(words[0]);
    const char *filter = "an";
    
    size_t out_size = 0;
    char **filtered = remove_words(words, size, filter, &out_size);
    
    printf("[");
    for (size_t i = 0; i < out_size; i++) {
        printf("'%s'%s", filtered[i], (i < out_size - 1) ? ", " : "");
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