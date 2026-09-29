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
    tuple.length = str ? strnlen(str, MAX_SIZE) : 0;
    return tuple;
}

int additionalBufferCheck(const char* str){
    size_t len = strnlen(str, MAX_SIZE + 1);
    
    if(len >= MAX_SIZE){
        printf("Input too long.\n");
        return 0;
    }
    return 1;
}

int main(){
    char string[MAX_SIZE + 1] = "";

    printf("Enter a string: ");
    fgets(string, MAX_SIZE + 1, stdin);

    size_t len = strnlen(string, MAX_SIZE + 1);
    if (len>0 && string[len-1] == '\n'){
        string[len-1] = '\0';
    }

    if(additionalBufferCheck(string)){
        Tuple tuple = convertToTuple(string);

        printf("Converted tuple -\n");
        printf("String: %s\n", tuple.str);
        printf("Length: %d\n", tuple.length);
    }

    return 0;
}