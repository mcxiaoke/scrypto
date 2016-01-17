/*
* @Author: mcxiaoke
* @Date:   2016-01-17 16:50:53
* @Last Modified by:   mcxiaoke
* @Last Modified time: 2016-01-17 17:33:37
*/

#include "common.h"

static uint8_t c2i(char c)
{
    if (c >= '0' && c <= '9') return      c - '0';
    if (c >= 'A' && c <= 'F') return 10 + c - 'A';
    if (c >= 'a' && c <= 'f') return 10 + c - 'a';
    return -1;
}

uint8_t* hex2bin(const char* in)
{
    size_t len = strlen(in);
    uint8_t* out = (uint8_t*)malloc((len / 2) * sizeof(uint8_t));
    int i;
    for (i = 0; i < len; i += 2)
    {
        out[i / 2] = c2i(in[i]) * 16 + c2i(in[i + 1]);
    }
    return out;
}

char* bin2hex(const uint8_t* data, size_t len)
{
    char* buffer = (char*)calloc(len * 2, sizeof(char));
    int i;
    for (i = 0; i < len; ++i)
    {
        sprintf(buffer + (i * 2), "%02X", data[i]);
        // printf("%d:%x\n", i, data[i]);
    }
    return buffer;
}

// int main() {

//     char* buffer = "A9B8C7D6E5F41234567890FF";
//     printf("buffer:\t%s\n", buffer);
//     uint8_t* data = hex2bin(buffer);
//     char* text = bin2hex(data, strlen(buffer) / 2);
//     printf("text:\t%s\n", text);
//     return 0;
// }
