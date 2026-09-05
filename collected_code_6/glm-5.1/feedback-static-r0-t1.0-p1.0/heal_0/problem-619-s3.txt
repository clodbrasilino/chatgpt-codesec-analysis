#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *move_numbers(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t write_index = 0;
    for (size_t i = 0; i < len; i++) {
        if (isdigit((unsigned char)input[i])) {
            result[write_index++] = input[i];
        }
    }

    result[write_index] = '\0';
    return result;
}

int main(void) {
    const char *str = "A1B2C3D4E5";
    char *numbers = move_numbers(str);

    if (numbers != NULL) {
        printf("%s\n", numbers);
        free(numbers);
    }

    return 0;
}