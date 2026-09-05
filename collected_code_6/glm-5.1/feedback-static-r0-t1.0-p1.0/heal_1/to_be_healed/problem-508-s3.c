#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'a' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'b' can be declared as pointer to const [constParameterPointer]
 */
int check_common_order(int *a, int size_a, int *b, int size_b) {
    int *common_a = malloc((size_a < size_b ? size_a : size_b) * sizeof(int));
    int *common_b = malloc((size_a < size_b ? size_a : size_b) * sizeof(int));
    
    if (!common_a || !common_b) {
        free(common_a);
        free(common_b);
        return -1;
    }

    int count_a = 0;
    for (int i = 0; i < size_a; i++) {
        for (int j = 0; j < size_b; j++) {
            if (a[i] == b[j]) {
                common_a[count_a++] = a[i];
                break;
            }
        }
    }

    int count_b = 0;
    for (int i = 0; i < size_b; i++) {
        for (int j = 0; j < size_a; j++) {
            if (b[i] == a[j]) {
                common_b[count_b++] = b[i];
                break;
            }
        }
    }

    if (count_a != count_b) {
        free(common_a);
        free(common_b);
        return -1;
    }

    for (int i = 0; i < count_a; i++) {
        if (common_a[i] != common_b[i]) {
            free(common_a);
            free(common_b);
            return 0;
        }
    }

    free(common_a);
    free(common_b);
    return 1;
}

int main(void) {
    int a1[] = {1, 2, 3, 4, 5, 6};
    int b1[] = {0, 2, 9, 4, 8, 6};
    int size_a1 = sizeof(a1) / sizeof(a1[0]);
    int size_b1 = sizeof(b1) / sizeof(b1[0]);
    int res1 = check_common_order(a1, size_a1, b1, size_b1);
    if (res1 == 1) printf("List 1: Same order\n");
    else if (res1 == 0) printf("List 1: Different order\n");
    else printf("List 1: Error\n");

    int a2[] = {1, 2, 3, 4};
    int b2[] = {4, 3, 2, 1};
    int size_a2 = sizeof(a2) / sizeof(a2[0]);
    int size_b2 = sizeof(b2) / sizeof(b2[0]);
    int res2 = check_common_order(a2, size_a2, b2, size_b2);
    if (res2 == 1) printf("List 2: Same order\n");
    else if (res2 == 0) printf("List 2: Different order\n");
    else printf("List 2: Error\n");

    int a3[] = {1, 2, 3, 4};
    int b3[] = {1, 3, 2, 4};
    int size_a3 = sizeof(a3) / sizeof(a3[0]);
    int size_b3 = sizeof(b3) / sizeof(b3[0]);
    int res3 = check_common_order(a3, size_a3, b3, size_b3);
    if (res3 == 1) printf("List 3: Same order\n");
    else if (res3 == 0) printf("List 3: Different order\n");
    else printf("List 3: Error\n");

    return 0;
}