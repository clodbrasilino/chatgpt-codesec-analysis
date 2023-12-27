#include <stdio.h>

void findLargestProducts(const int list1[], const int list2[], int size1, int size2, int numProducts) {
    int products[size1 * size2];
    int count = 0;

    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            products[count] = list1[i] * list2[j];
            count++;
        }
    }

    for (int i = 0; i < numProducts; i++) {
        int maxIndex = 0;
        int maxProduct = products[0];
        for (int j = 1; j < size1 * size2; j++) {
            if (products[j] > maxProduct) {
                maxProduct = products[j];
                maxIndex = j;
            }
        }

        printf("%d ", maxProduct);
        products[maxIndex] = -1;
    }
}

int main() {
    int list1[] = {2, 4, 6};
    int list2[] = {1, 3, 5};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);
    int numProducts = 3;

    findLargestProducts(list1, list2, size1, size2, numProducts);

    return 0;
}