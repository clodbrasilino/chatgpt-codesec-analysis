#include <stdio.h>

void splitList(int list[], int length, int n) {
    int i;
    for(i = 0; i < length; i++) {
        if(i % n == 0) {
            printf("\n");
        }
        printf("%d ", list[i]);
    }
}

int main() {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int length = sizeof(list) / sizeof(list[0]);
    int n = 3;
    
    splitList(list, length, n);
    
    return 0;
}