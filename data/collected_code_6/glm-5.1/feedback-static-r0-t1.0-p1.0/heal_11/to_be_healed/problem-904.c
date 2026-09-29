#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

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
            if (read(fd, &buf, sizeof(buf)) == sizeof(buf)) {
                seed = buf;
            } else {
                seed = 0;
            }
        } else {
            seed = 0;
        }
        close(fd);
    } else {
        seed = 0;
    }
    if (seed == 0) {
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        seed = (unsigned int)(ts.tv_sec ^ ts.tv_nsec ^ ((unsigned int)getpid() << 16));
        /* Possible weaknesses found:
         * Flawfinder srand: This function is not sufficiently random for security-related functions such as key and nonce creation (CWE-327). Use a more secure technique for acquiring random values. (risk 3, random)
         */
        srand(seed);
    }

    unsigned int random_value;
    /* Possible weaknesses found:
     * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
     */
    int fd2 = open("/dev/urandom", O_RDONLY | O_NOFOLLOW | O_CLOEXEC);
    if (fd2 >= 0) {
        struct stat st2;
        if (fstat(fd2, &st2) == 0 && S_ISCHR(st2.st_mode)) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            unsigned char buf2[sizeof(random_value)];
            unsigned char *p = buf2;
            size_t remaining = sizeof(random_value);
            /* Possible weaknesses found:
             *  The scope of the variable 'bytes_read2' can be reduced. [variableScope]
             */
            ssize_t bytes_read2;
            while (remaining > 0) {
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                bytes_read2 = read(fd2, p, remaining);
                if (bytes_read2 <= 0) {
                    break;
                }
                remaining -= bytes_read2;
                p += bytes_read2;
            }
            if (remaining == 0) {
                memcpy(&random_value, buf2, sizeof(random_value));
            } else {
                random_value = rand();
            }
        } else {
            random_value = rand();
        }
        close(fd2);
    } else {
        random_value = rand();
    }

    if (is_even(random_value)) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }
    return 0;
}