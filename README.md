# op

*op* is a small library that allows you to define mathematical operations for your types easily. It is very useful to quickly add operations to [strong types](https://www.fluentcpp.com/2016/12/08/strong-types-for-strong-interfaces/):

```cpp
struct Radians
    : public op::Addable<Radians>      // Defines Radians + Radians and Radians += Radians. This is much simpler than implementing these operators yourself, and less error-prone
    , public op::Scalable<Radians>     // Defines Radians * float, float * Radians, and Radians *= float
    , public op::Subtractable<Radians> // Defines Radians - Radians and Radians -= Radians
    , public op::Negatable<Radians>    // Defines -Radians
{
    float value
};
```

This is very modular because – depending on the semantics of your type – some operations might not make sense. For example you can't multiply `Radians` with `Radians`, but you can multiply `Radians` with scalars (`float`s and `double`s).

## Including

To add this library to your project, simply add these two lines to your *CMakeLists.txt*:
```cmake
add_subdirectory(path/to/op)
target_link_libraries(${PROJECT_NAME} PRIVATE op::op)
```

Then include it as:
```cpp
#include <op/op.hpp>
```

## Usage

*op* is header-only! Simply `#include <op/op.hpp>` and you are good to go.

To add operations to your type it needs to inherit from the corresponding *op* class. Note that you need to pass your type as a template parameter to the *op* classes: this is the [CRTP pattern](https://www.fluentcpp.com/2017/05/12/curiously-recurring-template-pattern/).

Here are all the available operations:

```cpp
struct MyStrongType
    : public op::Addable<MyStrongType>      // Defines MyStrongType + MyStrongType and MyStrongType += MyStrongType. This is much simpler than implementing these operators yourself, and less error-prone
    , public op::Subtractable<MyStrongType> // Defines MyStrongType - MyStrongType and MyStrongType -= MyStrongType
    , public op::Negatable<MyStrongType>    // Defines -MyStrongType
    , public op::Scalable<MyStrongType>     // Defines MyStrongType * float, float * MyStrongType, and MyStrongType *= float
    , public op::Multipliable<MyStrongType> // Defines MyStrongType * MyStrongType and MyStrongType *= MyStrongType
{
    float value
};
```

## Running the tests

Simply use "tests/CMakeLists.txt" to generate a project, then run it.<br/>
If you are using VSCode and the CMake extension, this project already contains a *.vscode/settings.json* that will use the right CMakeLists.txt automatically.
