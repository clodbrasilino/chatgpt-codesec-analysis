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
    size_t i = 0;

    while (input[i] != '\0' && count < max_sequences) {
        if (islower((unsigned char)input[i])) {
            size_t seq_index = 0;
            while (input[i] != '\0' && islower((unsigned char)input[i])) {
                if (seq_index < MAX_SEQUENCE_LENGTH - 1) {
                    sequences[count][seq_index++] = input[i];
                }
                i++;
            }
            if (input[i] == '_') {
                i++;
                int underscore_added = 0;
                if (seq_index < MAX_SEQUENCE_LENGTH - 1) {
                    sequences[count][seq_index++] = '_';
                    underscore_added = 1;
                }
                while (input[i] != '\0' && islower((unsigned char)input[i])) {
                    if (seq_index < MAX_SEQUENCE_LENGTH - 1) {
                        sequences[count][seq_index++] = input[i];
                    }
                    i++;
                }
                if (underscore_added && seq_index > 1) {
                    sequences[count][seq_index] = '\0';
                    count++;
                }
            } else {
                if (seq_index > 0) {
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
    const char text[] = "hello_world test example_foo bar_baz_qux abc_def_ghi";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sequences[MAX_SEQUENCES][MAX_SEQUENCE_LENGTH];
    int num_sequences;

    memset(sequences, 0, sizeof(sequences));

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