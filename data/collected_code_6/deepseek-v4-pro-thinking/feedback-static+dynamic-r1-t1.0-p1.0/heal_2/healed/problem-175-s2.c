#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool isOpening(char c) {
    return c == '(' || c == '[' || c == '{';
}

static bool isClosing(char c) {
    return c == ')' || c == ']' || c == '}';
}

static bool matches(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

bool isValid(const char *s) {
    if (s == NULL) {
        return false;
    }

    size_t len = strlen(s);
    if (len == 0) {
        return true;
    }

    if (len % 2u != 0u) {
        return false;
    }

    char *stack = malloc(len * sizeof(char));
    if (stack == NULL) {
        return false;
    }

    size_t top = 0;
    bool valid = true;

    for (size_t i = 0; i < len && valid; ++i) {
        char c = s[i];

        if (isOpening(c)) {
            stack[top++] = c;
        } else if (isClosing(c)) {
            if (top == 0 || !matches(stack[top - 1], c)) {
                valid = false;
            } else {
                --top;
            }
        } else {
            valid = false;
        }
    }

    if (valid && top != 0) {
        valid = false;
    }

    free(stack);
    return valid;
}

static char *read_line(void) {
    size_t capacity = 128;
    char *buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    size_t length = 0;
    int ch;

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length + 1 >= capacity) {
            capacity *= 2;
            char *new_buffer = realloc(buffer, capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
        }
        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        char *empty = malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    buffer[length] = '\0';

    char *shrunk = realloc(buffer, length + 1);
    return shrunk != NULL ? shrunk : buffer;
}

int main(void) {
    char *input = read_line();
    if (input == NULL) {
        return 1;
    }

    printf("%s\n", isValid(input) ? "valid" : "invalid");
    free(input);

    return 0;
}