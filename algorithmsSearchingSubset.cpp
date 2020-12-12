#include  <vector>
#include <iostream>
#include <math.h>
#include <chrono>
#include <fstream>
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
				duration<double, milli> sec = end - start;
				res.answer = i;
				res.time = sec.count();
				return res;
			}
        }
	    numberOfMatches = 0;
	}
	
	return res;
}

vector<int> prefixFunction(const string& s) {
    vector<int> pi(s.length(), 0);

    for (int i = 1; i < s.length(); i++) {
        int j = pi[i - 1];  
                            
        while (j > 0 && s[i] != s[j]) {     
            j = pi[j - 1];  
        }

        if (s[i] == s[j]) {
            pi[i] = j + 1;
        } else {   
            pi[i] = j;
        }
    }

    return pi;
}

resultOfAlgorithm kmp(string text, string str) {
	
	resultOfAlgorithm res;
	res.answer = -1;
	res.time = -1;
	if(text == "" || str == "") return res;

	vector<int> pi = prefixFunction(str + '#' + text);

    int strLen = str.length();
	auto start = system_clock::now();
    
	for (int i = 0; i < text.length(); i++) {
        if (pi[strLen + 1 + i] == strLen) {
        	auto end = system_clock::now();
			duration<double, milli> sec = end - start;
			res.answer = (i - strLen + 1);
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

resultOfAlgorithm rk(string text, string str) {
	
    resultOfAlgorithm res;
	res.answer = -1;
	res.time = -1;

	if(text == "" || str == "") return res;

	int n = text.length();
	int m = str.length();
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

	H[0] = mod((text[0] * 1), p);

	for (int i = 1; i < n; i++) {
		H[i] = mod((H[i - 1] + int(text[i]*A[i])), p);
		
	}
	
	int P_hash = 0;
	for (int i = 0; i < m; i++) {
		P_hash = mod((P_hash + (str[i] * A[i])), p);
	}
	
	auto start = system_clock::now();

	curr_hash = mod(H[m - 1], p);
	if (curr_hash == P_hash) {
		for (int k = 0; k < m; k++) {
			if (str[k] == text[k]) 
				count++;
			}
		if (count == m) {
			auto end = system_clock::now();
			duration<double, milli> sec = end - start;
			res.answer = 0;
			res.time = sec.count();
			return res;
		}
		else
			count = -1; 
	}

	for (int j = m; j < n; j++) {
		count = 0;
		int i = j - m;
	
		curr_hash = mod((H[j] - H[i])* anti_A[i + 1], p);
		
		if (curr_hash == P_hash) {
			for (int k = 0; k < m; k++) {
				if (str[k] == text[k + i + 1]) 
					count++;
			}
			if (count == m) {
				auto end = system_clock::now();
				duration<double, milli> sec = end - start;
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
	string* FirstString = new string[10];
	string* SecondStringTest1 = new string[10];
	string* SecondStringTest2 = new string[10];
	
	FirstString[0] = "abcdefghijklmnop"; //16
	SecondStringTest1[0] = "mnop";
	SecondStringTest2[0] = "fghi";
	
	FirstString[1] = "Real Madrid Footbal Club"; //24
	SecondStringTest1[1] = "l Club";
	SecondStringTest2[1] = "Madrid";
	
	FirstString[2] = "Анализ и разработка алгоритмов!!"; //32
	SecondStringTest1[2] = "ритмов!!";
	SecondStringTest2[2] = "разработ";
	
	FirstString[3] = "U got mud on your face, you big disgrace"; //40
	SecondStringTest1[3] = "disgrace";//8
	SecondStringTest2[3] = " your face";//10
	
	FirstString[4] = "Каждый охотник желает знать, где сидит фазан"; //44
	SecondStringTest1[4] = "сидит фазан";//11
	SecondStringTest2[4] = "желает знать";//12
	
	FirstString[5] = "Институт Информационных Технологий Математики и Механики"; //56
	SecondStringTest1[5] = "ики и Механики";
	SecondStringTest2[5] = "Информационных";
	
	FirstString[6] = "Нижегородский государственный университет им. Н. И. Лобачевского";//64
	SecondStringTest1[6] = " И. Лобачевского";
	SecondStringTest2[6] = "государственный ";
	
	FirstString[7] = "One, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve"; //73
	SecondStringTest1[7] = "ten, eleven, twelve";
	SecondStringTest2[7] = " six, seven, eight";
	
	FirstString[8] = "Всё зависит от нас самих, ничего в мире нет такого, что не подвластно было б нам"; //80
	SecondStringTest1[8] = "одвластно было б нам";
	SecondStringTest2[8] = "чего в мире нет тако";
	
	FirstString[9] = "Я помню чудное мгновенье: передо мной явилась ты, как мимолетное виденье, как гений чистой красоты."; // 99
	SecondStringTest1[9] = "как гений чистой красоты.";
	SecondStringTest2[9] = "ты, как мимолетное виденье";
	
	ofstream fout;
  	fout.open("results.txt");
	fout << "+++++++++++++++++++++++++++++++PART A+++++++++++++++++++++++++++++++++++" << endl;
	fout << "NAIVE ALGORIHTM:" << endl;
	for (int i = 0; i < 10; i++) {
		fout << "<< test #" << i << " >>" << endl;
		
		fout << "end: " << "(" << FirstString[i].length() + SecondStringTest1[i].length() << ", " << naiveSearch(FirstString[i], SecondStringTest1[i]).time << ")" << endl;
		fout << "middle: " << "(" << FirstString[i].length() + SecondStringTest2[i].length() << ", " << naiveSearch(FirstString[i], SecondStringTest2[i]).time << ")" << endl;
	}
	
	fout << "--------------------------------------------------------------------------------" << endl;
	fout << "RK ALGORIHTM:" << endl;
	
	for (int i = 0; i < 10; i++) {
		fout << "<< test #" << i << " >>" << endl;
		
		fout << "end: " << "(" << FirstString[i].length() + SecondStringTest1[i].length() << ", " << rk(FirstString[i], SecondStringTest1[i]).time << ")" << endl;
		fout << "middle: " << "(" << FirstString[i].length() + SecondStringTest2[i].length() << ", " << rk(FirstString[i], SecondStringTest2[i]).time << ")" << endl;
	}
	
	fout << "--------------------------------------------------------------------------------" << endl;
	fout << "KMP ALGORIHTM:" << endl;
	
	for (int i = 0; i < 10; i++) {
		fout << "<< test #" << i << " >>" << endl;
		
		fout << "end: " << "(" << FirstString[i].length() + SecondStringTest1[i].length() << ", " << kmp(FirstString[i], SecondStringTest1[i]).time << ")" << endl;
		fout << "middle: " << "(" << FirstString[i].length() + SecondStringTest2[i].length() << ", " << kmp(FirstString[i], SecondStringTest2[i]).time << ")" << endl;
	}

	fout << "+++++++++++++++++++++++++++++++PART B+++++++++++++++++++++++++++++++++++" << endl;
	string* FirstString2 = new string[10];
	string* SecondStringTest4 = new string[10];
	string* SecondStringTest5 = new string[10];
	
	FirstString2[0] = "fskjfjsdkfjsdjkf"; //16
	SecondStringTest4[0] = "djkf";
	SecondStringTest5[0] = "sdkf";
	
	FirstString2[1] = "fskjfjsdkfjsdjkfweiowdmb"; //24
	SecondStringTest4[1] = "iowdmb";
	SecondStringTest5[1] = "dkfjsd";
	
	FirstString2[2] = "fskjfjsdkfjsdjkfweiowdmboppaqaax"; //32
	SecondStringTest4[2] = "oppaqaax";
	SecondStringTest5[2] = "kfjsdjkf";
	
	FirstString2[3] = "fskjfjsdkfjsdjkfweiowdmboppaqaaxzzxxccvv"; //40
	SecondStringTest4[3] = "axzzxxccvv";
	SecondStringTest5[3] = "jsdjkfweio";
	
	FirstString2[4] = "fskjfjsdkfjsdjkfweiowdmboppaqaaxzzxxccvvyuyighik"; //48
	SecondStringTest4[4] = "ccvvyuyighik";
	SecondStringTest5[4] = "weiowdmboppa";
	
	FirstString2[5] = "fskjfjsdkfjsdjkfweiowdmboppaqaaxzzxxccvvyuyighikalllolop"; //56
	SecondStringTest4[5] = "yighikalllolop";
	SecondStringTest5[5] = "iowdmboppaqaax";
	
	FirstString2[6] = "fskjfjsdkfjsdjkfweiowdmboppaqaaxzzxxccvvyuyighikalllolophgfdjkfs";//64
	SecondStringTest4[6] = "alllolophgfdjkfs";
	SecondStringTest5[6] = "boppaqaaxzzxxccv";
	
	FirstString2[7] = "fskjfjsdkfjsdjkfweiowdmboppaqaaxzzxxccvvyuyighikalllolophgfdjkfsnmbvcdde"; //72
	SecondStringTest4[7] = "ophgfdjkfsnmbvcdde";
	SecondStringTest5[7] = "dmboppaqaaxzzxxccv";
	
	FirstString2[8] = "fskjfjsdkfjsdjkfweiowdmboppaqaaxzzxxccvvyuyighikalllolophgfdjkfsnmbvcddecnjaskas"; //80
	SecondStringTest4[8] = "jkfsnmbvcddecnjaskas";
	SecondStringTest5[8] = "ccvvyuyighikalllolop";
	
	FirstString2[9] = "fskjfjsdkfjsdjkfweiowdmboppaqaaxzzxxccvvyuyighikalllolophgfdjkfsnmbvcddecnjaskasxcasdfsd"; // 88
	SecondStringTest4[9] = "bvcddecnjaskasxcasdfsd";
	SecondStringTest5[9] = "axzzxxccvvyuyighikalll";
  	
	fout << "NAIVE ALGORIHTM:" << endl;
	for (int i = 0; i < 10; i++) {
		fout << "<< test #" << i << " >>" << endl;
		
		fout << "end: " << "(" << FirstString2[i].length() + SecondStringTest4[i].length() << ", " << naiveSearch(FirstString2[i], SecondStringTest4[i]).time << ")" << endl;
		fout << "middle: " << "(" << FirstString2[i].length() + SecondStringTest5[i].length() << ", " << naiveSearch(FirstString2[i], SecondStringTest5[i]).time << ")" << endl;
	}
	
	fout << "--------------------------------------------------------------------------------" << endl;
	fout << "RK ALGORIHTM:" << endl;

	for (int i = 0; i < 10; i++) {
		fout << "<< test #" << i << " >>" << endl;
		
		fout << "end: " << "(" << FirstString2[i].length() + SecondStringTest4[i].length() << ", " << rk(FirstString2[i], SecondStringTest4[i]).time << ")" << endl;
		fout << "middle: " << "(" << FirstString2[i].length() + SecondStringTest5[i].length() << ", " << rk(FirstString2[i], SecondStringTest5[i]).time << ")" << endl;
	}
	
	fout << "--------------------------------------------------------------------------------" << endl;
	fout << "KMP ALGORIHTM:" << endl;


	for (int i = 0; i < 10; i++) {
		fout << "<< test #" << i << " >>" << endl;
		
		fout << "end: " << "(" << FirstString2[i].length() + SecondStringTest4[i].length() << ", " << kmp(FirstString2[i], SecondStringTest4[i]).time << ")" << endl;
		fout << "middle: " << "(" << FirstString2[i].length() + SecondStringTest5[i].length() << ", " << kmp(FirstString2[i], SecondStringTest5[i]).time << ")" << endl;
	}

	fout.close();
    
	return 0;
}
