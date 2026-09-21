#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_SEQUENCES 100
#define MAX_SEQUENCE_LENGTH 64

static size_t safe_strnlen(const char *str, size_t maxlen) {
    size_t i = 0;
    while (i < maxlen && str[i] != '\0') {
        i++;
    }
    return i;
}

int find_sequences(const char *str, char sequences[][MAX_SEQUENCE_LENGTH], int max_sequences) {
    if (str == NULL || sequences == NULL || max_sequences <= 0) {
        return -1;
    }
    
    int count = 0;
    size_t len = safe_strnlen(str, MAX_SEQUENCE_LENGTH * MAX_SEQUENCES);
    size_t i = 0;
    
    while (i < len && count < max_sequences) {
        if (isupper((unsigned char)str[i])) {
            size_t start = i;
            i++;
            
            if (i < len && islower((unsigned char)str[i])) {
                while (i < len && islower((unsigned char)str[i])) {
                    i++;
                }
                
                size_t seq_len = i - start;
                if (seq_len >= MAX_SEQUENCE_LENGTH) {
                    seq_len = MAX_SEQUENCE_LENGTH - 1;
                }
                
                /* Possible weaknesses found:
                 *  Assuming that condition 'seq_len>0' is not redundant
                 */
                if (seq_len > 0 && seq_len < MAX_SEQUENCE_LENGTH) {
                    /* Possible weaknesses found:
                     *  Assignment 'copy_len=seq_len', assigned value is greater than 0
                     */
                    size_t copy_len = seq_len;
                    if (copy_len >= MAX_SEQUENCE_LENGTH) {
                        copy_len = MAX_SEQUENCE_LENGTH - 1;
                    }
                    /* Possible weaknesses found:
                     *  Condition 'copy_len>0' is always true [knownConditionTrueFalse]
                     *  Condition 'copy_len>0' is always true
                     */
                    if (copy_len > 0) {
                        /* Possible weaknesses found:
                         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                         */
                        memcpy(sequences[count], &str[start], copy_len);
                        sequences[count][copy_len] = '\0';
                        count++;
                    }
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
    
    if (sizeof(sequences) > 0) {
        memset(sequences, 0, sizeof(sequences));
    }
    
    int found = find_sequences(text, sequences, MAX_SEQUENCES);
    
    if (found < 0) {
        printf("Error: invalid parameters\n");
        return 1;
    }
    
    if (found > MAX_SEQUENCES) {
        found = MAX_SEQUENCES;
    }
    
    printf("Found %d sequences:\n", found);
    for (int i = 0; i < found; i++) {
        printf("%s\n", sequences[i]);
    }
    
    return 0;
}