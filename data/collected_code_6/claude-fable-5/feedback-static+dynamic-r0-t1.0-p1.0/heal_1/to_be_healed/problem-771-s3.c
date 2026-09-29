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

static Stack *stack_create(size_t capacity)
{
    Stack *s;

    if (capacity == 0) {
        return NULL;
    }

    s = malloc(sizeof(Stack));
    if (s == NULL) {
        return NULL;
    }

    s->data = malloc(capacity);
    if (s->data == NULL) {
        free(s);
        return NULL;
    }

    s->top = 0;
    s->capacity = capacity;
    return s;
}

static void stack_destroy(Stack *s)
{
    if (s != NULL) {
        free(s->data);
        free(s);
    }
}

static bool stack_push(Stack *s, char c)
{
    if (s == NULL || s->top >= s->capacity) {
        return false;
    }
    s->data[s->top] = c;
    s->top++;
    return true;
}

static bool stack_pop(Stack *s, char *out)
{
    if (s == NULL || out == NULL || s->top == 0) {
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

/* Possible weaknesses found:
 * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
 */
static bool is_matching_pair(char open, char close)
{
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

static bool is_balanced(const char *expr)
{
    Stack *s;
    size_t len;
    size_t i;
    char popped;
    bool result;

    if (expr == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(expr);
    if (len == 0) {
        return true;
    }

    s = stack_create(len);
    if (s == NULL) {
        return false;
    }

    result = true;
    for (i = 0; i < len; i++) {
        char c = expr[i];
        if (c == '(' || c == '[' || c == '{') {
            if (!stack_push(s, c)) {
                result = false;
                break;
            }
        } else if (c == ')' || c == ']' || c == '}') {
            if (!stack_pop(s, &popped) || !is_matching_pair(popped, c)) {
                result = false;
                break;
            }
        }
    }

    if (result && !stack_is_empty(s)) {
        result = false;
    }

    stack_destroy(s);
    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT];
    size_t len;

    printf("Enter an expression: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    if (is_balanced(input)) {
        printf("The expression is balanced\n");
    } else {
        printf("The expression is not balanced\n");
    }

    return EXIT_SUCCESS;
}