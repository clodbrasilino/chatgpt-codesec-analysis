#include <stdio.h>
#include <stdlib.h>

int get_ascii_value(char c) {
    return (int)c;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <character>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0') {
        fprintf(stderr, "Error: No character provided.\n");
        return EXIT_FAILURE;
    }

    int ascii = get_ascii_value(argv[1][0]);
    printf("%d\n", ascii);

    return EXIT_SUCCESS;
}