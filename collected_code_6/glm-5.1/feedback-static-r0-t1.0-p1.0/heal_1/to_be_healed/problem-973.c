#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void left_rotate_string(char *str, int n) {
    if (str == NULL) {
        return;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return;
    }

    size_t rotations = (size_t)n % len;

    char *buffer = (char *)malloc(rotations);
    if (buffer == NULL) {
        return;
    }

    memcpy(buffer, str, rotations);
    memmove(str, str + rotations, len - rotations);
    memcpy(str + len - rotations, buffer, rotations);

    free(buffer);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <rotations>\n", argv[0]);
        return 1;
    }

    char *input = (char *)malloc(strlen(argv[1]) + 1);
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(input, argv[1]);

    long rotations = strtol(argv[2], NULL, 10);
    if (rotations < 0) {
        rotations = 0;
    }

    left_rotate_string(input, (int)rotations);
    printf("%s\n", input);

    free(input);
    return 0;
}