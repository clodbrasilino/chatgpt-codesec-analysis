#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

#define MAX_EXPR_LEN 4096U

typedef struct {
    char *data;
    size_t top;
    size_t capacity;
} Stack;

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t n = 0U;

    if (s == NULL) {
        return 0U;
    }
    while (n < max_len && s[n] != '\0') {
        n++;
    }
    return n;
}

static int stack_init(Stack *s, size_t capacity)
{
    if (s == NULL || capacity == 0U || capacity > MAX_EXPR_LEN) {
        return -1;
    }
    if (capacity > SIZE_MAX / sizeof(char)) {
        return -1;
    }
    s->data = (char *)malloc(capacity * sizeof(char));
    if (s->data == NULL) {
        s->top = 0U;
        s->capacity = 0U;
        return -1;
    }
    s->top = 0U;
    s->capacity = capacity;
    return 0;
}

static void stack_destroy(Stack *s)
{
    if (s != NULL) {
        free(s->data);
        s->data = NULL;
        s->top = 0U;
        s->capacity = 0U;
    }
}

static int stack_push(Stack *s, char c)
{
    if (s == NULL || s->data == NULL || s->capacity == 0U ||
        s->top >= s->capacity) {
        return -1;
    }
    s->data[s->top] = c;
    s->top++;
    return 0;
}

static int stack_pop(Stack *s, char *c)
{
    if (s == NULL || c == NULL || s->data == NULL || s->top == 0U) {
        return -1;
    }
    s->top--;
    *c = s->data[s->top];
    return 0;
}

static int is_matching_pair(char open_char, char close_char)
{
    return ((open_char == '(' && close_char == ')') ||
            (open_char == '[' && close_char == ']') ||
            (open_char == '{' && close_char == '}'));
}

int is_balanced(const char *expr)
{
    Stack s;
    size_t i;
    size_t len;
    int result;

    s.data = NULL;
    s.top = 0U;
    s.capacity = 0U;

    if (expr == NULL) {
        return -1;
    }

    len = bounded_strlen(expr, MAX_EXPR_LEN + 1U);
    if (len > MAX_EXPR_LEN) {
        return -1;
    }
    if (len == 0U) {
        return 1;
    }

    if (stack_init(&s, len) != 0) {
        return -1;
    }

    result = 1;
    for (i = 0U; i < len; i++) {
        char ch = expr[i];
        if (ch == '(' || ch == '[' || ch == '{') {
            if (stack_push(&s, ch) != 0) {
                result = -1;
                break;
            }
        } else if (ch == ')' || ch == ']' || ch == '}') {
            char top_char = '\0';
            if (stack_pop(&s, &top_char) != 0) {
                result = 0;
                break;
            }
            if (is_matching_pair(top_char, ch) == 0) {
                result = 0;
                break;
            }
        }
    }

    if (result == 1 && s.top != 0U) {
        result = 0;
    }

    stack_destroy(&s);
    return result;
}

int main(void)
{
    const char *tests[] = {
        "(a+b)*(c-d)",
        "{[(a+b)]*(c-d)}",
        "((a+b)",
        "([a+b)]",
        "{[()]}",
        "a+b",
        "}"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0U; i < count; i++) {
        int status = is_balanced(tests[i]);
        if (status == 1) {
            printf("Expression \"%s\" is balanced.\n", tests[i]);
        } else if (status == 0) {
            printf("Expression \"%s\" is not balanced.\n", tests[i]);
        } else {
            fprintf(stderr, "Error: could not evaluate expression.\n");
        }
    }

    return 0;
}