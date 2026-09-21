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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    size_t len;
    char *buffer;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    len = strnlen(input, sizeof(input));
    if (len == 0) {
        printf("Empty string.\n");
        return EXIT_SUCCESS;
    }

    if (len >= sizeof(input)) {
        fprintf(stderr, "Input too long.\n");
        return EXIT_FAILURE;
    }

    buffer = malloc(len + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(buffer, input, len);
    buffer[len] = '\0';

    permute(buffer, 0, len - 1);

    free(buffer);
    return EXIT_SUCCESS;
}