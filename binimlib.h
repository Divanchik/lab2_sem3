#pragma once
namespace bim
{
    class BinImage
    {
        private:
        int **f;
        public:
        BinImage();
        ~BinImage();
        BinImage(const BinImage& b);
        BinImage& operator =(const BinImage& b);
    };
};