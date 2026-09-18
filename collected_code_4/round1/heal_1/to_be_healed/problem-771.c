#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_SIZE 100

typedef struct Stack{
    char arr[MAX_SIZE];
    int top;
} Stack;

int isFull(Stack* stack){
    return stack -> top == MAX_SIZE - 1;
}

int isEmpty(Stack* stack){
    return stack -> top == -1;
}

void push(Stack* stack, char element){
    if(!isFull(stack)){
        stack -> arr[++stack -> top] = element; 
    }
}

char pop(Stack* stack){
    if(!isEmpty(stack)){
        return stack -> arr[stack -> top--]; 
    }
    return '0';
}

char peek(Stack* stack){
    return stack -> arr[stack -> top];
}

int isMatchingPair(char character1, char character2){
    if(character1 == '(' && character2 == ')')
        return 1;
    else if(character1 == '{' && character2 == '}')
        return 1;
    else if(character1 == '[' && character2 == ']')
        return 1;
    else
        return 0;
}

int areParenthesisBalanced(char* exp){
    int i = 0;
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'stack' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    stack -> top = -1;
    
    while(exp[i]){
        if(exp[i] == '{' || exp[i] == '(' || exp[i] == '['){
            push(stack, exp[i]);
        }
        if(exp[i] == '}' || exp[i] == ')' || exp[i] == ']'){
            if(isEmpty(stack)){
                /* Possible weaknesses found:
                 *  leak of 'stack' [CWE-401] [-Wanalyzer-malloc-leak]
                 */
                return 0;
            } else if(!isMatchingPair(pop(stack), exp[i])){
                return 0;
            }
        }
        i++;
    }
    if(isEmpty(stack)){
        free(stack);
        return 1;
    } else {
        free(stack);
        return 0;
    }
}

int main(){
    char exp[MAX_SIZE];
    printf("Enter an expression :  ");
    fgets(exp, MAX_SIZE, stdin);

    if (areParenthesisBalanced(exp))
        printf("Balanced \n");
    else
        printf("Not Balanced \n");

    return 0;
} 