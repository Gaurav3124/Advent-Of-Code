#include <bits/stdc++.h>
using namespace std;



int main() {
    ifstream file("/Users/gauravshah/Developer/Advent of Code/2024/input_03.txt");
    if(!file.is_open()) {
        cout << "error opening file";
        return 1;
    }
    
    string s="";
    char ch;
    while(file.get(ch)) {
        s += ch;
    }

    int ans1 = 0;
    int ans2 = 0;
    bool isEnabled = true;
    int n = s.length();
    s+= "############"; //to handle edge case

    // defining lambda function which captures all the args from the encapsulating function by using : [&]
    auto getNumber = [&] (int& i) {
        int x  = 0;
        while(x<1000 && isdigit(s[i])) {
            x = x*10 + (s[i]-'0');
            i++;
        }
        if(x>=1 && x<1000) return x;
        else return -1;
    };

    for(int i =0;i <n; i++) {

        if(s[i] == 'd') {
            if(s.substr(i, 4) == "do()") {
                isEnabled = true;
                i+=4;
            } else if(s.substr(i,7) == "don't()") {
                isEnabled = false;
                i+=7;
            }

        } 

        if(s[i]=='m'){
            if(s[i+1]=='u' && s[i+2]=='l' && s[i+3]=='(' ){
                i+=4;
                int x = getNumber(i); //passing the index
                
                if(s[i]==',') {
                    i++;
                    int y = getNumber(i);

                    if(s[i]==')') {
                        cout << x << " " << y << endl;
                        if(x != -1 && y != -1)  {
                            ans1 += x*y;
                            if(isEnabled) ans2 += x*y;
                        }
                    } else --i; //doing this to accumulate test case : mul(45,mul(56,767) where it registers 56*767
                } else --i; // same to accumulate tc : mul(mul(35,67) to register 35,67
            }
        }
    }
    cout << "answer for part 1 : " << ans1 << endl;
    cout << "answer for part 2 : " << ans2 << endl;
    file.close();
    return 1;
}