#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    ifstream file("input_01.txt");
    
    if (!file.is_open()) {
        cout << "problem with opening file." << endl;
        return -1;
    }
    else cout << "filed open successfully" << endl;

    vector<long> arr1;
    vector<long> arr2;
    int a,b;
    while(file >> a >> b) {
        arr1.push_back(a);
        arr2.push_back(b);
    }
    
    if(arr1.empty()) cout << "arr1 empty";

    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());

    long ans=0;
    for(long i=0;i<arr1.size();i++){
        ans += abs(arr1[i]-arr2[i]);
    }

    cout << ans;
}