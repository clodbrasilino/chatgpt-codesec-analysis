#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LIST_SIZE 100

int countSamePairs(const int list1[], const int list2[], int size) {
    int count = 0;
  
    for (int i = 0; i < size; i++) {
        int num1 = list1[i];
      
        for (int j = 0; j < size; j++) {
            int num2 = list2[j];
          
            if (num1 == num2) {
                count++;
                break;
            }
        }
    }
  
    return count;
}

int main() {
    int list1[MAX_LIST_SIZE] = {0};
    int list2[MAX_LIST_SIZE] = {0};
  
    int size = 0;
    printf("Enter the size of the lists: ");
    scanf("%d", &size);
  
    printf("Enter the numbers for list1:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &list1[i]);
    }
  
    printf("Enter the numbers for list2:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &list2[i]);
    }
  
    int samePairs = countSamePairs(list1, list2, size);
    printf("Number of same pairs: %d\n", samePairs);
  
    return 0;
}