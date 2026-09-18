#include <stdio.h>
#include <math.h>

int demlo(int num) {
    int demlo_num;
    if (num > 0 && num <= 9){
        demlo_num = pow(((pow(10, num)) - 1) / 9, 2);
    } else {
        printf("The input is out of bounds\n");
        return -1;
    }
    return demlo_num;
}

int main() {
    int input_number;
    printf("Enter a number between 1 and 9: ");
    scanf("%d", &input_number);
    int result = demlo(input_number);
    if(result != -1){
        printf("Demlo number for input number %d is: %d\n", input_number, result);
    }
    return 0;
}