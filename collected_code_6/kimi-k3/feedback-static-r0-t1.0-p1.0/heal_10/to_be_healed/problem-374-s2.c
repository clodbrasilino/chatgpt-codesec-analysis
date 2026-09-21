#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static void swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

static void permute(char *str, size_t left, size_t right)
{
    if (left == right) {
        printf("%s\n", str);
        return;
    }

    for (size_t i = left; i <= right; i++) {
        swap(&str[left], &str[i]);
        permute(str, left + 1, right);
        swap(&str[left], &str[i]);
    }
}

int main(void)
{
    char *input = NULL;
    size_t input_size = 0;
    ssize_t len;

    printf("Enter a string: ");

    len = getline(&input, &input_size, stdin);
    if (len == -1) {
        fprintf(stderr, "Error reading input.\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        printf("Empty string.\n");
        free(input);
        return EXIT_SUCCESS;
    }

    if ((size_t)len >= SIZE_MAX) {
        fprintf(stderr, "Input too large.\n");
        free(input);
        return EXIT_FAILURE;
    }

    size_t buffer_size = (size_t)len + 1;
    char *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(input);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(input) >= buffer_size) {
        fprintf(stderr, "Buffer size insufficient.\n");
        free(buffer);
        free(input);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(buffer, input);

    permute(buffer, 0, (size_t)len - 1);

    free(buffer);
    free(input);
    return EXIT_SUCCESS;
}