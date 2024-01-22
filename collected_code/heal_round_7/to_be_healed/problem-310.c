#include<stdio.h>
#include<string.h>

#define MAX_SIZE 102

typedef struct {
    const char* str;
    int length;
} Tuple;

Tuple convertToTuple(const char* str){
    Tuple tuple;
    tuple.str = str;
    tuple.length = str ? strnlen(str, MAX_SIZE - 1) : 0; 
    return tuple;
}

int additionalBufferCheck(const char* str){
    if(strnlen(str, MAX_SIZE) >= MAX_SIZE - 1){
        printf("Input too long.\n");
        return 0;
    }
    return 1;
}

int main(){
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char string[MAX_SIZE];

    printf("Enter a string: ");
    fgets(string, MAX_SIZE, stdin);
    string[strcspn(string, "\n")] = '\0';

    if(additionalBufferCheck(string)){
        Tuple tuple = convertToTuple(string);

        printf("Converted tuple -\n");
        printf("String: %s\n", tuple.str);
        printf("Length: %d\n", tuple.length);
    }
    
    return 0;
}