#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void left_rotate_string(char *str, size_t n) {
    if (str == NULL) {
        return;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return;
    }

    size_t rotations = n % len;

    char *buffer = (char *)malloc(rotations);
    if (buffer == NULL) {
        return;
    }

    errno_t err;
    
    err = memcpy_s(buffer, rotations, str, rotations);
    if (err != 0) {
        free(buffer);
        return;
    }

    memmove_s(str, len, str + rotations, len - rotations);

    err = memcpy_s(str + len - rotations, rotations, buffer, rotations);
    if (err != 0) {
        free(buffer);
        return;
    }

    free(buffer);
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <rotations>\n", argv[0]);
        return 1;
    }

    size_t input_len = strlen(argv[1]);
    char *input = (char *)malloc(input_len + 1);
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    errno_t err = memcpy_s(input, input_len + 1, argv[1], input_len + 1);
    if (err != 0) {
        free(input);
        fprintf(stderr, "Copy failed\n");
        return 1;
    }

    long rotations = strtol(argv[2], NULL, 10);
    if (rotations < 0) {
        rotations = 0;
    }

    left_rotate_string(input, (size_t)rotations);
    printf("%s\n", input);

    free(input);
    return 0;
}