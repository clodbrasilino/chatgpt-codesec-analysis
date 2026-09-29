#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_words_of_length(const char *str, size_t k)
{
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    int first_word = 1;

    while (i < len) {
        while (i < len && isspace((unsigned char)str[i])) {
            i++;
        }
        if (i >= len) {
            break;
        }

        size_t word_start = i;
        while (i < len && !isspace((unsigned char)str[i])) {
            i++;
        }
        size_t word_len = i - word_start;

        if (word_len != k) {
            if (!first_word) {
                result[j++] = ' ';
            }
            memcpy(result + j, str + word_start, word_len);
            j += word_len;
            first_word = 0;
        }
    }
    result[j] = '\0';

    char *shrunk = (char *)realloc(result, j + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void)
{
    char input[1024];
    size_t k = 0;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    size_t input_len = strlen(input);
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
    }

    printf("Enter the word length to remove: ");
    if (scanf("%zu", &k) != 1) {
        fprintf(stderr, "Invalid length value.\n");
        return EXIT_FAILURE;
    }

    char *modified = remove_words_of_length(input, k);
    if (modified == NULL) {
        fprintf(stderr, "Failed to process the string.\n");
        return EXIT_FAILURE;
    }

    printf("Result: \"%s\"\n", modified);

    free(modified);
    return EXIT_SUCCESS;
}