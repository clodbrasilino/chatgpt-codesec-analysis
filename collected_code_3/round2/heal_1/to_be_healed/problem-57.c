#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

int compare(const void* a, const void* b) {
    return *(char*)b - *(char*)a;
}

void findLargestNum(char* str) {
    /* Possible weaknesses found:
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     *  include '<string.h>' or provide a declaration of 'strlen'
     *  incompatible implicit declaration of built-in function 'strlen' [-Wbuiltin-declaration-mismatch]
     */
    qsort(str, strlen(str), sizeof(char), compare);
}

int main() {
    char str[] = "1234567890";
    findLargestNum(str);
    printf("Largest Number: %s\n", str);
    return 0;
}