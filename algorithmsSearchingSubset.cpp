#include  <vector>
#include "iostream"
using namespace std;
#define BASE 10000000
int naiveSearch(string firstString, string secondString) {
	
    if(firstString == "" or secondString == "") return -1;
    
    int lengthFirstStr = firstString.length();
	int lengthSecondStr = secondString.length();
	int numberOfMatchedChars = 0;
	
    for (int i = 0; i <= lengthFirstStr - lengthSecondStr; i++) {
		for (int j = i; j < i + lengthSecondStr; j++) {
			if (firstString[j] == secondString[j - i]) {
				numberOfMatchedChars++;
                if (numberOfMatchedChars == lengthSecondStr)
                    return i;
            }
			else 
				numberOfMatchedChars = 0;
		}
	}
	return -1;
}

int KMP(string t, string p) {
	
    if(t == "" or p == "") return -1;
    
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

int rabinKarpSearch(string source, string target){
        
        if(source == "" or target == "") return -1;
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

int main()
{
	string firstStr = "ffjfjsadjdkfsaffjkfsa";
	string secondStr = "sa";
	cout <<"naive = "<<naiveSearch(firstStr, secondStr)<<"\n";
	cout <<"KMP = "<< KMP(firstStr, secondStr)<<"\n";
	cout << "RK = " << rabinKarpSearch(firstStr, secondStr) << "\n";
	return 0;
}
