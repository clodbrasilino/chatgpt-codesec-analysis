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
    if (length == MAX_INPUT_LENGTH && input[MAX_INPUT_LENGTH - 1] != '\0') {
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

int main(int argc, char *argv[])
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_LENGTH];
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    int i;

    memset(buffer, 0, sizeof(buffer));

    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            if (argv[i] == NULL) {
                fputs("False\n", stdout);
                continue;
            }
            if (strnlen(argv[i], MAX_INPUT_LENGTH) >= MAX_INPUT_LENGTH) {
                fputs("False\n", stdout);
                continue;
            }
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(buffer, argv[i], sizeof(buffer) - 1);
            buffer[sizeof(buffer) - 1] = '\0';
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