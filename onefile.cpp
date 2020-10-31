/**
 * \file
 * \brief Whole program in one file
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
/// Enable/disable logging
bool trace = false;
/**
 * Print message if logging enabled
 * \param[in] s Message
 */
void log(const char* s)
{
    if (trace)
        std::cout << s;
}
/// \return Length of string.
int strlen(const char *s)
{
    int i = 0;
    for (; *(s + i); i++)
        ;
    return i;
}
/**
 * \param[in] s String
 * \param[in] c Character that you want to find
 * \return Index of char in string or '-1' if NOT found
 */
int find_char(const char c, const char *s)
{
    for (int i = 0; i < strlen(s); i++)
        if (s[i] == c)
            return i;
    return -1;
}
/**
 * Safe integer input
 * \param[out] a Integer
 * \param[in] s Message
 */
void int_input(int &a, const char *s)
{
    char num[] = "0123456789 ";
    char buf[10];
    while (1)
    {
        cout << s << endl;
        fgets(buf, 10, stdin);
        while (getchar() != '\n');
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
/**
 * \param[in] s String
 * \param[in] c Character that you want to count
 * \return Amount of char in string
 */
int count_char(const char c, const char *s)
{
    int i = 0;
    for (; *s; s++)
        if (c == *s)
            i += 1;
    return i;
}
/// \return True if 'n' is in interval ['a', 'b']
int int_in(const int n, const int a, const int b)
{
    if (n >= a && n <= b)
        return 1;
    else
        return 0;
}
/**
 * \brief Binary image class
 * 
 * 
*/
class BinImage
{
    /// Image array
    bool **f;
    int n, m;
    /// Cache for amount of 'true' values
    bool is_image_changed;
    /// Cache for coefficient
    double cache_coefficient;
    /// Free image array
    void delete_f()
    {
        if (!(_is_created()))
        {
            for (int i = 0; i < n; i++)
                free(f[i]);
            free(f);
        }
    }
    /// Create image array
    void create_f(int a, int b)
    {
        if (_is_created())
            f = (bool **)malloc(a * sizeof(bool));
            for (int i = 0; i < a; i++)
                f[i] = (bool *)malloc(b * sizeof(bool));
    }
    
    
public:
    /// \return Amount of true values in image
    int count_true()
    {
        int z = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (f[i][j])
                    z += 1;
        return z;
    }
    /// Fill image with 'fill' value.
    void fill_value(const int fill)
    {
        if (_is_created())
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    f[i][j] = fill;
    }
    // Set height and width of image.
    void resize(int new_height, int new_width)
    {
        f = (bool **)realloc(f, new_height * sizeof(bool));
        for (int i = 0; i < new_height; i++)
            f[i] = (bool *)realloc(f[i], new_width * sizeof(bool));
        n = new_height;
        m = new_width;
    }
    // Returns height of image.
    int _n() const { return n; }
    // Returns width of image.
    int _m() const { return m; }
    // Returns true if image is changed.
    bool _is_image_changed() const {return is_image_changed;}
    // Returns true if size of image is defined.
    bool _is_created() const { return (n==0 || m==0) ? false : true;}
    double _cache() const {return cache_coefficient;}
    // Input method.
    void input()
    {
        log("Input method!\n");
        if (!(_is_created()))
        {
            std::cout << "Input height, then input width:" << std::endl;
            int_input(n, "Input height:");
            int_input(m, "Input width:");
            while (getchar() != '\n');
            resize(n,m);
        }
        std::cout << "Input image(string by string):" << std::endl;
        char buf[m + 1];
        char buf1[2];
        for (int i = 0; i < n; i++)
        {
            fgets(buf, m + 1, stdin);
            while (getchar() != '\n');
            for (int j = 0; j < m; j++)
                f[i][j] = buf[j] - '0';
        }
    }
    // Output method.
    void output() const
    {
        log("Output method!\n");
        if (trace)
            cout << "Size: " << n << " x " << m << endl; // size output
        // head
        for (int j = 0; j < m + 2; j++)
            std::cout << '=';
        std::cout << std::endl;
        // body
        for (int i = 0; i < n; i++)
        {
            std::cout << '|';
            for (int j = 0; j < m; j++)
                if (f[i][j])
                    std::cout << '#';
                else
                    std::cout << '.';
            std::cout << '|' << std::endl;
        }
        // bottom
        for (int j = 0; j < m + 2; j++)
            std::cout << '=';
        std::cout << std::endl;
    }
    // Default constructor.
    BinImage() : f(nullptr), n(0), m(0), is_image_changed(true), cache_coefficient(0)
    {
        log("Default constructor!\n");
    }
    // Constructor, defining size and filling image with some value.
    BinImage(const int a, const int b, const int fill) : f(nullptr), n(a), m(b), is_image_changed(true), cache_coefficient(0)
    {
        log("Constructor, defining size and filling image!\n");
        create_f(n, m);
        fill_value(fill);
    }
    // Copy constructor.
    BinImage(const BinImage &b) : f(nullptr), n(b._n()), m(b._m()), is_image_changed(b._is_image_changed()), cache_coefficient(b._cache())
    {
        log("Copying constructor!\n");
        create_f(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                f[i][j] = b(i, j);
    }
    // Move constructor.
    BinImage(BinImage &&b) : n(b._n()), m(b._m()), f(b.f), is_image_changed(b._is_image_changed()), cache_coefficient(b._cache())
    {
        log("Moving constructor!\n");
        b.f = nullptr;
    }
    // Destructor.
    ~BinImage()
    {
        log("Destructor!\n");
        delete_f();
    }

    // Operators overload.

    // Access operator overload.
    bool operator()(const int a, const int b) const
    {
        if (int_in(a, 0, n - 1) && int_in(b, 0, m - 1))
            return f[a][b];
        else
        {
            log("Warning: index out of range!\n");
            return f[0][0];
        }
    }
    bool &operator()(const int a, const int b)
    {
        if (int_in(a, 0, n - 1) && int_in(b, 0, m - 1))
            return f[a][b];
        else
        {
            log("Warning: index out of range!\n");
            return f[0][0];
        }
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
        log("Coefficient method!\n");
        if (is_image_changed)
        {
            cache_coefficient = (double)count_true() / (n * m);
            is_image_changed = false;
            log("Cache recalculated!\n");
        }
        log("Cache returned!\n");
        return cache_coefficient;
    }
    // Copying assignment operator overload.
    BinImage &operator=(const BinImage &b)
    {
        log("Copy assign overload!\n");
        if (&b == this)
            return *this;
        n = b._n();
        m = b._m();
        resize(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                f[i][j] = b(i, j);
        return *this;
    }
    // Moving assignment operator overload.
    BinImage &operator=(BinImage &&b)
    {
        log("Move assign overload!\n");
        if (&b == this)
            return *this;
        n = b._n();
        m = b._m();
        delete_f();
        f = b.f;
        b.f = nullptr;
        return *this;
    }

    // Output operator overload.
    // friend std::ostream &operator<<(std::ostream &out, const BinImage &image)
    // {
    //     image.output();
    // }
};
std::ostream& operator<<(std::ostream& os, const BinImage& a)
{
    a.output();
    return os;
}
// Fill image with random values.
void fill_random(BinImage& a)
{
    if (a._is_created())
        for (int i = 0; i < a._n(); i++)
            for (int j = 0; j < a._m(); j++)
                a(i, j) = rand() % 2;
}
// Image * image operator overload.
BinImage operator*(const BinImage &a, const BinImage &b)
{
    BinImage tmp(a._n(), a._m(), 0);
    for (int i = 0; i < a._n(); i++)
        for (int j = 0; j < a._m(); j++)
            tmp(i, j) = a(i, j) & b(i, j);
    return tmp;
}
// Image + image operator overload.
BinImage operator+(const BinImage &a, const BinImage &b)
{
    BinImage tmp(a._n(), a._m(), 0);
    for (int i = 0; i < a._n(); i++)
        for (int j = 0; j < a._m(); j++)
            tmp(i, j) = a(i, j) | b(i, j);
    return tmp;
}
// Image * value operator overload.
BinImage operator*(const BinImage &a, const int l)
{
    BinImage tmp(a._n(), a._m(), 0);
    for (int i = 0; i < a._n(); i++)
        for (int j = 0; j < a._m(); j++)
            tmp(i, j) = a(i, j) & l;
    return tmp;
}
// Image + value operator overload.
BinImage operator+(const BinImage &a, const int l)
{
    BinImage tmp(a._n(), a._m(), 0);
    for (int i = 0; i < a._n(); i++)
        for (int j = 0; j < a._m(); j++)
            tmp(i, j) = a(i, j) | l;
    return tmp;
}
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
    trace = false;
    BinImage a;
    a.resize(1, 5);
    fill_random(a);
    BinImage b;
    b.resize(1, 5);
    fill_random(b);
    BinImage c;
    cout << a << b << endl;
    cout << a + b << a * b << a * 0 << b + 1;
    return 0;
}