#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

bool is_even(int number) {
    return (number % 2) == 0;
}

int main(void) {
    unsigned int seed;
    /* Possible weaknesses found:
     * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
     */
    int fd = open("/dev/urandom", O_RDONLY | O_NOFOLLOW | O_CLOEXEC);
    if (fd >= 0) {
        struct stat st;
        if (fstat(fd, &st) == 0 && S_ISCHR(st.st_mode)) {
            unsigned int buf;
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ssize_t bytes_read = read(fd, &buf, sizeof(buf));
            close(fd);
            if (bytes_read == sizeof(buf)) {
                seed = buf;
            } else {
                seed = 0;
            }
        } else {
            close(fd);
            seed = 0;
        }
    } else {
        seed = 0;
    }
    if (seed == 0) {
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        seed = (unsigned int)(ts.tv_sec ^ ts.tv_nsec ^ ((unsigned int)getpid() << 16));
    }
    /* Possible weaknesses found:
     * Flawfinder srand: This function is not sufficiently random for security-related functions such as key and nonce creation (CWE-327). Use a more secure technique for acquiring random values. (risk 3, random)
     */
    srand(seed);

    int num = rand();
    if (is_even(num)) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }
    return 0;
}