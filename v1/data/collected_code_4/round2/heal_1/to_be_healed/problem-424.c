#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

char *extract_rear_elements(char **input, int length) {
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    char *rear_elements = malloc(length * sizeof(char));
    if(rear_elements == NULL) {
        printf("Memory allocation failed.\n");
        /* Possible weaknesses found:
         *  implicit declaration of function 'exit' [-Wimplicit-function-declaration]
         *  incompatible implicit declaration of built-in function 'exit' [-Wbuiltin-declaration-mismatch]
         *  include '<stdlib.h>' or provide a declaration of 'exit'
         */
        exit(1);
    }

    for(int i = 0; i < length; i++) {
        int str_len = strlen(input[i]);

        if(str_len > 0) {
            rear_elements[i] = input[i][str_len - 1];
        } else {
            printf("Empty string at index %d.\n", i);
            /* Possible weaknesses found:
             *  include '<stdlib.h>' or provide a declaration of 'exit'
             *  incompatible implicit declaration of built-in function 'exit' [-Wbuiltin-declaration-mismatch]
             */
            exit(1);
        }
    }
    return rear_elements;
}

int main() {
    const int length = 3;
    /* Possible weaknesses found:
     *  variable-sized object may not be initialized except with an empty initializer
     */
    char *strings[length] = {"Hello", "World", "!"};

    char *rear_elements = extract_rear_elements(strings, length);

    for (int i = 0; i < length; i++)
        printf("%c\n", rear_elements[i]);

    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     */
    free(rear_elements);

    return 0;
}