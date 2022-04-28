#include<bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long int ll;

stack<string> parse_stack;
vector<pair<string,string>> tokens;
vector<string> line_no;
ll ctr=0;
bool status=false;
typedef struct TreeNode
{
    string var;
    struct TreeNode* parent;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;
void parsesp();
void Ssp();
void BEXPsp();
void Asp();
bool isoperatorsp(string s);
void EPsp();
void EXPsp();
void opsp();
void varsp();
void varisp();
void codesp();
void compsp();
void typesp();
void errorsp();

void parsesp(vector<pair<string,string>> code)
{
    tokens = code;
    parse_stack.push("S");
    cout<<"Parse stack during parsing :\nS|$|\n";
    Ssp();
}

void Ssp()
{
    parse_stack.pop();
    parse_stack.push("ELSE");
    parse_stack.push("}");
    parse_stack.push("code");
    parse_stack.push("{");
    parse_stack.push(")");
    parse_stack.push("BEXP");
    parse_stack.push("(");
    parse_stack.push("if");
    vector<string> apsp;
    while(!parse_stack.empty())
    {
        apsp.push_back(parse_stack.top());
        cout<<parse_stack.top()<<"|";
        parse_stack.pop();
    }
    cout<<"\n";
    for(ll i=apsp.size()-1;i>=0;i--)
        parse_stack.push(apsp[i]);

    if(tokens[ctr].second=="if")
    {
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        ctr++;
    }
    else
    {
        //cout<<"Error : expected if found "+tokens[ctr].second<<"\n";
        errorsp();
    }
    if(tokens[ctr].second=="(")
    {
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        ctr++;
    }
    else
    {
        //cout<<"Error : expected ( found "+tokens[ctr].second<<"\n";
        errorsp();
    }
    BEXPsp();
    if(tokens[ctr].second==")")
    {
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        ctr++;
    }
    else
    {
        //cout<<"Error : expected ) found "+tokens[ctr].second<<"\n";
        errorsp();
    }
    if(tokens[ctr].second=="{")
    {
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        ctr++;
    }
    else
    {
        //cout<<"Error : expected { found "+tokens[ctr].second<<"\n";
        errorsp();
    }
    codesp();
    if(tokens[ctr].second=="}")
    {
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        ctr++;
    }
    else
    {
        //cout<<"Error : expected } found "+tokens[ctr].second<<"\n";
        errorsp();
    }
    if(tokens[ctr].second!="else")
    {
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
    }
    if(tokens[ctr].second=="else")
    {
        parse_stack.pop();
        parse_stack.push("}");
        parse_stack.push("code");
        parse_stack.push("{");
        parse_stack.push("else");
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        ctr++;

        if(tokens[ctr].second=="{")
        {
            parse_stack.pop();
            apsp.clear();
            while(!parse_stack.empty())
            {
                apsp.push_back(parse_stack.top());
                cout<<parse_stack.top()<<"|";
                parse_stack.pop();
            }
            cout<<"\n";
            for(ll i=apsp.size()-1;i>=0;i--)
                parse_stack.push(apsp[i]);
            ctr++;
        }
        else
        {
            //cout<<"Error : expected { found "+tokens[ctr].second<<"\n";
            errorsp();
        }
        codesp();
        if(tokens[ctr].second=="}")
        {
            parse_stack.pop();
            apsp.clear();
            while(!parse_stack.empty())
            {
                apsp.push_back(parse_stack.top());
                cout<<parse_stack.top()<<"|";
                parse_stack.pop();
            }
            cout<<"\n";
            for(ll i=apsp.size()-1;i>=0;i--)
                parse_stack.push(apsp[i]);
            ctr++;
        }
        else
        {
            //cout<<"Error : expected } found "+tokens[ctr].second<<"\n";
            errorsp();
        }
        //cout<<"Parsing complete\n";
        status=true;
        return;
    }
    else
    {
        //cout<<"Parsing complete\n";
        status = true;
        return;
    }
}

void Asp()
{
    parse_stack.pop();
    parse_stack.push("ELSE");
    parse_stack.push("}");
    parse_stack.push("code");
    parse_stack.push("{");
    parse_stack.push(")");
    parse_stack.push("BEXP");
    parse_stack.push("(");
    parse_stack.push("if");
    vector<string> apsp;
    while(!parse_stack.empty())
    {
        apsp.push_back(parse_stack.top());
        cout<<parse_stack.top()<<"|";
        parse_stack.pop();
    }
    cout<<"\n";
    for(ll i=apsp.size()-1;i>=0;i--)
        parse_stack.push(apsp[i]);

    if(tokens[ctr].second=="if")
    {
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        ctr++;
    }
    else
    {
        //cout<<"Error : expected if found "+tokens[ctr].second<<"\n";
        errorsp();
    }
    if(tokens[ctr].second=="(")
    {
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        ctr++;
    }
    else
    {
        //cout<<"Error : expected ( found "+tokens[ctr].second<<"\n";
        errorsp();
    }
    BEXPsp();
    if(tokens[ctr].second==")")
    {
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        ctr++;
    }
    else
    {
        //cout<<"Error : expected ) found "+tokens[ctr].second<<"\n";
        errorsp();
    }
    if(tokens[ctr].second=="{")
    {
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        ctr++;
    }
    else
    {
        //cout<<"Error : expected { found "+tokens[ctr].second<<"\n";
        errorsp();
    }
    codesp();
    if(tokens[ctr].second=="}")
    {
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        ctr++;
    }
    else
    {
        //cout<<"Error : expected } found "+tokens[ctr].second<<"\n";
        errorsp();
    }
    if(tokens[ctr].second!="else")
    {
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
    }
    if(tokens[ctr].second=="else")
    {
        parse_stack.pop();
        parse_stack.push("}");
        parse_stack.push("code");
        parse_stack.push("{");
        parse_stack.push("else");
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        ctr++;

        if(tokens[ctr].second=="{")
        {
            parse_stack.pop();
            apsp.clear();
            while(!parse_stack.empty())
            {
                apsp.push_back(parse_stack.top());
                cout<<parse_stack.top()<<"|";
                parse_stack.pop();
            }
            cout<<"\n";
            for(ll i=apsp.size()-1;i>=0;i--)
                parse_stack.push(apsp[i]);
            ctr++;
        }
        else
        {
            //cout<<"Error : expected { found "+tokens[ctr].second<<"\n";
            errorsp();
        }
        codesp();
        if(tokens[ctr].second=="}")
        {
            parse_stack.pop();
            apsp.clear();
            while(!parse_stack.empty())
            {
                apsp.push_back(parse_stack.top());
                cout<<parse_stack.top()<<"|";
                parse_stack.pop();
            }
            cout<<"\n";
            for(ll i=apsp.size()-1;i>=0;i--)
                parse_stack.push(apsp[i]);
            ctr++;
        }
        else
        {
            //cout<<"Error : expected } found "+tokens[ctr].second<<"\n";
            errorsp();
        }
        //cout<<"Parsing complete\n";
        //status=true;
        return;
    }
    else
    {
        //cout<<"Parsing complete\n";
        //status = true;
        return;
    }
}

void BEXPsp()
{
    parse_stack.pop();
    vector<string> apsp;

    if(tokens[ctr].second=="true"||tokens[ctr].second=="false")
    {
        parse_stack.push(tokens[ctr].second);
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        ctr++;
        return;
    }

    parse_stack.push("EP");
    parse_stack.push("comp");
    parse_stack.push("EP");

    while(!parse_stack.empty())
    {
        apsp.push_back(parse_stack.top());
        cout<<parse_stack.top()<<"|";
        parse_stack.pop();
    }
    cout<<"\n";
    for(ll i=apsp.size()-1;i>=0;i--)
        parse_stack.push(apsp[i]);
    EPsp();
    compsp();
    EPsp();
}

void codesp()
{
    parse_stack.pop();
    vector<string> apsp;
    if(tokens[ctr].second=="if")
    {
        parse_stack.push("code");
        parse_stack.push("S");
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        Asp();
        if(tokens[ctr].second!="}")
        {
            codesp();
        }
        else
        {
            parse_stack.pop();
            apsp.clear();
            while(!parse_stack.empty())
            {
                apsp.push_back(parse_stack.top());
                cout<<parse_stack.top()<<"|";
                parse_stack.pop();
            }
            cout<<"\n";
            for(ll i=apsp.size()-1;i>=0;i--)
                parse_stack.push(apsp[i]);
            return;
        }
    }
    else if(tokens[ctr].first=="Identifier"||tokens[ctr].first=="Keyword")
    {
        parse_stack.push("code");
        parse_stack.push("EXP");
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        EXPsp();
        if(tokens[ctr].second!="}")
        {
            codesp();
        }
        else
        {
            parse_stack.pop();
            apsp.clear();
            while(!parse_stack.empty())
            {
                apsp.push_back(parse_stack.top());
                cout<<parse_stack.top()<<"|";
                parse_stack.pop();
            }
            cout<<"\n";
            for(ll i=apsp.size()-1;i>=0;i--)
                parse_stack.push(apsp[i]);
            return;
        }
    }
    else if(tokens[ctr].second=="}")
    {
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        return;
    }
}

void EPsp()
{
    parse_stack.pop();
    parse_stack.push("CONT");
    parse_stack.push("var");
    vector<string> apsp;
    while(!parse_stack.empty())
    {
        apsp.push_back(parse_stack.top());
        cout<<parse_stack.top()<<"|";
        parse_stack.pop();
    }
    cout<<"\n";
    for(ll i=apsp.size()-1;i>=0;i--)
        parse_stack.push(apsp[i]);

    varsp();
    if(!isoperatorsp(tokens[ctr].second))
    {
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        return;
    }
    opsp();
    bool truth = tokens[ctr].first=="Identifier"||tokens[ctr].first=="Integer_literal"||tokens[ctr].first=="Floating_point_literal"||tokens[ctr].first=="String_literal";
    if(truth)
    {
        if(isoperatorsp(tokens[ctr+1].second))
            EPsp();
        else
        {
            parse_stack.pop();
            parse_stack.push("var");
            apsp.clear();
            while(!parse_stack.empty())
            {
                apsp.push_back(parse_stack.top());
                cout<<parse_stack.top()<<"|";
                parse_stack.pop();
            }
            cout<<"\n";
            for(ll i=apsp.size()-1;i>=0;i--)
                parse_stack.push(apsp[i]);
            parse_stack.pop();
            parse_stack.push(tokens[ctr].second);
            apsp.clear();
            while(!parse_stack.empty())
            {
                apsp.push_back(parse_stack.top());
                cout<<parse_stack.top()<<"|";
                parse_stack.pop();
            }
            cout<<"\n";
            for(ll i=apsp.size()-1;i>=0;i--)
                parse_stack.push(apsp[i]);
            parse_stack.pop();
            apsp.clear();
            while(!parse_stack.empty())
            {
                apsp.push_back(parse_stack.top());
                cout<<parse_stack.top()<<"|";
                parse_stack.pop();
            }
            cout<<"\n";
            for(ll i=apsp.size()-1;i>=0;i--)
                parse_stack.push(apsp[i]);
            ctr++;
            return;
        }
    }
    else
    {
        //cout<<"Error : expected variable or constant found "+tokens[ctr].second<<"\n";
        errorsp();
        return;
    }
}

void EXPsp()
{
    parse_stack.pop();
    parse_stack.push(";");
    parse_stack.push("EP");
    parse_stack.push("=");
    parse_stack.push("var");
    parse_stack.push("type");
    vector<string> apsp;
    while(!parse_stack.empty())
    {
        apsp.push_back(parse_stack.top());
        cout<<parse_stack.top()<<"|";
        parse_stack.pop();
    }
    cout<<"\n";
    for(ll i=apsp.size()-1;i>=0;i--)
        parse_stack.push(apsp[i]);
    typesp();
    varisp();
    
    if(tokens[ctr].second=="=")
    {
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        ctr++;
    }
    else
    {
        //cout<<"Error : expexted = found "+tokens[ctr].second<<"\n";
        errorsp();
    }
    EPsp();
    if(tokens[ctr].second==";")
    {
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        ctr++;
        return;
    }
    else
    {
        //cout<<"Error : expected ; found "+tokens[ctr].second<<"\n";
        errorsp();
        return;
    }
}

void compsp()
{
    vector<string> apsp;
    if(tokens[ctr].second=="=="||tokens[ctr].second=="!="||tokens[ctr].second==">="||tokens[ctr].second=="<="||tokens[ctr].second==">"||tokens[ctr].second=="<")
    {
        parse_stack.pop();
        parse_stack.push(tokens[ctr].second);
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        ctr++;
        return;
    }
    else
    {
        //cout<<"Error : expected comparator found "+tokens[ctr].second<<"\n";
        errorsp();
        return;
    }
}

void typesp()
{
    vector<string> apsp;
    if(tokens[ctr].first=="Keyword"&&(tokens[ctr].second=="int"||tokens[ctr].second=="float"||tokens[ctr].second=="double"||tokens[ctr].second=="string"||tokens[ctr].second=="char"))
    {
        parse_stack.pop();
        parse_stack.push(tokens[ctr].second);
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        ctr++;
        return;
    }
    else
    {
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        return;
    }
}

void opsp()
{
    vector<string> apsp;
    if(tokens[ctr].second=="+"||tokens[ctr].second=="-"||tokens[ctr].second=="*"||tokens[ctr].second=="/"||tokens[ctr].second=="%")
    {
        parse_stack.pop();
        parse_stack.push("EP");
        parse_stack.push("op");
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        parse_stack.pop();
        parse_stack.push(tokens[ctr].second);
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        ctr++;
        return;
    }
    else
    {
        //cout<<"Error : expected operator found "+tokens[ctr].second<<"\n";
        errorsp();
        return;
    }
}

void varsp()
{
    vector<string> apsp;
    if(tokens[ctr].first=="Identifier"||tokens[ctr].first=="Integer_literal"||tokens[ctr].first=="Floating_point_literal"||tokens[ctr].first=="String_literal")
    {
        parse_stack.pop();
        parse_stack.push(tokens[ctr].second);
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        ctr++;
        return;
    }
    else
    {
        //cout<<"Error : expected variable or constant found "+tokens[ctr].second<<"\n";
        errorsp();
        return;
    }
}

void varisp()
{
    vector<string> apsp;
    if(tokens[ctr].first=="Identifier")
    {
        parse_stack.pop();
        parse_stack.push(tokens[ctr].second);
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        parse_stack.pop();
        apsp.clear();
        while(!parse_stack.empty())
        {
            apsp.push_back(parse_stack.top());
            cout<<parse_stack.top()<<"|";
            parse_stack.pop();
        }
        cout<<"\n";
        for(ll i=apsp.size()-1;i>=0;i--)
            parse_stack.push(apsp[i]);
        ctr++;
        return;
    }
    else
    {
        //cout<<"Error : expected identifier found "+tokens[ctr].second<<"\n";
        errorsp();
        return;
    }
}

void errorsp()
{
    //cout<<"at line number "<<line_no[ctr]<<"\n";
    parse_stack.pop();
}
 bool isoperatorsp(string s)
 {
    if(s=="+"||s=="-"||s=="*"||s=="/"||s=="%")
        return true;
    else
    return false;
 }



