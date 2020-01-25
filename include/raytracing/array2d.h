#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <vector>

template <class T>
class Array2D
{
public:
    Array2D() = default;
    Array2D(size_t size1, size_t size2);
    Array2D(size_t size1, size_t size2, T initVal);

    ~Array2D() = default;

    Array2D(const Array2D&) = default;
    Array2D& operator=(const Array2D&) = default;
    Array2D(Array2D&&) noexcept = default;
    Array2D& operator=(Array2D&&) noexcept = default;

    size_t size1() const;
    size_t size2() const;

    T& operator()(size_t index1, size_t index2);
    const T& operator()(size_t index1, size_t index2) const;

    T* data() const;

private:
    size_t m_size1 {0};
    size_t m_size2 {0};
    std::vector<T> m_data {0};
};

template <class T>
Array2D<T>::Array2D(size_t size1, size_t size2) : m_size1(size1), m_size2(size2), m_data(m_size1 * m_size2)
{
}

template <class T>
Array2D<T>::Array2D(size_t size1, size_t size2, T initVal) :
    m_size1(size1), m_size2(size2), m_data(size1 * size2, initVal)
{
}

template <class T>
size_t Array2D<T>::size1() const
{
    return m_size1;
}

template <class T>
size_t Array2D<T>::size2() const
{
    return m_size2;
}

template <class T>
T& Array2D<T>::operator()(size_t index1, size_t index2)
{
    return m_data[index1 * m_size2 + index2];
}

template <class T>
const T& Array2D<T>::operator()(size_t index1, size_t index2) const
{
    return m_data[index1 * m_size2 + index2];
}

template <class T>
T* Array2D<T>::data() const
{
    return m_data.data();
}

#endif  // ARRAY2D_H
