#include<stdio.h>
#include<stdlib.h>
#define MAX 100

int isSubset(int* arr1, int n1, int* arr2, int n2)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < n2; i++) {
        for (j = 0; j < n1; j++) {
            if (arr2[i] == arr1[j])
                break;
        }

        if (j == n1)
            return 0;
    }
    return 1;
}

int main()
{
    int arr1[MAX], arr2[MAX];
    int n1, n2, i;

    printf("Enter number of elements in first set: ");
    scanf("%d",&n1);
    printf("Enter elements of first set: ");
    for(i = 0; i < n1; i++)
        scanf("%d",&arr1[i]);

    printf("Enter number of elements in second set: ");
    scanf("%d",&n2);
    printf("Enter elements of second set: ");
    for(i = 0; i < n2; i++)
        scanf("%d",&arr2[i]);

    if(isSubset(arr1, n1, arr2, n2))
        printf("Second set is a subset of the first set\n");
    else
        printf("Second set is not a subset of the first set\n");

    return 0;
}