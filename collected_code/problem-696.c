#include <stdio.h>

// Function to zip two given lists of lists
void zipLists(int lists1[][2], int n1, int lists2[][2], int n2) {
    int i, j;
    
    for (i = 0; i < n1; i++) {
        for (j = 0; j < 2; j++) {
            printf("%d ", lists1[i][j]);
        }
        printf("%d ", lists2[i][0]);
        printf("%d\n", lists2[i][1]);
    }
}

int main() {
    int list1[][2] = {{1, 2}, {3, 4}, {5, 6}};
    int list2[][2] = {{7, 8}, {9, 10}, {11, 12}};
    int n1 = sizeof(list1) / sizeof(list1[0]);
    int n2 = sizeof(list2) / sizeof(list2[0]);
    
    zipLists(list1, n1, list2, n2);
    
    return 0;
}