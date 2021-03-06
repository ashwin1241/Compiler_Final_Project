#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>


typedef long long int ll;

using namespace std;

map<string,int> token_id,pti;
ll ctr=1000;
vector<char> spchar = {'!','%','^','&','*','(',')','-','+','+','{','[','}',']',':',';','/',',','<','>','='};
vector<string> binop = {"<<",">>","<=",">=","==","+=","-=","*=","!=","!=","&&","||",":=","++","--","//"};
vector<string> delimiter = {"{", "}", "(", ")", "[", "]", ";", ","};
vector<string> oprator = {"<<",">>","<", ">", "<=", ">=", "*", "+", "-", "/", "=", "-=", "*=", "+=", "!=", "++", "--", "=="};
vector<string> keywords = {"char","cout","cin","return","void","int","main", "float", "boolean", "string", "while", "until", "if" ,"else", "true", "false", "continue", "break","double"};

bool isKeyword(string word){
    if(find(keywords.begin(), keywords.end(), word) != keywords.end())
    {
        if(pti.find(word)==pti.end())
        {
            pti[word]=token_id[word];
        }
        return true;
    }
    else
    return false;
}

bool isOperator(string word){
    if(find(oprator.begin(), oprator.end(), word) != oprator.end())
    {
        if(pti.find(word)==pti.end())
        {
            pti[word]=token_id[word];
        }
        return true;
    }
    else
    return false;
}

bool isDelimiter(string word){
    if(find(delimiter.begin(), delimiter.end(), word) != delimiter.end())
    {
        if(pti.find(word)==pti.end())
        {
            pti[word]=token_id[word];
        }
        return true;
    }
    else
    return false;
}

bool isString(string word){
    if(word[0] == '"' && word[word.size()-1] == '"')
    {
        if(token_id.find(word)==token_id.end())
        {
            token_id[word]=ctr;
            pti[word]=token_id[word];
            ctr++;
        }
        return true;
    }
    else
    return false;
}

bool isInteger(string word){
    for(int i=0;i<word.size();i++){
        if(word[i]>='0'&&word[i]<='9')
        continue;
        return false;
    }
    word= regex_replace(word, regex("^0+"), "");
    if(word.size()==0)
    word+="0";
    if(token_id.find(word)==token_id.end())
    {
        token_id[word]=ctr;
        pti[word]=ctr;
        ctr++;
    }
    return true;
}

bool isFloat(string word){
    int t=-1;
    for(int i=0;i<word.size();i++){
        if(word[i]=='.'){
            t=i;
            break;
        }
    }

    if(t==-1)
    return false;

    string beforeDecimal = word.substr(0, t);
    string afterDecimal = word.substr(t + 1);

    word= regex_replace(word, regex("^0+"), "");
    reverse(word.begin(), word.end());
    word= regex_replace(word, regex("^0+"), "");
    reverse(word.begin(), word.end());
    if(word[0]=='.')
    word="0"+word;

    if(isInteger(beforeDecimal) && isInteger(afterDecimal))
    {
        if(token_id.find(word)==token_id.end())
        {
            token_id[word]=ctr;
            pti[word]=ctr;
            ctr++;
        }
        return true;
    }
    else
    return false;
}

bool isIdentifier(string word){
    char x = word[0];
    if(!isKeyword(word)&&((x>='a'&&x<='z')||(x>='A'&&x<='Z')||(x=='_')))
    {
        int i;
        for(i=1;i<word.size();i++)
        {
            x=word[i];
            bool t = (x>='0'&&x<='9')||(x>='a'&&x<='z')||(x>='A'&&x<='Z')||(x=='_');
            if(!t)
                return false;
        }
        if(token_id.find(word)==token_id.end())
        {
            token_id[word]=ctr;
            pti[word]=token_id[word];
            ctr++;
        }
        return true;
    }
    else
    return false;
}

