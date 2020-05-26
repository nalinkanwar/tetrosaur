#ifndef NUMBERBAG_H
#define NUMBERBAG_H

#include <vector>


/* Note: uses rand(); so make sure to set seed with
 * srand before using this class */
class NumberBag
{
    private:
        std::vector<int> bag;
        int lo, hi;
    public:
        NumberBag(int n);
        NumberBag(int lo, int hi);

        void generateBag(int lo, int hi);

        int getNumber();
        bool isEmpty();
};

#endif // NUMBERBAG_H
