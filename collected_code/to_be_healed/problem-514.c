#include <stdio.h>

typedef struct {
    int x, y;
} Tuple;

int summationOfTupleElements(Tuple tupleList[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += tupleList[i].x + tupleList[i].y;
    }
    return sum;
}

int main() {
    Tuple tupleList[3];
    
    /* Possible weaknesses found:
     *  Cannot determine that 'tupleList[0] members' is initialized [premium-bughuntingUninit]
     */
    tupleList[0].x = 1;
    /* Possible weaknesses found:
     *  Cannot determine that 'tupleList[0] members' is initialized [premium-bughuntingUninit]
     */
    tupleList[0].y = 2;
    
    /* Possible weaknesses found:
     *  Cannot determine that 'tupleList[1] members' is initialized [premium-bughuntingUninit]
     */
    tupleList[1].x = 3;
    /* Possible weaknesses found:
     *  Cannot determine that 'tupleList[1] members' is initialized [premium-bughuntingUninit]
     */
    tupleList[1].y = 4;
    
    /* Possible weaknesses found:
     *  Cannot determine that 'tupleList[2] members' is initialized [premium-bughuntingUninit]
     */
    tupleList[2].x = 5;
    /* Possible weaknesses found:
     *  Cannot determine that 'tupleList[2] members' is initialized [premium-bughuntingUninit]
     */
    tupleList[2].y = 6;
    
    int totalSum = summationOfTupleElements(tupleList, 3);
    printf("Sum of tuple elements: %d\n", totalSum);
    
    return 0;
}