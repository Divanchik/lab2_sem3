#include <iostream>
#include <cstdio>
#include <cstdlib>
const char lt(201);
const char lb(200);
const char rt(187);
const char rb(188);
const char vl(186);
const char hl(205);
const char tv(178);
const char fv(176);
int count_char(char c, char *s)
{
    int i = 0;
    for (; *s; s++)
        if (c == *s)
            i += 1;
    return i;
}
int int_in(int n, int a, int b)
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

public:
    int _n(){return n;}
    int _m(){return m;}
    int** _f(){return f;}
    void filling(int fill)
    {
        if(f!=NULL)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    f[i][j] = fill;
    }
    BinImage() : f(NULL), n(0), m(0) {}
    BinImage(int a, int b, int fill) : n(a), m(b)
    {
        f = (int **)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            f[i] = (int *)malloc((m + 1) * sizeof(int));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                f[i][j] = fill;
    }
    void input()
    {
        if (n == 0 || m == 0)
        {
            std::cout << "Input height, then input width:" << std::endl;
            std::cin >> n >> m;
            while (getchar() != '\n'){}
        }
        f = (int **)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
            f[i] = (int *)malloc((m + 1) * sizeof(int));
        std::cout << "Input image:" << std::endl;
        char *buf = new char[2 * m];
        char *buf1 = new char[2];
        for (int i = 0; i < n; i++)
        {
            fgets(buf, m + 1, stdin);
            while (getchar() != '\n'){}
            for (int j = 0; j < m; j++)
            {
                f[i][j] = buf[j] - '0';
                printf("%d\n", f[i][j]);
            }
        }
        delete buf;
        delete buf1;
    }
    void output()
    {
        // defining special characters
        char lt(201);
        char lb(200);
        char rt(187);
        char rb(188);
        char vl(186);
        char hl(205);
        char tv(178);
        char fv(176);
        // head
        std::cout << lt;
        for (int j = 0; j < m; j++)
            std::cout << hl;
        std::cout << rt << std::endl;
        // body
        for (int i = 0; i < n; i++)
        {
            std::cout << vl;
            for (int j = 0; j < m; j++)
                if (f[i][j] == 1)
                    std::cout << tv;
                else
                    std::cout << fv;
            std::cout << vl << std::endl;
        }
        // bottom
        std::cout << lb;
        for (int j = 0; j < m; j++)
            std::cout << hl;
        std::cout << rb << std::endl;
    }
    ~BinImage()
    {
        for (int i = 0; i < n; i++)
            free(f[i]);
        free(f);
    }
    // operators overload
    int& operator()(int a, int b)
    {
        if (int_in(a,0,n-1) && int_in(a,0,m-1))
            return f[a][b];
        else
            return f[0][0];
    }
    BinImage& operator*(BinImage& b)
    {
        BinImage* tmp = new BinImage(n,m,0);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                (*tmp)(i,j) = f[i][j]&b(i,j);
        return *tmp;
    }
    BinImage& operator+(BinImage& b)
    {
        BinImage* tmp = new BinImage(n,m,0);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                (*tmp)(i,j) = f[i][j]|b(i,j);
        return *tmp;
    }
    BinImage& operator*(int l)
    {
        BinImage* tmp = new BinImage(n,m,0);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                (*tmp)(i,j) = f[i][j]&l;
        return *tmp;
    }
    BinImage& operator+(int l)
    {
        BinImage* tmp = new BinImage(n,m,0);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                (*tmp)(i,j) = f[i][j]|l;
        return *tmp;
    }
    BinImage& operator!()
    {
        BinImage* tmp = new BinImage(n,m,0);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                (*tmp)(i,j) = !(f[i][j]);
        return *tmp;
    }
    double coefficient()
    {
        int true_amount = 0;
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                if(f[i][j])
                    true_amount += 1;
        return (double)true_amount/(n*m);
    }
    //copy constructor
    BinImage(const BinImage &b);
    BinImage &operator=(const BinImage &b);
    //move constructor
    BinImage(BinImage &&b);
    BinImage &operator=(BinImage &&b);

    friend std::ostream& operator<< (std::ostream &out, const BinImage &image)
    {
        // head
        std::cout << lt;
        for (int j = 0; j < image.m; j++)
            std::cout << hl;
        std::cout << rt << std::endl;
        // body
        for (int i = 0; i < image.n; i++)
        {
            std::cout << vl;
            for (int j = 0; j < image.m; j++)
                if (image.f[i][j] == 1)
                    std::cout << tv;
                else
                    std::cout << fv;
            std::cout << vl << std::endl;
        }
        // bottom
        std::cout << lb;
        for (int j = 0; j < image.m; j++)
            std::cout << hl;
        std::cout << rb << std::endl;
    }
};
BinImage& operator*(int l, BinImage& b)
{
    BinImage *tmp = new BinImage(b._n(),b._m(),0);
    for(int i=0;i<b._n();i++)
        for(int j=0;j<b._m();j++)
            (*tmp)(i,j) = b._f()[i][j]&l;
    return *tmp;
}
BinImage& operator+(int l, BinImage& b)
{
    BinImage *tmp = new BinImage(b._n(),b._m(),0);
    for(int i=0;i<b._n();i++)
        for(int j=0;j<b._m();j++)
            (*tmp)(i,j) = b._f()[i][j]|l;
    return *tmp;
}
int main()
{
    BinImage a;
    a.input();
    a.output();
    std::cout << a;
    return 0;
}