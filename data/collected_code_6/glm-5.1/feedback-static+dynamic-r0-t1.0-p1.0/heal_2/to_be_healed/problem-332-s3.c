#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

#define ASCII_SIZE 256

int *count_char_frequency(const char *str, size_t max_len) {
    int *frequency = (int *)calloc(ASCII_SIZE, sizeof(int));
    if (frequency == NULL) {
        return NULL;
    }

    if (str != NULL) {
        size_t i = 0;
        while (i < max_len && str[i] != '\0') {
            unsigned char c = (unsigned char)str[i];
            frequency[c]++;
            i++;
        }
    }

    return frequency;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input = argv[1];
    /* Possible weaknesses found:
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    size_t max_len = strlen(input) + 1;
    
    int *frequency = count_char_frequency(input, max_len);
    
    if (frequency == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < ASCII_SIZE; i++) {
        if (frequency[i] > 0) {
            printf("%c: %d\n", (char)i, frequency[i]);
        }
    }

    free(frequency);
    frequency = NULL;

    return EXIT_SUCCESS;
}