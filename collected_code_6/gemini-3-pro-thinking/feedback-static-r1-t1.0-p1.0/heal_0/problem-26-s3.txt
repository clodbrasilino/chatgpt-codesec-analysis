#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int first;
    int second;
} Tuple;

bool has_all_k_elements(const Tuple *list, size_t size, int k) {
    if (list == NULL || k < 0) {
        return false;
    }
    if (k == 0) {
        return true;
    }

    bool *found = (bool *)calloc((size_t)k, sizeof(bool));
    if (found == NULL) {
        return false;
    }

    for (size_t i = 0; i < size; i++) {
        if (list[i].first >= 1 && list[i].first <= k) {
            found[list[i].first - 1] = true;
        }
        if (list[i].second >= 1 && list[i].second <= k) {
            found[list[i].second - 1] = true;
        }
    }

    bool all_present = true;
    for (int i = 0; i < k; i++) {
        if (!found[i]) {
            all_present = false;
            break;
        }
    }

    free(found);
    return all_present;
}

int main(void) {
    Tuple list[] = {
        {1, 2},
        {3, 4},
        {5, 1}
    };
    size_t size = sizeof(list) / sizeof(list[0]);
    int k = 5;

    bool result = has_all_k_elements(list, size, k);
    if (result) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    k = 6;
    result = has_all_k_elements(list, size, k);
    if (result) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}