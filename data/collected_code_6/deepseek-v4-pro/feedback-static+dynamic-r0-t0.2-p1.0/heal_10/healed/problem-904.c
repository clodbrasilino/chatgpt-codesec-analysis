#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#include <wincrypt.h>
#else
#include <unistd.h>
#include <fcntl.h>
#endif

bool is_even(int number) {
    return number % 2 == 0;
}

static int get_secure_random_seed(unsigned int *seed) {
#ifdef _WIN32
    HCRYPTPROV crypt_provider;
    if (!CryptAcquireContext(&crypt_provider, NULL, NULL, PROV_RSA_FULL,
                             CRYPT_VERIFYCONTEXT | CRYPT_SILENT)) {
        return 0;
    }
    BOOL result = CryptGenRandom(crypt_provider, sizeof(*seed),
                                 (BYTE *)seed);
    CryptReleaseContext(crypt_provider, 0);
    return result;
#else
    int fd = open("/dev/urandom", O_RDONLY | O_CLOEXEC);
    if (fd == -1) {
        return 0;
    }
    
    ssize_t bytes_read = read(fd, seed, sizeof(*seed));
    close(fd);
    
    return bytes_read == sizeof(*seed);
#endif
}

int main(void) {
    unsigned int seed;
    
    if (!get_secure_random_seed(&seed)) {
        seed = (unsigned int)time(NULL) ^ (unsigned int)clock();
    }
    
    srand(seed);
    
    int test_number = rand() % 100;
    bool result = is_even(test_number);
    
    if (result) {
        return EXIT_SUCCESS;
    }
    
    return EXIT_FAILURE;
}