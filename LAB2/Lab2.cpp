// Lab2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <windows.h>
#include "ultity.h"
#include "array.h"
#include "linked.h"
#include "RBTree.h"

using namespace std;



void acceptance_test()//实验验收函数，【无需修改，不要改动】，请仔细阅读代码，理解IO接口
{
	vector<struct CSVDATA> dataList = dataload();
	// Get the data from CSV File
	std::cout << "There are " << dataList.size() << " datas in the CSV file." << std::endl;
	/* 数组部分 （开始）*/
	// 生成数组
	ARRAY_node* data_ARRAY = new ARRAY_node[100000];
	int ARRAY_length = 0;
	for (int i = 0; i < 99900; i++) {
		ARRAY_node new_data;
		new_data.mac = dataList[i].mac;
		new_data.index = dataList[i].index;
		ARRAY_Insert(data_ARRAY, new_data, ARRAY_length);
		ARRAY_length++;
	}
	
	// ======= 插入 =======
	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	for (int i = 0; i < 100; i++) {
		ARRAY_node new_data;
		new_data.mac = dataList[i + 99900].mac;
		new_data.index = dataList[i + 99900].index;
		ARRAY_Insert(data_ARRAY, new_data, ARRAY_length);
		ARRAY_length++;
	}
	QueryPerformanceCounter(&t2);
	double ARRAY_insert_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "ARRAY_insert_time = " << ARRAY_insert_time << " s" << endl;  //输出时间（单位：ｓ）

	// ======= 查找 =======
	int* Query_index = new int[10]{ 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 99999 };
	QueryPerformanceCounter(&t1);
	ARRAY_Query(data_ARRAY, Query_index, ARRAY_length);
	QueryPerformanceCounter(&t2);
	double ARRAY_query_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "ARRAY_query_time = " << ARRAY_query_time << " s" << endl;  //输出时间（单位：ｓ）

	// ======= 删除 =======
	int* Delete_index = new int[10]{ 15000, 25000, 35000, 45000, 55000, 65000, 75000, 85000, 95000, 99999 };
	QueryPerformanceCounter(&t1);
	ARRAY_Delete(data_ARRAY, Delete_index, ARRAY_length);
	QueryPerformanceCounter(&t2);
	double ARRAY_delete_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "ARRAY_delete_time = " << ARRAY_delete_time << " s" << endl;  //输出时间（单位：ｓ）


	cout << endl;
	

	/* 链表部分 （开始）*/
	//生成链表头
	LINKED_node* HEAD = created_LINKED();

	for (int i = 0; i < 99900; i++) {
		LINKED_node* new_data = new LINKED_node;
		new_data->mac = dataList[i].mac;
		new_data->index = dataList[i].index;
		new_data->next = NULL;
		LINKED_Insert(HEAD, new_data);
	}

	// ======= 插入 =======
	QueryPerformanceCounter(&t1);
	for (int i = 0; i < 100; i++) {
		LINKED_node* new_data = new LINKED_node;
		new_data->mac = dataList[i + 99900].mac;
		new_data->index = dataList[i + 99900].index;
		new_data->next = NULL;
		LINKED_Insert(HEAD, new_data);
	}
	QueryPerformanceCounter(&t2);
	double LINKED_insert_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "LINKED_insert_time = " << LINKED_insert_time << " s" << endl;  //输出时间（单位：ｓ）

	// ======= 查找 =======
	QueryPerformanceCounter(&t1);
	LINKED_Query(HEAD, Query_index);
	QueryPerformanceCounter(&t2);
	double LINKED_query_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "LINKED_query_time = " << LINKED_query_time << " s" << endl;  //输出时间（单位：ｓ）

	// ======= 删除 =======
	QueryPerformanceCounter(&t1);
	LINKED_Delete(HEAD, Delete_index);
	QueryPerformanceCounter(&t2);
	double LINKED_Delete_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "LINKED_Delete_time = " << LINKED_Delete_time << " s" << endl;  //输出时间（单位：ｓ）;

	cout << endl;



	//生成红黑树
	RBTree* tree = new RBTree();
	for (int i = 0; i < 99900; i++)
		tree->insert(dataList[i].index, dataList[i].mac);

	// ======= 插入 =======
	QueryPerformanceCounter(&t1);
	for (int i = 99900; i < 100000; i++)
		tree->insert(dataList[i].index, dataList[i].mac);
	QueryPerformanceCounter(&t2);
	double RBTREE_insert_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "RBTREE_insert_time = " << RBTREE_insert_time << " s" << endl;  //输出时间（单位：ｓ）;

	// ======= 查找 =======
	QueryPerformanceCounter(&t1);
	for (int i = 0; i < 10; i++)
		cout << Query_index[i] << " : " << tree->search(Query_index[i])->mac << endl;
	QueryPerformanceCounter(&t2);
	double RBTREE_Query_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "RBTREE_Query_time = " << RBTREE_Query_time << " s" << endl;  //输出时间（单位：ｓ）;

	// ======= 删除 =======
	QueryPerformanceCounter(&t1);
	for (int i = 0; i < 10; i++)
		tree->remove(Delete_index[i]);
	QueryPerformanceCounter(&t2);
	double RBTREE_Delete_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "RBTREE_Delete_time = " << RBTREE_Delete_time << " s" << endl;  //输出时间（单位：ｓ）;

	cout << endl;
}


void RBTree_test()//红黑树测试函数，供同学在补全红黑树函数时测试正确性，验收时也会用此函数对红黑树代码正确性进行测试
{
	RBTree* test = new RBTree();
	cout << "RBTree test" << endl;
	test->insert(8, "I");
	test->print();
	test->insert(2, "L");
	test->print();
	test->insert(5, "O");
	test->print();
	test->insert(9, "V");
	test->print();
	test->insert(1, "E");
	test->print();
	test->insert(7, "U");
	test->print();
	test->insert(6, "S");
	test->print();
	test->insert(10, "T");
	test->print();
	test->insert(4, "C");
	test->print();
	test->remove(2);
	test->print();
	cout << endl;
}

int main()
{	
	acceptance_test();//实验验收
	RBTree_test();//红黑树测试

	return 0;
}