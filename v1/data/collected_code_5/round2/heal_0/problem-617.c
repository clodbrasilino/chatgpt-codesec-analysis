#include <stdio.h>

int JumpsRequired(int d, int length) {
    if(d <= 0 || length <= 0){    // Improper values returns -1
        return -1;
    }
  
    int quotient = d / length;
    int remainder = d % length;

    if(remainder == 0){
        return quotient;
    }
    else{
        return quotient + 1;
    }
}

int main() {
    int d, length;

    printf("Enter distance from origin: ");
    scanf("%d", &d);

    printf("Enter jump length: ");
    scanf("%d", &length);

    int result = JumpsRequired(d, length);

    if(result == -1){
        printf("Invalid inputs!\n");
    }
    else{
        printf("Jumps required: %d\n", result);
    }
  
    return 0;
}