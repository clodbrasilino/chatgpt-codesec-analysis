#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int product;
    int index1;
    int index2;
} ProductPair;

int compare_products(const void *a, const void *b) {
    const ProductPair *pa = (const ProductPair *)a;
    const ProductPair *pb = (const ProductPair *)b;
    
    if (pa->product < pb->product) return 1;
    if (pa->product > pb->product) return -1;
    return 0;
}

int* find_largest_products(const int *list1, size_t size1, const int *list2, size_t size2, 
                          size_t num_products, size_t *result_size) {
    if (list1 == NULL || list2 == NULL || size1 == 0 || size2 == 0 || 
        num_products == 0 || result_size == NULL) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    size_t total_combinations = size1 * size2;
    if (total_combinations / size1 != size2) {
        *result_size = 0;
        return NULL;
    }

    if (num_products > total_combinations) {
        num_products = total_combinations;
    }

    ProductPair *all_products = malloc(total_combinations * sizeof(ProductPair));
    if (all_products == NULL) {
        *result_size = 0;
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size1; i++) {
        for (size_t j = 0; j < size2; j++) {
            all_products[count].product = list1[i] * list2[j];
            all_products[count].index1 = (int)i;
            all_products[count].index2 = (int)j;
            count++;
        }
    }

    qsort(all_products, total_combinations, sizeof(ProductPair), compare_products);

    int *result = malloc(num_products * sizeof(int));
    if (result == NULL) {
        free(all_products);
        *result_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < num_products; i++) {
        result[i] = all_products[i].product;
    }

    free(all_products);
    *result_size = num_products;
    return result;
}

int main(void) {
    int list1[] = {5, 3, 8, 1};
    int list2[] = {4, 2, 6};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    size_t num_products = 5;
    size_t result_size = 0;

    int *largest_products = find_largest_products(list1, size1, list2, size2, 
                                                  num_products, &result_size);

    if (largest_products == NULL) {
        fprintf(stderr, "Error: Failed to compute largest products\n");
        return EXIT_FAILURE;
    }

    printf("The %zu largest products are: ", result_size);
    for (size_t i = 0; i < result_size; i++) {
        printf("%d", largest_products[i]);
        if (i < result_size - 1) {
            printf(", ");
        }
    }
    printf("\n");

    free(largest_products);
    return EXIT_SUCCESS;
}