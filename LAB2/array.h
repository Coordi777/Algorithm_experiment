#pragma once
#include <string>
#include <iostream>
using namespace std;
struct ARRAY_node {
	int index;
	std::string mac;
};

void ARRAY_Insert(ARRAY_node data_ARRAY[], ARRAY_node data_node, int ARRAY_length);//【需要自行补全】
void ARRAY_Query(ARRAY_node data_ARRAY[], int* ARRAY_Query, int ARRAY_length);//【需要自行补全】
void ARRAY_Delete(ARRAY_node data_ARRAY[], int* ARRAY_Delete, int& ARRAY_length);//【需要自行补全】