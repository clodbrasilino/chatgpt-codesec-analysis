#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_SEQUENCES 100
#define MAX_SEQUENCE_LENGTH 256

static int safe_memcpy(char *dest, size_t dest_size, const char *src, size_t src_len) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return -1;
    }
    if (src_len >= dest_size) {
        return -1;
    }
    memcpy(dest, src, src_len);
    dest[src_len] = '\0';
    return 0;
}

static int is_valid_sequence_end(const char *current, int seq_len) {
    return seq_len >= 2 && 
           seq_len < MAX_SEQUENCE_LENGTH && 
           current[seq_len - 1] == '_' &&
           islower((unsigned char)current[seq_len - 2]);
}

static int store_sequence(char (*sequences)[MAX_SEQUENCE_LENGTH], int max_sequences, 
                          const char *current, int seq_len, int *count) {
    if (*count >= max_sequences) {
        return -1;
    }
    if (safe_memcpy(sequences[*count], MAX_SEQUENCE_LENGTH, current, (size_t)seq_len) != 0) {
        return -1;
    }
    (*count)++;
    return 0;
}

int find_lowercase_underscore_sequences(const char *input, char (*sequences)[MAX_SEQUENCE_LENGTH], int max_sequences) {
    int count = 0;
    int seq_len = 0;
    int in_sequence = 0;
    int valid_sequence = 0;
    char *current = NULL;
    
    if (input == NULL || sequences == NULL || max_sequences <= 0) {
        return -1;
    }
    
    if (max_sequences > MAX_SEQUENCES) {
        max_sequences = MAX_SEQUENCES;
    }
    
    current = (char *)malloc(MAX_SEQUENCE_LENGTH);
    if (current == NULL) {
        return -1;
    }
    
    memset(current, 0, MAX_SEQUENCE_LENGTH);
    
    for (size_t i = 0; input[i] != '\0' && count < max_sequences; i++) {
        if (islower((unsigned char)input[i])) {
            if (!in_sequence) {
                seq_len = 0;
                in_sequence = 1;
                valid_sequence = 1;
            }
            if (seq_len < MAX_SEQUENCE_LENGTH - 1) {
                current[seq_len++] = input[i];
            } else {
                in_sequence = 0;
                valid_sequence = 0;
                seq_len = 0;
            }
        } else if (input[i] == '_') {
            if (in_sequence && valid_sequence && seq_len >= 1 && seq_len < MAX_SEQUENCE_LENGTH - 1) {
                current[seq_len++] = input[i];
                valid_sequence = 0;
            } else {
                in_sequence = 0;
                valid_sequence = 0;
                seq_len = 0;
            }
        } else {
            if (in_sequence && !valid_sequence && is_valid_sequence_end(current, seq_len)) {
                if (store_sequence(sequences, max_sequences, current, seq_len, &count) != 0) {
                    free(current);
                    return count;
                }
            }
            in_sequence = 0;
            valid_sequence = 0;
            seq_len = 0;
        }
    }
    
    if (in_sequence && !valid_sequence && is_valid_sequence_end(current, seq_len) && count < max_sequences) {
        store_sequence(sequences, max_sequences, current, seq_len, &count);
    }
    
    free(current);
    return count;
}

int main(void) {
    const char *test_string = "hello_world test_123 abc_def_ghi not_valid_  single_ a_b_c  correct_seq another_test_here";
    char (*sequences)[MAX_SEQUENCE_LENGTH] = NULL;
    int result;
    size_t allocation_size;
    
    if (MAX_SEQUENCES > (SIZE_MAX / sizeof(char[MAX_SEQUENCE_LENGTH]))) {
        fprintf(stderr, "Error: Allocation size overflow\n");
        return EXIT_FAILURE;
    }
    
    allocation_size = (size_t)MAX_SEQUENCES * sizeof(char[MAX_SEQUENCE_LENGTH]);
    sequences = (char (*)[MAX_SEQUENCE_LENGTH])malloc(allocation_size);
    if (sequences == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    memset(sequences, 0, allocation_size);
    
    result = find_lowercase_underscore_sequences(test_string, sequences, MAX_SEQUENCES);
    
    if (result < 0) {
        fprintf(stderr, "Error: Invalid parameters\n");
        free(sequences);
        return EXIT_FAILURE;
    }
    
    printf("Found %d sequences:\n", result);
    for (int i = 0; i < result; i++) {
        printf("  %s\n", sequences[i]);
    }
    
    free(sequences);
    return EXIT_SUCCESS;
}