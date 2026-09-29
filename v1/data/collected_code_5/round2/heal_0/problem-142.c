#include <stdio.h>
#include <stdlib.h>

int pair_counter(int* list1, int* list2, int* list3, int list_length) {
    int counter = 0;
    for(int i=0; i<list_length; i++) {
        for(int j=0; j<list_length; j++) {
            for(int k=0; k<list_length; k++) {
                if(list1[i] == list2[j] && list1[i] == list3[k]) {
                    counter++;
                }
            }
        }
    }
    return counter;
}

int main() {
    int list1[] = {1,2,3,4};
    int list2[] = {2,3,4,5};
    int list3[] = {3,4,5,6};
    int list_length = sizeof(list1) / sizeof(int);
    int count = pair_counter(list1, list2, list3, list_length);
    printf("The number of same pairs in the three lists is: %d\n", count);
    return 0;
}