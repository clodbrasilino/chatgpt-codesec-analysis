#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SEQUENCE_LENGTH 256
#define MAX_SEQUENCES 100

int find_sequences(const char *input, char (*sequences)[MAX_SEQUENCE_LENGTH], int max_sequences) {
    if (input == NULL || sequences == NULL || max_sequences <= 0) {
        return -1;
    }

    int count = 0;
    size_t i = 0;
    size_t input_len = strlen(input);

    while (i < input_len && count < max_sequences) {
        if (islower((unsigned char)input[i])) {
            size_t seq_index = 0;
            size_t low_start = i;
            while (i < input_len && islower((unsigned char)input[i])) {
                i++;
            }
            if (i < input_len && input[i] == '_') {
                size_t underscore_pos = i;
                i++;
                if (i < input_len && islower((unsigned char)input[i])) {
                    size_t second_start = i;
                    while (i < input_len && islower((unsigned char)input[i])) {
                        i++;
                    }
                    size_t total_len = (underscore_pos - low_start) + 1 + (i - second_start);
                    if (total_len >= MAX_SEQUENCE_LENGTH) {
                        total_len = MAX_SEQUENCE_LENGTH - 1;
                    }
                    size_t copy_i = low_start;
                    size_t end = low_start + total_len;
                    while (copy_i < end && copy_i < input_len) {
                        sequences[count][seq_index++] = input[copy_i++];
                    }
                    sequences[count][seq_index] = '\0';
                    count++;
                }
            } else if (i == input_len && low_start < i) {
                size_t total_len = i - low_start;
                if (total_len >= MAX_SEQUENCE_LENGTH) {
                    total_len = MAX_SEQUENCE_LENGTH - 1;
                }
                memcpy(sequences[count], input + low_start, total_len);
                sequences[count][total_len] = '\0';
                count++;
            }
        } else {
            i++;
        }
    }

    return count;
}

int main(void) {
    const char *text = "hello_world test example_foo bar_baz_qux abc_def_ghi";
    char (*sequences)[MAX_SEQUENCE_LENGTH] = malloc(MAX_SEQUENCES * sizeof(*sequences));
    int num_sequences;
    size_t text_len;
    size_t max_safe_len = (size_t)MAX_SEQUENCE_LENGTH * (size_t)MAX_SEQUENCES;

    if (sequences == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    text_len = strnlen(text, max_safe_len + 1);
    if (text_len >= max_safe_len) {
        fprintf(stderr, "Error: Input string too long\n");
        free(sequences);
        return EXIT_FAILURE;
    }

    num_sequences = find_sequences(text, sequences, MAX_SEQUENCES);

    if (num_sequences < 0) {
        fprintf(stderr, "Error: Invalid input parameters\n");
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