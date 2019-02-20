#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <argon2d/argon2.h>

static const size_t INPUT_BYTES = 80;
static const size_t OUTPUT_BYTES = 32;
static const unsigned int DEFAULT_ARGON2_FLAG = 2;

void argon2d_hash(const char* input, char* output)
{
    char hashout[32];
    memset(hashout,'\0',32);

    argon2_context context;
    context.out = (uint8_t*)hashout;
    context.outlen = (uint32_t)OUTPUT_BYTES;
    context.pwd = (uint8_t*)input;
    context.pwdlen = (uint32_t)INPUT_BYTES;
    context.salt = (uint8_t*)input;
    context.saltlen = (uint32_t)INPUT_BYTES;
    context.secret = NULL;
    context.secretlen = 0;
    context.ad = NULL;
    context.adlen = 0;
    context.allocate_cbk = NULL;
    context.free_cbk = NULL;
    context.flags = DEFAULT_ARGON2_FLAG;
    context.m_cost = 250;
    context.lanes = 4;
    context.threads = 1;
    context.t_cost = 1;
    argon2_ctx(&context, Argon2_d);

    memcpy(output,hashout,32);
}
