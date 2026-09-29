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
    char buf[MAX_INPUT_LENGTH + 2];
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        return NULL;
    }

    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[--len] = '\0';
    } else {
        if (len == sizeof(buf) - 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            return NULL;
        }
    }

    if (len >= MAX_INPUT_LENGTH) {
        return NULL;
    }

    char *result = malloc(len + 1);
    if (result) {
        memcpy(result, buf, len + 1);
    }
    return result;
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