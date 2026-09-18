#include <stdio.h>
#include <stdlib.h>

float avg_from_list(int *list, int size) {
    int sum = 0;
    if(list != NULL && size > 0) {
        for(int i=0; i<size; i++) {
            sum += list[i];
        }
        return ((float)sum / size);
    }
    return 0.0;
}

int main() {
    int list[5] = {1, 2, 3, 4, 5};
    printf("Average is: %.2f", avg_from_list(list, 5));
    
    return 0;
}