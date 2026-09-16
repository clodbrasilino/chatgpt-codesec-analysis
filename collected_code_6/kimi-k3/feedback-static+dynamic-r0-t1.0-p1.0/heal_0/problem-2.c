#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

Tuple* find_similar_elements(const Tuple* list1, size_t size1, const Tuple* list2, size_t size2, size_t* result_size) {
    if (list1 == NULL || list2 == NULL || result_size == NULL || size1 == 0 || size2 == 0) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    size_t max_size = (size1 < size2) ? size1 : size2;
    Tuple* result = (Tuple*)malloc(max_size * sizeof(Tuple));
    
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size1; i++) {
        for (size_t j = 0; j < size2; j++) {
            if (list1[i].x == list2[j].x && list1[i].y == list2[j].y) {
                result[count] = list1[i];
                count++;
                break;
            }
        }
    }

    if (count == 0) {
        free(result);
        result = NULL;
    } else if (count < max_size) {
        Tuple* temp = (Tuple*)realloc(result, count * sizeof(Tuple));
        if (temp != NULL) {
            result = temp;
        }
    }

    *result_size = count;
    return result;
}

int main(void) {
    Tuple list1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    Tuple list2[] = {{3, 4}, {5, 6}, {9, 10}, {1, 2}};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    size_t result_size = 0;

    Tuple* similar = find_similar_elements(list1, size1, list2, size2, &result_size);

    if (similar != NULL) {
        printf("Similar elements:\n");
        for (size_t i = 0; i < result_size; i++) {
            printf("(%d, %d)\n", similar[i].x, similar[i].y);
        }
        free(similar);
    } else {
        printf("No similar elements found or error occurred.\n");
    }

    return 0;
}