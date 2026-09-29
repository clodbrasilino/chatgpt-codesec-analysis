#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_odd_characters(char *str) {
    if (str == NULL) {
        return;
    }

    size_t length = strlen(str);
    if (length == 0) {
        return;
    }

    size_t write_index = 0;

    for (size_t read_index = 0; read_index < length; read_index++) {
        if ((read_index % 2) != 0) {
            str[write_index] = str[read_index];
            write_index++;
        }
    }

    str[write_index] = '\0';
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t len = strlen(argv[1]);
    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    strncpy(buffer, argv[1], len + 1);
    buffer[len] = '\0';

    remove_odd_characters(buffer);

    printf("%s\n", buffer);

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}