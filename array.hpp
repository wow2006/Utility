#ifndef ARRAY_HPP
#define ARRAY_HPP
#include <cctype>
#include <cstring>
#include <cassert>
#include <ostream>
#include <iostream>
#include <initializer_list>

namespace utility
{
    using cint = const int;

    template<typename T, std::size_t SIZE>
    class array
    {
    public:
        static_assert(SIZE < 256, "Can not allocate array greater than 256\n");
        using iterator = T*;
        using citerator = const T*;
        static constexpr std::size_t size = SIZE;

        array(std::initializer_list<T> list) {
            assert(list.size() < 256);
            int i = 0;
            for(auto item : list)
            {
                mData[i++] = item;
            }
        }
        array() = default;
        array(const array&) = delete;
        array(array&&) = delete;

        array& operator=(array&) = delete;
        array& operator=(array&& _that) = delete;

        iterator begin() { return &mData[0]; }
        citerator begin() const { return &mData[0]; }

        iterator end() { return &mData[SIZE]; }
        citerator end() const { return &mData[SIZE]; }

        T& operator[](cint _index) { return mData[_index]; }
        const T& operator[](cint _index) const { return mData[_index]; }

    protected:
        T mData[SIZE];
    };

    template<typename T, std::size_t SIZE>
    static std::ostream& operator<<(std::ostream& _stream, const array<T, SIZE>& _array)
    {
        for(auto item : _array){
            _stream << item << ' ';
        }
        _stream << '\n';
        return _stream;
    }

    template<typename T, std::size_t SIZE>
    static double sum(const array<T, SIZE>& _array)
    {
        double temp = 0.0;
        for(auto item : _array)
        { temp += item; }
        return temp;
    }
}
#endif//!ARRAY_HPP
