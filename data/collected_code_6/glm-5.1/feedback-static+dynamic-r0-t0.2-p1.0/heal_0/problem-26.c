#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool check_tuple_list(int **list, int num_tuples, int k) {
    if (list == NULL) {
        return false;
    }

    for (int i = 0; i < num_tuples; i++) {
        if (list[i] == NULL) {
            return false;
        }

        int j = 0;
        while (list[i][j] != 0) {
            j++;
        }

        if (j != k) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int t0[] = {1, 2, 3, 0};
    int t1[] = {4, 5, 6, 0};
    int *list1[] = {t0, t1};

    bool res1 = check_tuple_list(list1, 2, 3);
    printf("%d\n", res1);

    int t2[] = {7, 8, 0};
    int *list2[] = {t0, t2};

    bool res2 = check_tuple_list(list2, 2, 3);
    printf("%d\n", res2);

    bool res3 = check_tuple_list(NULL, 2, 3);
    printf("%d\n", res3);

    return 0;
}