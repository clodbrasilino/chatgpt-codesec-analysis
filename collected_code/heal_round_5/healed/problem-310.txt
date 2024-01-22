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

int additionalBufferCheck(const char* str){
    if(strnlen(str, 102) >= 101){
        printf("Input too long.\n");
        return 0;
    }
    return 1;
}

int main(){
    char string[102];

    printf("Enter a string: ");
    fgets(string, 102, stdin);
    string[strcspn(string, "\n")] = 0;

    if(additionalBufferCheck(string)){
        Tuple tuple = convertToTuple(string);

        printf("Converted tuple -\n");
        printf("String: %s\n", tuple.str);
        printf("Length: %d\n", tuple.length);
    }
    
    return 0;
}