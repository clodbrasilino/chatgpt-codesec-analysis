#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    char *buffer = malloc((size_t)len + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(input);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(buffer, input, (size_t)len + 1);

    permute(buffer, 0, (size_t)len - 1);

    free(buffer);
    free(input);
    return EXIT_SUCCESS;
}