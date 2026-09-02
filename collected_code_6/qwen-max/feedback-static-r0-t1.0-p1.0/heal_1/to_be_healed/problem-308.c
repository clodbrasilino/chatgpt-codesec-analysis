#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

/* Possible weaknesses found:
 *  Parameter 'list1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'list2' can be declared as pointer to const [constParameterPointer]
 */
void findLargestProducts(int *list1, int *list2, int n, int m, int k, int *result) {
    int products[n * m];
    int index = 0;
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            products[index++] = list1[i] * list2[j];
        }
    }
    /* Possible weaknesses found:
     *  Uninitialized variable: products [uninitvar]
     *  Uninitialized variable: products
     */
    qsort(products, n * m, sizeof(int), compare);
    for (int i = 0; i < k; ++i) {
        result[i] = products[i];
    }
}

int main() {
    int list1[] = { 3, 4, 5 };
    int list2[] = { 2, 7, 2 };
    int n = sizeof(list1) / sizeof(list1[0]);
    int m = sizeof(list2) / sizeof(list2[0]);
    int k = 5;
    int *result = (int *)malloc(k * sizeof(int));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    findLargestProducts(list1, list2, n, m, k, result);
    for (int i = 0; i < k; ++i) {
        printf("%d ", result[i]);
    }
    free(result);
    return 0;
}