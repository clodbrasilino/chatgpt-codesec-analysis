#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT 1024

typedef struct {
    char *data;
    size_t top;
    size_t capacity;
} Stack;

static bool stack_init(Stack *s, size_t capacity)
{
    if (s == NULL || capacity == 0) {
        return false;
    }
    s->data = malloc(capacity);
    if (s->data == NULL) {
        return false;
    }
    s->top = 0;
    s->capacity = capacity;
    return true;
}

static void stack_destroy(Stack *s)
{
    if (s != NULL) {
        free(s->data);
        s->data = NULL;
        s->top = 0;
        s->capacity = 0;
    }
}

static bool stack_push(Stack *s, char c)
{
    if (s == NULL || s->data == NULL || s->top >= s->capacity) {
        return false;
    }
    s->data[s->top] = c;
    s->top++;
    return true;
}

static bool stack_pop(Stack *s, char *out)
{
    if (s == NULL || s->data == NULL || out == NULL || s->top == 0) {
        return false;
    }
    s->top--;
    *out = s->data[s->top];
    return true;
}

static bool stack_is_empty(const Stack *s)
{
    return (s == NULL) || (s->top == 0);
}

static bool is_opening(char c)
{
    return (c == '(') || (c == '[') || (c == '{');
}

static bool is_closing(char c)
{
    return (c == ')') || (c == ']') || (c == '}');
}

static char matching_open(char c)
{
    switch (c) {
    case ')':
        return '(';
    case ']':
        return '[';
    case '}':
        return '{';
    default:
        return '\0';
    }
}

static bool is_balanced(const char *expr, size_t max_len, bool *result)
{
    Stack s;
    size_t len;
    size_t i;
    char popped;

    if (expr == NULL || result == NULL) {
        return false;
    }

    len = strnlen(expr, max_len);
    if (len == 0) {
        *result = true;
        return true;
    }

    if (!stack_init(&s, len)) {
        return false;
    }

    *result = true;
    for (i = 0; i < len; i++) {
        char c = expr[i];
        if (is_opening(c)) {
            if (!stack_push(&s, c)) {
                stack_destroy(&s);
                return false;
            }
        } else if (is_closing(c)) {
            if (!stack_pop(&s, &popped) || popped != matching_open(c)) {
                *result = false;
                break;
            }
        }
    }

    if (*result && !stack_is_empty(&s)) {
        *result = false;
    }

    stack_destroy(&s);
    return true;
}

static char *read_line(FILE *stream, size_t max_len)
{
    char *buffer;
    size_t used;
    int ch;

    if (stream == NULL || max_len == 0) {
        return NULL;
    }

    buffer = malloc(max_len);
    if (buffer == NULL) {
        return NULL;
    }

    used = 0;
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    while (used < max_len - 1) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
        if (ch == EOF || ch == '\n') {
            break;
        }
        buffer[used] = (char)ch;
        used++;
    }

    /* Possible weaknesses found:
     *  Uninitialized variable: ch [uninitvar]
     *  Uninitialized variable: ch
     */
    if (used == 0 && ch == EOF) {
        free(buffer);
        return NULL;
    }

    buffer[used] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    bool balanced;

    printf("Enter an expression: ");
    fflush(stdout);

    input = read_line(stdin, MAX_INPUT);
    if (input == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (!is_balanced(input, MAX_INPUT, &balanced)) {
        fprintf(stderr, "Error processing expression\n");
        free(input);
        return EXIT_FAILURE;
    }

    if (balanced) {
        printf("The expression is balanced\n");
    } else {
        printf("The expression is not balanced\n");
    }

    free(input);
    return EXIT_SUCCESS;
}