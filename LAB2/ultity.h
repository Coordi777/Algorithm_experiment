#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;
struct CSVDATA {
	int index;
	std::string mac;
};

vector<struct CSVDATA> dataload();
