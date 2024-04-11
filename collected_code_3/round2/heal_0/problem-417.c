#include <stdio.h>

struct Tuple {
    int first;
    int second;
};

int findCommonFirst(struct Tuple arr[], int n) {
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = i + 1; j < n; j++) {
            if(arr[i].first == arr[j].first) {
                return arr[i].first;
            }
        }
    }
    return -1;
}

int main() {
    struct Tuple arr[] = {{1, 2}, {3, 4}, {5, 6}, {1, 7}};
    int n = sizeof(arr) / sizeof(arr[0]);
    int common = findCommonFirst(arr, n);
    if(common != -1) {
        printf("Common first element is %d\n", common);
    } else {
        printf("No common first element found\n");
    }
    return 0;
}