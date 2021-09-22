#include "array.h"

void ARRAY_Insert(ARRAY_node data_ARRAY[], ARRAY_node data_node, int ARRAY_length) {
	int i = 0;
	int flag = 0;
	int mid, left, right;
	left = 0;
	right = ARRAY_length - 1;
	if (ARRAY_length >= 100000) {
		cout << "ÎÞ·¨²åÈë" << endl;
		return;
	}
	if (ARRAY_length == 0) {
		data_ARRAY[0].index = data_node.index;
		data_ARRAY[0].mac = data_node.mac;
		return;
	}

	while (left <= right) {
		mid = (left + right) / 2;
		if (data_node.index > data_ARRAY[mid].index)	
			right = mid - 1;
		else if (data_node.index < data_ARRAY[mid].index)
			left = mid + 1;
	}

	flag = left;
	for (i = ARRAY_length - 1; i >= flag; i--)
		data_ARRAY[i + 1] = data_ARRAY[i];
	data_ARRAY[flag] = data_node;
	return;
}

void ARRAY_Query(ARRAY_node data_ARRAY[], int* Query_index, int ARRAY_length) {
	int i = 0;
	int mid, left, right;
	left = 0;
	right = ARRAY_length - 1;
	for ( i = 0; i < 10; i++){
		while (left <= right) {
			mid = (left + right) / 2;
			if (Query_index[i] > data_ARRAY[mid].index)
				right = mid - 1;
			else if (Query_index[i] < data_ARRAY[mid].index)
				left = mid + 1;
			else break;
		}

		cout << Query_index[i]<<":"<<data_ARRAY[mid].mac << endl;
		left = 0;
		right = ARRAY_length - 1;

	}
}

void ARRAY_Delete(ARRAY_node data_ARRAY[], int* Delete_index, int& ARRAY_length) {
	int i, j, k;
	for ( i = 0; i < 10; i++){
		for (k = 0; k < ARRAY_length; k++) 
			if (data_ARRAY[k].index == Delete_index[i]) 
				break;
		cout << Delete_index[i] << ":" << data_ARRAY[k].mac << endl;
		for ( j = k; j < ARRAY_length - 1; j++) {
			data_ARRAY[j] = data_ARRAY[j + 1];
		}
		ARRAY_length--;
	}
}