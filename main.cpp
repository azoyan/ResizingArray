#include <iostream>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <string>
#include <vector>
#include <cassert>

#include "ResizingArray.hpp"

template<typename T>
void print(
    T & _container
  )
{
  const auto length = _container.size();
  for (unsigned int i = 0; i < length; ++i)
  {
    std::cout << _container[i] << " ";
  }
  std::cout << "\n\n";
}

template<typename T>
bool hasDifference(
    const ResizingArray<T> & _array,
    const std::vector<T> & _vector
  )
{
  const auto arraySize = _array.size();
  const auto vecSize = _vector.size();
  const auto vecCapacity = _vector.capacity();
  const auto arrayCapacity = _array.capacity();

  bool isEqualSizes = arraySize == vecSize;
  bool isEqualCapacities = arrayCapacity == vecCapacity;
  bool ok = isEqualSizes && isEqualCapacities;
  if (ok)
  {
    for (unsigned int i = 0; i < _array.size(); ++i)
    {
      ok = ok && _array[i] == _vector.at(i);
    }
  }
  assert(ok);
  return !ok;
}

bool fillingTest(
    ResizingArray<int> & _array,
    std::vector<int>  & _standartVec,
    unsigned int count = 20
  )
{
  for (unsigned int i = 0; i < count; ++i)
  {
    int value = rand() % 100;
    _array.push_back(value);
    _standartVec.push_back(value);
  }
  return !hasDifference(_array, _standartVec);
}

template<typename T>
bool sortingTest(
    ResizingArray<T> & _array,
    std::vector<T> & _standartVec
  )
{
  std::sort(_array.begin(), _array.end());
  std::sort(_standartVec.begin(), _standartVec.end());
  return !hasDifference(_array, _standartVec);
}

bool eraseItemsTest(
    ResizingArray<int> & _array,
    std::vector<int> & _standartVec
  )
{
  for (unsigned int i = _array.size() - 1; i > 0; --i)
  {
    if (1 == i % 2)
    {
      _array.erase(i);
      _standartVec.erase(_standartVec.begin() + i);
    }
  }
  return !hasDifference(_array, _standartVec);
}

bool insertItemsTest(
    ResizingArray<int> & _array,
    std::vector<int> & _standartVec
  )
{
  for (unsigned int i = 0; i < 10; ++i)
  {
    unsigned int index = rand() % _array.size();
    unsigned int value = rand() % 100;
    _array.insert(index, value);
    _standartVec.insert(_standartVec.begin() + index, value);
  }
  return !hasDifference(_array, _standartVec);
}

template<typename T>
bool copyConstructorTest(
    ResizingArray<T> & _array,
    std::vector<T> & _standartVec
  )
{
  auto arr = _array;
  auto vec = _standartVec;
  return !hasDifference(arr, vec);
}

template<typename T>
bool moveConstructorTest(
    ResizingArray<T> _array,
    std::vector<T> _standartVec
  )
{
  auto arr = std::move(_array);
  auto vec = std::move(_standartVec);
  assert(nullptr == _array.data() && nullptr == _standartVec.data());
  return (nullptr == _array.data()) && (nullptr == _standartVec.data());
}

template<typename T>
bool copyAssignmentOperatorTest(
    ResizingArray<T> _array,
    std::vector<T> _standartVec
  )
{
  {
    ResizingArray<T> arr2;
    arr2 = _array;
    std::vector<T> vec2;
    vec2 = _standartVec;
  }
  _array[0] = _standartVec[0];
  return !hasDifference(_array, _standartVec);
}

template<typename T>
bool moveAssignmentOperatorTest(
    ResizingArray<T> _array,
    std::vector<T> _standartVec
  )
{
  {
    ResizingArray<T> arr2;
    arr2 = std::move(_array);
    std::vector<T> vec2;
    vec2 = std::move(_standartVec);
  }
  assert(nullptr == _array.data());
  assert(nullptr == _standartVec.data());
  return (nullptr == _array.data()) && (nullptr == _standartVec.data());
}

template<typename T>
bool popBackTest(
    ResizingArray<T> & _array,
    std::vector<T> & _standardVec
  )
{
  while (!_array.empty() && !_standardVec.empty())
  {
    _array.pop_back();
    _standardVec.pop_back();
  }
  return !hasDifference(_array, _standardVec);
}

template<typename T>
bool modifyItemsTest(
    ResizingArray<T> & _array,
    std::vector<T> & _standartVec,
    T _value
  )
{
  _array[0] = _value;
  _standartVec[0] = _value;
  return !hasDifference(_array, _standartVec);
}

std::string generateLowercaseString(
    unsigned int length = 0
  )
{
  if (length == 0)
  {
    length = 1 + rand() % 5;
  }
  std::string result;
  for (unsigned int i = 0; i < length; ++i)
  {
    result.push_back(static_cast<char>(97 + rand() % 26));
  }
  return result;
}

bool fillingTest(
    ResizingArray<std::string> & _array,
    std::vector<std::string> & _standartVec
  )
{
  for (unsigned int i = 0; i < 20; ++i)
  {
    const std::string s = generateLowercaseString();
    _array.push_back(s);
    _standartVec.push_back(s);
  }
  return !hasDifference(_array, _standartVec);
}

bool hasSymbols(
    const std::string& str
  )
{
  if (str.find('a') != std::string::npos) return true;
  if (str.find('b') != std::string::npos) return true;
  if (str.find('c') != std::string::npos) return true;
  if (str.find('d') != std::string::npos) return true;
  if (str.find('e') != std::string::npos) return true;
  return false;
}

