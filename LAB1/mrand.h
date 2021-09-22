#pragma once
#ifndef __MRAND_H__
#define __MRAND_H__
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void randbuild(long* a, long size) {
	long i;
	srand((unsigned)time(NULL));
	for ( i = 0; i < size; i++){
		a[i] = (rand() * 32767 + rand()) % 10000000 + 1;
	}
}





#endif // !__MRAND_H__
