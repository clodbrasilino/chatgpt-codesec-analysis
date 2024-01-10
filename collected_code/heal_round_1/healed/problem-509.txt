#include <stdio.h>

float findAverage(int n) {
    int sum = 0;
    int count = 0;
    int num = 1;

    while (num <= n) {
        sum += num;
        count++;
        num += 2;
    }

    return (float)sum / count;
}

int main() {
    int givenNumber = 0;
    printf("Enter the given odd number: ");
    scanf("%d", &givenNumber);

    float average = findAverage(givenNumber);
    printf("The average of odd numbers till %d is %.2f", givenNumber, average);

    return 0;
}