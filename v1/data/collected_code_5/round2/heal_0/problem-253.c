#include <stdio.h>

int count_integers(int list[], int size) {
    int count = 0;
    for(int i = 0; i < size; i++) {
        if(list[i] >= 0) {
            count++;
        }
    }
    return count;
}

int main(){
    int list[] = {1, 2, 3, -1, -2, 3, 4, -1, -2, 5, -4, -6};
    int size = sizeof(list)/sizeof(list[0]);

    int count = count_integers(list, size);
    printf("Count of integers: %d", count);

    return 0;
}