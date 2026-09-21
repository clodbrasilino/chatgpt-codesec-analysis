#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char add_all_characters(const char *str, size_t max_len)
{
    unsigned int sum = 0;
    size_t i;
    size_t len;

    if (str == NULL || max_len == 0) {
        return '\0';
    }

    len = strnlen(str, max_len);
    for (i = 0; i < len; i++) {
        sum = (sum + (unsigned char)str[i]) % 256;
    }

    return (char)sum;
}

int main(void)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read_len;
    char result;

    printf("Enter a string: ");
    read_len = getline(&buffer, &buffer_size, stdin);
    if (read_len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (read_len > 0 && buffer[read_len - 1] == '\n') {
        buffer[read_len - 1] = '\0';
        read_len--;
    }

    result = add_all_characters(buffer, (size_t)read_len);
    printf("Resulting character: %c (ASCII: %d)\n", 
           (result >= 32 && result <= 126) ? result : '.', 
           (unsigned char)result);

    free(buffer);
    return EXIT_SUCCESS;
}