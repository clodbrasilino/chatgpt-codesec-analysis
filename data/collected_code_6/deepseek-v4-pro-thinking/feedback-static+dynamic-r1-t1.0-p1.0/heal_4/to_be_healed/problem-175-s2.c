#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1048576

static bool isOpening(char c) {
    return c == '(' || c == '[' || c == '{';
}

static bool isClosing(char c) {
    return c == ')' || c == ']' || c == '}';
}

/* Possible weaknesses found:
 * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
 */
static bool matches(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

static size_t safe_strnlen(const char *s, size_t maxlen) {
    size_t i = 0;
    while (i < maxlen && s[i] != '\0') {
        ++i;
    }
    return i;
}

bool isValid(const char *s) {
    if (s == NULL) {
        return false;
    }

    size_t len = safe_strnlen(s, MAX_INPUT_LENGTH);
    if (len == MAX_INPUT_LENGTH) {
        return false;
    }

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
    if (capacity > MAX_INPUT_LENGTH) {
        capacity = MAX_INPUT_LENGTH;
    }
    char *buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    size_t length = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length >= MAX_INPUT_LENGTH) {
            free(buffer);
            return NULL;
        }
        while (length + 1 >= capacity) {
            if (capacity == MAX_INPUT_LENGTH) {
                free(buffer);
                return NULL;
            }
            size_t new_capacity = (capacity * 2 < MAX_INPUT_LENGTH) ? capacity * 2 : MAX_INPUT_LENGTH;
            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
            capacity = new_capacity;
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