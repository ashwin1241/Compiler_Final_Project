#include<bits/stdc++.h>
#include<iostream>
#include"parser.h"
using namespace std;

typedef long long int ll;

TreeNode* treenode = (TreeNode*)malloc(sizeof(TreeNode));

string extract_line_no(string line)
{
    string lno="";
    ll i;
    istringstream ss(line);
    string word;
    vector<string> temp;
    while(ss>>word)
    {
        temp.push_back(word);
    }
    for(i=temp.size()-1;i>=0;i--)
    {
        if(temp[i]=="token")
        {
            lno = temp[i-1];
            break;
        }
    }
    lno.pop_back();
    return lno;
}

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
            return "\n"+line+"\n";
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

string extract_token_type(string line)
{
    string token="";
    ll i;
    istringstream ss(line);
    string word;
    while(ss>>word)
    {
        return word;
    }
    return token;
}

void parse();
void S();
void BEXP();
void A();
bool isoperator(string s);
void EP();
void EXP();
void op();
void var();
void vari();
void code();
void comp();
void type();
void error();

void parse(vector<pair<string,string>> code)
{
    tokens = code;
    S();
}

void S()
{
    if(tokens[ctr].second=="if")
    {
        ctr++;
    }
    else
    {
        cout<<"Error : expected if found "+tokens[ctr].second<<"\n";
        error();
    }
    if(tokens[ctr].second=="(")
        ctr++;
    else
    {
        cout<<"Error : expected ( found "+tokens[ctr].second<<"\n";
        error();
    }
    BEXP();
    if(tokens[ctr].second==")")
        ctr++;
    else
    {
        cout<<"Error : expected ) found "+tokens[ctr].second<<"\n";
        error();
    }
    if(tokens[ctr].second=="{")
        ctr++;
    else
    {
        cout<<"Error : expected { found "+tokens[ctr].second<<"\n";
        error();
    }
    code();
    if(tokens[ctr].second=="}")
        ctr++;
    else
    {
        cout<<"Error : expected } found "+tokens[ctr].second<<"\n";
        error();
    }
    if(tokens[ctr].second=="else")
    {
        ctr++;
        if(tokens[ctr].second=="{")
            ctr++;
        else
        {
            cout<<"Error : expected { found "+tokens[ctr].second<<"\n";
            error();
        }
        code();
        if(tokens[ctr].second=="}")
            ctr++;
        else
        {
            cout<<"Error : expected } found "+tokens[ctr].second<<"\n";
            error();
        }
        cout<<"Parsing complete\n";
        status=true;
        return;
    }
    else
    {
        cout<<"Parsing complete\n";
        status = true;
        return;
    }
}

void A()
{
    if(tokens[ctr].second=="if")
        ctr++;
    else
    {
        cout<<"Error : expected if found "+tokens[ctr].second<<"\n";
        error();
    }
    if(tokens[ctr].second=="(")
        ctr++;
    else
    {
        cout<<"Error : expected ( found "+tokens[ctr].second<<"\n";
        error();
    }
    BEXP();
    if(tokens[ctr].second==")")
        ctr++;
    else
    {
        cout<<"Error : expected ) found "+tokens[ctr].second<<"\n";
        error();
    }
    if(tokens[ctr].second=="{")
        ctr++;
    else
    {
        cout<<"Error : expected { found "+tokens[ctr].second<<"\n";
        error();
    }
    code();
    if(tokens[ctr].second=="}")
        ctr++;
    else
    {
        cout<<"Error : expected } found "+tokens[ctr].second<<"\n";
        error();
    }
    if(tokens[ctr].second=="else")
    {
        ctr++;
        if(tokens[ctr].second=="{")
        ctr++;
        else
        {
            cout<<"Error : expected { found "+tokens[ctr].second<<"\n";
            error();
        }
        code();
        if(tokens[ctr].second=="}")
            ctr++;
        else
        {
            cout<<"Error : expected } found "+tokens[ctr].second<<"\n";
            error();
        }
        return;
    }
    else
    {
        return;
    }
}

void BEXP()
{
    if(tokens[ctr].second=="true"||tokens[ctr].second=="false")
    {
        ctr++;
        return;
    }
    EP();
    comp();
    EP();
}

