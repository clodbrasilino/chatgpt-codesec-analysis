#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char *replace_characters(const char *input, char old_char, char new_char)
{
    if (input == NULL) {
        errno = EINVAL;
        return NULL;
    }

    size_t length = 0;
    while (input[length] != '\0') {
        length++;
        if (length == SIZE_MAX) {
            errno = EOVERFLOW;
            return NULL;
        }
    }

    if (length == SIZE_MAX) {
        errno = EOVERFLOW;
        return NULL;
    }

    char *result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; i++) {
        result[i] = (input[i] == old_char) ? new_char : input[i];
    }
    result[length] = '\0';

    return result;
}

int main(void)
{
    const char *original = "hello world";
    char old_char = 'o';
    char new_char = '0';

    char *modified = replace_characters(original, old_char, new_char);
    
    if (modified == NULL) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", original);
    printf("Modified: %s\n", modified);

    free(modified);
    modified = NULL;

    return EXIT_SUCCESS;
}