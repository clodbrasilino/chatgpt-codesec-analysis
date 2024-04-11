#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int frequency[MAX_SIZE];

void find_frequency(int arr[], int n) {
    for(int i = 0; i < n; i++) {
        if(arr != NULL && arr[i] >= 0 && arr[i] < MAX_SIZE) {
            frequency[arr[i]]++;
        }
    }
}

int main() {
    int n, i, j, m;
    int **arr = NULL;

    printf("Enter the number of lists: ");
    scanf("%d", &n);

    if(n > 0) {
        arr = (int **)malloc(n * sizeof(int *));
        if(arr != NULL) {
            for(i = 0; i < n; i++) {
                printf("Enter the size of list %d: ", i+1);
                scanf("%d", &m);
                if(m > 0) {
                    arr[i] = (int *)malloc(m * sizeof(int));
                    if(arr[i] != NULL) {
                        printf("Enter elements of list %d: ", i+1);
                        for(j = 0; j < m; j++) {
                            scanf("%d", &arr[i][j]);
                        }
                        find_frequency(arr[i], m);
                    }
                }
            }

            printf("Frequency of all elements of list : \n");
            for (i = 0; i < MAX_SIZE; i++) {
                if(frequency[i] != 0) {
                    printf("%d occurs %d times\n", i, frequency[i]);
                }
            }

            for(i = 0; i < n; i++) {
                free(arr[i]);
            }
        }
        free(arr);
    }

    return 0;
}