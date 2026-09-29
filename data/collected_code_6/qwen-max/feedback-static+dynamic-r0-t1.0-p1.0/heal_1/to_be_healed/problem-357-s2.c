#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

typedef struct {
    int data;
} Tuple;

int findMax(Tuple *tuples, int count) {
    if (count <= 0) return INT_MIN;
    int max = tuples[0].data;
    for (int i = 1; i < count; ++i) {
        if (tuples[i].data > max) {
            max = tuples[i].data;
        }
    }
    return max;
}

int main() {
    int n;
    printf("Enter the number of tuples: ");
    scanf("%d", &n);

    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     */
    Tuple *tuples = (Tuple *)malloc(n * sizeof(Tuple));
    if (tuples == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        printf("Enter data for tuple %d: ", i + 1);
        scanf("%d", &tuples[i].data);
    }

    int max_value = findMax(tuples, n);
    printf("Maximum value: %d\n", max_value);

    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    free(tuples);
    return 0;
}