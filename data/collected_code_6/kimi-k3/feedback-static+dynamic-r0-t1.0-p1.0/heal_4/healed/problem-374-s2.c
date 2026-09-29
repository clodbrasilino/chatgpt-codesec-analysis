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
    ssize_t read_len;
    size_t len;
    char *buffer;

    printf("Enter a string: ");
    
    read_len = getline(&input, &input_size, stdin);
    if (read_len == -1) {
        fprintf(stderr, "Error reading input.\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (read_len > 0 && input[read_len - 1] == '\n') {
        input[read_len - 1] = '\0';
        read_len--;
    }

    len = (size_t)read_len;
    
    if (len == 0) {
        printf("Empty string.\n");
        free(input);
        return EXIT_SUCCESS;
    }

    if (len > 254) {
        fprintf(stderr, "Input too long.\n");
        free(input);
        return EXIT_FAILURE;
    }

    buffer = malloc(len + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (len + 1 <= input_size) {
        memcpy(buffer, input, len + 1);
    } else {
        fprintf(stderr, "Buffer size mismatch.\n");
        free(buffer);
        free(input);
        return EXIT_FAILURE;
    }

    permute(buffer, 0, len - 1);

    free(buffer);
    free(input);
    return EXIT_SUCCESS;
}