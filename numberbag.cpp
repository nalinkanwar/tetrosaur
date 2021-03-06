#include "numberbag.h"
#include <iostream>
#include <random>
#include <string>

/* project-specific vars */
#include "tetromino.h"
std::string ttstr[TETROMINO_MAX] = { "()", "I", "O", "T", "S", "Z", "J", "L" };

NumberBag::NumberBag(int n) {
    this->lo = 0;
    this->hi = n;
}

NumberBag::NumberBag(int nlo, int nhi) {
    this->lo = nlo;
    this->hi = nhi;
}

void NumberBag::generateBag(int lo, int hi)
{
    std::vector<int>space;
    int i;

    this->bag.clear();

    for(i = lo; i <= hi; i++) {
        space.push_back(i);
    }

    while(!space.empty()) {
        i = rand() % space.size();
        this->bag.push_back(space[i]);
        space.erase(space.begin() + i);
    }

    //this->printBag();
}


void NumberBag::printBag() {

    std::cout<<"Generated Bag : ";
    auto bit = this->bag.end();

    do {
        bit--;
        std::cout<<ttstr[*bit]<<" ";
    } while(bit != this->bag.begin());

    std::cout<<std::endl;
}

int NumberBag::getNumber() {

    int val;
    if(this->bag.empty()) {
        generateBag(this->lo, this->hi);
    }

    val = this->bag.back();
    this->bag.pop_back();
    //    std::cout<<"Took out : "<<val<<" from the bag"<<std::endl;
    return val;
}

bool NumberBag::isEmpty() {
    return this->bag.empty();
}
