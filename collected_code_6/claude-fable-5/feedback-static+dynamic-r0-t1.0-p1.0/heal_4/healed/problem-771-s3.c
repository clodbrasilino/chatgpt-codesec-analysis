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

    if (capacity == 0 || capacity > MAX_INPUT) {
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

static bool is_matching_pair(char opening, char closing)
{
    return (opening == '(' && closing == ')') ||
           (opening == '[' && closing == ']') ||
           (opening == '{' && closing == '}');
}

static bool is_balanced(const char *expr, size_t max_len)
{
    Stack *s;
    size_t len;
    size_t i;
    char popped;
    bool result;

    if (expr == NULL || max_len == 0) {
        return false;
    }

    len = strnlen(expr, max_len);
    if (len >= max_len) {
        return false;
    }
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

static char *read_input_line(size_t max_len)
{
    char *buffer;
    size_t pos;
    int c;

    if (max_len == 0) {
        return NULL;
    }

    buffer = malloc(max_len);
    if (buffer == NULL) {
        return NULL;
    }

    pos = 0;
    while (pos < max_len - 1) {
        c = fgetc(stdin);
        if (c == EOF || c == '\n') {
            break;
        }
        buffer[pos] = (char)c;
        pos++;
    }

    if (pos == 0 && c == EOF) {
        free(buffer);
        return NULL;
    }

    if (pos == max_len - 1 && c != EOF && c != '\n') {
        while ((c = fgetc(stdin)) != EOF && c != '\n') {
            continue;
        }
        free(buffer);
        return NULL;
    }

    buffer[pos] = '\0';
    return buffer;
}

int main(void)
{
    char *input;

    printf("Enter an expression: ");
    if (fflush(stdout) != 0) {
        fprintf(stderr, "Error flushing output\n");
        return EXIT_FAILURE;
    }

    input = read_input_line(MAX_INPUT);
    if (input == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (is_balanced(input, MAX_INPUT)) {
        printf("The expression is balanced\n");
    } else {
        printf("The expression is not balanced\n");
    }

    free(input);
    return EXIT_SUCCESS;
}