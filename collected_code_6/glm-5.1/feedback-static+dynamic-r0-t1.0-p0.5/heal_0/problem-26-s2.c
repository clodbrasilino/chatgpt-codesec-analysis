#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool check_tuple_list(int **list, int num_tuples, int k) {
    if (list == NULL || num_tuples < 0 || k < 0) {
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
    int t2[] = {7, 8, 9, 0};

    int *list1[] = {t0, t1, t2};
    int status1 = check_tuple_list(list1, 3, 3);
    printf("%d\n", status1);

    int t3[] = {1, 2, 0};
    int t4[] = {3, 4, 5, 0};

    int *list2[] = {t3, t4};
    int status2 = check_tuple_list(list2, 2, 2);
    printf("%d\n", status2);

    int status3 = check_tuple_list(NULL, 3, 3);
    printf("%d\n", status3);

    int *list4[] = {t0, NULL, t2};
    int status4 = check_tuple_list(list4, 3, 3);
    printf("%d\n", status4);

    return 0;
}