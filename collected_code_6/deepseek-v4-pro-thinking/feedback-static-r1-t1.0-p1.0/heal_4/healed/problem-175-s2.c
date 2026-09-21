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

static bool matches(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
           (opening == '[' && closing == ']') ||
           (opening == '{' && closing == '}');
}

static size_t safe_strnlen(const char *s, size_t maxlen) {
    size_t len = 0;
    while (len < maxlen && s[len] != '\0') {
        len++;
    }
    return len;
}

#define MAX_VALID_LENGTH 100000

bool isValid(const char *s) {
    if (s == NULL) {
        return false;
    }

    size_t len = safe_strnlen(s, MAX_VALID_LENGTH + 1);
    if (len > MAX_VALID_LENGTH) {
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

int main(void) {
    size_t max_input = MAX_VALID_LENGTH + 2;
    char *input = malloc(max_input * sizeof(char));
    if (input == NULL) {
        return 1;
    }

    if (fgets(input, max_input, stdin) == NULL) {
        free(input);
        return 1;
    }

    size_t len = safe_strnlen(input, max_input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    printf("%s\n", isValid(input) ? "valid" : "invalid");

    free(input);
    return 0;
}