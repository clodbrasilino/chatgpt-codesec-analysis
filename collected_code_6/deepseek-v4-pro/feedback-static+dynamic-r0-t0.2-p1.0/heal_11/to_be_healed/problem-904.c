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
    /* Possible weaknesses found:
     * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
     */
    int fd = open("/dev/urandom", O_RDONLY | O_CLOEXEC);
    if (fd == -1) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
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
    
    /* Possible weaknesses found:
     * Flawfinder srand: This function is not sufficiently random for security-related functions such as key and nonce creation (CWE-327). Use a more secure technique for acquiring random values. (risk 3, random)
     */
    srand(seed);
    
    int test_number = rand() % 100;
    bool result = is_even(test_number);
    
    if (result) {
        return EXIT_SUCCESS;
    }
    
    return EXIT_FAILURE;
}