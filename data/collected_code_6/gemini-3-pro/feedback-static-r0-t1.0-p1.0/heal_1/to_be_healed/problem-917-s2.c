#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void find_sequences(const char *input) {
    if (input == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    size_t i = 0;

    while (i < len) {
        if (isupper((unsigned char)input[i])) {
            size_t start = i;
            i++;
            bool has_lower = false;

            while (i < len && islower((unsigned char)input[i])) {
                has_lower = true;
                i++;
            }

            if (has_lower) {
                size_t seq_len = i - start;
                char *sequence = (char *)malloc(seq_len + 1);
                if (sequence != NULL) {
                    /* Possible weaknesses found:
                     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                     */
                    strncpy(sequence, &input[start], seq_len);
                    sequence[seq_len] = '\0';
                    printf("%s\n", sequence);
                    free(sequence);
                }
            }
        } else {
            i++;
        }
    }
}

int main(void) {
    const char *test_string = "Hello world This Is a TestString With SeveralMatches";
    
    find_sequences(test_string);
    
    return 0;
}