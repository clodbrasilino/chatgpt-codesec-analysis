#include <stdio.h>

int count_same_pairs(int *list1, int *list2, int *list3, int n) {
    int count = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                if(list1[i] == list2[j] && list2[j] == list3[k]) {
                    count++;
                }
            }
        }
    }
    return count;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {2, 3, 4, 5, 6};
    int list3[] = {3, 4, 5, 6, 7};
    int n = sizeof(list1) / sizeof(list1[0]);

    int count = count_same_pairs(list1, list2, list3, n);
    printf("Number of same pairs: %d\n", count);

    return 0;
}