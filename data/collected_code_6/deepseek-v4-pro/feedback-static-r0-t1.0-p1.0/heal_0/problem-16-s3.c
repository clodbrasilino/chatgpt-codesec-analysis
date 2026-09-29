#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **find_lowercase_underscore_sequences(const char *input, int *count) {
    char **sequences = NULL;
    int seq_count = 0;
    int capacity = 0;
    const char *p = input;

    *count = 0;

    while (*p) {
        if (islower((unsigned char)*p)) {
            const char *start = p;
            int is_valid = 1;

            while (*p && (islower((unsigned char)*p) || *p == '_')) {
                if (*p == '_') {
                    if (*(p + 1) == '_' || !islower((unsigned char)*(p + 1))) {
                        is_valid = 0;
                        while (*p && *p != ' ') {
                            p++;
                        }
                        break;
                    }
                }
                p++;
            }

            if (is_valid && *(p - 1) != '_') {
                if (seq_count >= capacity) {
                    capacity = capacity == 0 ? 4 : capacity * 2;
                    char **temp = realloc(sequences, capacity * sizeof(char *));
                    if (!temp) {
                        for (int i = 0; i < seq_count; i++) {
                            free(sequences[i]);
                        }
                        free(sequences);
                        return NULL;
                    }
                    sequences = temp;
                }

                int len = p - start;
                sequences[seq_count] = malloc((len + 1) * sizeof(char));
                if (!sequences[seq_count]) {
                    for (int i = 0; i < seq_count; i++) {
                        free(sequences[i]);
                    }
                    free(sequences);
                    return NULL;
                }
                strncpy(sequences[seq_count], start, len);
                sequences[seq_count][len] = '\0';
                seq_count++;
            }
        } else {
            p++;
        }
    }

    *count = seq_count;
    return sequences;
}

int main(void) {
    const char *text = "hello_world test_case valid_sequence invalid__sequence invalid_ not_valid_  another_one_here";
    int count = 0;
    char **result = find_lowercase_underscore_sequences(text, &count);

    if (result) {
        printf("Found %d sequences:\n", count);
        for (int i = 0; i < count; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    } else {
        printf("Memory allocation error or no sequences found.\n");
    }

    return 0;
}