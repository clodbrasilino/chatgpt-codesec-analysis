#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int product;
    int index1;
    int index2;
} ProductPair;

int compare_products(const void *a, const void *b) {
    const ProductPair *pa = (const ProductPair *)a;
    const ProductPair *pb = (const ProductPair *)b;
    if (pb->product != pa->product) {
        return (pb->product > pa->product) - (pb->product < pa->product);
    }
    if (pa->index1 != pb->index1) {
        return pa->index1 - pb->index1;
    }
    return pa->index2 - pb->index2;
}

void find_largest_products(const int *list1, int size1, const int *list2, int size2, int k, ProductPair *results) {
    if (list1 == NULL || list2 == NULL || results == NULL || k <= 0 || size1 <= 0 || size2 <= 0) {
        for (int i = 0; i < k; i++) {
            results[i].product = 0;
            results[i].index1 = -1;
            results[i].index2 = -1;
        }
        return;
    }
    
    if (k > size1 * size2) {
        k = size1 * size2;
    }
    
    ProductPair *all_products = (ProductPair *)malloc((size_t)size1 * size2 * sizeof(ProductPair));
    if (all_products == NULL) {
        for (int i = 0; i < k; i++) {
            results[i].product = 0;
            results[i].index1 = -1;
            results[i].index2 = -1;
        }
        return;
    }
    
    int count = 0;
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            all_products[count].product = list1[i] * list2[j];
            all_products[count].index1 = i;
            all_products[count].index2 = j;
            count++;
        }
    }
    
    qsort(all_products, (size_t)count, sizeof(ProductPair), compare_products);
    
    for (int i = 0; i < k; i++) {
        results[i] = all_products[i];
    }
    
    free(all_products);
}

int main(void) {
    int list1[] = {3, 1, 4, 1, 5};
    int list2[] = {2, 7, 1, 8};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);
    int k = 5;
    
    ProductPair *results = (ProductPair *)malloc((size_t)k * sizeof(ProductPair));
    if (results == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    find_largest_products(list1, size1, list2, size2, k, results);
    
    printf("Top %d largest products:\n", k);
    for (int i = 0; i < k; i++) {
        printf("Product: %d (list1[%d]=%d, list2[%d]=%d)\n",
               results[i].product,
               results[i].index1, list1[results[i].index1],
               results[i].index2, list2[results[i].index2]);
    }
    
    free(results);
    return 0;
}