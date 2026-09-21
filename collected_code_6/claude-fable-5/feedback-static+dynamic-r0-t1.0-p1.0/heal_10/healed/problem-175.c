#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 4096

bool is_valid_parentheses(const char *input)
{
    size_t length;
    char *stack;
    size_t top = 0;
    size_t i;
    bool result = true;

    if (input == NULL) {
        return false;
    }

    length = strnlen(input, MAX_INPUT_LENGTH);
    if (length >= MAX_INPUT_LENGTH) {
        return false;
    }

    if (length == 0) {
        return true;
    }

    stack = (char *)malloc(length);
    if (stack == NULL) {
        return false;
    }

    for (i = 0; i < length; i++) {
        char c = input[i];

        if (c == '(' || c == '[' || c == '{') {
            if (top >= length) {
                result = false;
                break;
            }
            stack[top] = c;
            top++;
        } else if (c == ')' || c == ']' || c == '}') {
            if (top == 0) {
                result = false;
                break;
            }
            top--;
            if ((c == ')' && stack[top] != '(') ||
                (c == ']' && stack[top] != '[') ||
                (c == '}' && stack[top] != '{')) {
                result = false;
                break;
            }
        } else {
            result = false;
            break;
        }
    }

    if (result && top != 0) {
        result = false;
    }

    free(stack);
    return result;
}

static void process_line(char *buffer, size_t buffer_size)
{
    size_t len;

    if (buffer == NULL || buffer_size == 0) {
        fputs("False\n", stdout);
        fflush(stdout);
        return;
    }

    buffer[buffer_size - 1] = '\0';

    len = strnlen(buffer, buffer_size);

    while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
        buffer[len - 1] = '\0';
        len--;
    }

    if (is_valid_parentheses(buffer)) {
        fputs("True\n", stdout);
    } else {
        fputs("False\n", stdout);
    }

    fflush(stdout);
}

static bool copy_argument(char *dest, size_t dest_size, const char *src)
{
    size_t src_len;

    if (dest == NULL || src == NULL || dest_size == 0) {
        return false;
    }

    src_len = strnlen(src, dest_size);
    if (src_len >= dest_size) {
        return false;
    }

    memmove(dest, src, src_len);
    dest[src_len] = '\0';
    return true;
}

int main(int argc, char *argv[])
{
    char buffer[MAX_INPUT_LENGTH];

    memset(buffer, 0, sizeof(buffer));

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (!copy_argument(buffer, sizeof(buffer), argv[i])) {
                fputs("False\n", stdout);
                fflush(stdout);
                continue;
            }

            process_line(buffer, sizeof(buffer));
            memset(buffer, 0, sizeof(buffer));
        }
        fflush(stdout);
        return EXIT_SUCCESS;
    }

    while (fgets(buffer, (int)sizeof(buffer), stdin) != NULL) {
        process_line(buffer, sizeof(buffer));
        memset(buffer, 0, sizeof(buffer));
    }

    fflush(stdout);

    return EXIT_SUCCESS;
}