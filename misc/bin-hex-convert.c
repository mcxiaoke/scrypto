/*
* @Author: mcxiaoke
* @Date:   2016-01-17 15:14:55
* @Last Modified by:   mcxiaoke
* @Last Modified time: 2016-01-17 17:33:25
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint8_t c2i(char c)
{
    if (c >= '0' && c <= '9') return      c - '0';
    if (c >= 'A' && c <= 'F') return 10 + c - 'A';
    if (c >= 'a' && c <= 'f') return 10 + c - 'a';
    return -1;
}

uint8_t* hex2bin(const char* in)
{
    size_t len = strlen(in);
    uint8_t* out = malloc((len / 2) * sizeof(uint8_t));
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
        // printf("%d:%02X\n", i, data[i]);
    }
    return buffer;
}

int main() {
    char* buffer = "2B7E151628AED2A6ABF7158809CF4F3C";
    printf("buffer:\t%s\n", buffer);
    uint8_t* data = hex2bin(buffer);
    char* text = bin2hex(data, strlen(buffer) / 2);
    printf("text:\t%s\n", text);
    return 0;
}
