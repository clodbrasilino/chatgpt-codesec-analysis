#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int remove_non_alphanumeric(char *string)
{
    const unsigned char *read;
    char *write;

    if (string == NULL) {
        return -1;
    }

    read = (const unsigned char *)string;
    write = string;

    while (*read != '\0') {
        if ((*read >= '0' && *read <= '9') ||
            (*read >= 'A' && *read <= 'Z') ||
            (*read >= 'a' && *read <= 'z')) {
            *write++ = (char)*read;
        }
        ++read;
    }

    *write = '\0';
    return 0;
}

int main(int argc, const char *const argv[])
{
    char *string;
    size_t length;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    length = strlen(argv[1]);

    if (length == SIZE_MAX) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    string = malloc(length + 1);
    if (string == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(string, argv[1], length + 1);

    if (remove_non_alphanumeric(string) != 0) {
        fprintf(stderr, "Failed to process string\n");
        free(string);
        return EXIT_FAILURE;
    }

    puts(string);
    free(string);

    return EXIT_SUCCESS;
}