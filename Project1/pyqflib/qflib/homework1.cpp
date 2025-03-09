#include <iostream>

using namespace std;

int main() {
    cout << "QFGB8960 Advanced C++ for Finance - Homework 1 Solutions\n\n";

    // 1. Sizes of Data
    cout << "1. Sizes of Data\n";
    cout << "   (a) Boolean size: " << sizeof(bool) * 8 << " bits\n";
    cout << "   (b) Double size: " << sizeof(double) * 8 << " bits\n\n";

    // 2. Integer Arithmetic
    cout << "2. Integer Arithmetic\n";
    int i = 3;
    int l = i / -2;
    int k = i % -2;
    cout << "   Output: " << l << " " << k << "\n\n";

    // 3. Integers and Logicals in Arithmetic
    cout << "3. Integers and Logicals\n";
    bool a = true, b = false;
    int x = 10, y = 5;
    int p = ((x | y) + (a + b));
    cout << "   Output: " << p << "\n\n";

    // 4. Pre/Post Increment
    cout << "4. Pre/Post Increment\n";
    i = 1;
    int j = (--i)++;
    cout << "   Output: " << i << " " << j << "\n\n";

    // 5. Short-Circuiting Logical Operations
    cout << "5. Short-Circuiting Logical Operations\n";
    int x1{ 0 }, y1{ 0 };
    if (x1 > 0 && ++y1) x1++;
    cout << "   Output: " << x1 << " " << y1 << "\n\n";

    // 6. Operator Overloading
    cout << "6. Operator Overloading\n";
    cout << "   (b) % - Can be overloaded\n";
    cout << "   (d) == - Can be overloaded\n\n";

    // 7. Reference Modification
    cout << "7. Reference Modification\n";
    int aRef = 9;
    int& aref = aRef;
    ++aRef;
    cout << "   Output: " << aref << "\n\n";

    // 8. Constructors and Destructors
    cout << "8. Constructors and Destructors\n";
    class A {
    public:
        A() { cout << "   1\n"; }
        ~A() { cout << "   2\n"; }
    };

    class B : public A {
    public:
        B() { cout << "   3\n"; }
        ~B() { cout << "   4\n"; }
    };

    {
        B b; // Object created and destructed in the scope
    }
    cout << "\n";

    // 9. Lambda Function
    cout << "9. Lambda Function\n";
    int x2 = 1;
    auto check = [&]() -> bool {
        --x2;
        return x2 != 0;
    };
    cout << "   Output: " << check() << " " << x2 << "\n\n";

    // 10. Template Functions
    cout << "10. Template Functions\n";
    template <typename T>
    void fun(const T& x) {
        static int count = 0;
        cout << "   " << x << " " << count << "\n";
        ++count;
    }

    fun<int>(1);
    fun<int>(2);
    fun<double>(1.2);
    
    return 0;
}
