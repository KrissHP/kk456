#include "task_rk1.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <cstdint>
#include <cmath>
#include <bitset>
#include <cstring> 
long long int GetMantissa(float number) {
    // Получаем битовое представление числа
    uint32_t bits = *reinterpret_cast<uint32_t*>(&number);

    // Маска для извлечения мантиссы
    const uint32_t mantissaMask = 0x007FFFFF;

    // Извлекаем мантиссу с помощью маски
    uint32_t mantissaBits = bits & mantissaMask;

    // Добавляем неявный единичный бит
    mantissaBits |= (1 << 23);

    // Приводим мантиссу к типу long long int
    long long int mantissaLL = mantissaBits;

    return mantissaLL;
}

void SeparateFloat(float number, const char* fileName) {
    // Открываем файл для записи
    std::ofstream outFile(fileName);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file " << fileName << " for writing." << std::endl;
        return;
    }

    // Записываем вещественное число
    outFile << "Вещественное число" << std::endl << number << std::endl;

    // Получаем битовое представление числа
    uint32_t bits = *reinterpret_cast<uint32_t*>(&number);

    // Извлекаем знак, экспоненту и мантиссу
    uint32_t sign = (bits >> 31) & 0x1;
    int32_t exponent = static_cast<int32_t>((bits >> 23) & 0xFF) - 127;
    uint32_t mantissa = bits & 0x7FFFFF;

    // Записываем целую часть в бинарном и шестнадцатеричном форматах
    outFile << std::bitset<1>(sign) << "\t" << std::hex << std::setw(8) << std::setfill('0') << bits << std::endl;

    // Записываем степень в бинарном и шестнадцатеричном форматах
    outFile << std::bitset<8>(exponent) << "\t" << std::hex << std::setw(2) << std::setfill('0') << exponent << std::endl;

    // Записываем мантиссу в бинарном и шестнадцатеричном форматах
    outFile << std::bitset<23>(mantissa) << "\t" << std::hex << std::setw(6) << std::setfill('0') << mantissa << std::endl;

    // Закрываем файл
    outFile.close();
}

char* convertBinToHex(const char* binNum) {
    // Проверяем, что передана непустая строка
    if (binNum == nullptr || *binNum == '\0') {
        std::cerr << "Error: Empty input string." << std::endl;
        return nullptr;
    }

    // Определяем длину входной строки
    size_t len = strlen(binNum);

    // Проверяем, что длина строки не превышает 64 символа
    if (len > 64) {
        std::cerr << "Error: Input string exceeds maximum length of 64 bits." << std::endl;
        return nullptr;
    }

    // Создаем динамический массив для шестнадцатеричного числа (максимальный размер - половина длины входной строки)
    char* hexNum = new char[len / 4 + 1];
    hexNum[len / 4] = '\0'; // Устанавливаем завершающий нуль-символ

    // Проходим по входной строке и конвертируем каждую тетраду в шестнадцатеричное число
    for (size_t i = 0; i < len / 4; ++i) {
        int hexDigit = 0;
        // Вычисляем значение для текущей тетрады
        for (size_t j = 0; j < 4; ++j) {
            hexDigit <<= 1; // Сдвигаем на один разряд влево
            if (binNum[i * 4 + j] == '1') {
                hexDigit |= 1; // Устанавливаем младший бит, если текущий символ - '1'
            } else if (binNum[i * 4 + j] != '0') {
                std::cerr << "Error: Invalid input binary digit." << std::endl;
                delete[] hexNum; // Освобождаем память, выделенную для hexNum
                return nullptr;
            }
        }
        // Конвертируем значение в символ шестнадцатеричной цифры и записываем в выходной массив
        hexNum[i] = (hexDigit < 10) ? ('0' + hexDigit) : ('A' + hexDigit - 10);
    }

    return hexNum;
}
void ConvertDecToHex(int dec, char* hex) {
    // Проверяем, что указатель hex не равен nullptr
    if (hex == nullptr) {
        std::cerr << "Error: Null pointer passed for hex string." << std::endl;
        return;
    }

    // Конвертируем десятичное число в шестнадцатеричное
    std::string hexString = "";
    while (dec > 0) {
        int remainder = dec % 16;
        char hexDigit;
        if (remainder < 10) {
            hexDigit = '0' + remainder;
        } else {
            hexDigit = 'A' + (remainder - 10);
        }
        hexString += hexDigit;
        dec /= 16;
    }

    // Реверсируем строку, чтобы получить правильный порядок цифр шестнадцатеричного числа
    std::reverse(hexString.begin(), hexString.end());

    // Копируем шестнадцатеричное представление в строку char*
    strcpy(hex, hexString.c_str());
}
void swap(char& a, char& b) {
    char temp = a;
    a = b;
    b = temp;
}

void ChangeLSB(char* binNumber) {
    // Проверяем, что передана непустая строка
    if (binNumber == nullptr || *binNumber == '\0') {
        std::cerr << "Error: Empty input string." << std::endl;
        return;
    }

    // Определяем длину строки
    size_t len = strlen(binNumber);

    // Проходим по строке и меняем порядок следования бит
    for (size_t i = 0; i < len / 2; ++i) {
        swap(binNumber[i], binNumber[len - i - 1]);
    }
}