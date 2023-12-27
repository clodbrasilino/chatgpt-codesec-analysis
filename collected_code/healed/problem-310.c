#include<stdio.h>
#include<string.h>

typedef struct {
    char* str;
    int length;
} Tuple;

Tuple convertToTuple(const char* str){
    Tuple tuple;
    tuple.str = str;
    tuple.length = str ? strlen(str) : 0;
    return tuple;
}

int main(){
    char string[101];
    
    printf("Enter a string: ");
    scanf("%100s", string);
    
    Tuple tuple = convertToTuple(string);
    
    printf("Converted tuple -\n");
    printf("String: %s\n", tuple.str);
    printf("Length: %d\n", tuple.length);
    
    return 0;
}