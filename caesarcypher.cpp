#include <iostream>
using namespace std;

int main() {
    // Write C++ code here
    string str;
    int key;
    cin>>str;
    cin>>key;
    char arr[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    for(int i=0;i<str.length();i++){
        int new_int=str[i]+key;
        if(new_int<=122){
            char newchar=str[i]+key;
            cout<<newchar;
        }
        else{
            int index=new_int-122;
            cout<<arr[index];
        }
    }

    return 0;
}
