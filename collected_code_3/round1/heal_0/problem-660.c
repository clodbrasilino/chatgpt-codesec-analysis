#include <stdio.h>

void choosePoints(int range1Start, int range1End, int range2Start, int range2End) {
    int i;

    if(range1End < range2Start || range2End < range1Start) {
        for(i = range1Start; i <= range1End; i++) {
            printf("%d ", i);
        }
        for(i = range2Start; i <= range2End; i++) {
            printf("%d ", i);
        }
    } else {
        if(range1Start < range2Start) {
            for(i = range1Start; i < range2Start; i++) {
                printf("%d ", i);
            }
            for(i = range2End + 1; i <= range1End; i++) {
                printf("%d ", i);
            }
        } else {
            for(i = range2Start; i < range1Start; i++) {
                printf("%d ", i);
            }
            for(i = range1End + 1; i <= range2End; i++) {
                printf("%d ", i);
            }
        }
    }
}

int main() {
    int range1Start = 1, range1End = 10, range2Start = 15, range2End = 20;
    choosePoints(range1Start, range1End, range2Start, range2End);
    return 0;
}