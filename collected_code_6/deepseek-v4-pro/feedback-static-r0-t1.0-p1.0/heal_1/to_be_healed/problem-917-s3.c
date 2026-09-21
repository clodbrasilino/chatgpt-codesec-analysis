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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = (int)strlen(str);
    int i = 0;
    
    while (i < len && count < max_sequences) {
        if (isupper((unsigned char)str[i])) {
            int start = i;
            i++;
            
            if (i < len && islower((unsigned char)str[i])) {
                int j = 0;
                while (i < len && islower((unsigned char)str[i]) && j < MAX_SEQUENCE_LENGTH - 1) {
                    i++;
                    j++;
                }
                
                int seq_len = i - start;
                if (seq_len < MAX_SEQUENCE_LENGTH) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(sequences[count], &str[start], seq_len);
                    sequences[count][seq_len] = '\0';
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sequences[MAX_SEQUENCES][MAX_SEQUENCE_LENGTH];
    
    int found = find_sequences(text, sequences, MAX_SEQUENCES);
    
    printf("Found %d sequences:\n", found);
    for (int i = 0; i < found; i++) {
        printf("%s\n", sequences[i]);
    }
    
    return 0;
}