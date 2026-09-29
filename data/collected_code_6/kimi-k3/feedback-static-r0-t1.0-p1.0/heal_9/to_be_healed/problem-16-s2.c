#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_INPUT_SIZE 1024
#define MAX_SEQUENCE_SIZE 256

int find_lowercase_underscore_sequences(const char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return -1;
    }
    
    size_t len = strnlen(str, max_len);
    size_t i = 0;
    bool found_any = false;
    
    while (i < len) {
        if (islower((unsigned char)str[i])) {
            size_t seq_start = i;
            size_t seq_len = 0;
            
            while (i < len && (islower((unsigned char)str[i]) || str[i] == '_')) {
                seq_len++;
                i++;
            }
            
            if (seq_len > 0 && seq_len < MAX_SEQUENCE_SIZE) {
                if (seq_len == SIZE_MAX) {
                    return -1;
                }
                
                char *sequence = calloc(seq_len + 1, sizeof(char));
                if (sequence == NULL) {
                    return -1;
                }
                
                size_t remaining = len - seq_start;
                if (remaining < seq_len) {
                    free(sequence);
                    return -1;
                }
                
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(sequence, str + seq_start, seq_len);
                sequence[seq_len] = '\0';
                
                bool has_underscore = false;
                bool valid = true;
                
                for (size_t j = 0; j < seq_len; j++) {
                    if (sequence[j] == '_') {
                        has_underscore = true;
                        if (j == 0 || j == seq_len - 1) {
                            valid = false;
                            break;
                        }
                        if (sequence[j - 1] == '_') {
                            valid = false;
                            break;
                        }
                    }
                }
                
                if (valid && has_underscore) {
                    printf("Found sequence: %s\n", sequence);
                    found_any = true;
                }
                
                free(sequence);
            }
        } else {
            i++;
        }
    }
    
    return found_any ? 0 : 1;
}

int main(void) {
    char *input = NULL;
    size_t input_size = 0;
    ssize_t chars_read;
    
    printf("Enter a string: ");
    
    chars_read = getline(&input, &input_size, stdin);
    if (chars_read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return 1;
    }
    
    if (chars_read > 0 && input[chars_read - 1] == '\n') {
        input[chars_read - 1] = '\0';
        chars_read--;
    }
    
    if (chars_read >= MAX_INPUT_SIZE) {
        fprintf(stderr, "Input too long\n");
        free(input);
        return 1;
    }
    
    int result = find_lowercase_underscore_sequences(input, (size_t)chars_read + 1);
    
    free(input);
    
    if (result == 1) {
        printf("No sequences found\n");
    } else if (result == -1) {
        fprintf(stderr, "Error processing string\n");
        return 1;
    }
    
    return 0;
}