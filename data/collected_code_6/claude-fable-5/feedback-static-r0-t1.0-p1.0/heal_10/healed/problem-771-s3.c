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
        s->data = NULL;
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

static bool is_matching_pair(char opening_char, char closing_char)
{
    return (opening_char == '(' && closing_char == ')') ||
           (opening_char == '[' && closing_char == ']') ||
           (opening_char == '{' && closing_char == '}');
}

static bool is_valid_char(int c)
{
    return c >= 32 && c <= 126;
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

static bool discard_remaining_input(size_t limit)
{
    size_t count;

    count = 0;
    while (count < limit) {
        int c = getchar();
        if (c == EOF || c == '\n') {
            return true;
        }
        if (is_valid_char(c)) {
            return false;
        }
        count++;
    }
    return false;
}

static char *read_line(size_t max_len)
{
    char *raw;
    char *buffer;
    size_t raw_len;
    size_t len;
    size_t i;
    bool truncated;

    if (max_len < 2 || max_len > MAX_INPUT) {
        return NULL;
    }

    raw = malloc(max_len);
    if (raw == NULL) {
        return NULL;
    }

    if (fgets(raw, (int)max_len, stdin) == NULL) {
        free(raw);
        return NULL;
    }

    raw_len = strnlen(raw, max_len);
    truncated = true;

    if (raw_len > 0 && raw[raw_len - 1] == '\n') {
        raw[raw_len - 1] = '\0';
        raw_len--;
        truncated = false;
    } else if (raw_len < max_len - 1) {
        truncated = false;
    }

    if (truncated) {
        if (!discard_remaining_input(MAX_INPUT)) {
            free(raw);
            return NULL;
        }
    }

    buffer = malloc(max_len);
    if (buffer == NULL) {
        free(raw);
        return NULL;
    }

    len = 0;
    for (i = 0; i < raw_len && len < max_len - 1; i++) {
        if (is_valid_char((unsigned char)raw[i])) {
            buffer[len] = raw[i];
            len++;
        }
    }
    buffer[len] = '\0';

    free(raw);
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

    input = read_line(MAX_INPUT);
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