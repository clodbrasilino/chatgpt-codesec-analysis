#include<stdio.h>
#include<string.h>

typedef struct {
    const char* str;
    int length;
} Tuple;

Tuple convertToTuple(const char* str){
    Tuple tuple;
    tuple.str = str;
    tuple.length = str ? strnlen(str, 100) : 0; 
    return tuple;
}

int main(){
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char string[102];

    printf("Enter a string: ");
    fgets(string, 102, stdin);
    string[strcspn(string, "\n")] = 0;

    /* Possible weaknesses found:
     *  implicit declaration of function 'additionalBufferCheck' [-Wimplicit-function-declaration]
     */
    if(additionalBufferCheck(string)){
        Tuple tuple = convertToTuple(string);

        printf("Converted tuple -\n");
        printf("String: %s\n", tuple.str);
        printf("Length: %d\n", tuple.length);
    }
    return 0;
}

int additionalBufferCheck(const char* str){
    if(strnlen(str, 102) >= 101){
        printf("Input too long.\n");
        return 0;
    }
    return 1;
}