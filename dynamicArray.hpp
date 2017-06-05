/**
* @file dynamicArray.hpp
* @Synopsis Implement dynamic array
* inspired by https://github.com/Robbepop/dynarray/blob/master/dynarray.hpp
* @author Ahmed Abd El-Aal <eng.ahmedhussein89@gmail.com>
* @version 0.1
* @date 2017-06-05
*/
#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP
#include <memory>
#include <iostream>
#include <initializer_list>

template <typename T>
class dynamicArray {
public:
    // type alias
    /**
     * @defgroup Type alias
     * @{
     */
    using value_type = T;
    using dArray = dynamicArray<T>;
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    /**  @} */

    /**
     * @defgroup Constructors
     * @{
     */
    dynamicArray();
    dynamicArray(size_type _size);
    dynamicArray(size_type _size, const T _value);
    dynamicArray(const dArray& _that);
    dynamicArray(dArray&& _that);
    dynamicArray(std::initializer_list<T> list);
    /**  @} */

    bool empty() const { return m_size == 0; }


    size_type size() { return m_size; }
    size_type size() const { return m_size; }

    /**
     * @defgroup Operators
     * @{
     */
    dynamicArray<T>& operator=(const dArray& _that) {
        m_data.reset(new T[_that.m_size]);
        std::copy(begin(), end(), _that.begin());
        return *this;
    }
    dynamicArray<T>& operator=(dArray&& _that) {
        m_size = _that.m_size;
        _that.m_size = 0;
        m_data = std::move(_that.m_data);
        return *this;
    }
    dynamicArray<T>& operator=(std::initializer_list<T> _list) {
        if (m_size != _list.size()) {
            m_data.reset(new T[_list.size()]);
            m_size = _list.size();
        }
        std::copy(_list.begin(), _list.end(), begin());
    }
    reference operator[](const std::size_t _index) { return m_data[_index]; }
    const_reference operator[](const std::size_t _index) const {
        return m_data[_index];
    }
    /** @} */

    /**
     * @defgroup Access
     * @{
     */
    reference at(size_type pos);
    const_reference at(size_type pos) const;

    reference front();
    const_reference front() const;

    reference back();
    const_reference back() const;

    pointer data();
    const_pointer data() const;
    /** @} */

    /**
     * @defgroup Iterators
     * @{
     */
    iterator begin() { return m_data.get(); }
    const_iterator begin() const { return m_data.get(); }

    const_iterator cbegin() const { return m_data.get(); }

    reverse_iterator rbegin() { return std::reverse_iterator<iterator>(end()); }
    const_reverse_iterator rbegin() const {
        return std::reverse_iterator<iterator>(end());
    }

    const_reverse_iterator crbegin() const {
        return std::reverse_iterator<iterator>(cend());
    }

    iterator end() { return m_data.get() + m_size; }
    const_iterator end() const { return m_data.get() + m_size; }

    const_iterator cend() const { return m_data.get() + m_size; }

    reverse_iterator rend() { return std::reverse_iterator<iterator>(begin()); }
    reverse_iterator rend() const {
        return std::reverse_iterator<iterator>(begin());
    }

    const_reverse_iterator crend() const {
        return std::reverse_iterator<iterator>(cbegin());
    }
    /** @} */

    /**
     * @defgroup Modifiers
     * @{
     */
    void clear() { m_data.reset(nullptr); }

    void resize(const std::size_t _newSize) {
        if (m_size != _newSize) {
            m_data.reset(new T[_newSize]);
            m_size = _newSize;
        }
    }

    // TODO Implement http://en.cppreference.com/w/cpp/container/vector
    /** @} */

protected:
    std::unique_ptr<T[]> m_data;
    std::size_t m_size;
};

template <typename T>
dynamicArray<T>::dynamicArray() : m_size(0) {}

template <typename T>
dynamicArray<T>::dynamicArray(size_type _size)
    : m_data{new T[_size]}, m_size{_size} {}

template <typename T>
dynamicArray<T>::dynamicArray(size_type _size, const T _value)
    : m_data{new T[_size]}, m_size{_size} {
    std::fill(begin(), end(), _value);
}

template <typename T>
dynamicArray<T>::dynamicArray(const dynamicArray<T>& _that)
    : m_data(new T[_that.size()]), m_size(_that.size()) {
    std::copy(_that.begin(), _that.end() + 1, begin());
}

template <typename T>
dynamicArray<T>::dynamicArray(dynamicArray<T>&& _that)
    : m_data(std::move(_that.m_data)), m_size(_that.size()) {}

template <typename T>
dynamicArray<T>::dynamicArray(std::initializer_list<T> _list)
    : m_data(new T[_list.size()]), m_size(_list.size()) {
    std::move(_list.begin(), _list.end(), begin());
}

template <typename T>
std::ostream& operator<<(std::ostream& _stream, const dynamicArray<T>& _array) {
    for (int i = 0; i < _array.size() - 1; ++i) _stream << _array[i] << ' ';
    _stream << _array[_array.size() - 1];
}
#endif  //! DYNAMIC_ARRAY_HPP
