#include <stdio.h>

void choosePoints(int start1, int end1, int start2, int end2) {
    int i;

    if(end1 < start2 || end2 < start1) {
        for(i = start1; i <= end1; i++) {
            printf("%d ", i);
        }
        for(i = start2; i <= end2; i++) {
            printf("%d ", i);
        }
    } else {
        if(start1 < start2) {
            for(i = start1; i < start2; i++) {
                printf("%d ", i);
            }
            for(i = end2 + 1; i <= end1; i++) {
                printf("%d ", i);
            }
        } else {
            for(i = start2; i < start1; i++) {
                printf("%d ", i);
            }
            for(i = end1 + 1; i <= end2; i++) {
                printf("%d ", i);
            }
        }
    }
}

int main() {
    int start1 = 1, end1 = 10, start2 = 15, end2 = 20;
    choosePoints(start1, end1, start2, end2);
    return 0;
}