#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'tuple1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'tuple2' can be declared as pointer to const [constParameterPointer]
 */
bool check_tuples(int *tuple1, int *tuple2, int length) {
    for (int i = 0; i < length; ++i) {
        if (tuple2[i] <= i || tuple1[i] != i) {
            return false;
        }
    }
    return true;
}

int main() {
    int tuple1[] = {0, 1, 2, 3};
    int tuple2[] = {1, 2, 3, 4};
    int length = sizeof(tuple1) / sizeof(tuple1[0]);
    bool result = check_tuples(tuple1, tuple2, length);
    if (result) {
        printf("All elements in the second tuple are greater than their corresponding index in the first tuple.\n");
    } else {
        printf("Not all elements in the second tuple are greater than their corresponding index in the first tuple.\n");
    }
    return 0;
}