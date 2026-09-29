#include <stdio.h>
#include <stdlib.h>

double babylonianSqrt(double num){
    if(num == 0) {
        return 0;
    }

    double guess = num;
    double accuracy = 0.000001;

    while((guess - num/guess) > accuracy) {
        guess = (guess + num/guess)/2;
    }

    return guess;
}

int main(){
    double num;

    printf("Enter a number: ");
    scanf("%lf", &num);

    if(num < 0) {
        fprintf(stderr, "Error: The number must be non-negative.\n");
        return EXIT_FAILURE;
    }

    double root = babylonianSqrt(num);

    printf("Square root: %.6lf\n", root);

    return EXIT_SUCCESS;
}