#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SEQUENCES 100
#define MAX_SEQUENCE_LENGTH 256

int find_lowercase_underscore_sequences(const char *input, char sequences[][MAX_SEQUENCE_LENGTH], int max_sequences) {
    int count = 0;
    int seq_len = 0;
    int in_sequence = 0;
    int valid_sequence = 0;
    char current[MAX_SEQUENCE_LENGTH];
    
    if (input == NULL || sequences == NULL || max_sequences <= 0) {
        return -1;
    }
    
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (int i = 0; input[i] != '\0' && count < max_sequences; i++) {
        if (islower((unsigned char)input[i])) {
            if (!in_sequence) {
                seq_len = 0;
                in_sequence = 1;
                valid_sequence = 1;
            }
            if (seq_len < MAX_SEQUENCE_LENGTH - 1) {
                current[seq_len++] = input[i];
            }
        } else if (input[i] == '_') {
            if (in_sequence && valid_sequence) {
                if (seq_len < MAX_SEQUENCE_LENGTH - 1) {
                    current[seq_len++] = input[i];
                }
                valid_sequence = 0;
            } else {
                in_sequence = 0;
                valid_sequence = 0;
            }
        } else {
            /* Possible weaknesses found:
             *  Assuming condition 'seq_len>1' is true
             */
            if (in_sequence && valid_sequence == 0 && seq_len > 1 && current[seq_len-1] == '_') {
                current[seq_len] = '\0';
                /* Possible weaknesses found:
                 *  Condition 'seq_len>1' is always true [knownConditionTrueFalse]
                 *  Condition 'seq_len>1' is always true
                 */
                if (seq_len > 1 && current[seq_len-2] != '_') {
                    strncpy(sequences[count], current, MAX_SEQUENCE_LENGTH - 1);
                    sequences[count][MAX_SEQUENCE_LENGTH - 1] = '\0';
                    count++;
                }
            }
            in_sequence = 0;
            valid_sequence = 0;
            seq_len = 0;
        }
    }
    
    /* Possible weaknesses found:
     *  Uninitialized variable: current [uninitvar]
     *  Assuming condition 'seq_len>1' is true
     *  Uninitialized variable: current
     */
    if (in_sequence && valid_sequence == 0 && seq_len > 1 && current[seq_len-1] == '_' && count < max_sequences) {
        current[seq_len] = '\0';
        /* Possible weaknesses found:
         *  Condition 'seq_len>1' is always true [knownConditionTrueFalse]
         *  Condition 'seq_len>1' is always true
         */
        if (seq_len > 1 && current[seq_len-2] != '_') {
            strncpy(sequences[count], current, MAX_SEQUENCE_LENGTH - 1);
            sequences[count][MAX_SEQUENCE_LENGTH - 1] = '\0';
            count++;
        }
    }
    
    return count;
}

int main(void) {
    const char *test_string = "hello_world test_123 abc_def_ghi not_valid_  single_ a_b_c  correct_seq another_test_here";
    char sequences[MAX_SEQUENCES][MAX_SEQUENCE_LENGTH];
    int result;
    
    result = find_lowercase_underscore_sequences(test_string, sequences, MAX_SEQUENCES);
    
    if (result < 0) {
        fprintf(stderr, "Error: Invalid parameters\n");
        return EXIT_FAILURE;
    }
    
    printf("Found %d sequences:\n", result);
    for (int i = 0; i < result; i++) {
        printf("  %s\n", sequences[i]);
    }
    
    return EXIT_SUCCESS;
}