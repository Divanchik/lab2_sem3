#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
const char ltop(201);
const char lbottom(200);
const char rtop(187);
const char rbottom(188);
const char vline(186);
const char hline(205);
const char value1(178);
const char value0(249);
int trace = 0;
// Returns string length.
int strlen(const char *s)
{
    int i = 0;
    for (; *(s + i); i++)
        ;
    return i;
}
// Returns index of char in string. If NOT found, returns '-1'.
int find_char(const char c, const char *s)
{
    for (int i = 0; i < strlen(s); i++)
        if (s[i] == c)
            return i;
    return -1;
}
// Safe input of integer value.
void int_input(int &a, const char *s)
{
    char num[] = "0123456789 ";
    char buf[10];
    while (1)
    {
        cout << s << endl;
        fgets(buf, 10, stdin);
        for (int i = 0; i < strlen(buf); i++)
            if (find_char(buf[i], num) == -1)
            {
                cout << "Input cannot contain any characters!" << endl;
                continue;
            }
        a = atoi(buf);
        break;
    }
}
// Returns amount of char 'c' in string.
int count_char(const char c, const char *s)
{
    int i = 0;
    for (; *s; s++)
        if (c == *s)
            i += 1;
    return i;
}
// Returns True if 'n' is in interval ['a', 'b'].
int int_in(const int n, const int a, const int b)
{
    if (n >= a && n <= b)
        return 1;
    else
        return 0;
}
// Binary image class. Parameters: int **f, int n, int m, int prev_amount, int prev_coefficient.
class BinImage
{
    // Image array.
    int **f;
    int n, m;
    // Cache for amount of True values.
    int prev_amount;
    // Cache for coefficient.
    double prev_coefficient;
    // Delete image.
    void delete_f()
    {
        if (f != nullptr)
        {
            for (int i = 0; i < n; i++)
                free(f[i]);
            free(f);
        }
    }
    // Create image.
    void create_f(int a, int b)
    {
        f = (int **)malloc(a * sizeof(int));
        for (int i = 0; i < a; i++)
            f[i] = (int *)malloc(b * sizeof(int));
    }
    // Returns amount of True values.
    int count_1() const
    {
        int z = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (f[i][j])
                    z += 1;
        return z;
    }

public:
    // Fill image with random values.
    void fill_random()
    {
        if (f != nullptr)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    f[i][j] = rand() % 2;
    }
    // Fill image with 'fill' value.
    void fill_value(const int fill)
    {
        if (f != nullptr)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    f[i][j] = fill;
    }
    // Set height and width of image.
    void set_size(int a, int b)
    {
        n = a;
        m = b;
    }
    // Returns height of image.
    int _n() const { return n; }
    // Returns width of image.
    int _m() const { return m; }
    // Input method.
    void input()
    {
        if (trace)
            cout << "Input method!" << endl;
        if (n == 0 || m == 0) // checking if image size defined or not
        {
            std::cout << "Input height, then input width:" << std::endl;
            int_input(n, "Input height:");
            int_input(m, "Input width:");
            while (getchar() != '\n')
            {
            }
        }
        create_f(n, m);
        std::cout << "Input image(string by string):" << std::endl;
        char buf[m + 1];
        char buf1[2];
        for (int i = 0; i < n; i++)
        {
            fgets(buf, m + 1, stdin);
            while (getchar() != '\n')
            {
            }
            for (int j = 0; j < m; j++)
                f[i][j] = buf[j] - '0';
        }
    }
    // Output method.
    void output() const
    {
        if (trace)
            cout << "Output method!" << endl;
        cout << "Size: " << n << " x " << m << endl; // size output
        // head
        std::cout << ltop;
        for (int j = 0; j < m; j++)
            std::cout << hline;
        std::cout << rtop << std::endl;
        // body
        for (int i = 0; i < n; i++)
        {
            std::cout << vline;
            for (int j = 0; j < m; j++)
                if (f[i][j])
                    std::cout << value1;
                else
                    std::cout << value0;
            std::cout << vline << std::endl;
        }
        // bottom
        std::cout << lbottom;
        for (int j = 0; j < m; j++)
            std::cout << hline;
        std::cout << rbottom << std::endl;
    }
    // Default constructor.
    BinImage() : f(nullptr), n(0), m(0), prev_amount(-1), prev_coefficient(0)
    {
        if (trace)
            cout << "Default constructor!" << endl;
    }
    // Constructor, defining size and filling image with some value.
    BinImage(const int a, const int b, const int fill) : f(nullptr), n(a), m(b), prev_amount(-1), prev_coefficient(0)
    {
        if (trace)
            cout << "Constructor, defining size and filling image!" << endl;
        create_f(n, m);
        fill_value(fill);
    }
    // Copy constructor.
    BinImage(const BinImage &b) : f(nullptr), n(b._n()), m(b._m()), prev_amount(-1), prev_coefficient(0)
    {
        if (trace)
            cout << "Copying constructor!" << endl;
        create_f(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                f[i][j] = b(i, j);
    }
    // Move constructor.
    BinImage(BinImage &&b) : n(b._n()), m(b._m()), f(b.f), prev_amount(-1), prev_coefficient(0)
    {
        if (trace)
            cout << "Moving constructor!" << endl;
        b.f = nullptr;
    }
    // Destructor.
    ~BinImage()
    {
        if (trace)
            cout << "Destructor!" << endl;
        delete_f();
    }

    // Operators overload.

    // Access operator overload.
    int &operator()(const int a, const int b) const
    {
        if (int_in(a, 0, n - 1) && int_in(b, 0, m - 1))
            return f[a][b];
        else
        {
            cout << "Warning: index out of range!" << endl;
            return f[0][0];
        }
    }
    // Image * image operator overload.
    BinImage operator*(const BinImage &b)
    {
        BinImage tmp(n, m, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                tmp(i, j) = f[i][j] & b(i, j);
        return tmp;
    }
    // Image + image operator overload.
    BinImage operator+(const BinImage &b)
    {
        BinImage tmp(n, m, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                tmp(i, j) = f[i][j] | b(i, j);
        return tmp;
    }
    // Image * value operator overload.
    BinImage operator*(const int l)
    {
        BinImage tmp(n, m, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                tmp(i, j) = f[i][j] & l;
        return tmp;
    }
    // Image + value operator overload.
    BinImage operator+(const int l)
    {
        BinImage tmp(n, m, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                tmp(i, j) = f[i][j] | l;
        return tmp;
    }
    // Inverting operator overload.
    BinImage operator!()
    {
        BinImage tmp(n, m, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                tmp(i, j) = !(f[i][j]);
        return tmp;
    }
    // Calculating coefficient of filling.
    double coefficient()
    {
        if (trace)
            cout << "Coefficient method!" << endl;
        int true_amount = count_1();
        if (true_amount != prev_amount)
        {
            std::cout << "Cache recalculated!" << endl;
            prev_coefficient = (double)true_amount / (n * m);
            prev_amount = true_amount;
        }
        std::cout << "Cache returned!" << endl;
        return prev_coefficient;
    }
    // Copying assignment operator overload.
    BinImage &operator=(const BinImage &b)
    {
        if (trace)
            cout << "Copy assign overload!" << endl;
        if (&b == this)
            return *this;
        n = b._n();
        m = b._m();
        delete_f();
        create_f(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                f[i][j] = b(i, j);
        return *this;
    }
    // BinImage &operator=(BinImage &&b) // moving assignment operator overload
    // {
    //     if (trace)
    //         cout << "Move assign overload!" << endl;
    //     if (&b == this)
    //         return *this;
    //     n = b._n();
    //     m = b._m();
    //     delete_f();
    //     f = b.f;
    //     b.f = nullptr;
    //     return *this;
    // }

    // Output operator overload.
    friend std::ostream &operator<<(std::ostream &out, const BinImage &image)
    {
        image.output();
    }
};
// Value * image operator overload.
BinImage operator*(const int l, const BinImage &b)
{
    BinImage tmp(b._n(), b._m(), 0);
    for (int i = 0; i < b._n(); i++)
        for (int j = 0; j < b._m(); j++)
            tmp(i, j) = b(i, j) & l;
    return tmp;
}
// Value + image operator overload.
BinImage operator+(const int l, const BinImage &b)
{
    BinImage tmp(b._n(), b._m(), 0);
    for (int i = 0; i < b._n(); i++)
        for (int j = 0; j < b._m(); j++)
            tmp(i, j) = b(i, j) | l;
    return tmp;
}
int main()
{
    srand(time(NULL));
    trace = 1;
    BinImage a;
    a.set_size(2, 2);
    a.fill_random();
    BinImage b;
    b.set_size(2, 2);
    b.fill_random();
    BinImage c;
    cout << a + b << a * b << a * 0 << b + 1;
    return 0;
}