/**
 * \file
 * Binary Image library (source file)
 */
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "binimlib.h"

namespace binim
{
    void enable_logging()
    {
        trace = true;
    }
    void disable_logging()
    {
        trace = false;
    }
    void log(const char *s)
    {
        if (trace)
            std::cout << s;
    }
    int strlen(const char *s)
    {
        int i = 0;
        for (; *(s + i); i++)
            ;
        return i;
    }
    int find_char(const char c, const char *s)
    {
        for (int i = 0; i < strlen(s); i++)
            if (s[i] == c)
                return i;
        return -1;
    }
    void int_input(int &a, const char *s)
    {
        char num[] = "0123456789 ";
        char buf[10];
        while (1)
        {
            std::cout << s << std::endl;
            fgets(buf, 10, stdin);
            while (getchar() != '\n')
                ;
            for (int i = 0; i < strlen(buf); i++)
                if (find_char(buf[i], num) == -1)
                {
                    std::cout << "Input cannot contain any characters!" << std::endl;
                    continue;
                }
            a = atoi(buf);
            break;
        }
    }
    int count_char(const char c, const char *s)
    {
        int i = 0;
        for (; *s; s++)
            if (c == *s)
                i += 1;
        return i;
    }
    int int_in(const int n, const int a, const int b)
    {
        if (n >= a && n <= b)
            return 1;
        else
            return 0;
    }
    void BinImage::delete_f()
    {
        if (!(_is_created()))
        {
            for (int i = 0; i < n; i++)
                free(f[i]);
            free(f);
        }
    }
    void BinImage::create_f(int a, int b)
    {
        if (_is_created())
            f = (bool **)malloc(a * sizeof(bool));
        for (int i = 0; i < a; i++)
            f[i] = (bool *)malloc(b * sizeof(bool));
    }
    int BinImage::count_true() const
    {
        int z = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (f[i][j])
                    z += 1;
        return z;
    }
    void BinImage::fill_value(const bool fill)
    {
        if (_is_created())
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    f[i][j] = fill;
    }
    void BinImage::resize(int new_height, int new_width)
    {
        f = (bool **)realloc(f, new_height * sizeof(bool));
        for (int i = 0; i < new_height; i++)
            f[i] = (bool *)realloc(f[i], new_width * sizeof(bool));
        n = new_height;
        m = new_width;
    }
    int BinImage::_n() const { return n; }
    int BinImage::_m() const { return m; }
    bool BinImage::_is_image_changed() const { return is_image_changed; }
    bool BinImage::_is_created() const { return (n == 0 || m == 0) ? false : true; }
    double BinImage::_cache() const { return cache_coefficient; }
    void BinImage::input()
    {
        log("Input method!\n");
        if (!(_is_created()))
        {
            std::cout << "Input height, then input width:" << std::endl;
            int_input(n, "Input height:");
            int_input(m, "Input width:");
            while (getchar() != '\n')
                ;
            resize(n, m);
        }
        std::cout << "Input image(string by string):" << std::endl;
        char buf[m + 1];
        char buf1[2];
        for (int i = 0; i < n; i++)
        {
            fgets(buf, m + 1, stdin);
            while (getchar() != '\n')
                ;
            for (int j = 0; j < m; j++)
                f[i][j] = buf[j] - '0';
        }
    }
    void BinImage::output() const
    {
        log("Output method!\n");
        if (trace)
            std::cout << "Size: " << n << " x " << m << std::endl; // size output
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
    BinImage::BinImage() : f(nullptr), n(0), m(0), is_image_changed(true), cache_coefficient(0)
    {
        log("Default constructor!\n");
    }
    BinImage::BinImage(const int a, const int b, const int fill) : f(nullptr), n(a), m(b), is_image_changed(true), cache_coefficient(0)
    {
        log("Constructor, defining size and filling image!\n");
        create_f(n, m);
        fill_value(fill);
    }
    BinImage::BinImage(const BinImage &b) : f(nullptr), n(b._n()), m(b._m()), is_image_changed(b._is_image_changed()), cache_coefficient(b._cache())
    {
        log("Copying constructor!\n");
        create_f(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                f[i][j] = b(i, j);
    }
    BinImage::BinImage(BinImage &&b) : n(b._n()), m(b._m()), f(b.f), is_image_changed(b._is_image_changed()), cache_coefficient(b._cache())
    {
        log("Moving constructor!\n");
        b.f = nullptr;
    }
    BinImage::~BinImage()
    {
        log("Destructor!\n");
        delete_f();
    }
    bool BinImage::operator()(const int a, const int b) const
    {
        if (int_in(a, 0, n - 1) && int_in(b, 0, m - 1))
            return f[a][b];
        else
        {
            log("Warning: index out of range!\n");
            return f[0][0];
        }
    }
    bool& BinImage::operator()(const int a, const int b)
    {
        if (int_in(a, 0, n - 1) && int_in(b, 0, m - 1))
            return f[a][b];
        else
        {
            log("Warning: index out of range!\n");
            return f[0][0];
        }
    }
    BinImage BinImage::operator!()
    {
        BinImage tmp(n, m, 0);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                tmp(i, j) = !(f[i][j]);
        return tmp;
    }
    double BinImage::coefficient()
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
    BinImage& BinImage::operator=(const BinImage &b)
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
    BinImage& BinImage::operator=(BinImage &&b)
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
    std::ostream &operator<<(std::ostream &os, const BinImage &a)
    {
        a.output();
        return os;
    }
    void fill_random(BinImage &a)
    {
        if (a._is_created())
            for (int i = 0; i < a._n(); i++)
                for (int j = 0; j < a._m(); j++)
                    a(i, j) = (bool)(rand() % 2);
    }
    BinImage operator*(const BinImage &a, const BinImage &b)
    {
        BinImage tmp(a._n(), a._m(), 0);
        for (int i = 0; i < a._n(); i++)
            for (int j = 0; j < a._m(); j++)
                tmp(i, j) = a(i, j) & b(i, j);
        return tmp;
    }
    BinImage operator+(const BinImage &a, const BinImage &b)
    {
        BinImage tmp(a._n(), a._m(), 0);
        for (int i = 0; i < a._n(); i++)
            for (int j = 0; j < a._m(); j++)
                tmp(i, j) = a(i, j) | b(i, j);
        return tmp;
    }
    BinImage operator*(const BinImage &a, const int l)
    {
        BinImage tmp(a._n(), a._m(), 0);
        for (int i = 0; i < a._n(); i++)
            for (int j = 0; j < a._m(); j++)
                tmp(i, j) = a(i, j) & l;
        return tmp;
    }
    BinImage operator+(const BinImage &a, const int l)
    {
        BinImage tmp(a._n(), a._m(), 0);
        for (int i = 0; i < a._n(); i++)
            for (int j = 0; j < a._m(); j++)
                tmp(i, j) = a(i, j) | l;
        return tmp;
    }
    BinImage operator*(const int l, const BinImage &b)
    {
        BinImage tmp(b._n(), b._m(), 0);
        for (int i = 0; i < b._n(); i++)
            for (int j = 0; j < b._m(); j++)
                tmp(i, j) = b(i, j) & l;
        return tmp;
    }
    BinImage operator+(const int l, const BinImage &b)
    {
        BinImage tmp(b._n(), b._m(), 0);
        for (int i = 0; i < b._n(); i++)
            for (int j = 0; j < b._m(); j++)
                tmp(i, j) = b(i, j) | l;
        return tmp;
    }
};