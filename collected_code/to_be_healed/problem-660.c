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
    int range1_start, range2_start, range1_end, range2_end;

    printf("Enter the start and end points of the 1st range: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'range1_start' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'range1_end' is initialized [premium-bughuntingUninit]
     */
    scanf("%d %d", &range1_start, &range1_end);
    printf("Enter the start and end points of the 2nd range: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'range2_start' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'range2_end' is initialized [premium-bughuntingUninit]
     */
    scanf("%d %d", &range2_start, &range2_end);

    choosePoints(range1_start, range1_end, range2_start, range2_end);

    return 0;
}