#ifndef STRING_UTILITY_HPP
#define STRING_UTILITY_HPP
#include <iostream>
#include <string>
#include <cstring>

namespace utility
{
    static inline void swap(char& _a, char& _b)
    {
        _a = _a ^ _b;
        _b = _a ^ _b;
        _a = _a ^ _b;
    }

    static void reverse(std::string& _input)
    {
        const std::size_t stringLen = _input.size();
        for(int i = 0; i < static_cast<int>(stringLen/2); ++i)
        {
            swap(_input[i], _input[stringLen-i-1]);
        }
    }

    static void reverse(char* _pInput)
    {
        const int stringLen = strlen(_pInput);
        for(int i = 0; i < stringLen/2; ++i)
        {
            swap(_pInput[i], _pInput[stringLen-i-1]);
        }
    }

    static inline bool isRotated(const std::string& _a,
                          const std::string& _b)
    {
        return !(_a.empty() || _b.empty()) && (_a.size() == _b.size()) && ((_a+_a).find(_b) != std::string::npos);
    }
}
#endif//!STRING_UTILITY_HPP

