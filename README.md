# RC4

RC4 stream cipher.

## How to use
Include `rc4.h` and use `marusa::RC4<KEY_SIZE>` class.

Template Argument of `KEY_SIZE` is a size of key
and argument of the constructor is a encryption key using `std::array<marusa::BYTE, KEY_SIZE>`.

## methods

``` c++
template <std::size_t KEY_SIZE>
class RC4
{
public:
    RC4(std::array<BYTE, KEY_SIZE> key);

    void exec(const std::vector<BYTE> &data, std::vector<BYTE> &result);
    void reset();
};
```

## Sample
``` c++
static const int KEY_SIZE = 4;
std::array<marusa::BYTE, KEY_SIZE> key{1, 2, 3, 4};

marusa::RC4<KEY_SIZE> rc4(key);

std::vector<marusa::BYTE> plain_text{5, 6, 7, 8, 9};

### Encryption
std::vector<marusa::BYTE> cipher_text;
rc4.exec(plain_text, cipher_text);

### Reset State
rc4.reset();

## Decryption
std::vector<marusa::BYTE> decrypted_text;
rc4.exec(cipher_text, decrypted_text);

### printing
std::cout << "Plain Text : ";
for (auto pos : plain_text) std::cout << (int)pos << " ";
std::cout << std::endl;

std::cout << "Cipher Text : ";
for (auto pos : cipher_text) std::cout << (int)pos << " ";
std::cout << std::endl;

std::cout << "Decrypted Text : ";
for (auto pos : decrypted_text) std::cout << (int)pos << " ";
std::cout << std::endl;
```



