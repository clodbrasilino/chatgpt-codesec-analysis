#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **find_underscore_sequences(const char *str, size_t *out_count) {
    size_t capacity = 10;
    size_t count = 0;
    char **results = malloc(capacity * sizeof(char *));
    if (results == NULL) {
        *out_count = 0;
        return NULL;
    }

    const char *ptr = str;
    while (*ptr != '\0') {
        if (islower((unsigned char)*ptr)) {
            const char *start = ptr;
            while (*ptr != '\0' && islower((unsigned char)*ptr)) {
                ptr++;
            }
            if (*ptr == '_' && islower((unsigned char)*(ptr + 1))) {
                ptr++;
                while (*ptr != '\0' && islower((unsigned char)*ptr)) {
                    ptr++;
                }
                size_t len = ptr - start;
                if (count >= capacity) {
                    capacity *= 2;
                    char **temp = realloc(results, capacity * sizeof(char *));
                    if (temp == NULL) {
                        for (size_t i = 0; i < count; i++) {
                            free(results[i]);
                        }
                        free(results);
                        *out_count = 0;
                        return NULL;
                    }
                    results = temp;
                }
                results[count] = malloc(len + 1);
                if (results[count] == NULL) {
                    for (size_t i = 0; i < count; i++) {
                        free(results[i]);
                    }
                    free(results);
                    *out_count = 0;
                    return NULL;
                }
                memcpy(results[count], start, len);
                results[count][len] = '\0';
                count++;
            }
        } else {
            ptr++;
        }
    }

    *out_count = count;
    return results;
}

void free_sequences(char **sequences, size_t count) {
    if (sequences == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(sequences[i]);
    }
    free(sequences);
}

int main(void) {
    const char *text = "hello_world test_case a_b 123 bad_ good_bad ugly_ x_y_z";
    size_t count = 0;
    char **seqs = find_underscore_sequences(text, &count);

    if (seqs != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", seqs[i]);
        }
        free_sequences(seqs, count);
    }

    return 0;
}