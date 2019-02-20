#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "TBC"

void argon2d_hash(const char* input, char* output)
{
        unsigned char hash[64 * 4] = {0}, hash2[64] = {0};

TBC
        memcpy(output, hash, 32);
}
