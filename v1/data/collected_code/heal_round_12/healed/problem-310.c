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
    tuple.length = strlen(str);
    return tuple;
}

int additionalBufferCheck(char* str){
    size_t len = strlen(str);
    
    if(len >= MAX_SIZE){
        printf("Input too long.\n");
        return 0;
    }
    return 1;
}

int main(){
    char string[MAX_SIZE + 1] = "";

    printf("Enter a string: ");
    fgets(string, sizeof(string), stdin);

    string[strcspn(string, "\n")] = 0;

    if(additionalBufferCheck(string)){
        Tuple tuple = convertToTuple(string);

        printf("Converted tuple -\n");
        printf("String: %s\n", tuple.str);
        printf("Length: %d\n", tuple.length);
    }

    return 0;
}