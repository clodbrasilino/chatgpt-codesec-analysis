#include <stdio.h>

int countLists(int numOfElements, int list[]){
    int count = 0;

    for (int i = 0; i < numOfElements; i++){
        if(list[i] == -1){
            count++;
        }
    }

    return count;
}

int main(){
    int num1[] = {-1, 2, 3, -1, 5, -1};
    int num2[] = {-1, -1, -1};
    int num3[] = {1, 2, 3};

    int numOfElements1 = sizeof(num1) / sizeof(num1[0]);
    int numOfElements2 = sizeof(num2) / sizeof(num2[0]);
    int numOfElements3 = sizeof(num3) / sizeof(num3[0]);

    int result1 = countLists(numOfElements1, num1);
    int result2 = countLists(numOfElements2, num2);
    int result3 = countLists(numOfElements3, num3);
    int total = result1 + result2 + result3;
    
    printf("Number of -1s in lists: %d\n", total);

    return 0;
}