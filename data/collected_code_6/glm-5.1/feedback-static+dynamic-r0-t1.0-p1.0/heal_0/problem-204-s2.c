#include <stdio.h>
#include <stdlib.h>

size_t count_char(const char *str, char c) {
    if (str == NULL) {
        return 0;
    }

    size_t count = 0;
    size_t i = 0;
    while (str[i] != '\0') {
        if (str[i] == c) {
            count++;
        }
        i++;
    }
    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <char>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_str = argv[1];
    char input_char = argv[2][0];

    size_t result = count_char(input_str, input_char);
    printf("%zu\n", result);

    return EXIT_SUCCESS;
}