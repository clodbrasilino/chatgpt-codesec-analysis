#include<stdio.h>
#include<string.h>

typedef struct {
    char* str;
    int length;
} Tuple;

Tuple convertToTuple(char* str){
    Tuple tuple;
    tuple.str = str;
    tuple.length = strlen(str);
    return tuple;
}

int main(){
    char string[100];
    
    printf("Enter a string: ");
    scanf("%s", string);
    
    Tuple tuple = convertToTuple(string);
    
    printf("Converted tuple -\n");
    printf("String: %s\n", tuple.str);
    printf("Length: %d\n", tuple.length);
    
    return 0;
}