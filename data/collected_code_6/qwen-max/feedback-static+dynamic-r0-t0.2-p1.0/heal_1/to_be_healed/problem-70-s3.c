#include <stdio.h>
#include <stdlib.h>

int are_tuples_equal_length(int **tuples, int num_tuples) {
    if (num_tuples == 0) return 1;
    int length = 0;
    for (int i = 0; i < num_tuples; ++i) {
        if (i == 0) {
            length = tuples[i][0];
        } else if (tuples[i][0] != length) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int num_tuples = 3;
    /* Possible weaknesses found:
     *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
     *  (near initialization for 'tuple1[5]')
     *  (near initialization for 'tuple1[0]')
     *  (near initialization for 'tuple1[4]')
     *  (near initialization for 'tuple1[3]')
     *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     *  (near initialization for 'tuple1[2]')
     *  (near initialization for 'tuple1[1]')
     */
    int *tuple1[] = {5, 1, 2, 3, 4, 5};
    /* Possible weaknesses found:
     *  (near initialization for 'tuple2[3]')
     *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
     *  (near initialization for 'tuple2[5]')
     *  (near initialization for 'tuple2[0]')
     *  (near initialization for 'tuple2[1]')
     *  (near initialization for 'tuple2[2]')
     *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     *  (near initialization for 'tuple2[4]')
     */
    int *tuple2[] = {5, 6, 7, 8, 9, 10};
    /* Possible weaknesses found:
     *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
     *  (near initialization for 'tuple3[4]')
     *  (near initialization for 'tuple3[5]')
     *  (near initialization for 'tuple3[3]')
     *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     *  (near initialization for 'tuple3[0]')
     *  (near initialization for 'tuple3[2]')
     *  (near initialization for 'tuple3[1]')
     */
    int *tuple3[] = {5, 11, 12, 13, 14, 15};

    /* Possible weaknesses found:
     *  initialization of 'int *' from incompatible pointer type 'int **' [-Wincompatible-pointer-types]
     *  (near initialization for 'tuples[1]')
     *  (near initialization for 'tuples[2]')
     *  (near initialization for 'tuples[0]')
     */
    int *tuples[] = {tuple1, tuple2, tuple3};

    if (are_tuples_equal_length(tuples, num_tuples)) {
        printf("All tuples have equal length.\n");
    } else {
        printf("Tuples do not have equal length.\n");
    }

    return 0;
}