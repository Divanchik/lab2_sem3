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
    int int_in(const int n, const int left, const int right)
    {
        if (n >= left && n <= right)
            return 1;
        return 0;
    }
    int int_min(int left, int right)
    {
        if (left < right)
            return left;
        else
            return right;
    }
    void BinImage::delete_image()
    {
        log("Deleting image array!\n");
        if (_is_created() == false)
            throw "Memory error: Failed to delete image: Image is not created!";
        delete data;
        height = 0;
        width = 0;
    }
    void BinImage::create_image(const int new_height, const int new_width)
    {
        log("Creating image!\n");
        if (new_height  < 1 || new_width < 1)
            throw "Memory error: Failed to create image: Incorrect new_height or new_width!";
        if (_is_created() == true)
            throw "Memory error: Failed to create image: Image already created!";
        if (new_height * new_width > 100000000)
            throw "Memory error: Failed to resize image: Image size overflow!";
        height = new_height;
        width = new_width;
        data = new bool[height * width];
    }
    int BinImage::count_true() const
    {
        int z = 0;
        for (int i = 0; i < height * width; i++)
            if (data[i])
                z += 1;
        return z;
    }
    void BinImage::fill_value(const bool fill)
    {
        log("\\Filling image with some value!\n");
        if (_is_created())
        {
            for (int i = 0; i < height * width; i++)
                data[i] = fill;
        }
        is_image_changed = true;
    }
    void BinImage::resize(int new_height, int new_width)
    {
        if (new_height  < 1 || new_width < 1)
            throw "Memory error: Failed to resize image: Incorrect new_height or new_width!";
        if (new_height * new_width > 100000000)
            throw "Memory error: Failed to resize image: Image size overflow!";
        bool* tmp = new bool[new_height * new_width];
        for (int i = 0; i < int_min(height, new_height); i++)
            for(int j = 0; j < int_min(width, new_width); j++)
                tmp[i * new_width + j] = data[i * width + j];
        delete data;
        data = tmp;
        tmp = nullptr;
        height = new_height;
        width = new_width;
        is_image_changed = true;
    }
    int BinImage::_height() const { return height; }
    int BinImage::_width() const { return width; }
    bool BinImage::_is_image_changed() const { return is_image_changed; }
    bool BinImage::_is_created() const
    { 
        if (height == 0 || width == 0)
            return false;
        return true;
    }
    double BinImage::_cache() const { return cache_coefficient; }
    void BinImage::input()
    {
        log("Input method!\n");
        if (!(_is_created()))
        {
            std::cout << "Input height, then input width:" << std::endl;
            int_input(height, "Input height:");
            int_input(width, "Input width:");
            create_image(height, width);
        }
        std::cout << "Input image(string by string):" << std::endl;
        char buf[width + 1];
        char buf1[2];
        for (int i = 0; i < height; i++)
        {
            fgets(buf, width + 1, stdin);
            while (getchar() != '\n')
                ;
            for (int j = 0; j < width; j++)
                data[i * width + j] = buf[j] - '0';
        }
        is_image_changed = true;
    }
    void BinImage::output() const
    {
        log("Output method!\n");
        if (trace)
            std::cout << "Size: " << height << " x " << width << std::endl;
        // head
        for (int j = 0; j < width + 2; j++)
            std::cout << '=';
        std::cout << std::endl;
        // body
        for (int i = 0; i < height; i++)
        {
            std::cout << '|';
            for (int j = 0; j < width; j++)
                if (data[i * width + j])
                    std::cout << '#';
                else
                    std::cout << '.';
            std::cout << '|' << std::endl;
        }
        // bottom
        for (int j = 0; j < width + 2; j++)
            std::cout << '=';
        std::cout << std::endl;
    }
    BinImage::BinImage() : data(nullptr), height(0), width(0), is_image_changed(true), cache_coefficient(0)
    {
        log("Default constructor!\n");
    }
    BinImage::BinImage(const int new_height, const int new_width, const bool fill) : height(0), width(0), data(nullptr), is_image_changed(true), cache_coefficient(0)
    {
        log("\\Constructor, defining size and filling image!\n");
        create_image(new_height, new_width);
        if (trace)
            std::cout << " |Size: " << height << " x " << width << std::endl;
        fill_value(fill);
    }
    BinImage::BinImage(const BinImage &b) : height(0), width(0), data(nullptr), is_image_changed(b._is_image_changed()), cache_coefficient(b._cache())
    {
        log("Copy constructor!\n");
        create_image(b._height(), b._width());
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                data[i * width + j] = b(i, j);
    }
    BinImage::BinImage(BinImage &&b) : height(b._height()), width(b._width()), data(b.data), is_image_changed(b._is_image_changed()), cache_coefficient(b._cache())
    {
        log("Move constructor!\n");
        b.data = nullptr;
    }
    BinImage::~BinImage()
    {
        log("Destructor!\n");
        delete_image();
    }
    bool BinImage::operator()(const int i, const int j) const
    {
        if (_is_created() == false)
            throw "Access error: Incorrect image size!";
        if (!(int_in(i,0,height-1)) || !(int_in(j,0,width-1)))
            throw "Access error: Index out of range!";
        return data[i * width + j];
    }
    bool& BinImage::operator()(const int i, const int j)
    {
        if (_is_created() == false)
            throw "Access error: Incorrect image size!";
        if (!(int_in(i,0,height-1)) || !(int_in(j,0,width-1)))
            throw "Access error: Index out of range!";
        return data[i * width + j];
    }
    BinImage BinImage::operator!()
    {
        BinImage tmp(height, width, false);
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                tmp(i, j) = !(data[i * width + j]);
        return tmp;
    }
    double BinImage::coefficient()
    {
        log("Coefficient method!\n");
        if (is_image_changed)
        {
            cache_coefficient = (double)count_true() / (height * width);
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
        is_image_changed = true;
        resize(b._height(), b._width());
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                data[i * width + j] = b(i, j);
        return *this;
    }
    BinImage& BinImage::operator=(BinImage &&b)
    {
        log("Move assign overload!\n");
        if (&b == this)
            return *this;
        is_image_changed = true;
        delete_image();
        height = b._height();
        width = b._width();
        data = b.data;
        b.data = nullptr;
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
            for (int i = 0; i < a._height(); i++)
                for (int j = 0; j < a._width(); j++)
                    a(i, j) = (bool)(rand() % 2);
    }
    BinImage operator*(const BinImage &a, const BinImage &b)
    {
        BinImage tmp(a._height(), a._width(), 0);
        for (int i = 0; i < a._height(); i++)
            for (int j = 0; j < a._width(); j++)
                tmp(i, j) = a(i, j) & b(i, j);
        return tmp;
    }
    BinImage operator+(const BinImage &a, const BinImage &b)
    {
        BinImage tmp(a._height(), a._width(), 0);
        for (int i = 0; i < a._height(); i++)
            for (int j = 0; j < a._width(); j++)
                tmp(i, j) = a(i, j) | b(i, j);
        return tmp;
    }
    BinImage operator*(const BinImage &a, const bool l)
    {
        BinImage tmp(a._height(), a._width(), 0);
        for (int i = 0; i < a._height(); i++)
            for (int j = 0; j < a._width(); j++)
                tmp(i, j) = a(i, j) & l;
        return tmp;
    }
    BinImage operator+(const BinImage &a, const bool l)
    {
        BinImage tmp(a._height(), a._width(), 0);
        for (int i = 0; i < a._height(); i++)
            for (int j = 0; j < a._width(); j++)
                tmp(i, j) = a(i, j) | l;
        return tmp;
    }
    BinImage operator*(const bool l, const BinImage &b)
    {
        BinImage tmp(b._height(), b._width(), 0);
        for (int i = 0; i < b._height(); i++)
            for (int j = 0; j < b._width(); j++)
                tmp(i, j) = b(i, j) & l;
        return tmp;
    }
    BinImage operator+(const bool l, const BinImage &b)
    {
        BinImage tmp(b._height(), b._width(), 0);
        for (int i = 0; i < b._height(); i++)
            for (int j = 0; j < b._width(); j++)
                tmp(i, j) = b(i, j) | l;
        return tmp;
    }
};