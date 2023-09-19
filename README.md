# Church Encoding in C++

This code demonstrates the use of Church Encoding to represent and manipulate non-negative integers (known as Church Numerals) using C++ lambdas.

**Curry Function**: A utility to curry given functions. It helps in the implementation of Church Encoding.

```cpp
   template<typename Func, typename... CapturedArgs>
   constexpr auto curry(Func func, CapturedArgs... captured);
```
