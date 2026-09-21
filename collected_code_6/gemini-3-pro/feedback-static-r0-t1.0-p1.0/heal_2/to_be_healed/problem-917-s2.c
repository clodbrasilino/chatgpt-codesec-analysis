#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void find_sequences(const char *input) {
    if (input == NULL) {
        return;
    }

    size_t i = 0;

    while (input[i] != '\0') {
        if (isupper((unsigned char)input[i])) {
            size_t start = i;
            i++;
            bool has_lower = false;

            while (input[i] != '\0' && islower((unsigned char)input[i])) {
                has_lower = true;
                i++;
            }

            if (has_lower) {
                size_t seq_len = i - start;
                char *sequence = (char *)malloc(seq_len + 1);
                if (sequence != NULL) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(sequence, &input[start], seq_len);
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