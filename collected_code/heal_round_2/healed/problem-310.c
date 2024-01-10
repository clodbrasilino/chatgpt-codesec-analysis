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
    char string[101];

    printf("Enter a string: ");
    scanf("%100s", string);
    string[100] = '\0'; 

    Tuple tuple = convertToTuple(string);

    printf("Converted tuple -\n");
    printf("String: %s\n", tuple.str);
    printf("Length: %d\n", tuple.length);

    return 0;
}