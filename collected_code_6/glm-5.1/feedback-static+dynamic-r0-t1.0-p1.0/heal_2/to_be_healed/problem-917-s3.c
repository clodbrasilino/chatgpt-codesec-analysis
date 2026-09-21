#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char** find_sequences(const char* str, int* count) {
    *count = 0;
    size_t capacity = 10;
    char** results = malloc(capacity * sizeof(char*));
    if (!results) {
        return NULL;
    }

    size_t max_len = SIZE_MAX;
    const char* ptr = str;
    while (*ptr != '\0' && max_len-- > 0) {
        ptr++;
    }
    size_t len = ptr - str;

    size_t i = 0;

    while (i < len) {
        if (isupper((unsigned char)str[i])) {
            size_t start = i;
            i++;
            while (i < len && islower((unsigned char)str[i])) {
                i++;
            }
            /* Possible weaknesses found:
             *  Assuming that condition 'i>start' is not redundant
             */
            if (i > start) {
                if ((size_t)*count >= capacity) {
                    size_t new_capacity = capacity * 2;
                    if (new_capacity < capacity) {
                        for (int j = 0; j < *count; j++) {
                            free(results[j]);
                        }
                        free(results);
                        *count = 0;
                        return NULL;
                    }
                    char** temp = realloc(results, new_capacity * sizeof(char*));
                    if (!temp) {
                        for (int j = 0; j < *count; j++) {
                            free(results[j]);
                        }
                        free(results);
                        *count = 0;
                        return NULL;
                    }
                    results = temp;
                    capacity = new_capacity;
                }
                /* Possible weaknesses found:
                 *  Assignment 'seq_len=i-start', assigned value is greater than 0
                 */
                size_t seq_len = i - start;
                char* seq = malloc(seq_len + 1);
                /* Possible weaknesses found:
                 *  Assuming condition is false
                 */
                if (!seq) {
                    for (int j = 0; j < *count; j++) {
                        free(results[j]);
                    }
                    free(results);
                    *count = 0;
                    return NULL;
                }
                /* Possible weaknesses found:
                 *  Condition 'seq_len>0' is always true [knownConditionTrueFalse]
                 *  Condition 'seq_len>0' is always true
                 */
                if (seq_len > 0) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(seq, str + start, seq_len);
                }
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