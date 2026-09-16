#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char *remove_lowercase_substrings(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;
    while (i < len) {
        if (islower((unsigned char)input[i])) {
            while (i < len && islower((unsigned char)input[i])) {
                i++;
            }
        } else {
            result[j++] = input[i++];
        }
    }
    result[j] = '\0';

    char *final_result = (char *)realloc(result, j + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }

    return final_result;
}

int main(void) {
    const char *test_string = "Hello WORLD, this IS a Test STRING.";
    char *cleaned_string = remove_lowercase_substrings(test_string);

    if (cleaned_string == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Original: %s\n", test_string);
    printf("Cleaned:  %s\n", cleaned_string);

    free(cleaned_string);
    return 0;
}