#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char **find_sequences(const char *str, size_t *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;
    size_t capacity = 10;
    char **results = malloc(capacity * sizeof(char *));
    if (results == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)str[i])) {
            size_t start = i;
            while (i < len && isupper((unsigned char)str[i])) {
                i++;
            }
            while (i < len && islower((unsigned char)str[i])) {
                i++;
            }
            size_t seq_len = i - start;
            if (seq_len > 1) {
                if (*count >= capacity) {
                    capacity *= 2;
                    char **temp = realloc(results, capacity * sizeof(char *));
                    if (temp == NULL) {
                        for (size_t j = 0; j < *count; j++) {
                            free(results[j]);
                        }
                        free(results);
                        return NULL;
                    }
                    results = temp;
                }
                results[*count] = malloc(seq_len + 1);
                if (results[*count] == NULL) {
                    for (size_t j = 0; j < *count; j++) {
                        free(results[j]);
                    }
                    free(results);
                    return NULL;
                }
                memcpy(results[*count], str + start, seq_len);
                results[*count][seq_len] = '\0';
                (*count)++;
            }
            i--;
        }
    }

    return results;
}

int main(void) {
    const char *text = "Hello World, this is a Test string for ABCDefgh and ZYXWvuts.";
    size_t count = 0;
    char **sequences = find_sequences(text, &count);

    if (sequences != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", sequences[i]);
            free(sequences[i]);
        }
        free(sequences);
    }

    return 0;
}