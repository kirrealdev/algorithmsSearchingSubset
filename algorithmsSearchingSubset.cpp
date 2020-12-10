#include  <vector>
#include <iostream>
#include <math.h>
#include <chrono>
using namespace std;
using namespace chrono;

struct resultOfAlgorithm {
    int answer;
    double time;
};

struct dataForPlot {
    int length;
    double time;
};

resultOfAlgorithm naiveSearch(string text, string str) {
	
    resultOfAlgorithm res;
	res.answer = -1;
	res.time = -1;

	if(text == "" || str == "") return res;
    
    unsigned int textLength = text.length();
	unsigned int strLength = str.length();
	unsigned int numberOfMatches = 0;

	auto start = system_clock::now();

    for (unsigned int i = 0; i <= (textLength - strLength); i++) {
        for (unsigned int j = i; j < (i + strLength) && (text[j] == str[j - i]); j++) {
            numberOfMatches++;
            if (numberOfMatches == strLength) { 
				auto end = system_clock::now();
				duration<double> sec = end - start;
				res.answer = i;
				res.time = sec.count();
				return res;
			}
        }
	    numberOfMatches = 0;
	}
	
	return res;
}

vector<int> prefix_function(const string& s) {
    vector<int> pi(s.length(), 0);

    for (int i = 1; i < s.length(); i++) {
        int j = pi[i - 1];  //текущая длина префикса, который мы хотим продолжить
                            //гарантируется, что s[0..j-1] = s[i-j..i-1].

        while (j > 0 && s[i] != s[j]) {     //пока мы не можем продолжить текущий префикс
            j = pi[j - 1];  //уменьшаем его длину до следующей возможной
        }

        //Теперь j - максимальная длина префикса, который мы можем продолжить,
        //или 0, если такового не существует.

        if (s[i] == s[j]) {
            pi[i] = j + 1;
        } else {    //такое может произойти только при j = 0
            pi[i] = j;
        }
    }

    return pi;
}

resultOfAlgorithm kmp(string s, string t) {
	
	resultOfAlgorithm res;
	res.answer = -1;
	res.time = -1;

	vector<int> pi = prefix_function(t + '#' + s);

    int t_len = t.length();
	auto start = system_clock::now();
    
	for (int i = 0; i < s.length(); i++) {
        if (pi[t_len + 1 + i] == t_len) {
        	auto end = system_clock::now();
			duration<double> sec = end - start;
			res.answer = (i - t_len + 1);
			res.time = sec.count();
			return res;
        }
    }

	return res;
}

int mod(int a, int b) {
	
	int ret = a%b; 
	return ret>=0? ret: ret+b; 
}

resultOfAlgorithm rk(string T, string P) {
	
    resultOfAlgorithm res;
	res.answer = -1;
	res.time = -1;

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
	
	auto start = system_clock::now();

	curr_hash = mod(H[m - 1], p);
	if (curr_hash == P_hash) {
		for (int k = 0; k < m; k++) {
			if (P[k] == T[k]) 
				count++;
			}
		if (count == m) {
			auto end = system_clock::now();
			duration<double> sec = end - start;
			res.answer = 0;
			res.time = sec.count();
			return res;
		}
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
			if (count == m) {
				auto end = system_clock::now();
				duration<double> sec = end - start;
				res.answer = (i + 1);
				res.time = sec.count();
				return res;
			}
			else
				count = -1;
		}
	}
	
	return res;
}

int main()
{		
    // cout <<"naive search = "<<naiveSearch(firstStr, secondStr)<<"\n";
	// cout <<"KMP search = "<< KMPg(secondStr, firstStr)<<"\n";
	// cout << "RK search = " << new_RK(firstStr, secondStr) << "\n";

	string* FirstString = new string[10];
	string* SecondString = new string[10];
	FirstString[0] = "Я помню чудное мгновенье: передо мной явилась ты, как мимолетное виденье, как гений чистой красоты.";
	SecondString[0] = "виденье";
	FirstString[1] = "a^2 + b^2 = c^2";
	SecondString[1] = "b";
	FirstString[2] = "hallelujah";
	SecondString[2] = "h";
	FirstString[3] = "Real Madrid";
	SecondString[3] = "rid";
	FirstString[4] = "Всё зависит от нас самих, ничего в мире нет такого, что не подвластно было б нам.";
	SecondString[4] = "н";
	FirstString[5] = "Анализ и разработка алгоритмов";
	SecondString[5] = "разработка";
	FirstString[6] = "c++, python";
	SecondString[6] = "t";
	FirstString[7] = "ITMM";
	SecondString[7] = "TM";
	FirstString[8] = "Нижегородский государственный университет им. Н. И. Лобачевского";
	SecondString[8] = "им.";
	FirstString[9] = "One, two, three, four, five, six, seven, eight, nine, ten";
	SecondString[9] = "five";
	
	resultOfAlgorithm* naiveResults = new resultOfAlgorithm[10];
	dataForPlot* naiveSearchData = new dataForPlot[10];
	for (int i = 0; i < 10; i++) {
		naiveResults[i] = naiveSearch(FirstString[i], SecondString[i]);
		// cout << "naive answer = " << naiveResults[i].answer << "\n";
		// cout << "naive time = " << naiveResults[i].time << "\n";
		
		naiveSearchData[i].length = FirstString[i].length() + SecondString[i].length();
		naiveSearchData[i].time = naiveResults[i].time;
		cout << "naive data length = " << naiveSearchData[i].length << "\n";
		cout << "naive data time = " << naiveSearchData[i].time << "\n";
		cout << "-----"  << "\n";
	}
	cout << "------------------------------------------"  << "\n";
	resultOfAlgorithm* rkResults = new resultOfAlgorithm[10];
	dataForPlot* rkSearchData = new dataForPlot[10];
	for (int i = 0; i < 10; i++) {
		rkResults[i] = rk(FirstString[i], SecondString[i]);
		// cout << "rk answer = " << rkResults[i].answer << "\n";
		// cout << "rk time = " << rkResults[i].time << "\n";
		
		rkSearchData[i].length = FirstString[i].length() + SecondString[i].length();
		rkSearchData[i].time = rkResults[i].time;
		cout << "rk data length = " << rkSearchData[i].length << "\n";
		cout << "rk data time = " << rkSearchData[i].time << "\n";
		cout << "-----"  << "\n";
	}
	cout << "------------------------------------------"  << "\n";
	resultOfAlgorithm* kmpResults = new resultOfAlgorithm[10];
	dataForPlot* kmpSearchData = new dataForPlot[10];
	for (int i = 0; i < 10; i++) {
		kmpResults[i] = kmp(FirstString[i], SecondString[i]);
		// cout << "kmp answer = " << kmpResults[i].answer << "\n";
		// cout << "kmp time = " << kmpResults[i].time << "\n";
		
		kmpSearchData[i].length = FirstString[i].length() + SecondString[i].length();
		kmpSearchData[i].time = kmpResults[i].time;
		cout << "kmp data length = " << kmpSearchData[i].length << "\n";
		cout << "kmp data time = " << kmpSearchData[i].time << "\n";
		cout << "-----"  << "\n";
	}

    return 0;
}
