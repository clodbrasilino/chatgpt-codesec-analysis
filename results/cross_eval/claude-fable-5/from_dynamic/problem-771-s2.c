#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EXPR_LEN 1024

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
    return (s == NULL || s->top == 0);
}

static bool is_matching_pair(char open, char close)
{
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

static bool is_balanced(const char *expr, bool *result)
{
    Stack s;
    size_t len;
    size_t i;
    char c;
    char popped;

    if (expr == NULL || result == NULL) {
        return false;
    }

    len = strlen(expr);
    if (!stack_init(&s, len + 1)) {
        return false;
    }

    *result = true;

    for (i = 0; i < len; i++) {
        c = expr[i];
        if (c == '(' || c == '[' || c == '{') {
            if (!stack_push(&s, c)) {
                stack_destroy(&s);
                return false;
            }
        } else if (c == ')' || c == ']' || c == '}') {
            if (!stack_pop(&s, &popped) || !is_matching_pair(popped, c)) {
                *result = false;
                stack_destroy(&s);
                return true;
            }
        }
    }

    if (!stack_is_empty(&s)) {
        *result = false;
    }

    stack_destroy(&s);
    return true;
}

int main(void)
{
    char expr[MAX_EXPR_LEN];
    size_t len;
    bool balanced;

    printf("Enter an expression: ");
    if (fgets(expr, sizeof(expr), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strlen(expr);
    if (len > 0 && expr[len - 1] == '\n') {
        expr[len - 1] = '\0';
    }

    if (!is_balanced(expr, &balanced)) {
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