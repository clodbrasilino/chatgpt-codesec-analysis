#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SEQUENCES 100
#define MAX_SEQUENCE_LENGTH 256

int find_lowercase_underscore_sequences(const char *input, char sequences[][MAX_SEQUENCE_LENGTH], size_t max_sequences) {
    size_t count = 0;
    size_t seq_len = 0;
    int in_sequence = 0;
    int valid_sequence = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char current[MAX_SEQUENCE_LENGTH];
    
    if (input == NULL || sequences == NULL || max_sequences == 0) {
        return -1;
    }
    
    memset(current, 0, sizeof(current));
    
    for (size_t i = 0; input[i] != '\0' && count < max_sequences; i++) {
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
            if (in_sequence && valid_sequence == 0 && seq_len > 1 && seq_len < MAX_SEQUENCE_LENGTH && current[seq_len-1] == '_') {
                if (current[seq_len-2] != '_') {
                    current[seq_len] = '\0';
                    /* Possible weaknesses found:
                     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                     */
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
    
    if (in_sequence && valid_sequence == 0 && seq_len > 1 && seq_len < MAX_SEQUENCE_LENGTH && current[seq_len-1] == '_' && count < max_sequences) {
        if (current[seq_len-2] != '_') {
            current[seq_len] = '\0';
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(sequences[count], current, MAX_SEQUENCE_LENGTH - 1);
            sequences[count][MAX_SEQUENCE_LENGTH - 1] = '\0';
            count++;
        }
    }
    
    return (int)count;
}

int main(void) {
    const char *test_string = "hello_world test_123 abc_def_ghi not_valid_  single_ a_b_c  correct_seq another_test_here";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sequences[MAX_SEQUENCES][MAX_SEQUENCE_LENGTH];
    int result;
    
    memset(sequences, 0, sizeof(sequences));
    
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