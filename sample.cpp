#include "rc4.h"
#include <vector>
#include <array>
#include <iostream>

int main(void)
{
    static const int KEY_SIZE = 4;
    std::array<marusa::BYTE, KEY_SIZE> key{1, 2, 3, 4};
    
    marusa::RC4<KEY_SIZE> rc4(key);
    
    std::vector<marusa::BYTE> plain_text{5, 6, 7, 8, 9};
    std::vector<marusa::BYTE> cipher_text;
    rc4.exec(plain_text, cipher_text); // encryption
    
    std::vector<marusa::BYTE> decrypted_text;
    rc4.reset();
    rc4.exec(cipher_text, decrypted_text);
    
    std::cout << "Plain Text : ";
    for (auto pos : plain_text) std::cout << (int)pos << " ";
    std::cout << std::endl;

    std::cout << "Cipher Text : ";
    for (auto pos : cipher_text) std::cout << (int)pos << " ";
    std::cout << std::endl;

    std::cout << "Decrypted Text : ";
    for (auto pos : decrypted_text) std::cout << (int)pos << " ";
    std::cout << std::endl;

    return (0);
}
