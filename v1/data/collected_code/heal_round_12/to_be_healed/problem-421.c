#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void concatenateTuple(const char tuple[][MAX_LENGTH], int size, const char* delimiter) {
  
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char result[MAX_LENGTH] = "";
    size_t result_len = 0;
    size_t delimiter_len = strnlen(delimiter, MAX_LENGTH);

    for (int i = 0; i < size; i++) {
        
        size_t tuple_len = strnlen(tuple[i], MAX_LENGTH);
      
        if (result_len + tuple_len + delimiter_len >= MAX_LENGTH) {
            printf("Error: Buffer overflow would occur.\n");
            return;
        }
    
        /* Possible weaknesses found:
         *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
         */
        strncpy(result + result_len, tuple[i], tuple_len);
        result_len += tuple_len;

        if (i != size - 1) {
            /* Possible weaknesses found:
             *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
             */
            strncpy(result + result_len, delimiter, delimiter_len);
            result_len += delimiter_len;
        }
    }
    
    result[result_len] = '\0';
    printf("%s\n", result);
}

int main() {
    const char tuple[][MAX_LENGTH] = {"Hello", "World", "How", "Are", "You"};
    const char *delimiter = "-";
    unsigned int size = sizeof(tuple) / sizeof(tuple[0]);
    
    concatenateTuple(tuple, size, delimiter);

    return 0;
}