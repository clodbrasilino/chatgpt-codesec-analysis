#include<stdio.h>
#include<string.h>

typedef struct {
    char* str;
    int length;
} Tuple;

Tuple convertToTuple(const char* str){
    Tuple tuple;
    /* Possible weaknesses found:
     *  assignment discards 'const' qualifier from pointer target type [-Wdiscarded-qualifiers]
     */
    tuple.str = str;
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    tuple.length = str ? strlen(str) : 0;
    return tuple;
}

int main(){
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char string[101];
    
    printf("Enter a string: ");
    /* Possible weaknesses found:
     *   It's unclear if the %s limit in the format string is small enough  (CWE-120). Check that the limit is sufficiently small, or use a different  input function.
     */
    scanf("%100s", string);
    
    Tuple tuple = convertToTuple(string);
    
    printf("Converted tuple -\n");
    printf("String: %s\n", tuple.str);
    printf("Length: %d\n", tuple.length);
    
    return 0;
}