#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 4096

char *remove_non_alphanumeric(const char *input)
{
    char *result;
    size_t result_len = 0;
    size_t input_len = 0;
    size_t i;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Assuming that condition 'input_len<4096' is not redundant
     *  Either the condition 'input_len<4096' is redundant or the array 'input[42]' is accessed at index 4095, which is out of bounds. [arrayIndexOutOfBoundsCond]
     */
    while (input_len < MAX_INPUT_LENGTH && input[input_len] != '\0') {
        input_len++;
    }

    result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < input_len; i++) {
        unsigned char ch = (unsigned char)input[i];
        if (isalnum(ch)) {
            result[result_len] = (char)ch;
            result_len++;
        }
    }

    result[result_len] = '\0';
    return result;
}

int main(void)
{
    const char *test = "Hello, World! 123 @#$% C-Programming_2024";
    char *cleaned = remove_non_alphanumeric(test);

    if (cleaned == NULL) {
        fprintf(stderr, "Error: string processing failed\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", test);
    printf("Cleaned:  %s\n", cleaned);

    free(cleaned);
    return EXIT_SUCCESS;
}