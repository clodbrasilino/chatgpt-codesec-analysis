#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* move_numbers_to_string(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    size_t digit_count = 0;

    for (size_t i = 0; i < len; i++) {
        if (isdigit((unsigned char)input[i])) {
            digit_count++;
        }
    }

    char* result = (char*)malloc(digit_count + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isdigit((unsigned char)input[i])) {
            result[j++] = input[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char* test_string = "abc123def456ghi789";
    char* numbers = move_numbers_to_string(test_string);

    if (numbers != NULL) {
        printf("Original: %s\n", test_string);
        printf("Numbers: %s\n", numbers);
        free(numbers);
    } else {
        printf("Error: Memory allocation failed or invalid input\n");
        return 1;
    }

    return 0;
}