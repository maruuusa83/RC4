#include "rc4.h"
#include <stdio.h>
#include <vector>
#include <random>

// #define ___DEBUG___
#ifdef ___DEBUG___
#define PRINT_COUNT (500000)
#endif /* ___DEBUG___ */

#define PRINT_BYTES(DATA) for (auto byte : (DATA)) printf("%x ", byte)

static const unsigned int KEY_SIZE = 1;
static const unsigned int TEXT_SIZE = 10;
static const unsigned int ITERATION_NUM = 1000000;

unsigned int attack(const std::vector<marusa::BYTE> &plain, const std::vector<marusa::BYTE> &cipher, std::array<marusa::BYTE, KEY_SIZE> &obtained_key)
{
    /*** Key Attack ***/
    obtained_key.fill(0);

    std::vector<marusa::BYTE> t_dec;
    int trip_count = 0;
    while (true){
 #ifdef ___DEBUG___
        if (trip_count % PRINT_COUNT == 0){
            printf("Tried %d keys\n", trip_count);
        }
 #endif /* ___DEBUG___ */

        /* try key */
        marusa::RC4<KEY_SIZE> t_rc4(obtained_key);
        t_rc4.exec(cipher, t_dec);

        if (t_dec == plain){ // when find the key
            break;
        }

        /* increment key */
        for (int i = 0; i < obtained_key.size(); i++){
            if (obtained_key[i] == 255){
                obtained_key[i] = 0;
            }
            else {
                obtained_key[i]++;
                break;
            }
        }

        trip_count++;
    }

    // printf("%d\n", trip_count);
    return (trip_count);
}

int main(void)
{
    std::random_device rd;
    std::mt19937 mt(rd()); // give a seed using std::random_device
    std::uniform_int_distribution<> rand_byte(0, marusa::BYTE_SIZE - 1);

    int itr_sum = 0;
    for (int iteration = 0; iteration < ITERATION_NUM; iteration++){
        /*** Generate Key, Plain text and Cipher Text ***/
        std::array<marusa::BYTE, KEY_SIZE> key;
        for (int i = 0; i < KEY_SIZE; i++) key[i] = rand_byte(mt) % marusa::BYTE_SIZE;

        std::vector<marusa::BYTE> plain;
        for (int i = 0; i < TEXT_SIZE; i++) plain.push_back(rand_byte(mt));

        marusa::RC4<sizeof(key)> rc4(key);
        std::vector<marusa::BYTE> cipher;
        rc4.exec(plain, cipher);

        /*** Attack ***/
        std::array<marusa::BYTE, KEY_SIZE> obtained_key;
        itr_sum += attack(plain, cipher, obtained_key);

#ifdef ___DEBUG___
        printf("key    : "); PRINT_BYTES(key); printf("\n");
        printf("plain  : "); PRINT_BYTES(plain); printf("\n");
        printf("cipher : "); PRINT_BYTES(cipher); printf("\n");
        printf("obt    : "); PRINT_BYTES(obtained_key); printf("\n");
#endif /* ___DEBUG___ */

        if (key != obtained_key){
            printf("ERROR : Obtained key is wrong.\n");
            exit(1);
        }

        // printf("Finish iteration : %d\n", iteration);
        if (iteration % 10000 == 0) printf("itr %d\n", iteration);
    }

    printf("Iteration average : %f\n", (float)itr_sum / ITERATION_NUM);

    return (0);
}

