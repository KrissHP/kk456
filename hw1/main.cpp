#include <iostream>

char WhatByte(long long int byte, int i)
{
    byte = byte << (60 - i*4);
    byte = byte >> (60 - i*4);
    byte = byte >> i*4;
    byte &= 0b1111;
    char byte_char = byte;
    return byte_char;
}

int CountSimilarBytes(long long int byte)
{
    char numbers[16];
    int ans = 0, max;

    for(int i = 16; i>=0; i--)
        numbers[i] = WhatByte(byte, i);

    for(int i = 0; i<16; i++){
        max = 0;
        for(int j = 0; j<16; j += 2)
            if(numbers[i] == numbers[j] && numbers[i+1] == numbers[j+1] && ((numbers[i] == 0)^(numbers[i+1] == 0)))
                max++;
        if(max > ans)
            ans = max;
    }
    return ans;
}

void SwapBytes(unsigned short* byte)
{
    unsigned short a = *byte;
    a = a << 8;
    *byte = *byte >> 8;
    *byte = *byte | a;
}

unsigned char GetMaxByte(const unsigned int* ar, size_t size)
{
    unsigned char max_byte = 0x00;
    for(int i = 0; i<size; i++)
        for(int k = 0; k<8; k = k+2)
            if((ar[i] >> (24 - k*4)) & (0b11111111 > max_byte))
                max_byte = (ar[i] >> (24 - k*4))&0b11111111;
    return max_byte;
}
int main()
{
    long long int test_1 = 0x0000006789ABCDEF;
    printf("%d\n", CountSimilarBytes(test_1));

    unsigned short test_2 = 0xFF01;
    SwapBytes(&test_2);
    printf("%x\n", test_2);

    size_t size = 3;
    const unsigned int *test_arr =  new unsigned int[size]{0x010201ff, 0x07890909, 0x8899AABB};
    printf("%x", GetMaxByte(test_arr, size));
    return 0;
}
