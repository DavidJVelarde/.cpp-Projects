#ifndef CANDY_H
#define CANDY_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

struct Candy
{
    string name;
    string description;
    double price;
    string candy_type;
    string effect_type;
    int effect_value;
};
#endif