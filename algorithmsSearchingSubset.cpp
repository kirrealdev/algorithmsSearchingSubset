#include  <vector>
#include "iostream"
using namespace std;
#include <math.h>

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


int searchRK(string text, string str) {
    
    unsigned int textLength = text.length();
	unsigned int strLength = str.length();
    int hashStr = 0;
    int hashText = 0;
    int count = 0;

    for(int i = 0; i < strLength; i++) {
        hashStr = hashStr + str[i] * pow(13, i);
    }

    for(int i = 0; i < strLength; i++) {
        hashText = hashText + text[i] * pow(13, i);
    }
    count = 0;
    for(int j = 0; j < textLength - strLength + 1; j++) {
        
        if(hashText == hashStr) {
            for(int i = 0; i < strLength; i++) {
                if(str[i] == text[j + i]) {
                    count++;
                }
            }
            if(count == strLength) {
                return j;
            }
            else {
                count = -1;
            }  
        } 
        hashText = (hashText - text[j] * 1) / 13 + text[j + strLength] * pow(13, strLength - 1);
    }
    return -1;
}

int main()
{
	string firstStr = "xbaaaaacb";
	string secondStr = "cb";
	
    cout <<"naive search = "<<naiveSearch(firstStr, secondStr)<<"\n";
    
    cout <<"search KMP = "<< searchKMP(firstStr, secondStr)<<"\n";
    
    cout << "search RK = " << searchRK(firstStr, secondStr) << "\n";

    return 0;
}
