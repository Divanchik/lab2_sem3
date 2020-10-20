#include <iostream>
#include <cstdio>
#include <cstdlib>

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
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                if (f[i][j] == 1)
                    std::cout << "#";
                else
                    std::cout << ".";
            std::cout << '\n';
        }
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
        BinImage tmp(n,m,0);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                tmp(i,j) = f[i][j]*b(i,j);
        return tmp;
    }
    BinImage& operator+(BinImage& b)
    {
         
    }
    //copy constructor
    BinImage(const BinImage &b);
    BinImage &operator=(const BinImage &b);
    //move constructor
    BinImage(BinImage &&b);
    BinImage &operator=(BinImage &&b);
};
int main()
{
    BinImage a;
    a.input();
    a(0,0) = 1;
    a(1,1) = 1;
    a.output();
    return 0;
}