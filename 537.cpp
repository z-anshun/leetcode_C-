#include "iostream"
#include "vector"
#include "string"

using namespace std;

class Solution {
public :
    string complexNumberMultiply(string a, string b) {
        string strA, strB;
        string iA, iB;
        split(a, &strA, &iA);
        split(b, &strB, &iB);
        int true_a = stoi(strA);
        int true_b = stoi(strB);
        int fa_a = stoi(iA);
        int fa_b = stoi(iB);


        return to_string(true_a * true_b - fa_a * fa_b) + "+" + to_string(fa_a * true_b + fa_b * true_a) + "i";
    }

    void split(string str, string *tru, string *istr) {
        bool f = false;
        for (int i = 0; i < str.size(); i++) {
            if (str[i] == '+') {
                f = true;
                continue;
            }
            if (str[i] == 'i') {
                break;
            }
            if (!f) {
                (*tru) = (*tru) + str[i];
            } else {
                *istr = (*istr) + str[i];
            }

        }
    }
};

