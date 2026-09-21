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
    int fd = open("/dev/urandom", O_RDONLY | O_NOFOLLOW | O_CLOEXEC);
    if (fd >= 0) {
        struct stat st;
        if (fstat(fd, &st) == 0 && S_ISCHR(st.st_mode)) {
            unsigned int buf;
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
        srand(seed);
    }

    unsigned int random_value;
    int fd2 = open("/dev/urandom", O_RDONLY | O_NOFOLLOW | O_CLOEXEC);
    if (fd2 >= 0) {
        struct stat st2;
        if (fstat(fd2, &st2) == 0 && S_ISCHR(st2.st_mode)) {
            if (read(fd2, &random_value, sizeof(random_value)) != sizeof(random_value)) {
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