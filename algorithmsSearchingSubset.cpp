#include  <vector>
#include "iostream"
using namespace std;
#define BASE 10000000

int naiveSearch(string text, string str) {
	
    if(text == "" || str == "") return -1;
    
    unsigned int textLength = text.length();
	unsigned int strLength = str.length();
	unsigned int numberOfMatches = 0;
	
    for (unsigned int i = 0; i <= (textLength - strLength); i++) {
        for (unsigned int j = i; j < (i + strLength) && text[j] == str[j - i]; j++) {
            numberOfMatches++;
            if (numberOfMatches == strLength) return i;
        }
	    numberOfMatches = 0;
	}
	return -1;
}

int KMP(string t, string p) {
	
    if(t == "" || p == "") return -1;
    
    int n = t.length();
	int m = p.length();

	int *d = new int[m];
	d[0] = 0;
	for (int i = 1, j = 0; i < m; i++) {
		while (j > 0 && p[j] != p[i])
			j = d[j - 1];
		if (p[j] == p[i])
			j++;
		d[i] = j;	
	}
	for (int i = 0, j = 0; i < n; i++) {
		while (j > 0 && p[j] != t[i])
			j = d[j - 1];
		if (p[j] == t[i])
			j++;
		if (j == m)
		{
			delete d;
			return i - j + 1;
		}
	}
	delete d;
	return -1;
}

int rabinKarpSearch2(string source, string target){
        
        if(source == "" || target == "") return -1;
        int m = target.size();
        int power = 1;
        for(int i = 0;i<m;i++){
            power = (power*31)%BASE;
        }
        int targetCode = 0;
        for(int i = 0;i<m;i++){
            targetCode = (targetCode*31+target[i])%BASE;
        }
        int hashCode = 0;
        for(int i = 0;i<source.size();i++){
            hashCode = (hashCode*31 + source[i])%BASE;
            if(i<m-1) continue;
            if(i>=m){
                hashCode = (hashCode-source[i-m]*power)%BASE;
            }
            if(hashCode<0)
                hashCode+=BASE;
            if(hashCode == targetCode){
                if(source.substr(i-m+1,m) == target)
                    return i-m+1;
            }
        }
        return -1;
    }

int hInit(unsigned int strLength) {
    
    int d = 52;
    int p = 65713;

    int h = 1;
    for(unsigned int i = 1; i < strLength; i++) {
        h = (h * d) % p;
    }

    return h;
}

int ringHash(string str, unsigned int strLength, int prevHash, int *h) {
    
      // h = d^(len-1) (mod p) - константа для быстроого пересчета хэша
    int d = 52; // Константа из формулы
    int p = 65713; // Вычисления производятся по модулю простого числа
    
    if(*h == 0) *h = hInit(strLength);

    if(prevHash == 0) {
        for(unsigned int i = 0; i < strLength; i++) {
            prevHash += (d*prevHash + (int)str[i]) % p;
        }
        if(prevHash < 0) prevHash += p;
        return prevHash;
    }
    else {
        int hash = (d * (prevHash - (int)str[0] * (*h)) + (int)str[strLength]) % p;
        if(hash < 0) hash += p;
        return hash;
    }
}
	int rabinKarpSearch(string text, string str) {
        
		if(text == "" or str == "") return -1;

		unsigned int textLength = text.length();
		unsigned int strLength = str.length();
        
		int h = 0;
		
        //Хэш подстроки для поиска
        int strHash = ringHash(str, strLength, 0, &h);
        //Хэш первого окна в тексте
        int textHash = ringHash(text, strLength, 0, &h);

        for(unsigned int i = 0; i <= (textLength-strLength); i++) {
            if(strHash == textHash) {
                for(unsigned int j = 0; (j < strLength) && (str[j] == text[i+i]); j++) {
                    if(j == (strLength - 1)) return i;
                }
            }
            textHash = ringHash(&text[i], strLength, textHash, &h);
        }
        return -1;
}

int main()
{
	string firstStr = "cbaaaaacb";
	string secondStr = "cb";
	cout <<"naive = "<<naiveSearch(firstStr, secondStr)<<"\n";
	cout <<"KMP = "<< KMP(firstStr, secondStr)<<"\n";
	cout << "RK = " << rabinKarpSearch(firstStr, secondStr) << "\n";
	cout << "RK = " << rabinKarpSearch2(firstStr, secondStr) << "\n";
	return 0;
}
