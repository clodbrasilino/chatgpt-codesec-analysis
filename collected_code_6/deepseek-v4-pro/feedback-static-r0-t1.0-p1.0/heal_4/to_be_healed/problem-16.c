#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SEQUENCE_LENGTH 256
#define MAX_SEQUENCES 100

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int find_sequences(const char *input, char (*sequences)[MAX_SEQUENCE_LENGTH], int max_sequences) {
    if (input == NULL || sequences == NULL || max_sequences <= 0) {
        return -1;
    }

    int count = 0;
    size_t pos = 0;

    while (input[pos] != '\0' && count < max_sequences) {
        if (islower((unsigned char)input[pos])) {
            size_t seq_index = 0;
            size_t start = pos;

            while (input[pos] != '\0' && islower((unsigned char)input[pos]) && seq_index < MAX_SEQUENCE_LENGTH - 1) {
                seq_index++;
                pos++;
            }

            if (input[pos] == '_' && seq_index < MAX_SEQUENCE_LENGTH - 1) {
                seq_index++;
                pos++;

                while (input[pos] != '\0' && islower((unsigned char)input[pos]) && seq_index < MAX_SEQUENCE_LENGTH - 1) {
                    seq_index++;
                    pos++;
                }

                if (seq_index + 1 > MAX_SEQUENCE_LENGTH) {
                    return -2;
                }

                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(sequences[count], input + start, seq_index);
                sequences[count][seq_index] = '\0';
                count++;
            } else {
                if (seq_index > 0) {
                    if (seq_index + 1 > MAX_SEQUENCE_LENGTH) {
                        return -2;
                    }

                    /* Possible weaknesses found:
                     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                     */
                    strncpy(sequences[count], input + start, seq_index);
                    sequences[count][seq_index] = '\0';
                    count++;
                }
            }
        } else {
            pos++;
        }
    }

    return count;
}

int main(void) {
    const char text[] = "hello_world test example_foo bar_baz_qux abc_def_ghi";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char (*sequences)[MAX_SEQUENCE_LENGTH] = NULL;
    int num_sequences;

    sequences = calloc(MAX_SEQUENCES, sizeof(*sequences));
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

    if (num_sequences > MAX_SEQUENCES) {
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