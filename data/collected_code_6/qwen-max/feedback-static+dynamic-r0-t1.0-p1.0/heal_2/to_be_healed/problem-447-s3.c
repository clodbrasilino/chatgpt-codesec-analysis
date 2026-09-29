#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'cbrt'
  */

void find_cubes(int *list, int n) {
    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  call to undeclared library function 'cbrt' with type 'double (double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <math.h> or explicitly provide a declaration for 'cbrt'
         *  implicit declaration of function 'cbrt' [-Wimplicit-function-declaration]
         */
        if (list[i] > 0 && list[i] > cbrt(INT_MAX)) {
            list[i] = INT_MAX;
        } else if (list[i] < 0 && list[i] < -cbrt(INT_MIN)) {
            list[i] = INT_MIN;
        } else {
            list[i] = list[i] * list[i] * list[i];
        }
    }
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Number of elements must be positive.\n");
        return 1;
    }

    int *list = malloc(n * sizeof(int));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &list[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free(list);
            return 1;
        }
    }

    find_cubes(list, n);

    printf("Cubes of the elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    free(list);
    return 0;
}