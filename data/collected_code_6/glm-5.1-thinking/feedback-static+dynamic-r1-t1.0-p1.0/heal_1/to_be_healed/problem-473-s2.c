#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int are_tuples_equal(Tuple t1, Tuple t2) {
    return (t1.a == t2.a && t1.b == t2.b) || (t1.a == t2.b && t1.b == t2.a);
}

/* Possible weaknesses found:
 *  Parameter 'list1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'list2' can be declared as pointer to const [constParameterPointer]
 */
Tuple* find_tuple_intersection(Tuple* list1, int size1, Tuple* list2, int size2, int* result_size) {
    if (list1 == NULL || list2 == NULL || result_size == NULL || size1 < 0 || size2 < 0) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    int max_size = size1 < size2 ? size1 : size2;
    if (max_size == 0) {
        *result_size = 0;
        return NULL;
    }

    Tuple* result = (Tuple*)malloc(max_size * sizeof(Tuple));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            if (are_tuples_equal(list1[i], list2[j])) {
                int already_exists = 0;
                for (int k = 0; k < count; k++) {
                    if (are_tuples_equal(result[k], list1[i])) {
                        already_exists = 1;
                        break;
                    }
                }
                if (!already_exists) {
                    result[count] = list1[i];
                    if (result[count].a > result[count].b) {
                        int temp = result[count].a;
                        result[count].a = result[count].b;
                        result[count].b = temp;
                    }
                    count++;
                }
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

int main() {
    Tuple list1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    Tuple list2[] = {{2, 1}, {5, 7}, {4, 3}, {9, 10}};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);
    int result_size = 0;

    Tuple* intersection = find_tuple_intersection(list1, size1, list2, size2, &result_size);

    printf("Intersection:\n");
    for (int i = 0; i < result_size; i++) {
        printf("(%d, %d)\n", intersection[i].a, intersection[i].b);
    }

    if (intersection != NULL) {
        free(intersection);
    }

    return 0;
}