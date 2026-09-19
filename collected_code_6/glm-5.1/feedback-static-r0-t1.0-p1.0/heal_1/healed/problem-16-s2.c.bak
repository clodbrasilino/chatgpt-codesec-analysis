#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **find_sequences(const char *str, size_t *count) {
    size_t capacity = 16;
    size_t idx = 0;
    char **results = malloc(capacity * sizeof(char *));

    if (!results) {
        *count = 0;
        return NULL;
    }

    const char *p = str;
    while (*p) {
        if (islower((unsigned char)*p)) {
            const char *start = p;
            while (*p && islower((unsigned char)*p)) {
                p++;
            }
            if (*p == '_' && islower((unsigned char)*(p + 1))) {
                p++;
                while (*p && islower((unsigned char)*p)) {
                    p++;
                }
                size_t seq_len = p - start;
                char *seq = malloc(seq_len + 1);
                if (!seq) {
                    for (size_t i = 0; i < idx; i++) {
                        free(results[i]);
                    }
                    free(results);
                    *count = 0;
                    return NULL;
                }
                memcpy(seq, start, seq_len);
                seq[seq_len] = '\0';
                if (idx >= capacity) {
                    capacity *= 2;
                    char **temp = realloc(results, capacity * sizeof(char *));
                    if (!temp) {
                        free(seq);
                        for (size_t i = 0; i < idx; i++) {
                            free(results[i]);
                        }
                        free(results);
                        *count = 0;
                        return NULL;
                    }
                    results = temp;
                }
                results[idx++] = seq;
            }
        } else {
            p++;
        }
    }
    *count = idx;
    return results;
}

int main(void) {
    const char *text = "hello_world test_case bad1 good_luck a_b_c another_here";
    size_t count = 0;
    char **seqs = find_sequences(text, &count);

    if (seqs) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", seqs[i]);
            free(seqs[i]);
        }
        free(seqs);
    }
    return 0;
}