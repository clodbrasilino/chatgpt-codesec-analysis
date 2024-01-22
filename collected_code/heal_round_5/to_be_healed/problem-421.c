#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void concatenateTuple(const char tuple[][MAX_LENGTH], int size, const char delimiter[]) {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char result[MAX_LENGTH] = "";
    int available_length = MAX_LENGTH;

    for(int i = 0; i < size; i++) {
        int delimiter_len = strnlen(delimiter, available_length);
        int tuple_len = strnlen(tuple[i], available_length - delimiter_len);

        if(tuple_len + delimiter_len >= available_length) {
            printf("Error: Buffer overflow would occur.\n");
            return;
        }
        
        /* Possible weaknesses found:
         *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        strncpy(result + strlen(result), tuple[i], tuple_len);
        available_length -= tuple_len;

        if(i != size - 1) {
            /* Possible weaknesses found:
             *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
             *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
             */
            strncpy(result + strlen(result), delimiter, delimiter_len);
            available_length -= delimiter_len;
        }
    }

    printf("%s\n", result);
}

int main() {
    const char tuple[][MAX_LENGTH] = {"Hello", "World", "How", "Are", "You"};
    const char delimiter[] = "-";
    int size = sizeof(tuple) / sizeof(tuple[0]);
    
    concatenateTuple(tuple, size, delimiter);

    return 0;
}