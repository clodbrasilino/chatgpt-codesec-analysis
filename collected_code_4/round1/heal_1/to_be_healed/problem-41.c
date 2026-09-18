#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

int * filter_even_numbers(int* array, int length, int* new_length) {
    int count = 0;
    for(int i = 0; i < length; i++) {
        if(array[i] % 2 == 0) {
            count++;
        }
    }

    int* result = NULL;
    if(count > 0) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
         *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
         *  include '<stdlib.h>' or provide a declaration of 'malloc'
         */
        result = (int *)malloc(count * sizeof(int));
        if(result == NULL) {
            *new_length = 0;
            return NULL;
        }

        int j = 0;
        for(int i = 0; i < length; i++) {
            if(array[i] % 2 == 0) {
                result[j++] = array[i];
            }
        }
    }
    *new_length = count;

    return result;
}

int main() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int new_length;
  
    int* filtered = filter_even_numbers(array, 10, &new_length);

    if(filtered != NULL) {
        for(int i = 0; i < new_length; i++) {
            printf("%d ", filtered[i]);
        }
        /* Possible weaknesses found:
         *  include '<stdlib.h>' or provide a declaration of 'free'
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
         */
        free(filtered);
    }

    return 0;
}