#include <stdio.h>

struct Range {
    int start;
    int end;
};

void choosePoints(struct Range range1, struct Range range2) {
    for(int i = range1.start; i <= range1.end; ++i) {
        if(i < range2.start || i > range2.end) {
            printf("Chosen point: %d\n", i);
        }
    }
    for(int i = range2.start; i <= range2.end; ++i) {
        if(i < range1.start || i > range1.end) {
            printf("Chosen point: %d\n", i);
        }
    }
}

int main() {
    struct Range range1 = {1, 5};
    struct Range range2 = {4, 8};

    choosePoints(range1, range2);

    return 0;
}