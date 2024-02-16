#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
    ifstream fn;
    fn.open(filename);
    string f;
    while(getline(fn,f)){
        const char* cf=f.c_str();
        char fm[]="%[^:]: %f %f %f";
        char a[100];
        float b,c,d;
        sscanf(cf,fm,a,&b,&c,&d);
        names.push_back(a);
        scores.push_back(b+c+d);
        grades.push_back(score2grade(b+c+d));
    }
}

void getCommand(string &command, string &key){
    cout << "Please input your command:";
    cin >> command;
    cin >> key;
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    int a=0;
    string b;
    cout << "---------------------------------" << endl;
    for(unsigned int i=0;i<names.size();i++)
    {
        b=toUpperStr(names[i]);
        if(b==key)
        {
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            a += scores[i];
        }
    }
    if(a<=0)
    {
        cout << "Cannot found." << endl;
    }
    cout << "---------------------------------";
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    const char* k=key.c_str();
    int a=0;
    cout << "---------------------------------"<< endl;
    for(unsigned int i=0;i<grades.size();i++)
    {
        if(*k == grades[i])
        {
            cout << names[i] << " (" << scores[i] << ")" << endl;
            a += scores[i];
        }
    }
    if(a<=0)
    {
        cout << "Cannot found." << endl;
    }
    cout << "---------------------------------";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
