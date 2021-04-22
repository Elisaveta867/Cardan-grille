#include "encrypt.h"

int main() {
	int m = 4, k = 0, rt = 0;
	bool key;
	string str;
	cout << " Encryption using Cardan grille. \n Input message: " << endl;
	getline(cin, str);

	while ((str.size() / 4 > m) || ((str.size() / 4 == m) && (str.size() % 4 != 0)))
		m += 4;

	vector <vector<int>> mask(m, vector<int>(m));
	vector <vector <string>> mtx(m, vector<string>(m));
	

	cout << " Choose the encription mode (0 - automatically, 1 - manually): " << endl;
	cin >> key;

	if (key == 1) {
		cout << " Input cut out cells. \n " << m * m / 4 << " cells needed for your message." << endl;
		for (int i = 0; i < m*m / 4; i++) {
			int k, l;
			cin >> k >> l;
			mask[k][l] = -111;
		}
	}
	else {
		randKey(mask, mask.size());
	}

	
	while (rt < 4) {
		for (int i = 0; i < m; i++) 
			for (int j = 0; j < m; j++)
				if ((mask[i][j] == -111) && (k < str.size())) {
					mtx[i][j] = str[k];
					k++;
				}
		rotation(mask, m);
		rt++;
	}

	cout << " Encryption result:" << endl;
	for (int i = 0; i < mtx.size(); i++)
		for (int j = 0; j < mtx.size(); j++)
			cout << mtx[i][j];
	cout << "\n";

	string res;
	k = 0;
	rt = 0;
	while (rt < 4) {
		for (int i = 0; i < mtx.size(); i++)
			for (int j = 0; j < mtx.size(); j++)
				if ((mask[i][j] == -111)) {
					res += mtx[i][j];
					k++;
				}
		rotation(mask, m);
		rt++;
	}

	cout << " Decryption result:" << endl;
	for (int i = 0; i < res.size(); i++)
		cout << res[i];

	cout << "\n Cipher analysis result:" << endl;
	cout << " complexity = " << analise_cipher(str, mtx, m);

	getchar();
	getchar();
	return 0;
}