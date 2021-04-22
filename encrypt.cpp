#include "encrypt.h"

void rotation(vector<vector<int>> &mtx, int n) {
	for (int i = 0; i < n / 2; i++) {
		for (int j = i; j < n - i - 1; j++) {
			int tmp = mtx[i][j];
			mtx[i][j] = mtx[n - 1 - j][i];
			mtx[n - 1 - j][i] = mtx[n - 1 - i][n - 1 - j];
			mtx[n - 1 - i][n - 1 - j] = mtx[j][n - 1 - i];
			mtx[j][n - 1 - i] = tmp;
		}
	}
}

void randKey(vector<vector<int>> &mtx, int n) {
	srand(time(NULL));
	vector <int> count;
	for (int i = 0; i < n; i++)
		count.push_back(i);
	int rt = 0;
	while (rt < 4) {
		int z = 0;
		for (int i = 0; i < n / 2; i++)
			for (int j = 0; j < n / 2; j++) {
				mtx[i][j] = z;
				z++;
			}
		rotation(mtx, n);
		rt++;
	}

	while (1) {

		int k = rand() % n;
		for (int l = 0; l < count.size(); l++)
			if (k == count[l]) {
				for (int i = 0; i < n / 2; i++)
					for (int j = 0; j < n / 2; j++)
						if (mtx[i][j] == k) mtx[i][j] = -111;
				count.erase(count.begin() + l);
				rotation(mtx, n);
			}
		//if (count.size() > 1)
		if (!count.size()) break;

	}
}

void tryKey(vector<vector<int>> &mtx, int n, vector<int> arr) {
	vector <int> count;
	for (int i = 0; i < n; i++)
		count.push_back(i);
	int rt = 0;
	while (rt < 4) {
		int z = 0;
		for (int i = 0; i < n / 2; i++)
			for (int j = 0; j < n / 2; j++) {
				mtx[i][j] = z;
				z++;
			}
		rotation(mtx, n);
		rt++;
	}

	for (int m = 0; m < n; m++) {
		for (int l = 0; l < count.size(); l++)
			if (m == count[l]) {
				for (int i = 0; i < n / 2; i++)
					for (int j = 0; j < n / 2; j++)
						if (mtx[i][j] == arr[m]) mtx[i][j] = -111;
				count.erase(count.begin() + l);
				rotation(mtx, n);
			}
		if (!count.size()) break;

	}
}

bool equals(string a, string b) {
	if (a.size() != b.size()) return false;
	for (int i = 0; i < a.size(); i++)
		if (a[i] != b[i]) return false;
	return true;
}

bool compare(string message, vector <vector <string>> encrypt, vector <vector<int>> mask, int* counter) {
	int rt = 0;

	int m = mask.size();
	string res;

	while (rt < 4) {
		for (int i = 0; i < m; i++)
			for (int j = 0; j < m; j++)
				if ((mask[i][j] == -111)) {
					res += encrypt[i][j];
				}
		rotation(mask, m);
		rt++;
	}
	rt = 0;
	*counter += 1;
	if (equals(res, message)) return true;
	return false;
}

bool nextSet(vector<int> &a) {
	int n = a.size();
	int j = n - 2;
	while (j != -1 && a[j] >= a[j + 1]) j--;
	if (j == -1) return false;
	int k = n - 1;
	while (a[j] >= a[k]) k--;
	swap(a[j], a[k]);
	int l = j + 1, r = n - 1;
	while (l < r)
		swap(a[l++], a[r--]);
	return true;
}

int analise_cipher(string message, vector <vector <string>> encrypt, int m) {
	int counter = 0;
	vector<int> arr(m);
	for (int i = 0; i < m; i++)
		arr[i] = i;

	while (1) {
		vector <vector<int>> mask(m, vector<int>(m));
		tryKey(mask, mask.size(), arr);
		if (compare(message, encrypt, mask, &counter)) break;
		nextSet(arr);
		if (counter > 100000) {
			cout << " Analysis failed " << endl;
			break;
		}
	}
	return counter;
}
