#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

bool is_even(int number) {
    return number % 2 == 0;
}

int main(void) {
    int test_number;
    unsigned int seed;
    int fd;
    struct stat st;
    
    /* Possible weaknesses found:
     * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
     */
    fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1) {
        seed = (unsigned int)time(NULL) ^ (unsigned int)getpid();
    } else {
        if (fstat(fd, &st) == 0 && S_ISCHR(st.st_mode)) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            if (read(fd, &seed, sizeof(seed)) != sizeof(seed)) {
                seed = (unsigned int)time(NULL) ^ (unsigned int)getpid();
            }
        } else {
            seed = (unsigned int)time(NULL) ^ (unsigned int)getpid();
        }
        close(fd);
    }
    
    test_number = (int)(seed % 2001) - 1000;
    
    if (is_even(test_number)) {
        printf("%d is even\n", test_number);
        return 0;
    } else {
        printf("%d is odd\n", test_number);
        return 1;
    }
}