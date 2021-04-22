#ifndef  encryptH
#define  encryptH

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

void rotation(vector<vector<int>> &mtx, int n);

void randKey(vector<vector<int>> &mtx, int n);

void tryKey(vector<vector<int>> &mtx, int n, vector<int> arr);

bool equals(string a, string b);

bool compare(string message, vector <vector <string>> encrypt, vector <vector<int>> mask, int* counter);

bool nextSet(vector<int> &a);

int analise_cipher(string message, vector <vector <string>> encrypt, int m);

#endif
