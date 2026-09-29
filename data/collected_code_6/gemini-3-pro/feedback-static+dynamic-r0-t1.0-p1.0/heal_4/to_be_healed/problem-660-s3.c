#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int getRandomInt(int min, int max) {
    if (min > max) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
     */
    int fd = open("/dev/urandom", O_RDONLY | O_CLOEXEC | O_NOFOLLOW);
    if (fd < 0) {
        return -1;
    }
    
    unsigned int random_value = 0;
    ssize_t bytes_read = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'result' can be reduced. [variableScope]
     */
    ssize_t result;
    
    while (bytes_read < (ssize_t)sizeof(random_value)) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        result = read(fd, ((char*)&random_value) + bytes_read, sizeof(random_value) - bytes_read);
        if (result < 0) {
            if (errno == EINTR) {
                continue;
            }
            close(fd);
            return -1;
        }
        if (result == 0) {
            close(fd);
            return -1;
        }
        bytes_read += result;
    }
    close(fd);
    
    return min + (int)(random_value % ((unsigned int)max - min + 1));
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