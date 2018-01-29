#include <stdexcept>

inline unsigned int increaseCapacity(
    unsigned int capacity
  ) 
{
#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
  capacity = capacity * 2;
#elif defined(_MSC_VER)
  if (capacity == 1)
  {
    capacity++;
  }
  else
  {
    capacity = int(capacity * 1.5);
  }
#endif
  if (capacity == 0)
  {
    capacity = 1;
  }
  return capacity;
}

template <typename TData>
class ResizingArray
{
public:
  ResizingArray()
  : m_array(nullptr)
  , m_size(0)
  , m_capacity(0)
  {

  }

  ResizingArray(
      const ResizingArray & _array
    )
    : m_array(nullptr)
    , m_size(0)
    , m_capacity(0)
  {
    m_size = _array.size();
    m_capacity = m_size;

    m_array = new TData[m_size];
    for (unsigned int i = 0; i < m_size; ++i)
    {
      m_array[i] = _array[i];
    }
  }

  ResizingArray(
      ResizingArray && _array
    )
  : m_array(nullptr)
  , m_size(0)
  , m_capacity(0)
  {
    std::swap(m_size, _array.m_size);
    std::swap(m_capacity, _array.m_capacity);
    std::swap(m_array, _array.m_array);
  }

  const ResizingArray & operator=(
      const ResizingArray & _array
    )
  {
    if (this == &_array)
    {
      return *this;
    }
    ResizingArray tmp(_array);
    std::swap(*this, tmp);
    return *this;
  }

  const ResizingArray & operator=(
      ResizingArray && _array
    )
  {
    if (this == &_array)
    {
      return *this;
    }
    std::swap(m_size, _array.m_size);
    std::swap(m_capacity, _array.m_capacity);
    std::swap(m_array, _array.m_array);
    return *this;
  }

  ~ResizingArray()
  {
    delete[] m_array;
  }

  void push_back(
      const TData & _value
    )
  {
    if (m_size >= m_capacity)
    {
      m_capacity = increaseCapacity(m_capacity);
      reserve(m_capacity);
    }
    m_array[m_size] = _value;
    ++m_size;
  }

  void insert(
      unsigned int _index,
      const TData & _value
    )
  {
    if (_index < m_size)
    {
      push_back(m_array[m_size - 1]);

      for (unsigned int i = m_size - 1; i > _index; --i)
      {
        m_array[i] = m_array[i - 1];
      }
      m_array[_index] = _value;
    }
  }

  void erase(
      unsigned int _index
    )
  {
    if (_index < m_size)
    {
      m_array[_index].~TData();
      for (unsigned int i = _index; i < m_size - 1; ++i)
      {
        m_array[i] = m_array[i + 1];
      }
      --m_size;
    }
  }

  void reserve(
      unsigned int _capacity
    )
  {
    m_capacity = _capacity;
    TData* array = new TData[m_capacity]();
    for (unsigned int i = 0; i < m_size; ++i)
    {
      array[i] = m_array[i];
    }
    delete[] m_array;
    m_array = array;
  }

  void pop_back()
  {
    erase(m_size - 1);
  }

  bool empty() const
  {
    return m_size == 0;
  }

  void clear()
  {
    m_size = 0;
  }

  unsigned int size() const
  {
    return m_size;
  }

  unsigned int capacity() const
  {
    return m_capacity;
  }

  const TData & at(
      unsigned int _index
    ) const
  {
    if (_index < m_size)
    {
      return m_array[_index];
    }
    else
    {
      throw std::out_of_range("index out of range");
    }
  }

  TData & operator[](
      unsigned int _index
    ) const
  {
    return m_array[_index];
  }

  TData * data()
  {
    return m_array;
  }

  TData * begin() const
  {
    return m_array;
  }

  TData * end() const
  {
    return &m_array[m_size];
  }

protected:
  TData * m_array;
  unsigned int m_size;
  unsigned int m_capacity;
};
