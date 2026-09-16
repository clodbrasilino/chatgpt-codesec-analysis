#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'sublist' can be declared as pointer to const [constParameterPointer]
 */
void print_sublist(int *sublist, int length) {
    for (int i = 0; i < length; ++i) {
        printf("%d ", sublist[i]);
    }
    printf("\n");
}

void generate_sublists(int *arr, int n, int *sublist, int pos, int length) {
    if (pos == n) {
        print_sublist(sublist, length);
        return;
    }
    generate_sublists(arr, n, sublist, pos + 1, length);
    sublist[length] = arr[pos];
    generate_sublists(arr, n, sublist, pos + 1, length + 1);
}

int main() {
    int arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int *sublist = (int *)malloc(n * sizeof(int));
    if (sublist == NULL) {
        return 1;
    }
    generate_sublists(arr, n, sublist, 0, 0);
    free(sublist);
    return 0;
}