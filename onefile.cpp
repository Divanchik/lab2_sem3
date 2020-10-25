#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
const char ltop(201);
const char lbottom(200);
const char rtop(187);
const char rbottom(188);
//const char vline(186);
const char vliner(186);
const char vlinel(186);
//const char hline(205);
const char hlineu(205);
const char hlined(205);
const char value1(178);
const char value0(249);
int trace = 0;
int strlen(const char *s) // string length
{
    int i = 0;
    for (; *(s + i); i++)
        ;
    return i;
}
int find_char(const char c, const char *s) // find char in string
{
    for (int i = 0; i < strlen(s); i++)
        if (s[i] == c)
            return i;
    return -1;
}
int char_in(const char c, const char *s) // checking if char is in string
{
    for (; *s; s++)
        if (*s == c)
            return 1;
    return 0;
}
void int_input(int &a, const char *s)
{
    char num[] = "0123456789 ";
    char buf[10];
    while (1)
    {
        cout << s << endl;
        fgets(buf, 10, stdin);
        for (int i = 0; i < strlen(buf); i++)
            if (!(char_in(buf[i], num)))
            {
                cout << "Input cannot contain any characters!" << endl;
                continue;
            }
        a = atoi(buf);
        break;
    }
}
int count_char(const char c, const char *s) // count all chars in string
{
    int i = 0;
    for (; *s; s++)
        if (c == *s)
            i += 1;
    return i;
}
int int_in(const int n, const int a, const int b) // checking if value fits the interval
{
    if (n >= a && n <= b)
        return 1;
    else
        return 0;
}
class BinImage
{
    int **f;
    int n, m;
    int prev_amount;         // cache for amount of 1
    double prev_coefficient; // cache for coefficient
    void delete_f()          //cleaning f
    {
        if (f != nullptr)
        {
            for (int i = 0; i < n; i++)
                free(f[i]);
            free(f);
        }
    }
    void create_f(int a, int b)
    {
        f = (int **)malloc(a * sizeof(int));
        for (int i = 0; i < a; i++)
            f[i] = (int *)malloc(b * sizeof(int));
    }
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
    void fill_random() // fill image with random values
    {
        if (f != nullptr)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    f[i][j] = rand() % 2;
    }
    void fill_value(const int fill) // filling image with some value
    {
        if (f != nullptr)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    f[i][j] = fill;
    }
    void set_size(int a, int b) // set size of image manually
    {
        n = a;
        m = b;
    }
    int _n() const { return n; } // return height
    int _m() const { return m; } // return width
    void input()                 // input method
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
    void output() const // output method
    {
        if (trace)
            cout << "Output method!" << endl;
        cout << "Size: " << n << " x " << m << endl; // size output
        // head
        std::cout << ltop;
        for (int j = 0; j < m; j++)
            std::cout << hlineu;
        std::cout << rtop << std::endl;
        // body
        for (int i = 0; i < n; i++)
        {
            std::cout << vlinel;
            for (int j = 0; j < m; j++)
                if (f[i][j])
                    std::cout << value1;
                else
                    std::cout << value0;
            std::cout << vliner << std::endl;
        }
        // bottom
        std::cout << lbottom;
        for (int j = 0; j < m; j++)
            std::cout << hlined;
        std::cout << rbottom << std::endl;
    }
    BinImage() : f(nullptr), n(0), m(0), prev_amount(-1), prev_coefficient(0) // default constructor
    {
        if (trace)
            cout << "Default constructor!" << endl;
    }
    BinImage(const int a, const int b, const int fill) : f(nullptr), n(a), m(b), prev_amount(-1), prev_coefficient(0) // constructor, defining size and filling image with some value
    {
        if (trace)
            cout << "Constructor, defining size and filling image!" << endl;
        create_f(n, m);
        fill_value(fill);
    }
    BinImage(const BinImage &b) : f(nullptr), n(b._n()), m(b._m()), prev_amount(-1), prev_coefficient(0) // copying constructor
    {
        if (trace)
            cout << "Copying constructor!" << endl;
        create_f(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                f[i][j] = b(i, j);
    }
    BinImage(BinImage &&b) : n(b._n()), m(b._m()), f(b.f), prev_amount(-1), prev_coefficient(0) // moving constructor
    {
        if (trace)
            cout << "Moving constructor!" << endl;
        b.f = nullptr;
    }
    ~BinImage() // destructor
    {
        if (trace)
            cout << "Destructor!" << endl;
        delete_f();
    }
    // operators overload
    int &operator()(const int a, const int b) const // access operator overload
    {
        if (int_in(a, 0, n - 1) && int_in(b, 0, m - 1))
            return f[a][b];
        else
        {
            cout << "Warning: index out of range!" << endl;
            return f[0][0];
        }
    }
    BinImage operator*(const BinImage &b) // image * image operator overload
    {
        BinImage tmp(n, m, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                tmp(i, j) = f[i][j] & b(i, j);
        return tmp;
    }
    BinImage operator+(const BinImage &b) // image + image operator overload
    {
        BinImage tmp(n, m, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                tmp(i, j) = f[i][j] | b(i, j);
        return tmp;
    }
    BinImage operator*(const int l) // image * value operator overload
    {
        BinImage tmp(n, m, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                tmp(i, j) = f[i][j] & l;
        return tmp;
    }
    BinImage operator+(const int l) // image + value operator overload
    {
        BinImage tmp(n, m, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                tmp(i, j) = f[i][j] | l;
        return tmp;
    }
    BinImage operator!() // inverting operator overload
    {
        BinImage tmp(n, m, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                tmp(i, j) = !(f[i][j]);
        return tmp;
    }
    double coefficient() // calculating coefficient of filling
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
    BinImage &operator=(const BinImage &b) // copying assignment operator overload
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
    friend std::ostream &operator<<(std::ostream &out, const BinImage &image) // output operator overload
    {
        image.output();
    }
};
BinImage operator*(const int l, const BinImage &b) // value * image operator overload
{
    BinImage tmp(b._n(), b._m(), 0);
    for (int i = 0; i < b._n(); i++)
        for (int j = 0; j < b._m(); j++)
            tmp(i, j) = b(i, j) & l;
    return tmp;
}
BinImage operator+(const int l, const BinImage &b) // value + image operator overload
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