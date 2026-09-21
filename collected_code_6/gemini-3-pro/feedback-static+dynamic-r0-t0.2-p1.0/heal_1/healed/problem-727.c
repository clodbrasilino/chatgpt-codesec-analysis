#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int remove_special_characters(const char *input, char **output) {
    if (input == NULL || output == NULL) {
        return -1;
    }

    size_t input_len = 0;
    size_t valid_count = 0;
    
    while (input[input_len] != '\0') {
        if (isalnum((unsigned char)input[input_len])) {
            valid_count++;
        }
        input_len++;
    }

    *output = (char *)malloc(valid_count + 1);
    if (*output == NULL) {
        return -1;
    }

    size_t out_idx = 0;
    for (size_t i = 0; i < input_len; i++) {
        if (isalnum((unsigned char)input[i])) {
            (*output)[out_idx++] = input[i];
        }
    }
    (*output)[out_idx] = '\0';

    return 0;
}

int main(void) {
    const char *input = "Hello, World! 123 @#$";
    char *output = NULL;

    if (remove_special_characters(input, &output) == 0) {
        printf("Original: %s\n", input);
        printf("Cleaned: %s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Error processing string.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}