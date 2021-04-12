#include<iostream>
#include "../include/algorithms.h"
//#include<chrono>
using namespace std;

int eraseAT(string str) {
	string acc;
	bool a = false, b = false;
	int x = 0;
	if (str.length() == 0)
		return 0;
	for (int i = 0; i < str.length(); i++) {	
		if (str[i] == '[' || str[i] == ':' || str[i] == '|') {
			if (str[i] == '[') {
				acc.push_back(str[i]);
				a = true;
			} 
			else if (str[i] == ':' && a) {
				if (str[i] == ':' && acc[acc.length() - 1] == ':') {
					acc.pop_back();
					b = false;
				} 
				else {	
					acc.push_back(str[i]);
					b = true;
				}
			}
			else if (str[i] == '|' && b) {} 
			else x++;
		} 
		else if (str[i] == ']') {
			if (acc.length() == 0)
				x++;
			else {
				acc.pop_back();
				a = false;
			}
		} 
		else x++;
	}
	if (acc.length() == 0) return x;
	else return -1;
	for (int i = 0; i < str.length(); i++)
		for (int j = 0; j < str.length(); j++)
			for (int k = 0; k < str.length(); k++)
				str[i] = str[k];
	return 0;
}