void tokenize(string inputCode,int i,ofstream& output_file){
    
    bool isComment=false;

    if(inputCode[0]=='"'){
        if(isString(inputCode))
        output_file<<"String_literal token, string: "<<inputCode<<" , line number: "<<i+1<<", token id: "<<token_id[inputCode]<<"\n";
        else
        output_file<<"*** Invalid token, string: "<<inputCode<<" , at line number: "<<i+1<<" ***\n";
        return;
    }

        istringstream ss(inputCode);
        string word;
        while (ss >> word) 
        {
            if(word=="//")
            {
                isComment=true;
                break;
            }

            if(isKeyword(word))
            output_file<<"Keyword token, string: "<<word<<" , line number: "<<i+1<<", token id: "<<token_id[word]<<"\n";
            else if(isOperator(word))
            output_file<<"Operator token, string: "<<word<<" , line number: "<<i+1<<", token id: "<<token_id[word]<<"\n";
            else if(isDelimiter(word))
            output_file<<"Delimiter token, string: "<<word<<" , line number: "<<i+1<<", token id: "<<token_id[word]<<"\n";
            else if(isString(word))
            output_file<<"String_literal token, string: "<<word<<" , line number: "<<i+1<<", token id: "<<token_id[word]<<"\n";
            else if(isInteger(word)){
                word= regex_replace(word, regex("^0+"), "");
                if(word.size()==0)
                word+="0";
                output_file<<"Integer_literal token, string: "<<word<<" , line number: "<<i+1<<", token id: "<<token_id[word]<<"\n";
            }
            else if(isFloat(word)){
                word= regex_replace(word, regex("^0+"), "");
                reverse(word.begin(), word.end());
                word= regex_replace(word, regex("^0+"), "");
                reverse(word.begin(), word.end());
                if(word[0]=='.')
                word="0"+word;
                output_file<<"Floating_point_literal token, string: "<<word<<" , line number: "<<i+1<<", token id: "<<token_id[word]<<"\n";
            }
            else if(isIdentifier(word))
            output_file<<"Identifier token, string: "<<word<<" , line number: "<<i+1<<", token id: "<<token_id[word]<<"\n";
            else
            output_file<<"*** Invalid token, string: "<<word<<" , at line number: "<<i+1<<" ***\n";

        }

        if(isComment)
        {
            isComment=false;
            return;
        }
}

string preProcess(string line){

    string newLine="";
    for(int i=0;i<line.size();i++) 
    {
    
    	if(line[i]=='"'){
            newLine+=line[i++];
            while(line[i]!='"' && i<line.size()){
                newLine+=line[i];
                i++;
            }
            if(i<line.size() && line[i]=='"')
            {newLine+='"';}
            if(i>=line.size())
            return newLine;
            continue;
        }
    	
        string bop="";
        if(i<line.size()-1){
            bop.push_back(line[i]);
            bop.push_back(line[i+1]);
        }
        
        if(find(binop.begin(),binop.end(),bop)!=binop.end()){
            newLine=newLine+" "+line[i]+line[i+1]+" ";
            i++;
        }
        else if(find(spchar.begin(),spchar.end(),line[i])!=spchar.end())
        newLine=newLine+" "+line[i]+" ";
        else 
        newLine=newLine+line[i];
    }
    return newLine;
}

