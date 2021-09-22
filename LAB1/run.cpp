#include<stdio.h>
#include"sorth.h"
#include"mrand.h"
#include <windows.h>
#include <stdlib.h>
#define size 10000


void showlist(long* a) {
	int m;
	for (m = 0; m < 100; m++) {
		if (m % 10 == 0 && m != 0)
			printf("\n");
		printf("%d ", a[m]);
	}
	printf("\n");
}


int main() {
	long* a;
	int i, j;
	FILE* fp;
	//fp = fopen("file.xls", "w+");
	double r[10][10];


	/*
		for (i = 1; i <= 10; i++) {
			for (j = 0; j < 10; j++) {
				LARGE_INTEGER t1, t2, nFreq;
				a = (long*)malloc(sizeof(long) * size * i);
				randbuild(a, size * i);
				QueryPerformanceFrequency(&nFreq);
				QueryPerformanceCounter(&t1);
				insert(a, size * i);
				QueryPerformanceCounter(&t2);
				double dt = (double)(t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
				r[i - 1][j] = dt;


				free(a);
			}
		}*/
		/*for (i = 0; i < 10; i++){
			for (j = 0; j < 10; j++)
			{
				fprintf(fp,"%lf\t", r[i][j]);
			}
			fprintf(fp,"\n");
		}*/
	printf("ÑéÖ¤£º\n");
	for (i = 0; i < 4; i++) {
		switch (i)
		{
		case 0:a = (long*)malloc(sizeof(long) * size);
			randbuild(a, size);
			insert(a, size);
			printf("²åÈëÅÅÐò£º\n");
			showlist(a);
			free(a);
			break;

		case 1:a = (long*)malloc(sizeof(long) * size);
			randbuild(a, size);
			merge(a, size);
			printf("¹é²¢ÅÅÐò£º\n");
			showlist(a);
			free(a);
			break;

		case 2:a = (long*)malloc(sizeof(long) * size);
			randbuild(a, size);
			quickdiv(a, 0, size-1);
			printf("¿ìËÙÅÅÐò£º\n");
			showlist(a);
			free(a);
			break;

		case 3:a = (long*)malloc(sizeof(long) * size);
			randbuild(a, size);
			heapsort(a, size);
			printf("¶ÑÅÅÐò£º\n");
			showlist(a);
			free(a);
			break;
		default:
			break;
		}
	}

}
