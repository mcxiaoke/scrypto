#ifdef NOPILOT
#include "posix_compat.h"
#include <stdlib.h>
#else
#include <PalmOS.h>
#endif

#include "hex2bin.h"

#define _T(a) L ## a
//#define _T(a) a

static inline int hex2byte(char c) {
	return (c>=_T('0') && c<=_T('9')) ? (c)-_T('0') :
		(c>=_T('A') && c<=_T('F')) ? (c)-_T('A')+10 :
		(c>=_T('a') && c<=_T('f')) ? (c)-_T('a')+10 : 0;
}

static inline int byte2hex(char c) {
	return ((c<10) ? (c)+_T('0') : (c)-10+_T('a'));
}

static inline int is_hex(char c) {
	return ((c>=_T('0') && c<=_T('9')) ||
		(((c>=_T('a') && c<=_T('f'))) ||
			((c>=_T('A') && c<=_T('F')))));
}

char *bin2hex(unsigned char *bin, char *hex, int len) {
	int i;	
	for(i = 0; i < len; i++) {
		unsigned char byte = *bin++;
		unsigned char hbyte = (byte & 0xF0) >> 4;
		unsigned char lbyte = byte & 0xF;
		*hex++ = byte2hex(hbyte);	
		*hex++ = byte2hex(lbyte);	
	}

	*hex++ = 0;

	return hex;
}

unsigned char* hex2bin(char *hex, unsigned char *bin, int iLen, int *oLen) {
	int bLen;
	int i;

	iLen = (iLen <= 0) ? StrLen(hex) : iLen;

	if(StrNCompare(hex, "0x", 2) == 0) {
		/* hex string has 0x prefix */
		hex = hex + 2;
		iLen -= 2;			
	}	

	if(iLen%2 != 0) {
		/* hex string is not a multiple of 2 in length */
		return NULL;
	}

	bLen = iLen / 2;
	MemSet(bin,0,bLen);
	
	for(i = 0; i < bLen; i++) {
		char hbyte = *hex++;
		char lbyte = *hex++;

		if(!is_hex(hbyte) || !is_hex(lbyte)) {
			/* invalid character */
			return NULL;
		}
		*bin++ = (unsigned char) (hex2byte(hbyte)<<4 | hex2byte(lbyte));
	}

	*oLen = i;

	return bin;
}

#ifdef TEST
int main(int argc, char **argv) {
	
	int len;
	char *in = "0123456789abcdef0a1b2c3d4e5f6a7b8c9daebf";
	char hout[1024];
	unsigned char bout[1024];

	printf("In:  %s\n", in);
	if(hex2bin(in, bout, 0, &len) != 0) {
		printf("ERROR: Malformed hex string\n");
	}
	bin2hex(bout, hout, len);
	printf("Out: %s\n", hout);
	if(strcmp(in, hout) != 0) {
		printf("ERROR: Hex strings do not match\n");
	}
}
#endif
