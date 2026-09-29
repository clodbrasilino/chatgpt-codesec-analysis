#include <stdio.h>
#include <stdlib.h>

void multiples(int m, int n) {
    for(int i=1; i<=m; i++)
        printf("%d ",n*i);

    printf("\n");
}

int main() {
    int m, n;

    printf("Enter the number of multiples: ");
    if(scanf("%d", &m) != 1){
        printf("Invalid Input!\n");
        return EXIT_FAILURE;
    }

    printf("Enter the number: ");
    if(scanf("%d", &n) != 1){
        printf("Invalid Input!\n");
        return EXIT_FAILURE;
    }

    multiples(m, n);

    return EXIT_SUCCESS;
}