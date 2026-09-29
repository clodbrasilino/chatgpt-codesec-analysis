#include <stdio.h>
#include <stdlib.h>

int check_common_order(int *list1, int size1, int *list2, int size2) {
    int *common1 = NULL;
    int *common2 = NULL;
    int c1_size = 0;
    int c2_size = 0;
    int i, j;
    int result = 1;

    common1 = (int *)malloc(size1 * sizeof(int));
    common2 = (int *)malloc(size2 * sizeof(int));

    if (common1 == NULL || common2 == NULL) {
        free(common1);
        free(common2);
        return -1;
    }

    for (i = 0; i < size1; i++) {
        for (j = 0; j < size2; j++) {
            if (list1[i] == list2[j]) {
                common1[c1_size++] = list1[i];
                break;
            }
        }
    }

    for (i = 0; i < size2; i++) {
        for (j = 0; j < size1; j++) {
            if (list2[i] == list1[j]) {
                common2[c2_size++] = list2[i];
                break;
            }
        }
    }

    if (c1_size != c2_size) {
        free(common1);
        free(common2);
        return -1;
    }

    for (i = 0; i < c1_size; i++) {
        if (common1[i] != common2[i]) {
            result = 0;
            break;
        }
    }

    free(common1);
    free(common2);

    return result;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {6, 2, 8, 3, 9, 5};

    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);

    int res = check_common_order(list1, size1, list2, size2);

    printf("%d\n", res);

    return 0;
}