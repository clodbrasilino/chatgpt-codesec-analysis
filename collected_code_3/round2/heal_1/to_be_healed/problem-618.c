#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

double* divideLists(double* list1, double* list2, int size) {
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     */
    double* result = (double*)malloc(size * sizeof(double));
    for(int i = 0; i < size; i++) {
        if(list2[i] != 0) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            result[i] = list1[i] / list2[i];
        } else {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            result[i] = 0;
        }
    }
    return result;
}

int main() {
    int size = 5;
    double list1[] = {10.0, 20.0, 30.0, 40.0, 50.0};
    double list2[] = {2.0, 4.0, 5.0, 8.0, 10.0};
    double* result = divideLists(list1, list2, size);
    for(int i = 0; i < size; i++) {
        printf("%f ", result[i]);
    }
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  include '<stdlib.h>' or provide a declaration of 'free'
     */
    free(result);
    return 0;
}