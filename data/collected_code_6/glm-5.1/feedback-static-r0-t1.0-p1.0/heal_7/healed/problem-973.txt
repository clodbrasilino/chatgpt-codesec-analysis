#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void left_rotate_string(char *str, size_t n) {
    if (str == NULL) {
        return;
    }

    size_t len = strnlen(str, SIZE_MAX);
    if (len == 0) {
        return;
    }

    size_t rotations = n % len;

    char *buffer = (char *)malloc(rotations);
    if (buffer == NULL) {
        return;
    }

    memcpy(buffer, str, rotations);
    memmove(str, str + rotations, len - rotations);
    memcpy(str + len - rotations, buffer, rotations);

    str[len] = '\0';
    free(buffer);
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <rotations>\n", argv[0]);
        return 1;
    }

    size_t input_len = strnlen(argv[1], SIZE_MAX);
    char *input = (char *)malloc(input_len + 1);
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    memcpy(input, argv[1], input_len + 1);

    long rotations = strtol(argv[2], NULL, 10);
    if (rotations < 0) {
        rotations = 0;
    }

    left_rotate_string(input, (size_t)rotations);
    printf("%s\n", input);

    free(input);
    return 0;
}