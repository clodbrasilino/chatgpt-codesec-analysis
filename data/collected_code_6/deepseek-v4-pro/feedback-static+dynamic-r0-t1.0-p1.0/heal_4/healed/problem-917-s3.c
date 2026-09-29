#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SEQUENCES 100
#define MAX_SEQUENCE_LENGTH 64

int find_sequences(const char *str, char sequences[][MAX_SEQUENCE_LENGTH], int max_sequences) {
    if (str == NULL || sequences == NULL || max_sequences <= 0) {
        return -1;
    }
    
    int count = 0;
    int i = 0;
    
    while (str[i] != '\0' && count < max_sequences) {
        if (isupper((unsigned char)str[i])) {
            int start = i;
            i++;
            
            if (str[i] != '\0' && islower((unsigned char)str[i])) {
                int j = 0;
                while (str[i] != '\0' && islower((unsigned char)str[i]) && j < MAX_SEQUENCE_LENGTH - 1) {
                    i++;
                    j++;
                }
                
                int seq_len = i - start;
                if (seq_len > 0) {
                    size_t copy_len;
                    if ((size_t)seq_len >= (size_t)MAX_SEQUENCE_LENGTH) {
                        copy_len = (size_t)(MAX_SEQUENCE_LENGTH - 1);
                    } else {
                        copy_len = (size_t)seq_len;
                    }
                    if (copy_len > 0) {
                        memcpy(sequences[count], &str[start], copy_len);
                    }
                    sequences[count][copy_len] = '\0';
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
    const char *text = "Hello World This is a Test String with Many Uppercase Words Like Python and JavaScript";
    char sequences[MAX_SEQUENCES][MAX_SEQUENCE_LENGTH];
    
    int found = find_sequences(text, sequences, MAX_SEQUENCES);
    
    if (found < 0 || found > MAX_SEQUENCES) {
        printf("Error processing sequences.\n");
        return 1;
    }
    
    printf("Found %d sequences:\n", found);
    for (int i = 0; i < found; i++) {
        printf("%s\n", sequences[i]);
    }
    
    return 0;
}