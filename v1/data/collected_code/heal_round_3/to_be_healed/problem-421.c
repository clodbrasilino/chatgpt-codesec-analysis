#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

void concatenateTuple(const char tuple[][MAX_LENGTH], int size, const char delimiter[]) {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char result[MAX_LENGTH] = "";
    int available_length = sizeof(result);

    for(int i = 0; i < size; i++) {
        int tuple_len = strnlen(tuple[i], available_length);

        if(tuple_len + 1 > available_length) {
            printf("Error: Buffer overflow would occur.\n");
            return;
        }

        /* Possible weaknesses found:
         *   Easily used incorrectly (e.g., incorrectly computing the correct maximum  size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf,  or automatically resizing strings.
         */
        strncat(result, tuple[i], tuple_len);
        available_length -= tuple_len;

        if(i != size - 1) {
            int delimiter_len = strnlen(delimiter, available_length);

            if(delimiter_len + 1 > available_length) {
                printf("Error: Buffer overflow would occur.\n");
                return;
            }

            /* Possible weaknesses found:
             *   Easily used incorrectly (e.g., incorrectly computing the correct maximum  size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf,  or automatically resizing strings.
             */
            strncat(result, delimiter, delimiter_len);
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