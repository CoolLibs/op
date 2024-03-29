#pragma once

#include <iostream>

namespace op {

template<typename Derived>
class Scalable {
public:
    friend Derived operator*(float x, Derived derived)
    {
        return Derived{derived.value * x};
    }

    friend Derived operator*(Derived derived, float x)
    {
        return operator*(x, derived);
    }

    friend Derived operator/(Derived derived, float x)
    {
        return Derived{derived.value / x};
    }

    void operator*=(float x)
    {
        This().value *= x;
    }

    void operator/=(float x)
    {
        This().value /= x;
    }

private:
    Derived& This()
    {
        return *static_cast<Derived*>(this);
    }
};

template<typename Derived>
class Multipliable {
public:
    friend Derived operator*(Derived a, Derived b)
    {
        return Derived{a.value * b.value};
    }

    void operator*=(Derived x)
    {
        This().value *= x.value;
    }

private:
    Derived& This()
    {
        return *static_cast<Derived*>(this);
    }
};

template<typename Derived>
class Addable {
public:
    friend Derived operator+(Derived a, Derived b)
    {
        return Derived{a.value + b.value};
    }

    void operator+=(Derived x)
    {
        This().value += x.value;
    }

private:
    Derived& This()
    {
        return *static_cast<Derived*>(this);
    }
};

template<typename Derived>
class Subtractable {
public:
    friend Derived operator-(Derived a, Derived b)
    {
        return Derived{a.value - b.value};
    }

    void operator-=(Derived x)
    {
        This().value -= x.value;
    }

private:
    Derived& This()
    {
        return *static_cast<Derived*>(this);
    }
};

template<typename Derived>
class Negatable {
public:
    friend Derived operator-(Derived derived)
    {
        return Derived{-derived.value};
    }
};

// Even if we had C++20, we would need that over the defaulted == operator because the later doesn't work when inheriting from op's classes.
// (They can't define an operator == otherwise it would be ambiguous (NB: maybe if we use private inheritance this would solve the problem))
template<typename Derived>
class EqualityComparable {
public:
    friend auto operator==(Derived derived1, Derived derived2) -> bool
    {
        return derived1.value == derived2.value;
    }
};

template<typename Derived>
class Printable {
public:
    friend std::ostream& operator<<(std::ostream& os, Derived const& derived)
    {
        return os << derived.value;
    }
};

} // namespace op
