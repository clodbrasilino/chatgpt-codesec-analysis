#include <stdio.h>

float findAverageOfEvenNumbers(int givenNumber) {
    int sum = 0;
    int count = 0;
    
    for (int i = 2; i <= givenNumber; i += 2) {
        sum += i;
        count++;
    }
    
    return (float) sum / count;
}

int main() {
    int givenNumber = 20;
    float average = findAverageOfEvenNumbers(givenNumber);
    
    printf("Average of even numbers till %d: %.2f\n", givenNumber, average);
    
    return 0;
}