#include <stdio.h>
#include <stdlib.h>

typedef int (*MapFunc)(int);

int identity(int x) {
    return x;
}

int *map(const int *list, size_t size, MapFunc f) {
    if (list == NULL || f == NULL || size == 0) {
        return NULL;
    }
    int *result = (int *)malloc(size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < size; i++) {
        result[i] = f(list[i]);
    }
    return result;
}

int count_pairs(const int *list1, size_t size1, const int *list2, size_t size2, MapFunc f) {
    if (list1 == NULL || list2 == NULL || f == NULL) {
        return 0;
    }
    int *map1 = map(list1, size1, f);
    int *map2 = map(list2, size2, f);
    if (map1 == NULL || map2 == NULL) {
        free(map1);
        free(map2);
        return 0;
    }
    int count = 0;
    for (size_t i = 0; i < size1; i++) {
        for (size_t j = 0; j < size2; j++) {
            if (map1[i] == map2[j]) {
                count++;
            }
        }
    }
    free(map1);
    free(map2);
    return count;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {4, 5, 6, 7, 8};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    int result = count_pairs(list1, size1, list2, size2, identity);
    printf("%d\n", result);
    return 0;
}