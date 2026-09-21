#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

typedef struct {
    char *items;
    size_t top;
    size_t capacity;
} Stack;

static bool stack_init(Stack *stack, size_t initial_capacity) {
    stack->items = malloc(initial_capacity * sizeof(char));
    if (stack->items == NULL) {
        return false;
    }
    stack->top = 0;
    stack->capacity = initial_capacity;
    return true;
}

static void stack_destroy(Stack *stack) {
    free(stack->items);
    stack->items = NULL;
    stack->top = 0;
    stack->capacity = 0;
}

static bool stack_push(Stack *stack, char value) {
    if (stack->top == stack->capacity) {
        if (stack->capacity > SIZE_MAX / 2) {
            return false;
        }
        size_t new_capacity = stack->capacity * 2;
        char *new_items = realloc(stack->items, new_capacity * sizeof(char));
        if (new_items == NULL) {
            return false;
        }
        stack->items = new_items;
        stack->capacity = new_capacity;
    }
    stack->items[stack->top++] = value;
    return true;
}

static bool stack_pop(Stack *stack, char *value) {
    if (stack->top == 0) {
        return false;
    }
    *value = stack->items[--stack->top];
    return true;
}

static bool is_opening_bracket(char c) {
    return c == '(' || c == '[' || c == '{';
}

static bool is_closing_bracket(char c) {
    return c == ')' || c == ']' || c == '}';
}

static bool brackets_match(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
           (opening == '[' && closing == ']') ||
           (opening == '{' && closing == '}');
}

bool is_balanced(const char *expression) {
    Stack stack;
    if (!stack_init(&stack, 64)) {
        return false;
    }

    for (const char *p = expression; *p != '\0'; ++p) {
        char c = *p;
        if (is_opening_bracket(c)) {
            if (!stack_push(&stack, c)) {
                stack_destroy(&stack);
                return false;
            }
        } else if (is_closing_bracket(c)) {
            char opening;
            if (!stack_pop(&stack, &opening) || !brackets_match(opening, c)) {
                stack_destroy(&stack);
                return false;
            }
        }
    }

    bool balanced = stack.top == 0;
    stack_destroy(&stack);
    return balanced;
}

static char *read_line(void) {
    size_t size = 128;
    size_t len = 0;
    char *buffer = malloc(size);
    if (buffer == NULL) {
        return NULL;
    }

    while (1) {
        size_t remaining = size - len;
        int n = (remaining > (size_t)INT_MAX) ? INT_MAX : (int)remaining;
        if (n <= 0) {
            free(buffer);
            return NULL;
        }

        if (fgets(buffer + len, n, stdin) == NULL) {
            if (len == 0) {
                free(buffer);
                return NULL;
            }
            buffer[len] = '\0';
            return buffer;
        }

        size_t chunk_len = 0;
        while (chunk_len < (size_t)n && buffer[len + chunk_len] != '\0') {
            chunk_len++;
        }
        len += chunk_len;

        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            return buffer;
        }

        if (size - len <= 1) {
            if (size > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }
            size_t new_size = size * 2;
            char *new_buf = realloc(buffer, new_size);
            if (new_buf == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = new_buf;
            size = new_size;
        }
    }
}

int main(void) {
    char *expression = read_line();
    if (expression == NULL) {
        return 1;
    }

    if (is_balanced(expression)) {
        puts("Balanced");
    } else {
        puts("Not Balanced");
    }

    free(expression);
    return 0;
}