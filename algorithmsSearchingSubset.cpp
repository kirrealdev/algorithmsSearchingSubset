#include  <vector>
#include "iostream"
using namespace std;
#include <math.h>
#include <time.h>

int naiveSearch(string text, string str) {
	
    if(text == "" || str == "") return -1;
    
    unsigned int textLength = text.length();
	unsigned int strLength = str.length();
	unsigned int numberOfMatches = 0;
	
    for (unsigned int i = 0; i <= (textLength - strLength); i++) {
        for (unsigned int j = i; j < (i + strLength) && (text[j] == str[j - i]); j++) {
            numberOfMatches++;
            if (numberOfMatches == strLength) return i;
        }
	    numberOfMatches = 0;
	}
	return -1;
}

void prefixFuncForKMP(const string &str, vector<int> &pi) {
 
    pi.resize(str.size());
    pi[0] = 0;
  
    for (int i = 1; i < pi.size(); ++i) {
        int pos = pi[i - 1];
        while (pos > 0 && str[pos] != str[i])
            pos = pi[pos - 1];
        if(str[pos] == str[i]) pi[i] = pos + 1;
        else pi[i] = pos;
    }
}

int searchKMP(string text, string str) {
  
    if(text == "" || str == "") return -1;
  
    unsigned int textLength = text.length();
    unsigned int strLength = str.length();
    vector<int> pi;
    prefixFuncForKMP(str, pi);
    int pos = 0;
  
    for (int i = 0; i < textLength; ++i) {
        while (pos > 0 && (pos >= strLength || str[pos] != text[i]))
            pos = pi[pos-1];
        if (text[i] == str[pos]) pos++;
        if (pos == str.size()) return (i - pos + 1);
    }
    
    return -1;
}

int mod(int a, int b) {
	
	int ret = a%b; 
	return ret>=0? ret: ret+b; 
}

int new_RK(string T, string P) {
	
    int n = T.length();
	int m = P.length();
	int* H = new int[n];
	int* A = new int[n];
	int* anti_A = new int[n];
	int difference = 0;
	const int p = 131;
	int count = 0;
	int a = 127;
    long long powerOfA = 1;
	int curr_hash = 0;
	
	for (int i = 0; i < n; i++) {
		A[i] = powerOfA;
        powerOfA = mod((powerOfA * a), p);
	}
	
	for (int i = 0; i < n; i++) {
		int x = 0;
		while (((mod((A[i] * x), p)) != 1) && (x < p)) {
			x++;
		}
		anti_A[i] = x;
	}

	H[0] = mod((T[0] * 1), p);

	for (int i = 1; i < n; i++) {
		H[i] = mod((H[i - 1] + int(T[i]*A[i])), p);
		
	}
	
	int P_hash = 0;
	for (int i = 0; i < m; i++) {
		P_hash = mod((P_hash + (P[i] * A[i])), p);
	}
	
	curr_hash = mod(H[m - 1], p);

	if (curr_hash == P_hash) {
		for (int k = 0; k < m; k++) {
			if (P[k] == T[k]) 
				count++;
			}
		if (count == m)
			return 0;
		else
			count = -1; 
	}

	for (int j = m + 1; j < n; j++) {
		count = 0;
		int i = j - m;
	
		curr_hash = mod((H[j] - H[i])* anti_A[i + 1], p);
		
		if (curr_hash == P_hash) {
			for (int k = 0; k < m; k++) {
				if (P[k] == T[k + i + 1]) 
					count++;
			}
			if (count == m)
				return i + 1;
			else
				count = -1;
		}
	}
	return -1;
}

int main()
{
	string firstStr = "caaaasdfgcqwerty123";
	string secondStr = "qwerty123";
	
	clock_t start = clock();
	
    cout <<"naive search = "<<naiveSearch(firstStr, secondStr)<<"\n";
	// cout <<"KMP search = "<< searchKMP(firstStr, secondStr)<<"\n";
	// cout << "RK search = " << new_RK(firstStr, secondStr) << "\n";
	clock_t finish = clock();

	double timeInSec = ((double)(finish - start) / (double)CLOCKS_PER_SEC);
    cout << "Time: " << timeInSec << " sec" << endl;
 

    return 0;
}
