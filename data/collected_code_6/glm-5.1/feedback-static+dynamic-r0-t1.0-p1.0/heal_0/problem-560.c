#include <stdio.h>
#include <stdlib.h>

int* tuple_union(const int* t1, size_t s1, const int* t2, size_t s2, size_t* out_size) {
    if (t1 == NULL || t2 == NULL || out_size == NULL) {
        if (out_size != NULL) *out_size = 0;
        return NULL;
    }

    size_t max_size = s1 + s2;
    int* temp = (int*)malloc(max_size * sizeof(int));
    if (temp == NULL) {
        *out_size = 0;
        return NULL;
    }

    size_t count = 0;

    for (size_t i = 0; i < s1; i++) {
        int found = 0;
        for (size_t j = 0; j < count; j++) {
            if (temp[j] == t1[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            temp[count++] = t1[i];
        }
    }

    for (size_t i = 0; i < s2; i++) {
        int found = 0;
        for (size_t j = 0; j < count; j++) {
            if (temp[j] == t2[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            temp[count++] = t2[i];
        }
    }

    int* result = (int*)malloc(count * sizeof(int));
    if (result == NULL) {
        free(temp);
        *out_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        result[i] = temp[i];
    }

    free(temp);
    *out_size = count;
    return result;
}

int main(void) {
    int t1[] = {1, 2, 3, 4};
    int t2[] = {3, 4, 5, 6};
    size_t s1 = sizeof(t1) / sizeof(t1[0]);
    size_t s2 = sizeof(t2) / sizeof(t2[0]);
    size_t out_size = 0;

    int* union_result = tuple_union(t1, s1, t2, s2, &out_size);

    if (union_result != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%d ", union_result[i]);
        }
        printf("\n");
        free(union_result);
    }

    return 0;
}