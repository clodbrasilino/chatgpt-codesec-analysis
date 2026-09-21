#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/random.h>

int getRandomInt(int min, int max) {
    if (min > max) {
        return -1;
    }

    uint32_t random_value;
    
    if (getrandom(&random_value, sizeof(random_value), 0) != sizeof(random_value)) {
        return -1;
    }

    uint32_t range = (uint32_t)(max - min + 1);
    return min + (int)(random_value % range);
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
        
        if (p1 == -1 || p2 == -1) {
            return -1;
        }

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

    if (chooseDistinctPoints(range1_min, range1_max, range2_min, range2_max, &point1, &point2) == 0) {
        printf("Point 1: %d\n", point1);
        printf("Point 2: %d\n", point2);
    } else {
        printf("Failed to find distinct points.\n");
    }

    return 0;
}