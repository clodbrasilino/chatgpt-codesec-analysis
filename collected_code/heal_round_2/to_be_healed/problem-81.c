#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

void zipTuples(const int* tuple1, const int* tuple2, int size) {
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     */
    int* zipTuple = malloc(size * 2 * sizeof(int));
    
    for (int i = 0; i < size * 2; i += 2) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'zipTuple' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        zipTuple[i] = tuple1[i / 2];
        zipTuple[i + 1] = tuple2[i / 2];
    }
    
    printf("Zip Tuple: ");
    for (int i = 0; i < size * 2; i++) {
        printf("%d ", zipTuple[i]);
    }

    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  include '<stdlib.h>' or provide a declaration of 'free'
     */
    free(zipTuple);
}

int main() {
    int tuple1[] = {1, 2, 3};
    int tuple2[] = {4, 5, 6};
    int size = sizeof(tuple1) / sizeof(tuple1[0]);

    zipTuples(tuple1, tuple2, size);
    
    return 0;
}