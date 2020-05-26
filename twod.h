#ifndef TWOD_H
#define TWOD_H


class twoD
{
    private:
        int x, y;
    public:
        twoD();
        twoD(int xparam, int yparam);
        twoD(const twoD& td);
        twoD& operator=(twoD& td);
        void setX(int tx);
        void setY(int ty);
        void setXY(int tx, int ty);
        int X() const;
        int Y() const;
};


#endif // TWOD_H