void code()
{
    if(tokens[ctr].second=="if")
    {
        A();
        if(tokens[ctr].second!="}")
            code();
        else
            return;
    }
    else if(tokens[ctr].first=="Identifier"||tokens[ctr].first=="Keyword")
    {
        EXP();
        if(tokens[ctr].second!="}")
            code();
        else
            return;
    }
    else if(tokens[ctr].second=="}")
        return;
}

void EP()
{
    var();
    if(!isoperator(tokens[ctr].second))
        return;
    op();
    bool truth = tokens[ctr].first=="Identifier"||tokens[ctr].first=="Integer_literal"||tokens[ctr].first=="Floating_point_literal"||tokens[ctr].first=="String_literal";
    if(truth)
    {
        if(isoperator(tokens[ctr+1].second))
            EP();
        else
        {
            ctr++;
            return;
        }
    }
    else
    {
        cout<<"Error : expected variable or constant found "+tokens[ctr].second<<"\n";
        error();
        return;
    }
}

void EXP()
{
    type();
    vari();
    if(tokens[ctr].second=="=")
        ctr++;
    else
    {
        cout<<"Error : expexted = found "+tokens[ctr].second<<"\n";
        error();
    }
    EP();
    if(tokens[ctr].second==";")
    {
        ctr++;
        return;
    }
    else
    {
        cout<<"Error : expected ; found "+tokens[ctr].second<<"\n";
        error();
        return;
    }
}

void comp()
{
    if(tokens[ctr].second=="=="||tokens[ctr].second=="!="||tokens[ctr].second==">="||tokens[ctr].second=="<="||tokens[ctr].second==">"||tokens[ctr].second=="<")
    {
        ctr++;
        return;
    }
    else
    {
        cout<<"Error : expected comparator found "+tokens[ctr].second<<"\n";
        error();
        return;
    }
}

void type()
{
    if(tokens[ctr].first=="Keyword"&&(tokens[ctr].second=="int"||tokens[ctr].second=="float"||tokens[ctr].second=="double"||tokens[ctr].second=="string"||tokens[ctr].second=="char"))
    {
        ctr++;
        return;
    }
    else
    {
        return;
    }
}

void op()
{
    if(tokens[ctr].second=="+"||tokens[ctr].second=="-"||tokens[ctr].second=="*"||tokens[ctr].second=="/"||tokens[ctr].second=="%")
    {
        ctr++;
        return;
    }
    else
    {
        cout<<"Error : expected operator found "+tokens[ctr].second<<"\n";
        error();
        return;
    }
}

void var()
{
    if(tokens[ctr].first=="Identifier"||tokens[ctr].first=="Integer_literal"||tokens[ctr].first=="Floating_point_literal"||tokens[ctr].first=="String_literal")
    {
        ctr++;
        return;
    }
    else
    {
        cout<<"Error : expected variable or constant found "+tokens[ctr].second<<"\n";
        error();
        return;
    }
}

void vari()
{
    if(tokens[ctr].first=="Identifier")
    {
        ctr++;
        return;
    }
    else
    {
        cout<<"Error : expected identifier found "+tokens[ctr].second<<"\n";
        error();
        return;
    }
}

void error()
{
    cout<<"at line number "<<line_no[ctr]<<"\n";
}
 bool isoperator(string s)
 {
    if(s=="+"||s=="-"||s=="*"||s=="/"||s=="%")
        return true;
    else
    return false;
 }

int main()
{
    ifstream ifile; 
    ifile.open("input.txt_output.txt");
    while(ifile)
    {
        string line;
        getline(ifile,line);
        string tkn,tkntype;
        tkntype = extract_token_type(line);
        tkn = extract_token(line);
        if(tkntype=="***")
            cout<<line<<"\n";
        else
        {
            tokens.push_back(make_pair(tkntype,tkn));
            line_no.push_back(extract_line_no(line));
            //cout<<extract_line_no(line)<<"\n";
        }
        //cout<<tokensp[tokensp.size()-1].first<<" ";
    }

    parse(tokens);
    //BEXP();
    if(status)
    {
        ctr=0;
        parse_stack.push("$");
        parsesp(tokens);
    }
    else
    {
        cout<<"Compilation errors detected";
    }

    return 0;
}