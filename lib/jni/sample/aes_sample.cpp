/*
* @Author: mcxiaoke
* @Date:   2016-01-16 21:46:52
* @Last Modified by:   mcxiaoke
* @Last Modified time: 2016-01-16 22:34:34
*/

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <aes.h>

using namespace std;

// used by bin2hex for conversion via stream.
struct bin2hex_str
{
    std::ostream& os;
    bin2hex_str(std::ostream& os) : os(os) {}
    void operator ()(unsigned char ch)
    {
        os << std::hex
           << std::setw(2)
           << static_cast<int>(ch);
    }
};

// convert a vector of unsigned char to a hex string
std::string bin2hex(const std::vector<unsigned char>& bin)
{
    std::ostringstream oss;
    oss << std::setfill('0');
    std::for_each(bin.begin(), bin.end(), bin2hex_str(oss));
    return oss.str();
}

std::vector<unsigned char> hex2bin(const std::string& hex) {
    std::vector<unsigned char> bytes;

    for (unsigned int i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        unsigned char byte = (unsigned char) strtol(byteString.c_str(), NULL, 16);
        bytes.push_back(byte);
    }

    return bytes;
}

int main(int  argc, char* argv[]) {
    auto key = hex2bin("2B7E151628AED2A6ABF7158809CF4F3C");
    auto plan_vec = hex2bin("6BC1BEE22E409F96E93D7E117393172A");
    std::vector<unsigned char> cipher_vec(16);
    std::vector<unsigned char> decrypt_vec(16);

// aes encrypt
    AES_KEY aes_enc_ctx;
    AES_set_encrypt_key(key.data(), 128, &aes_enc_ctx);
    AES_encrypt(plan_vec.data(), cipher_vec.data(), &aes_enc_ctx);

// aes decrypt
    AES_KEY aes_dec_ctx;
    AES_set_decrypt_key(key.data(), 128, &aes_dec_ctx);
    AES_decrypt(cipher_vec.data(), decrypt_vec.data(), &aes_dec_ctx);

    std::cout << "plan   : " << bin2hex(plan_vec) << std::endl;
    std::cout << "cipher : " << bin2hex(cipher_vec) << std::endl;
    std::cout << "decrypt: " << bin2hex(decrypt_vec) << std::endl;

    return 0;
}
