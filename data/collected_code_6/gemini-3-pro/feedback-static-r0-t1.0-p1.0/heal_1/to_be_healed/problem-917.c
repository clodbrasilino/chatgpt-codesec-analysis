#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void find_sequences(const char *str) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return;
    }

    const char *current = str;
    while (*current != '\0') {
        if (isupper((unsigned char)*current)) {
            const char *start = current;
            current++;
            
            if (islower((unsigned char)*current)) {
                while (islower((unsigned char)*current)) {
                    current++;
                }
                
                size_t seq_len = current - start;
                char *sequence = (char *)malloc(seq_len + 1);
                if (sequence != NULL) {
                    /* Possible weaknesses found:
                     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                     */
                    strncpy(sequence, start, seq_len);
                    sequence[seq_len] = '\0';
                    printf("%s\n", sequence);
                    free(sequence);
                }
            }
        } else {
            current++;
        }
    }
}

int main(void) {
    const char *test_str = "This Is A Test String With Some Sequences Like CamelCase and PascalCase.";
    
    find_sequences(test_str);
    
    return 0;
}