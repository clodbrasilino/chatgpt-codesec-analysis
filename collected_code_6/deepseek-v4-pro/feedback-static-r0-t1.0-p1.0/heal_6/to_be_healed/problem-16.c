#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SEQUENCE_LENGTH 256
#define MAX_SEQUENCES 100

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int find_sequences(const char *input, char (*sequences)[MAX_SEQUENCE_LENGTH], size_t max_sequences) {
    if (input == NULL || sequences == NULL || max_sequences == 0) {
        return -1;
    }

    size_t count = 0;
    size_t pos = 0;
    size_t input_length = safe_strlen(input, MAX_SEQUENCE_LENGTH * max_sequences + 256);

    while (pos < input_length && count < max_sequences) {
        if (islower((unsigned char)input[pos])) {
            size_t seq_index = 0;
            size_t start = pos;
            int has_underscore = 0;

            while (pos < input_length && islower((unsigned char)input[pos])) {
                if (seq_index >= MAX_SEQUENCE_LENGTH - 1) {
                    return -2;
                }
                pos++;
                seq_index++;
            }

            if (pos < input_length && input[pos] == '_') {
                has_underscore = 1;
                if (seq_index >= MAX_SEQUENCE_LENGTH - 1) {
                    return -2;
                }
                pos++;
                seq_index++;

                while (pos < input_length && islower((unsigned char)input[pos])) {
                    if (seq_index >= MAX_SEQUENCE_LENGTH - 1) {
                        return -2;
                    }
                    pos++;
                    seq_index++;
                }
            }

            if (seq_index > 0 && has_underscore) {
                if (seq_index >= MAX_SEQUENCE_LENGTH) {
                    return -2;
                }

                if (seq_index < MAX_SEQUENCE_LENGTH) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(sequences[count], input + start, seq_index);
                    sequences[count][seq_index] = '\0';
                    count++;
                }
            }
        } else {
            pos++;
        }
    }

    return (int)count;
}

int main(void) {
    const char text[] = "hello_world test example_foo bar_baz_qux abc_def_ghi";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char (*sequences)[MAX_SEQUENCE_LENGTH] = NULL;
    int num_sequences;

    sequences = calloc(MAX_SEQUENCES, sizeof(char[MAX_SEQUENCE_LENGTH]));
    if (sequences == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    num_sequences = find_sequences(text, sequences, MAX_SEQUENCES);

    if (num_sequences < 0) {
        fprintf(stderr, "Error: Invalid input parameters or buffer overflow detected\n");
        free(sequences);
        return EXIT_FAILURE;
    }

    if ((size_t)num_sequences > MAX_SEQUENCES) {
        fprintf(stderr, "Error: Too many sequences found\n");
        free(sequences);
        return EXIT_FAILURE;
    }

    printf("Found %d sequences:\n", num_sequences);
    for (int i = 0; i < num_sequences; i++) {
        printf("%s\n", sequences[i]);
    }

    free(sequences);
    return EXIT_SUCCESS;
}