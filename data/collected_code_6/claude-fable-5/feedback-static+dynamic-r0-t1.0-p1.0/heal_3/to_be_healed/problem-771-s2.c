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

static bool is_matching_pair(char open_c, char close_c)
{
    return (open_c == '(' && close_c == ')') ||
           (open_c == '[' && close_c == ']') ||
           (open_c == '{' && close_c == '}');
}

static size_t bounded_strlen(const char *str, size_t max_len)
{
    size_t i;

    if (str == NULL) {
        return 0;
    }
    for (i = 0; i < max_len; i++) {
        if (str[i] == '\0') {
            break;
        }
    }
    return i;
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

    len = bounded_strlen(expr, max_len);
    if (!stack_init(&s, len + 1)) {
        return false;
    }

    *result = true;

    for (i = 0; i < len; i++) {
        const char c = expr[i];
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

static char *read_expression(size_t max_len)
{
    char *buffer;
    size_t len;
    int c;

    if (max_len == 0) {
        return NULL;
    }

    buffer = malloc(max_len);
    if (buffer == NULL) {
        return NULL;
    }

    if (fgets(buffer, (int)max_len, stdin) == NULL) {
        free(buffer);
        return NULL;
    }

    buffer[max_len - 1] = '\0';

    len = bounded_strlen(buffer, max_len);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == max_len - 1) {
        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            c = getchar();
        } while (c != '\n' && c != EOF);
    }

    return buffer;
}

int main(void)
{
    char *expr;
    bool balanced;

    printf("Enter an expression: ");
    fflush(stdout);

    expr = read_expression(MAX_EXPR_LEN);
    if (expr == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (!is_balanced(expr, MAX_EXPR_LEN, &balanced)) {
        fprintf(stderr, "Error processing expression\n");
        free(expr);
        return EXIT_FAILURE;
    }

    if (balanced) {
        printf("The expression is balanced\n");
    } else {
        printf("The expression is not balanced\n");
    }

    free(expr);
    return EXIT_SUCCESS;
}