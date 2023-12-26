#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void concatenateTuple(char tuple[][MAX_LENGTH], int size, char delimiter[]) {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char result[MAX_LENGTH] = "";
    
    for(int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'tuple[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *   Does not check for buffer overflows when concatenating to destination  [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or  snprintf (warning: strncat is easily misused).
         */
        strcat(result, tuple[i]);
        if(i != size - 1) {
            /* Possible weaknesses found:
             *  Cannot determine that 'delimiter[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *   Does not check for buffer overflows when concatenating to destination  [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or  snprintf (warning: strncat is easily misused).
             */
            strcat(result, delimiter);
        }
    }
    
    printf("%s\n", result);
}

int main() {
    char tuple[][MAX_LENGTH] = {"Hello", "World", "How", "Are", "You"};
    char delimiter[] = "-";
    int size = sizeof(tuple) / sizeof(tuple[0]);
    
    concatenateTuple(tuple, size, delimiter);
    
    return 0;
}