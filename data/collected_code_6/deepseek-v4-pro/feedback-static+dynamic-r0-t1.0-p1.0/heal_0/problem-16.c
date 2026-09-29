#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SEQUENCE_LENGTH 256
#define MAX_SEQUENCES 100

int find_sequences(const char *input, char sequences[][MAX_SEQUENCE_LENGTH], int max_sequences) {
    if (input == NULL || sequences == NULL || max_sequences <= 0) {
        return -1;
    }

    int count = 0;
    int seq_index = 0;
    size_t input_len = strlen(input);
    size_t i = 0;

    while (i < input_len && count < max_sequences) {
        if (islower((unsigned char)input[i])) {
            seq_index = 0;
            while (i < input_len && islower((unsigned char)input[i])) {
                sequences[count][seq_index++] = input[i];
                i++;
            }
            if (i < input_len && input[i] == '_') {
                i++;
                int underscore_found = 1;
                while (i < input_len && islower((unsigned char)input[i])) {
                    if (underscore_found) {
                        if (seq_index < MAX_SEQUENCE_LENGTH - 1) {
                            sequences[count][seq_index++] = '_';
                        }
                        underscore_found = 0;
                    }
                    if (seq_index < MAX_SEQUENCE_LENGTH - 1) {
                        sequences[count][seq_index++] = input[i];
                    }
                    i++;
                }
                if (!underscore_found && seq_index > 0) {
                    sequences[count][seq_index] = '\0';
                    count++;
                }
            } else {
                if (seq_index > 0 && i >= input_len) {
                    sequences[count][seq_index] = '\0';
                    count++;
                }
            }
        } else {
            i++;
        }
    }

    return count;
}

int main(void) {
    const char *text = "hello_world test example_foo bar_baz_qux abc_def_ghi";
    char sequences[MAX_SEQUENCES][MAX_SEQUENCE_LENGTH];
    int num_sequences;

    num_sequences = find_sequences(text, sequences, MAX_SEQUENCES);

    if (num_sequences < 0) {
        fprintf(stderr, "Error: Invalid input parameters\n");
        return EXIT_FAILURE;
    }

    printf("Found %d sequences:\n", num_sequences);
    for (int i = 0; i < num_sequences; i++) {
        printf("%s\n", sequences[i]);
    }

    return EXIT_SUCCESS;
}