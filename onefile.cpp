#include<cstdio>
#include<cstdlib>

class BinImage
{
    int **f;
    int n,m;
    public:
    BinImage();
    ~BinImage();
    //copy constructor
    BinImage(const BinImage& b);
    BinImage& operator =(const BinImage& b);
    //move constructor
    BinImage(BinImage&& b);
    BinImage& operator =(BinImage&& b);
};
int main()
{
    return 0;
}