#include <stdbool.h> 
#include <stdio.h> 
#include <string.h> 

bool isUndulating(int num) {
    char str[12];
    sprintf(str, "%d", num);

    int len = strlen(str);
    if (len < 3)
        return false;

    char first = str[0], second = str[1];

    if(first == second) 
        return false;
    
    for (int i = 2; i < len; ++i) {
        if (i % 2 == 0) {
            if (str[i] != first)
                return false;
        }
        else {
            if (str[i] != second)
                return false;
        }
    }
    return true;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (isUndulating(num)) {
        printf("The number is undulating\n");
    }
    else {
        printf("The number is not undulating\n");
    }

    return 0;
}