#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>

bool is_even(int number) {
    return (number % 2) == 0;
}

int main(void) {
    unsigned int seed;
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd >= 0) {
        struct stat st;
        if (fstat(fd, &st) == 0 && S_ISCHR(st.st_mode)) {
            ssize_t bytes_read = read(fd, &seed, sizeof(seed));
            close(fd);
            if (bytes_read != sizeof(seed)) {
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
        seed = (unsigned int)(ts.tv_sec ^ ts.tv_nsec ^ (getpid() << 16));
    }
    srand(seed);

    int num = rand();
    if (is_even(num)) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }
    return 0;
}