#include<iostream>
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
class BinImage
{
    int **f;
    int n, m;

public:
    BinImage() : f(NULL), n(0), m(0) {}
    BinImage(char *s)
    {
        int m = 0;
        for (; s[m] != '\n'; m += 1);
    }
    void input()
    {
        std::cout << "Input height, then input width:" << std::endl;
        //scanf("%d %d", &n, &m);
        std::cin >> n >> m;
        while(getchar() != '\n');
        f = (int**)malloc(n * sizeof(int));
        for(int i=0;i<n;i++)
            f[i] = (int*)malloc((m+1)*sizeof(int));
        std::cout << "Input image:" << std::endl;
        char* buf = new char[2*m];
        char* buf1= new char[2];
        for(int i=0;i<n;i++)
        {
            fgets(buf,m+1,stdin);
            while(getchar() != '\n');
            for(int j=0;j<m;j++)
            {
                f[i][j]=buf[j]-'0';
                printf("%d\n",f[i][j]);
            }
        }
        delete buf;
        delete buf1;
    }
    void output()
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
                if(f[i][j]==1)
                    std::cout << "#";
                else
                    std::cout << ".";
            std::cout << '\n';
        }
    }
    ~BinImage()
    {
        for(int i=0;i<n;i++)
            free(f[i]);
        free(f);
    }
    // //copy constructor
    // BinImage(const BinImage &b);
    // BinImage &operator=(const BinImage &b);
    // //move constructor
    // BinImage(BinImage &&b);
    // BinImage &operator=(BinImage &&b);
};
int main()
{
    BinImage a;
    a.input();
    a.output();
    return 0;
}