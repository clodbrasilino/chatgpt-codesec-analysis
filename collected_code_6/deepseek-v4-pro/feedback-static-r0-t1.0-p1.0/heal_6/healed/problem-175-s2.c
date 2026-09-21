#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    char *data;
    size_t top;
    size_t capacity;
} Stack;

static bool stack_init(Stack *stack, size_t capacity) {
    if (capacity == 0) {
        capacity = 1;
    }
    stack->data = (char *)malloc(capacity * sizeof(char));
    if (stack->data == NULL) {
        return false;
    }
    stack->top = 0;
    stack->capacity = capacity;
    return true;
}

static void stack_destroy(Stack *stack) {
    if (stack != NULL) {
        free(stack->data);
        stack->data = NULL;
        stack->top = 0;
        stack->capacity = 0;
    }
}

static bool stack_push(Stack *stack, char value) {
    if (stack->top >= stack->capacity) {
        size_t new_capacity;
        if (stack->capacity > 0 && stack->capacity <= SIZE_MAX / 2) {
            new_capacity = stack->capacity * 2;
        } else if (stack->capacity == 0) {
            new_capacity = 1;
        } else {
            return false;
        }
        char *new_data = (char *)realloc(stack->data, new_capacity * sizeof(char));
        if (new_data == NULL) {
            return false;
        }
        stack->data = new_data;
        stack->capacity = new_capacity;
    }
    stack->data[stack->top++] = value;
    return true;
}

static bool stack_pop(Stack *stack, char *value) {
    if (stack->top == 0) {
        return false;
    }
    *value = stack->data[--stack->top];
    return true;
}

static bool is_matching_pair(char open, char close) {
    switch (open) {
        case '(': return close == ')';
        case '[': return close == ']';
        case '{': return close == '}';
        default:  return false;
    }
}

static bool is_valid_char(char ch) {
    return ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}';
}

static size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

bool is_valid_parentheses(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    size_t len = safe_strlen(str, SIZE_MAX);
    if (len == 0) {
        return true;
    }
    
    if (len > SIZE_MAX / 2) {
        return false;
    }
    
    for (size_t i = 0; i < len; i++) {
        if (!is_valid_char(str[i])) {
            return false;
        }
    }
    
    Stack stack;
    if (!stack_init(&stack, len)) {
        return false;
    }
    
    for (size_t i = 0; i < len; i++) {
        char ch = str[i];
        if (ch == '(' || ch == '[' || ch == '{') {
            if (!stack_push(&stack, ch)) {
                stack_destroy(&stack);
                return false;
            }
        } else {
            char open;
            if (!stack_pop(&stack, &open) || !is_matching_pair(open, ch)) {
                stack_destroy(&stack);
                return false;
            }
        }
    }
    
    bool result = (stack.top == 0);
    stack_destroy(&stack);
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "()",
        "()[]{}",
        "(]",
        "([)]",
        "{[]}",
        "(((",
        ")))",
        "",
        "((()))",
        "{[()]}",
        "abc",
        NULL
    };
    
    for (int i = 0; test_cases[i] != NULL; i++) {
        printf("\"%s\": %s\n", test_cases[i], 
               is_valid_parentheses(test_cases[i]) ? "valid" : "invalid");
    }
    
    return 0;
}