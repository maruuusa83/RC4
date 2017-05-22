#ifndef ___RC4_H___
#define ___RC4_H___
#include <cstddef>
#include <array>
#include <vector>
#include <cstring>
#include <stdio.h>

namespace marusa {

using BYTE = unsigned char;
static const unsigned int BYTE_SIZE = (0x01 << (sizeof(BYTE) * 8));

template <std::size_t KEY_SIZE>
class RC4
{
public:
    RC4(std::array<BYTE, KEY_SIZE> key);

    void exec(const std::vector<BYTE> &data, std::vector<BYTE> &result);
    void reset();

private:
    static const unsigned int STATE_SIZE = 256;

    std::array<BYTE, KEY_SIZE> _key;
    std::array<BYTE, STATE_SIZE> _state;

    int _now_i, _now_j;

    void _KSA();
    BYTE _PRGA();
};

/********************************/

template <std::size_t KEY_SIZE>
RC4<KEY_SIZE>::RC4(std::array<BYTE, KEY_SIZE> key)
{
    for (int i = 0; i < KEY_SIZE; i++){
        _key[i] = key[i];
    }

    reset();
}

template <std::size_t KEY_SIZE>
void RC4<KEY_SIZE>::_KSA()
{
    for (int i = 0; i < STATE_SIZE; i++){
        _state[i] = i;
    }

    BYTE tmp;
    int j = 0;
    for (int i = 0; i < STATE_SIZE; i++){
        j = (j + _state[i] + _key[i % KEY_SIZE]) % STATE_SIZE;
        tmp = _state[i];
        _state[i] = _state[j];
        _state[j] = tmp;
    }
}

template <std::size_t KEY_SIZE>
BYTE RC4<KEY_SIZE>::_PRGA()
{
    _now_i = (_now_i + 1) % STATE_SIZE;
    _now_j = (_now_j + _state[_now_i]) % STATE_SIZE;

    BYTE tmp = _state[_now_i];
    _state[_now_i] = _state[_now_j];
    _state[_now_j] = tmp;

    return (_state[(_state[_now_i] + _state[_now_j]) % STATE_SIZE]);
}

template <std::size_t KEY_SIZE>
void RC4<KEY_SIZE>::exec(const std::vector<BYTE> &data, std::vector<BYTE> &result)
{
    result.clear();
    result.shrink_to_fit();

    for (auto byte : data){
        BYTE t = _PRGA();
        result.push_back(byte ^ t);
    }
}

template <std::size_t KEY_SIZE>
void RC4<KEY_SIZE>::reset()
{
    _now_i = 0;
    _now_j = 0;

    _KSA();
}

} /* namespace marusa */

#endif /* ___RC4_H___ */
