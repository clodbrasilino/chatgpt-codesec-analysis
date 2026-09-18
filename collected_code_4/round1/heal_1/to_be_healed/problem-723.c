#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

typedef struct pair {
    int x, y;
} Pair;

int count_same_pairs(Pair l1[], Pair l2[], int n1, int n2) {
    int map[MAX] = {0};
    int count = 0;

    for(int i = 0; i < n1; i++) {
        int index = l1[i].x * MAX + l1[i].y;
        /* Possible weaknesses found:
         *  write of 4 bytes to beyond the end of 'map'
         *  read of 4 bytes from after the end of 'map'
         *  stack-based buffer overflow [CWE-121] [-Wanalyzer-out-of-bounds]
         *  valid subscripts for 'map' are '[0]' to '[99999]'
         *  stack-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
         */
        map[index]++;
    }

    for(int i = 0; i < n2; i++) {
        int index = l2[i].x * MAX + l2[i].y;
        /* Possible weaknesses found:
         *  read of 4 bytes from after the end of 'map'
         *  valid subscripts for 'map' are '[0]' to '[99999]'
         *  stack-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
         */
        if(map[index] > 0) {
            count++;
            /* Possible weaknesses found:
             *  write of 4 bytes to beyond the end of 'map'
             *  read of 4 bytes from after the end of 'map'
             *  stack-based buffer overflow [CWE-121] [-Wanalyzer-out-of-bounds]
             *  valid subscripts for 'map' are '[0]' to '[99999]'
             *  stack-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
             */
            map[index]--;
        }
    }

    return count;
}

int main() {
    Pair l1[] = {{1, 2}, {3, 4}, {5, 6}};
    Pair l2[] = {{3, 4}, {1, 2}, {7, 8}};
    
    int n1 = sizeof(l1) / sizeof(l1[0]);
    int n2 = sizeof(l2) / sizeof(l2[0]);

    int res = count_same_pairs(l1, l2, n1, n2);
    printf("%d\n", res);

    return 0;
}