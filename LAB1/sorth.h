#pragma once
#ifndef __SORTH_H__
#define __SORTH_H__
#include<stdio.h>
#include<stdlib.h>

void insert(long* a, long n) {					//��������
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
	long* temp=(long*)malloc(sizeof(long) * (llen+rlen)); //��ʱ����
	 
	while (i < llen && j < rlen){		//�Ƚ��������ߵ������Ӧλ�ô�С �ϲ� ֱ��һ���������� 
		if (l[i] < r[j])
			temp[k++] = l[i++];
		else
			temp[k++] = r[j++];
	}
	//�ϲ�ʣ������� 
	while (i < llen){
		temp[k++] = l[i++];
	}

	while (j < rlen){
		temp[k++] = r[j++];
	}
//���������� ��l=a���е� ���԰ѽ����l���� 
	for (long m = 0; m < (llen + rlen); m++){
		l[m] = temp[m];
	}

}

void merge(long* a, long n) {			//�鲢���� 
	if (n < 2)
		return;
	long* listl = a;				//��� 
	long llen = n / 2;				//��߽� 
	long* listr = a + llen;			//�ұ� 
	long rlen = n - llen;			//�ұ߽� 
//�����ҵݹ� 
	merge(listl, llen);	
	merge(listr, rlen);

	mergediv(listl, listr, llen, rlen); //�ϲ� 
}

long quick(long* a, long l, long r) {
	long temp;
	long x = a[r];		//ѡȡ��ֵ 
	long i = l - 1;		//i��λ�þ���q��ǰһ��λ�� 

	for (long j = 0; j < r; j++) {	//�������� 
		if (a[j] <= x) {
			i = i + 1;		//ʼ�ռ�¼q��ǰһλ 
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
		long q = quick(a, l, r); 		//Ѱ��key��λ��
		//��q��ֵ���� �ݹ���� 
		quickdiv(a, l, q - 1);
		quickdiv(a, q + 1, r);
	}
}


void heapify(long *a, long l, long r) {			//���������
	long p = l;
	long s = p * 2 + 1;
	long temp;
	while (s <= r) { 						//�ж�δ���� 
		if (s + 1 <= r && a[s] < a[s + 1])  //�жϼ���Ҷ�� ѡ������Ҷ�� 
			s++;
		if (a[p] > a[s]) //�����ڵ��Ѿ�������ӽڵ�� ֱ�ӷ��� 
			return;
		else {				//���� ���Ҷ�ӽڵ㽻�� 
			temp = a[s];
			a[s] = a[p];
			a[p] = temp;
			p = s;  		//���ڽ����˽ڵ� ������ڵ���ܲ��Ϲ�� ����ִ�г��� 
			s = p * 2 + 1;
		}
	}

}

void heapsort(long *a, long n) {
	long i,temp;
	for (i = n / 2 - 1; i >= 0; i--)	//��������� ���һ����Ҷ�ڵ㿪ʼ 
		heapify(a, i, n - 1);

	for (i = n - 1; i > 0; i--) {		//�����һ������ 
		temp = a[i];
		a[i] = a[0];
		a[0] = temp;
		heapify(a, 0, i - 1);			//�ع������ 
	}
}

#endif // !__SORTH_H__
