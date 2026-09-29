#include <stdio.h>

void choosePoints(int range1_start, int range1_end, int range2_start, int range2_end) {
    int i, j;

    printf("Points from the 1st range: ");
    for (i = range1_start; i <= range1_end; i++) {
        printf("%d ", i);
    }

    printf("\nPoints from the 2nd range: ");
    for (j = range2_start; j <= range2_end; j++) {
        printf("%d ", j);
    }

    printf("\n");
}

int main() {
    int range1_start = 0;
    int range2_start = 0;
    int range1_end = 0;
    int range2_end = 0;

    printf("Enter the start and end points of the 1st range: ");
    scanf("%d %d", &range1_start, &range1_end);
    printf("Enter the start and end points of the 2nd range: ");
    scanf("%d %d", &range2_start, &range2_end);

    choosePoints(range1_start, range1_end, range2_start, range2_end);

    return 0;
}