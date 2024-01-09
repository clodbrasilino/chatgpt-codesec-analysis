#include<stdio.h>

void checkMonth(int month) {
    switch(month) {
        case 2:
            printf("The month contains 28 days\n");
            break;
        default:
            printf("The month does not contain 28 days\n");
            break;
    }
}

int main() {
    int month;
    printf("Enter the month number: ");
    scanf("%d", &month);
    checkMonth(month);
    return 0;
}