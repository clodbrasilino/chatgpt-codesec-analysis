#include <stdio.h>
#include <math.h>

double nth_term(double firstTerm, double ratio, int term) {
    if(term < 1) {
        printf("Error: term must be a positive integer.\n");
        return -1;
    }
    return firstTerm * pow(ratio, term - 1); 
}

int main(){
    double firstTerm, ratio;
    int term;
    printf("Enter the first term of the series: ");
    scanf("%lf", &firstTerm);
    printf("Enter the common ratio: ");
    scanf("%lf", &ratio);
    printf("Enter the term you want to find: ");
    scanf("%d", &term);
    double result = nth_term(firstTerm, ratio, term);
    if(result != -1){
        printf("The %d-th term of the geometric series is: %.2lf\n", term, result);
    }
    return 0;
}