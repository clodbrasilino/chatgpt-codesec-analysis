#include <stdio.h>
#include <stdlib.h>

void replace_spaces(char *str, char c) {
    if (str == NULL) {
        return;
    }
    size_t i = 0;
    while (str[i] != '\0') {
        if (str[i] == ' ') {
            str[i] = c;
        }
        i++;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <char>\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (argv[2][1] != '\0') {
        fprintf(stderr, "Error: Second argument must be a single character.\n");
        return EXIT_FAILURE;
    }
    replace_spaces(argv[1], argv[2][0]);
    printf("%s\n", argv[1]);
    return EXIT_SUCCESS;
}