void generate_symbol_table(vector<string> inputcode,string filename)
{
    ofstream symbolTable(filename+"_symbol_table.txt");
    if(!symbolTable.is_open())
    {
        cerr<<"Coud not generate symbol table\n";
        return;
    }
    int i;
    symbolTable<<"Keywords:\n";
    for(auto x : pti)
    {
        if(isKeyword(x.first))
        symbolTable<<x.first<<" : "<<x.second<<"\n";
    }
    symbolTable<<"\n";
    symbolTable<<"Identifiers:\n";
    for(auto x : pti)
    {
        if(isIdentifier(x.first))
        symbolTable<<x.first<<" : "<<x.second<<"\n";
    }
    symbolTable<<"\n";
    symbolTable<<"Operators:\n";
    for(auto x : pti)
    {
        if(isOperator(x.first))
        symbolTable<<x.first<<" : "<<x.second<<"\n";
    }
    symbolTable<<"\n";
    symbolTable<<"Integer literals:\n";
    for(auto x : pti)
    {
        if(isInteger(x.first))
        symbolTable<<x.first<<" : "<<x.second<<"\n";
    }
    symbolTable<<"\n";
    symbolTable<<"Float literals:\n";
    for(auto x : pti)
    {
        if(isFloat(x.first))
        symbolTable<<x.first<<" : "<<x.second<<"\n";
    }
    symbolTable<<"\n";
    symbolTable<<"Delimiters:\n";
    for(auto x : pti)
    {
        if(isDelimiter(x.first))
        symbolTable<<x.first<<" : "<<x.second<<"\n";
    }
    symbolTable<<"\n";
    symbolTable<<"String literals:\n";
    for(auto x : pti)
    {
        if(isString(x.first))
        symbolTable<<x.first<<" : "<<x.second<<"\n";
    }
    symbolTable<<"\n";
    cout<<"Symbol table created successfully\n";
    symbolTable.close();
}

void initialize_token_map()
{
    int counter = 50,i;
    for(i=0;i<keywords.size();i++)
    {
        if(token_id.find(keywords[i])==token_id.end())
        {
            token_id[keywords[i]]=counter;
            counter++;
        }
    }
    for(i=0;i<spchar.size();i++)
    {
        if(token_id.find(spchar[i]+"")==token_id.end())
        {
            token_id[spchar[i]+""]=counter;
            counter++;
        }
    }
    for(i=0;i<binop.size();i++)
    {
        if(token_id.find(binop[i])==token_id.end())
        {
            token_id[binop[i]]=counter;
            counter++;
        }
    }
    for(i=0;i<delimiter.size();i++)
    {
        if(token_id.find(delimiter[i])==token_id.end())
        {
            token_id[delimiter[i]]=counter;
            counter++;
        }
    }
    for(i=0;i<oprator.size();i++)
    {
        if(token_id.find(oprator[i])==token_id.end())
        {
            token_id[oprator[i]]=counter;
            counter++;
        }
    }
}

int main(){

    //Initialize token map
    initialize_token_map();

    //Name of input code file	
    string filename="input.txt";
    vector<string> inputCode;
    string line;

	//Check if file is already open
    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }
	
	//Insert each line in a vector
    while (getline(input_file, line)){
        line = regex_replace(line, regex("^ +"), "");
        line=preProcess(line);
        inputCode.push_back(line);
    }

    //Tokenize
    ofstream cc;
    cc.open(filename+"_output.txt");

    for(int i=0;i<inputCode.size();i++){
        int p=-1,q=-2;
        p = inputCode[i].find('"');
        if(p==-1){
            tokenize(inputCode[i],i,cc);
            continue;
        }
        int j=0;
        bool isStr=false;
        bool isComment=false;
        while(j<inputCode[i].size())
        {
            string s="";
            for(;j<inputCode[i].size();j++)
            {
                if(!isStr&&inputCode[i][j]=='/'&&inputCode[i][j+1]=='/'&&j<inputCode[i].size()-1)
                {
                    isComment=true;
                    break;
                }
                if(inputCode[i][j]!='"')
                s+=inputCode[i][j];
                else
                {
                    j++;
                    break;
                }
            }
            if(isStr)
            {
                s='"'+s;
                if(j<inputCode[i].size())
                s+='"';
                isStr=false;
                tokenize(s,i,cc);
                continue;
            }
            if(!isStr)
            {
                if(!isComment)
                {
                    isStr=true;
                    tokenize(s,i,cc);
                    continue;
                }
                else
                    break;
            }
        }
        if(isComment)
        {
            isComment=false;
            continue;
        }        
    }

    cout<<"Output file generated successfully\n";

    //Generate symbol table
    generate_symbol_table(inputCode,filename);

    
	//Closing the input code file
    input_file.close();
    return EXIT_SUCCESS;
}