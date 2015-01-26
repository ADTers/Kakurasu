#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <ctime>

using namespace std;

int main() {
	int rowsum[10];
	int colsum[10];
	int board[10][10];
	int size = 0;
	
	// Mengisi board dengan angka 0
	memset(board, 0, sizeof(board));
	
	// Membaca board Kakurasu dan menyimpannya dalam array jumlah per baris dan jumlah per kolom
	ifstream in("test.txt");
	
	string firstline;
	getline(in, firstline);
	istringstream first_in(firstline);
	while (first_in) {
		first_in >> size;
	}
	
	string line;
	for (int i=0;i<size;i++) {
		getline(in, line);
		istringstream line_in(line);
		while (line_in) {
			line_in >> rowsum[i];
		}
	}
	
	string lastline;
	getline(in, lastline);
	istringstream last_in(lastline);
	int j = 0;
	while (last_in) {
		last_in >> colsum[j];
		j++;
	}
	    
	clock_t t1,t2;
	t1 = clock();
	
	// Generator kombinasi	
	int combination[50][100][10];
	int bit[10];
	
	memset(combination,0,sizeof(combination));
	memset(bit,0,sizeof(bit));
	
	int sum;
	for(int i=1;i<=((1<<size)-1);i++) {
		bit[0]++;
		sum = 0;
		
		// Membuat kombinasi 1 dan 0 dengan jumlah digit sebanyak size
		for(int j=0;j<size;j++) {
			if (bit[j]==2) {
				bit[j]=0;
				bit[j+1]++;
			}
			if (bit[j]==1) {
				sum += (j+1);
			}
		}
		
		// Menyimpan kombinasi dalam array 3 dimensi
		combination[sum][0][0]++;
		int ccount = combination[sum][0][0];
		for(int j=0;j<size;j++) {
			combination[sum][ccount][j] = bit[j];
		}
	}

	// Algoritma pencarian hasil Kakurasu
	int attempt = 0;
	int key[10];
	bool isValid = false;
	
	for(int i=1;i<size;i++) {
		key[i] = 1;
	}
	
	while (not isValid) {
		key[0]++;
		for(int i=0;i<size;i++) {
			int rsum = rowsum[i];
			
			if (key[i] > combination[rsum][0][0]) { 
				key[i] = 1;
				key[i+1]++;
			};
			
			for(int j=0;j<size;j++) {
				board[i][j] = combination[rsum][key[i]][j];
				if (board[i][j] == 1) attempt++;
			}
			
		};
		
		int count = 0;
		for(int j=0;j<size;j++) {
			int csum = 0;
			for(int k=0;k<size;k++) {
				if (board[k][j] == 1) {
					csum += (k+1);
				}
			}
			if (csum == colsum[j]) { count++; };
		};
		
		if (count == size) { 
			isValid = true; 
			break;
		};
	};
	
	t2=clock();
	// Mencetak hasil ke file
	ofstream res("result.txt");
	
	res << "   ";
	for (int i=0;i<size;i++) {
		res << i+1 << "  ";
	}
	res << endl;
	
	for (int i=0;i<size;i++) {
			res << i+1 << "  ";
		for (int j=0;j<size;j++) {
			res << board[i][j] << "  ";
		};
		res << rowsum[i] << endl;
	}
	
	res << "   ";
	for (int i=0;i<size;i++) {
		res << colsum[i];
		if (colsum[i] >= 10) {
			res << " ";
		} else {
			res << "  ";
		}
	}
	res << endl << endl;
	
	float rtime (((float)t2-(float)t1)/CLOCKS_PER_SEC);
	
	res << "Jumlah pengisian kotak: " << attempt << endl;
	res << "Run time: " << rtime << "s" << endl;
	res << "Run on Toshiba Satellite M840, Intel(R) Core(TM) i7-3632QM @ 2.20GHz, 4GB RAM, Microsoft Windows 8.1 64-bit." << endl;
	return 0;
}
