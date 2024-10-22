//part 1
#include<sstream>
#include<iostream>
#include "trie_dictionary.hpp"

vector<string> console_interface::tokenize_input(string& in){
    stringstream in_stream (in);
    vector<string> out;
    string token;
    while(getline(in_stream, token, ' ')){
        if(!token.empty()){
            out.push_back(token);            
        }
    }
    return out;
};

vector<int> console_interface::prepare_tokens(vector<string>& in){
    string token;
    vector<int> out;
    for(vector<string>::iterator i = in.begin(); i != in.end(); i++){
        token = *i;
        if(token == "CREATE"){
            out.push_back(0);
        }
        else if(token == "INSERT"){
            out.push_back(1);
        }
        else if(token == "PRINT"){
            out.push_back(2);
        }
        else if(token == "CONTAINS"){
            out.push_back(3);
        }
        else if(token == "SERACH"){
            out.push_back(4);
        }
        else if(token == "HELP"){
            out.push_back(5);
        }
        else if(token == "WHERE"){
            out.push_back(6);
        }
        else if(token == "BETWEEN"){
            out.push_back(7);
        }
        else if(token == "MATCH"){
            out.push_back(8);
        }
        else if(token == "ASC"){
            out.push_back(9);
        }
        else if(token == "DESC"){
            out.push_back(10);
        }
        else{
            out.push_back(11);
        }                
    }
    return out;
};

void console_interface::parse(vector<int>& in){
    for(vector<int>::iterator i = in.begin(); i != in.end(); i++){
        state = program[state][*i];
        if(state == -1){
            throw invalid_argument("Unable to parse");
        }
    }
    for(int j = 0; j < 15; j++){
        if(state == terminal[j]){
            return;
        }
    }
    throw invalid_argument("Unable to parse");
};