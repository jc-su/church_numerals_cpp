#include <iostream>

// Curry: λf.λx.f x
template<typename Func, typename... CapturedArgs>
constexpr auto curry(Func func, CapturedArgs... captured) {
    return [func, ... captured = std::move(captured)](auto x) {
        if constexpr (std::is_invocable_v<Func, CapturedArgs..., decltype(x)>) {
            return func(captured..., x);
        } else {
            return curry(func, captured..., x);
        }
    };
}

// Zero: λf.λz.z
constexpr auto zero = curry([](auto f, auto z) { return z; });

// Successor: λn.λf.λz.f(n f z)
constexpr auto succ = curry([](auto n, auto f, auto z) { return f(n(f)(z)); });

// Addition: λm.λn.λf.λz.m f (n f z)
constexpr auto add =
        curry([](auto m, auto n, auto f, auto z) { return m(f)(n(f)(z)); });

// Multiplication: λm.λn.λf.m(n f)
constexpr auto mul = curry([](auto m, auto n, auto f) { return m(n(f)); });

// Separate overload for the pipe operator
template<typename Numeral, typename Adaptor>
constexpr auto operator||(Numeral n, Adaptor adaptor) {
    return adaptor(n);
}

int main() {
    auto one = zero || succ;
    auto two = zero || succ || succ;

    auto three = add(one)(two);
    auto seven = mul(two)(three) || succ;
    auto four = mul(two)(two);

    // Utility to convert Church numeral to integer
    auto to_int = [](auto n) { return n([](int x) { return x + 1; })(0); };

    std::cout << "One: " << to_int(one) << std::endl;     // Outputs: 1
    std::cout << "Two: " << to_int(two) << std::endl;     // Outputs: 2
    std::cout << "Three: " << to_int(three) << std::endl; // Outputs: 3
    std::cout << "Seven: " << to_int(seven) << std::endl; // Outputs: 7
    std::cout << "Four: " << to_int(four) << std::endl; //output: 4
}
