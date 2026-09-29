#include <stdio.h>
#include <stdlib.h>

typedef struct Stack
{
    char* arr;
    int top;
    int capacity;
} Stack;

Stack* createStack(unsigned int capacity)
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->arr = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

int isFull(Stack* stack)
{
    return stack->top == stack->capacity - 1;
}

int isEmpty(Stack* stack)
{
    return stack->top == -1;
}

void push(Stack* stack, char item)
{
    if (isFull(stack))
        return;
    stack->arr[++stack->top] = item;  
}

char pop(Stack* stack)
{
    if (isEmpty(stack))
        return 0;
    return stack->arr[stack->top--];
}

char peek(Stack* stack)
{
    if (isEmpty(stack))
        return 0;
    return stack->arr[stack->top];
}

int isBalanced(char* expr)
{
    Stack* stack = createStack(strlen(expr));
    for (int i = 0; i<strlen(expr); i++)
    {
        if (expr[i] == '{' || expr[i] == '(' || expr[i] == '[')
            push(stack, expr[i]);
        else if (expr[i] == '}' || expr[i] == ')' || expr[i] == ']')
        {
            if (isEmpty(stack))
                return 0;
            else if ((expr[i] == '}' && peek(stack) != '{') || 
                     (expr[i] == ')' && peek(stack) != '(') || 
                     (expr[i] == ']' && peek(stack) != '['))
                return 0;
            pop(stack);
        }
    }
    if (isEmpty(stack))
    {
        free(stack->arr);
        free(stack);
        return 1;
    }
    else
    {
        free(stack->arr);
        free(stack);
        return 0;
    }
}

int main()
{
    char expr[100];
    printf("Enter an expression: ");
    scanf("%s", expr);
    if (isBalanced(expr))
        printf("Balanced \n");
    else
        printf("Not Balanced \n");
    return 0;
}