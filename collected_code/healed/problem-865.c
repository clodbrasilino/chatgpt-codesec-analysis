#include<stdio.h>

void printList(int n) {
    int i;
    for(i = 0; i < n; i++) {
        printf("List\n");
    }
}

int main() {
    int n = 0;
    
    printf("Enter the number of times to print the list: ");
    scanf("%d", &n);
    
    printList(n);
    
    return 0;
}