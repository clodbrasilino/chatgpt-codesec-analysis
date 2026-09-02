#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'tuple' can be declared as pointer to const [constParameterPointer]
 */
bool is_element_present(int *tuple, int size, int element) {
    for (int i = 0; i < size; ++i) {
        if (tuple[i] == element) {
            return true;
        }
    }
    return false;
}

/* Possible weaknesses found:
 *  Parameter 'tuple2' can be declared as pointer to const [constParameterPointer]
 */
void find_dissimilar_elements(int *tuple1, int size1, int *tuple2, int size2) {
    /* Possible weaknesses found:
     *  The scope of the variable 'found' can be reduced. [variableScope]
     */
    bool found;
    for (int i = 0; i < size1; ++i) {
        found = false;
        for (int j = 0; j < size2; ++j) {
            if (tuple1[i] == tuple2[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            printf("%d ", tuple1[i]);
        }
    }
    for (int i = 0; i < size2; ++i) {
        if (!is_element_present(tuple1, size1, tuple2[i])) {
            printf("%d ", tuple2[i]);
        }
    }
}

int main() {
    int tuple1[] = {1, 2, 3, 4, 5};
    int tuple2[] = {4, 5, 6, 7, 8};
    int size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    int size2 = sizeof(tuple2) / sizeof(tuple2[0]);

    find_dissimilar_elements(tuple1, size1, tuple2, size2);
    return 0;
}