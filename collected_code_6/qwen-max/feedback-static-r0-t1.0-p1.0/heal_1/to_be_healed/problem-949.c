#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'log10'
  */

typedef struct {
    int a;
    int b;
} Tuple;

int countDigits(int number) {
    if (number == 0) return 1;
    number = abs(number);
    /* Possible weaknesses found:
     *  call to undeclared library function 'log10' with type 'double (double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <math.h> or explicitly provide a declaration for 'log10'
     *  implicit declaration of function 'log10' [-Wimplicit-function-declaration]
     */
    return (int)log10(number) + 1;
}

int totalDigits(Tuple t) {
    return countDigits(t.a) + countDigits(t.b);
}

int compare(const void *a, const void *b) {
    /* Possible weaknesses found:
     *  Variable 'tupleA' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *tupleA = (Tuple *)a;
    /* Possible weaknesses found:
     *  Variable 'tupleB' can be declared as pointer to const [constVariablePointer]
     */
    Tuple *tupleB = (Tuple *)b;
    return totalDigits(*tupleA) - totalDigits(*tupleB);
}

void printTuples(Tuple *tuples, int n) {
    for (int i = 0; i < n; ++i) {
        printf("(%d, %d) ", tuples[i].a, tuples[i].b);
    }
    printf("\n");
}

int main() {
    Tuple tuples[] = {{123, 45}, {67, 89}, {10, 2345}, {6, 789}};
    int n = sizeof(tuples) / sizeof(tuples[0]);

    qsort(tuples, n, sizeof(Tuple), compare);

    printTuples(tuples, n);

    return 0;
}