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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buf[MAX_INPUT_LENGTH + 2];
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[--len] = '\0';
    } else {
        if (len == sizeof(buf) - 1) {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF) {}
            return NULL;
        }
    }

    if (len >= MAX_INPUT_LENGTH) {
        return NULL;
    }

    char *result = malloc(len + 1);
    if (result) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
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