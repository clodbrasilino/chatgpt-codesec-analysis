#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getRandomInt(int min, int max) {
    if (min > max) {
        return -1;
    }
    return min + rand() % (max - min + 1);
}

int chooseDistinctPoints(int range1_min, int range1_max, int range2_min, int range2_max, int *point1, int *point2) {
    if (point1 == NULL || point2 == NULL) {
        return -1;
    }

    if (range1_min > range1_max || range2_min > range2_max) {
        return -1;
    }

    if ((range1_min <= range2_max && range1_max >= range2_min)) {
        if (range1_min == range2_min && range1_max == range2_max && range1_min == range1_max) {
             return -1;
        }
    }
    
    int p1, p2;
    int max_attempts = 10000;
    int attempts = 0;

    do {
        p1 = getRandomInt(range1_min, range1_max);
        p2 = getRandomInt(range2_min, range2_max);
        attempts++;
        if (attempts > max_attempts) {
            return -1;
        }
    } while (p1 == p2);

    *point1 = p1;
    *point2 = p2;

    return 0;
}

int main(void) {
    int range1_min = 1;
    int range1_max = 10;
    int range2_min = 5;
    int range2_max = 15;
    int point1, point2;

    /* Possible weaknesses found:
     * Flawfinder srand: This function is not sufficiently random for security-related functions such as key and nonce creation (CWE-327). Use a more secure technique for acquiring random values. (risk 3, random)
     */
    srand((unsigned int)time(NULL));

    if (chooseDistinctPoints(range1_min, range1_max, range2_min, range2_max, &point1, &point2) == 0) {
        printf("Point 1: %d\n", point1);
        printf("Point 2: %d\n", point2);
    } else {
        printf("Failed to find distinct points.\n");
    }

    return 0;
}