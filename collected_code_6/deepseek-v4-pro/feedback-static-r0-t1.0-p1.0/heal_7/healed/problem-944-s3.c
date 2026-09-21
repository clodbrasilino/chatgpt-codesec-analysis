#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

static int read_line(char *buffer, size_t size) {
    if (buffer == NULL || size == 0) {
        return 0;
    }

    size_t pos = 0;
    int c = 0;

    while (pos < size - 1) {
        c = getchar();
        if (c == EOF || c == '\n') {
            break;
        }
        buffer[pos++] = (char)c;
    }
    buffer[pos] = '\0';

    if (c == EOF) {
        if (ferror(stdin)) {
            return -1;
        }
        if (pos == 0) {
            return 0;
        }
        return 1;
    }

    if (c == '\n') {
        return 1;
    }

    while ((c = getchar()) != '\n' && c != EOF) {
    }

    return 1;
}

static void print_numbers_with_positions(const char *str) {
    if (str == NULL) {
        return;
    }

    size_t i = 0;
    int in_number = 0;
    size_t start_pos = 0;

    while (str[i] != '\0') {
        if (isdigit((unsigned char)str[i])) {
            if (!in_number) {
                start_pos = i;
                in_number = 1;
            }
        } else {
            if (in_number) {
                printf("Number: ");
                for (size_t j = start_pos; j < i; j++) {
                    putchar(str[j]);
                }
                printf(", Position: %zu\n", start_pos);
                in_number = 0;
            }
        }
        i++;
    }

    if (in_number) {
        printf("Number: ");
        for (size_t j = start_pos; j < i; j++) {
            putchar(str[j]);
        }
        printf(", Position: %zu\n", start_pos);
    }
}

int main(void) {
    size_t buf_size = 1024;
    int result;

    char *input = (char*)malloc(buf_size);
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter a string: ");

    result = read_line(input, buf_size);
    if (result < 0) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return 1;
    }
    if (result == 0) {
        free(input);
        return 0;
    }

    print_numbers_with_positions(input);

    free(input);
    return 0;
}