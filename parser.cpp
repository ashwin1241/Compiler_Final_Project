#include<bits/stdc++.h>
#include<iostream>
#include"parser.h"
using namespace std;

typedef long long int ll;

string extract_token(string line)
{
    string token="";
    ll i;
    istringstream ss(line);
    string word;
    bool it=false;
    while(ss>>word)
    {
        if(word=="***")
        {
            return "\n"+line;
        }
        if(it==true)
        {
            token=word;
            it=false;
            break;
        }
        if(word=="string:")
        it=true;
    }
    return token;
}

int main()
{
    ifstream ifile;
    vector<string> tokens;
    ifile.open("input.txt_output.txt");
    while(ifile)
    {
        string line;
        getline(ifile,line);
        tokens.push_back(extract_token(line));
        cout<<tokens[tokens.size()-1]<<" ";
    }
    return 0;
}