#pragma once
#ifndef __SORTH_H__
#define __SORTH_H__
#include<stdio.h>
#include<stdlib.h>

void insert(long* a, long n) {					//插入排序
	long i, j;
	long temp;
	for (i = 1; i < n; i++)
	{
		j = i - 1;
		if (a[i] < a[j])
		{
			temp = a[i];
			j = i - 1;
			while (a[j] > temp && j >= 0)
			{
				a[j + 1] = a[j];
				j = j - 1;
			}
			a[j + 1] = temp;
		}
	}
}

void mergediv(long* l, long* r, long llen, long rlen) {
	long i, j, k;
	i = j = k = 0;
	long* temp=(long*)malloc(sizeof(long) * (llen+rlen)); //临时数组
	 
	while (i < llen && j < rlen){		//比较左右两边的数组对应位置大小 合并 直到一个遍历结束 
		if (l[i] < r[j])
			temp[k++] = l[i++];
		else
			temp[k++] = r[j++];
	}
	//合并剩余的数组 
	while (i < llen){
		temp[k++] = l[i++];
	}

	while (j < rlen){
		temp[k++] = r[j++];
	}
//根据主函数 用l=a进行的 所以把结果用l返回 
	for (long m = 0; m < (llen + rlen); m++){
		l[m] = temp[m];
	}

}

void merge(long* a, long n) {			//归并排序 
	if (n < 2)
		return;
	long* listl = a;				//左边 
	long llen = n / 2;				//左边界 
	long* listr = a + llen;			//右边 
	long rlen = n - llen;			//右边界 
//对左右递归 
	merge(listl, llen);	
	merge(listr, rlen);

	mergediv(listl, listr, llen, rlen); //合并 
}

long quick(long* a, long l, long r) {
	long temp;
	long x = a[r];		//选取的值 
	long i = l - 1;		//i的位置就是q的前一个位置 

	for (long j = 0; j < r; j++) {	//交换策略 
		if (a[j] <= x) {
			i = i + 1;		//始终记录q的前一位 
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}
	// 
	temp = a[i + 1];
	a[i + 1] = a[r];
	a[r] = temp;

	return i + 1;
}

void quickdiv(long* a, long l, long r) {
	if (l < r) {
		long q = quick(a, l, r); 		//寻找key的位置
		//用q的值划分 递归进行 
		quickdiv(a, l, q - 1);
		quickdiv(a, q + 1, r);
	}
}


void heapify(long *a, long l, long r) {			//调整大根堆
	long p = l;
	long s = p * 2 + 1;
	long temp;
	while (s <= r) { 						//判断未出界 
		if (s + 1 <= r && a[s] < a[s + 1])  //判断几个叶子 选择最大的叶子 
			s++;
		if (a[p] > a[s]) //若父节点已经比最大子节点大 直接返回 
			return;
		else {				//若非 则和叶子节点交换 
			temp = a[s];
			a[s] = a[p];
			a[p] = temp;
			p = s;  		//由于交换了节点 后续孙节点可能不合规矩 继续执行程序 
			s = p * 2 + 1;
		}
	}

}

void heapsort(long *a, long n) {
	long i,temp;
	for (i = n / 2 - 1; i >= 0; i--)	//创建大根堆 最后一个非叶节点开始 
		heapify(a, i, n - 1);

	for (i = n - 1; i > 0; i--) {		//和最后一个交换 
		temp = a[i];
		a[i] = a[0];
		a[0] = temp;
		heapify(a, 0, i - 1);			//重构大根堆 
	}
}

#endif // !__SORTH_H__
