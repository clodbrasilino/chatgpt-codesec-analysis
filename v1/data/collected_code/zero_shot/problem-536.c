#include <stdio.h>

int selectNthItem(int list[], int length, int n) {
    if (n >= length) return -1;
    return list[n];
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    int length = sizeof(list) / sizeof(list[0]);
    int n = 3;
    
    int result = selectNthItem(list, length, n);
    printf("The %dth item of the list is %d\n", n, result);
    
    return 0;
}