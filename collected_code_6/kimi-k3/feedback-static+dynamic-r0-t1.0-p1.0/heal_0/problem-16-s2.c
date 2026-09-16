#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_INPUT_SIZE 1024
#define MAX_SEQUENCE_SIZE 256

int find_lowercase_underscore_sequences(const char *str) {
    if (str == NULL) {
        return -1;
    }
    
    size_t len = strlen(str);
    size_t i = 0;
    bool found_any = false;
    
    while (i < len) {
        if (islower((unsigned char)str[i])) {
            size_t start = i;
            size_t seq_len = 0;
            char sequence[MAX_SEQUENCE_SIZE];
            
            while (i < len && (islower((unsigned char)str[i]) || str[i] == '_')) {
                if (seq_len < MAX_SEQUENCE_SIZE - 1) {
                    sequence[seq_len++] = str[i];
                }
                i++;
            }
            
            if (seq_len > 0) {
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
                        if (j > 0 && sequence[j - 1] == '_') {
                            valid = false;
                            break;
                        }
                    }
                }
                
                if (valid && has_underscore) {
                    printf("Found sequence: %s\n", sequence);
                    found_any = true;
                }
            }
        } else {
            i++;
        }
    }
    
    return found_any ? 0 : 1;
}

int main(void) {
    char input[MAX_INPUT_SIZE];
    
    printf("Enter a string: ");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    int result = find_lowercase_underscore_sequences(input);
    
    if (result == 1) {
        printf("No sequences found\n");
    } else if (result == -1) {
        fprintf(stderr, "Error processing string\n");
        return 1;
    }
    
    return 0;
}