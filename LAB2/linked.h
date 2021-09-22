#pragma once
#include <string>
#include <iostream>
using namespace std;

struct LINKED_node {
	int index;
	std::string mac;
	struct LINKED_node* next;
};

LINKED_node* created_LINKED();
void LINKED_Insert(LINKED_node* HEAD, LINKED_node* data_node);//【需要自行补全】
void LINKED_Query(LINKED_node* HEAD, int* LINKED_Query);//【需要自行补全】
void LINKED_Delete(LINKED_node* HEAD, int* LINKED_Delete);//【需要自行补全】