bool eraseItemsTest(
    ResizingArray<std::string> & _array,
    std::vector<std::string> & _standartVec
  )
{
  for (unsigned int i = _array.size(); i > 0; --i)
  {
    const std::string& str = _array.at(i - 1);
    if (hasSymbols(str))
    {
      _array.erase(i - 1);
      _standartVec.erase(_standartVec.begin() + i - 1);
    }
  }
  return !hasDifference(_array, _standartVec);
}

bool insertItemsTest(
    ResizingArray<std::string> & _array,
    std::vector<std::string> & _standartVec
  )
{
  for (unsigned int i = 0; i < 3; ++i)
  {
    unsigned int index = rand() % _array.size();
    std::string value = generateLowercaseString();

    _array.insert(index, value);
    _standartVec.insert(_standartVec.begin() + index, value);
  }
  return !hasDifference(_array, _standartVec);
}

template<typename T>
bool outOfRangeTest(
    ResizingArray<T> & _array,
    std::vector<T> & _standartVector
  )
{
  int n = 0;
  while (n < 2) {
    switch (n)
    {
      case 0:
        try { _array.at(2); }
        catch (const std::out_of_range&) { ++n; }
        break;
      case 1:
        try { _standartVector.at(2); }
        catch (const std::out_of_range&) { ++n; }
        break;
      default:
        return false;
    }
  }
  return n == 2;
}


bool isIntegersTestsPassed()
{
  bool ok = true;
  ResizingArray<int> array;
  std::vector<int> vec;
  ok = fillingTest(array, vec);
  std::cout << ok << " - Test 1.1. Adding in the cycle 20 random numbers in the range from 0 to 100" << std::endl;
  print(array);

  ok = ok && sortingTest(array, vec);
  std::cout << ok << " - Test 1.2. Ordering the resulting array of numbers in ascending order" << std::endl;
  print(array);

  ok = ok && eraseItemsTest(array, vec);
  std::cout << ok << " - Test 1.3. Remove each 2 items" << std::endl;
  print(array);

  ok = ok && insertItemsTest(array, vec);
  std::cout << ok << " - Test 1.4. Insert 10 random numbers in the range from 0 to 100 at random positions" << std::endl;
  print(array);

  ok = ok && copyConstructorTest(array, vec);
  std::cout << ok << " - Copy Constructor Test" << std::endl;
  ok = ok && copyAssignmentOperatorTest(array, vec);
  std::cout << ok << " - Copy Assignment Operator Test" << std::endl;
  ok = ok && moveConstructorTest(array, vec);
  std::cout << ok << " - Move Constructor Test" << std::endl;
  ok = ok && moveAssignmentOperatorTest(array, vec);
  std::cout << ok << " - Move Assignment Operator Test" << std::endl;

  ok = ok && modifyItemsTest(array, vec, 666);
  std::cout << ok << " - Modify items Test" << std::endl;
  print(array);

  ok = ok && popBackTest(array, vec);
  std::cout << ok << " - Pop back from containers" << std::endl;
  print(array);

  ok = ok && outOfRangeTest(array, vec);
  std::cout << ok << " - Out of range Test" << std::endl;

  return ok;
}

bool isStringsTestPassed()
{
  bool ok = true;
  ResizingArray<std::string> array;
  std::vector<std::string> vec;

  ok = fillingTest(array, vec);
  std::cout << ok << " - Test 2.1. Adding in the cycle 15 randomly selected words, consisting of Latin letters in lowercase" << std::endl;
  print(array);

  ok = ok && sortingTest(array, vec);
  std::cout << ok << " - Test 2.2. Ordering the resulting set of words in ascending order" << std::endl;
  print(array);

  ok = ok && eraseItemsTest(array, vec);
  std::cout << ok << " - Test 2.3. Delete each word that includes any of the letters a, b, c, d, e" << std::endl;
  print(array);

  ok = ok && insertItemsTest(array, vec);
  std::cout << ok << " - Test 2.4. Insert 3 new randomly selected words into random positions" << std::endl;
  print(array);

  ok = ok && copyConstructorTest(array, vec);
  std::cout << ok << " - Copy Constructor Test" << std::endl;
  ok = ok && copyAssignmentOperatorTest(array, vec);
  std::cout << ok << " - Copy Assignment Operator Test" << std::endl;
  ok = ok && moveConstructorTest(array, vec);
  std::cout << ok << " - Move Constructor Test" << std::endl;
  ok = ok && moveAssignmentOperatorTest(array, vec);
  std::cout << ok << " - Move Assignment Operator Test" << std::endl;

  ok = ok && modifyItemsTest(array, vec, std::string("c++"));
  std::cout << ok << " - Modify items Test" << std::endl;
  print(array);

  ok = ok && popBackTest(array, vec);
  std::cout << ok << " - Pop back Test" << std::endl;
  print(array);

  ok = ok && outOfRangeTest(array, vec);
  std::cout << ok << " - Out of range Test\n" << std::endl;

  return ok;
}

int main()
{
  srand(unsigned(time(0)));
  std::cout << std::boolalpha;
  bool isIntegersTestsOk = isIntegersTestsPassed();
  bool isStringsTestsOk = isStringsTestPassed();
  bool isAllTestsOk = isIntegersTestsOk && isStringsTestsOk;
  std::cout << isIntegersTestsOk << " - Integers tests passed?\n";
  std::cout << isStringsTestsOk << " - Strings tests passed?\n";
  std::cout << isAllTestsOk << " - All test passed?\n";
  return 0;
}
