#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
void print_subsets(int *list, int n) {
    if (list == NULL || n <= 0) {
        return;
    }

    int total_subsets = 1 << n;

    for (int i = 0; i < total_subsets; i++) {
        printf("[ ");
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                printf("%d ", list[j]);
            }
        }
        printf("]\n");
    }
}

int main() {
    int list[] = {1, 2, 3};
    int n = sizeof(list) / sizeof(list[0]);

    print_subsets(list, n);

    return 0;
}