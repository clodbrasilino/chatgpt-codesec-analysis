#include<stdio.h>
#include<string.h>

typedef struct {
    char* str;
    int length;
} Tuple;

Tuple convertToTuple(char* str){
    Tuple tuple;
    tuple.str = str;
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    tuple.length = strlen(str);
    return tuple;
}

int main(){
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char string[100];
    
    printf("Enter a string: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'string[0]' is initialized [premium-bughuntingUninit]
     *   The scanf() family's %s operation, without a limit specification, permits  buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a  different input function.
     */
    scanf("%s", string);
    
    Tuple tuple = convertToTuple(string);
    
    printf("Converted tuple -\n");
    printf("String: %s\n", tuple.str);
    printf("Length: %d\n", tuple.length);
    
    return 0;
}