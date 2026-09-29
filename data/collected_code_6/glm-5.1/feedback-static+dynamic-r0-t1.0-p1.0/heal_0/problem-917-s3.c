#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** find_sequences(const char* str, int* count) {
    *count = 0;
    size_t capacity = 10;
    char** results = malloc(capacity * sizeof(char*));
    if (!results) {
        return NULL;
    }

    size_t len = strlen(str);
    size_t i = 0;

    while (i < len) {
        if (isupper((unsigned char)str[i])) {
            size_t start = i;
            i++;
            while (i < len && islower((unsigned char)str[i])) {
                i++;
            }
            if (i > start) {
                if ((size_t)*count >= capacity) {
                    capacity *= 2;
                    char** temp = realloc(results, capacity * sizeof(char*));
                    if (!temp) {
                        for (int j = 0; j < *count; j++) {
                            free(results[j]);
                        }
                        free(results);
                        *count = 0;
                        return NULL;
                    }
                    results = temp;
                }
                size_t seq_len = i - start;
                char* seq = malloc(seq_len + 1);
                if (!seq) {
                    for (int j = 0; j < *count; j++) {
                        free(results[j]);
                    }
                    free(results);
                    *count = 0;
                    return NULL;
                }
                memcpy(seq, str + start, seq_len);
                seq[seq_len] = '\0';
                results[*count] = seq;
                (*count)++;
            }
        } else {
            i++;
        }
    }

    return results;
}

int main(void) {
    const char* text = "This is a Test string with Multiple valid Sequences like Abc and Xyz.";
    int count = 0;
    char** sequences = find_sequences(text, &count);

    if (!sequences) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("%s\n", sequences[i]);
        free(sequences[i]);
    }
    free(sequences);

    return 0;
}