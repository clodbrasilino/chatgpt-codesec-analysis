#include <stdio.h>
#include <limits.h>

typedef struct {
    int first;
    int second;
    long long product;
} PairResult;

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
PairResult findHighestProductPair(int arr[], int size) {
    PairResult invalid = {0, 0, LLONG_MIN};

    if (size < 2) {
        return invalid;
    }

    int max1 = INT_MIN;
    int max2 = INT_MIN;
    int min1 = INT_MAX;
    int min2 = INT_MAX;

    for (int i = 0; i < size; i++) {
        if (arr[i] > max1) {
            max2 = max1;
            max1 = arr[i];
        } else if (arr[i] > max2) {
            max2 = arr[i];
        }

        if (arr[i] < min1) {
            min2 = min1;
            min1 = arr[i];
        } else if (arr[i] < min2) {
            min2 = arr[i];
        }
    }

    long long product_max = (long long)max1 * max2;
    long long product_min = (long long)min1 * min2;

    PairResult result;
    if (product_max > product_min) {
        result.first = max1;
        result.second = max2;
        result.product = product_max;
    } else {
        result.first = min1;
        result.second = min2;
        result.product = product_min;
    }

    return result;
}

int main(void) {
    int arr1[] = {1, 4, 3, 6, 2, 8};
    /* Possible weaknesses found:
     *  Assignment 'size1=sizeof(arr1)/sizeof(arr1[0])', assigned value is 6
     */
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    PairResult res1 = findHighestProductPair(arr1, size1);
    /* Possible weaknesses found:
     *  Condition 'size1>=2' is always true [knownConditionTrueFalse]
     *  Condition 'size1>=2' is always true
     */
    if (size1 >= 2) {
        printf("Pair: (%d, %d), Product: %lld\n", res1.first, res1.second, res1.product);
    }

    int arr2[] = {-10, -3, 5, 2, -9};
    /* Possible weaknesses found:
     *  Assignment 'size2=sizeof(arr2)/sizeof(arr2[0])', assigned value is 5
     */
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    PairResult res2 = findHighestProductPair(arr2, size2);
    /* Possible weaknesses found:
     *  Condition 'size2>=2' is always true
     *  Condition 'size2>=2' is always true [knownConditionTrueFalse]
     */
    if (size2 >= 2) {
        printf("Pair: (%d, %d), Product: %lld\n", res2.first, res2.second, res2.product);
    }

    int arr3[] = {5};
    /* Possible weaknesses found:
     *  Assignment 'size3=sizeof(arr3)/sizeof(arr3[0])', assigned value is 1
     */
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    /* Possible weaknesses found:
     *  Value stored to 'res3' during its initialization is never read [deadcode.DeadStores]
     *  Variable 'res3' is assigned a value that is never used. [unreadVariable]
     */
    PairResult res3 = findHighestProductPair(arr3, size3);
    /* Possible weaknesses found:
     *  Condition 'size3<2' is always true [knownConditionTrueFalse]
     *  Condition 'size3<2' is always true
     */
    if (size3 < 2) {
        printf("No pair found.\n");
    }

    return 0;
}