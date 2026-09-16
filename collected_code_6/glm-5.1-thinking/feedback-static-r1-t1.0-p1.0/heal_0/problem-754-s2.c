#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    size_t original_index;
} IndexedValue;

typedef struct {
    int value;
    size_t idx1;
    size_t idx2;
    size_t idx3;
} CommonIndexElement;

static int compare_indexed_value(const void *a, const void *b) {
    int va = ((const IndexedValue *)a)->value;
    int vb = ((const IndexedValue *)b)->value;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

CommonIndexElement *find_common_index_elements(const int *list1, size_t len1,
                                               const int *list2, size_t len2,
                                               const int *list3, size_t len3,
                                               size_t *result_len) {
    if (list1 == NULL || list2 == NULL || list3 == NULL || result_len == NULL) {
        return NULL;
    }

    if (len1 == 0 || len2 == 0 || len3 == 0) {
        *result_len = 0;
        return NULL;
    }

    *result_len = 0;
    size_t max_results = len1 < len2 ? len1 : len2;
    max_results = max_results < len3 ? max_results : len3;

    CommonIndexElement *results = malloc(max_results * sizeof(CommonIndexElement));
    if (results == NULL) {
        return NULL;
    }

    IndexedValue *iv1 = malloc(len1 * sizeof(IndexedValue));
    IndexedValue *iv2 = malloc(len2 * sizeof(IndexedValue));
    IndexedValue *iv3 = malloc(len3 * sizeof(IndexedValue));

    if (iv1 == NULL || iv2 == NULL || iv3 == NULL) {
        free(iv1);
        free(iv2);
        free(iv3);
        free(results);
        return NULL;
    }

    for (size_t i = 0; i < len1; ++i) {
        iv1[i].value = list1[i];
        iv1[i].original_index = i;
    }
    for (size_t i = 0; i < len2; ++i) {
        iv2[i].value = list2[i];
        iv2[i].original_index = i;
    }
    for (size_t i = 0; i < len3; ++i) {
        iv3[i].value = list3[i];
        iv3[i].original_index = i;
    }

    qsort(iv1, len1, sizeof(IndexedValue), compare_indexed_value);
    qsort(iv2, len2, sizeof(IndexedValue), compare_indexed_value);
    qsort(iv3, len3, sizeof(IndexedValue), compare_indexed_value);

    size_t i = 0, j = 0, k = 0;
    size_t count = 0;

    while (i < len1 && j < len2 && k < len3) {
        if (iv1[i].value == iv2[j].value && iv2[j].value == iv3[k].value) {
            results[count].value = iv1[i].value;
            results[count].idx1 = iv1[i].original_index;
            results[count].idx2 = iv2[j].original_index;
            results[count].idx3 = iv3[k].original_index;
            count++;
            i++;
            j++;
            k++;
        } else {
            int min_val = iv1[i].value;
            if (iv2[j].value < min_val) min_val = iv2[j].value;
            if (iv3[k].value < min_val) min_val = iv3[k].value;

            if (iv1[i].value == min_val) i++;
            if (iv2[j].value == min_val) j++;
            if (iv3[k].value == min_val) k++;
        }
    }

    free(iv1);
    free(iv2);
    free(iv3);

    if (count == 0) {
        free(results);
        return NULL;
    }

    CommonIndexElement *final_results = realloc(results, count * sizeof(CommonIndexElement));
    if (final_results == NULL) {
        *result_len = count;
        return results;
    }

    *result_len = count;
    return final_results;
}

int main(void) {
    int list1[] = {1, 5, 10, 20, 40, 80};
    int list2[] = {6, 7, 20, 80, 100};
    int list3[] = {3, 4, 15, 20, 30, 70, 80, 120};

    size_t len1 = sizeof(list1) / sizeof(list1[0]);
    size_t len2 = sizeof(list2) / sizeof(list2[0]);
    size_t len3 = sizeof(list3) / sizeof(list3[0]);

    size_t result_len = 0;
    CommonIndexElement *results = find_common_index_elements(list1, len1, list2, len2, list3, len3, &result_len);

    if (results != NULL) {
        for (size_t i = 0; i < result_len; ++i) {
            printf("Common element: %d, Indices: [%zu, %zu, %zu]\n",
                   results[i].value, results[i].idx1, results[i].idx2, results[i].idx3);
        }
        free(results);
    } else {
        printf("No common elements found or allocation failed.\n");
    }

    return 0;
}