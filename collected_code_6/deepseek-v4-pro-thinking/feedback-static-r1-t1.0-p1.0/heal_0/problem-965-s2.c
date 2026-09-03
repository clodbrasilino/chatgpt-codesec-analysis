#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    char *output = malloc(len * 2 + 1);
    if (output == NULL) {
        return NULL;
    }

    size_t j = 0;

    for (size_t i = 0; i < len; i++) {
        unsigned char c = input[i];

        if (isupper(c)) {
            int prev = i > 0 ? (unsigned char)input[i - 1] : 0;
            int next = i + 1 < len ? (unsigned char)input[i + 1] : 0;

            if (i > 0 && (islower(prev) || isdigit(prev))) {
                output[j++] = '_';
            } else if (i > 0 && isupper(prev) && next != 0 && islower(next)) {
                output[j++] = '_';
            }

            output[j++] = (char)tolower(c);
        } else {
            output[j++] = input[i];
        }
    }

    output[j] = '\0';
    return output;
}

int main(void) {
    const char *camel = "camelCaseString";
    char *snake = camel_to_snake(camel);

    if (snake == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", snake);
    free(snake);

    return EXIT_SUCCESS;
}