#include<iostream>
#include "../include/algorithms.h"
//#include<time.h>
//#include<chrono>
//#include <array>
using namespace std;

void swap(int * xp, int * yp){
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void STAY(int arr[], int n){
	int i, j;
	for(i=0; i<n-1; i++){
		for(j=0; j<n-i-1; j++){
			if(arr[j]>arr[j+1]) swap(&arr[j], &arr[j+1]);
		}
	}
}
