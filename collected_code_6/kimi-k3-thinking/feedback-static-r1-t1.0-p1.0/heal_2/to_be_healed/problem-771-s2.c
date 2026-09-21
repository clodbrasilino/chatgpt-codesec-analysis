#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EXPRESSION_LENGTH 4096

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
    s->data = (char *)malloc(capacity * sizeof(char));
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

static bool stack_pop(Stack *s, char *c)
{
    if (s == NULL || s->data == NULL || c == NULL || s->top == 0) {
        return false;
    }
    s->top--;
    *c = s->data[s->top];
    return true;
}

static bool stack_is_empty(const Stack *s)
{
    return s == NULL || s->top == 0;
}

static bool is_opening(char c)
{
    return c == '(' || c == '[' || c == '{';
}

static bool is_closing(char c)
{
    return c == ')' || c == ']' || c == '}';
}

/* Possible weaknesses found:
 * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
 */
static bool is_matching(char open, char close)
{
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

static size_t bounded_length(const char *s, size_t max_len)
{
    size_t len = 0;
    if (s == NULL) {
        return 0;
    }
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

bool is_balanced(const char *expression)
{
    if (expression == NULL) {
        return false;
    }

    size_t length = bounded_length(expression, MAX_EXPRESSION_LENGTH + 1);
    if (length > MAX_EXPRESSION_LENGTH) {
        return false;
    }

    size_t capacity = (length > 0) ? length : 1;
    Stack stack;
    bool balanced = true;

    if (!stack_init(&stack, capacity)) {
        return false;
    }

    for (size_t i = 0; i < length; i++) {
        char c = expression[i];
        if (is_opening(c)) {
            if (!stack_push(&stack, c)) {
                balanced = false;
                break;
            }
        } else if (is_closing(c)) {
            char top_char;
            if (!stack_pop(&stack, &top_char) || !is_matching(top_char, c)) {
                balanced = false;
                break;
            }
        }
    }

    if (balanced && !stack_is_empty(&stack)) {
        balanced = false;
    }

    stack_destroy(&stack);
    return balanced;
}

int main(void)
{
    const char *tests[] = {
        "(a + b) * [c - d]",
        "{[(a+b) * (c-d)]}",
        "{[(])}",
        "(((",
        "a + b",
        "])(",
        ""
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0; i < num_tests; i++) {
        printf("Expression: \"%s\" -> %s\n",
               tests[i],
               is_balanced(tests[i]) ? "Balanced" : "Not Balanced");
    }

    return EXIT_SUCCESS;
}