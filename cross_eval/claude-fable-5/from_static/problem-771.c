#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_INPUT 1024
#define DISCARD_GUARD_LIMIT 65536

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

    if (expr == NULL || result == NULL || max_len == 0) {
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

static void discard_remaining_input(void)
{
    int c;
    size_t guard = 0;

    do {
        c = getchar();
        guard++;
    } while (c != '\n' && c != EOF && guard < DISCARD_GUARD_LIMIT);
}

static bool read_line(char *buffer, size_t size)
{
    size_t len;

    if (buffer == NULL || size < 2 || size > MAX_INPUT || size > (size_t)INT_MAX) {
        return false;
    }

    memset(buffer, 0, size);

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return false;
    }

    buffer[size - 1] = '\0';

    len = strnlen(buffer, size);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == size - 1) {
        discard_remaining_input();
    }

    return true;
}

int main(void)
{
    char input[MAX_INPUT];
    bool balanced;

    memset(input, 0, sizeof(input));

    printf("Enter an expression: ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (!read_line(input, sizeof(input))) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (!is_balanced(input, sizeof(input), &balanced)) {
        fprintf(stderr, "Error processing expression\n");
        return EXIT_FAILURE;
    }

    if (balanced) {
        printf("The expression is balanced\n");
    } else {
        printf("The expression is not balanced\n");
    }

    return EXIT_SUCCESS;
}