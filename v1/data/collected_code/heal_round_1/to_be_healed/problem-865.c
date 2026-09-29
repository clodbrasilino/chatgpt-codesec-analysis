#include<stdio.h>

void printList(int n) {
    int i;
    for(i = 0; i < n; i++) {
        printf("List\n");
    }
}

int main() {
    int n;
    
    printf("Enter the number of times to print the list: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);
    
    printList(n);
    
    return 0;
}