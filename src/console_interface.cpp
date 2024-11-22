//part 1
#include<sstream>
#include<iostream>
#include<algorithm>
#include "trie_dictionary.hpp"

vector<string> console_interface::tokenize_input(string& in){
    stringstream in_stream (in);
    vector<string> out;
    string token;
    while(getline(in_stream, token, ' ')){
        token.erase(0, token.find_first_not_of(' '));
        token.erase(token.find_last_not_of(' ') + 1);
        if(!token.empty()){
            out.push_back(token);                
        }
    }
    return out;
};

bool console_interface::validate_name(string& in){
    if(in.empty()){
        return false;
    }
    for(string::iterator iter = in.begin(); iter != in.end(); iter++){
        if(*iter > 'z' || *iter < '0'){
            return false;
        }
        else if((*iter > '9' && *iter < 'A')||(*iter > 'Z' && *iter < 'a')){
            return false;
        }
    }
    if (*in.begin() < 'A'){
        return false;
    }
    return true;
}

vector<int> console_interface::prepare_tokens(vector<string>& in){
    string token = "";
    string temp = "";
    vector<int> out;
    for(vector<string>::iterator i = in.begin(); i != in.end(); i++){
        token = *i;
        temp.resize(token.size());
        transform(token.begin(), token.end(), temp.begin(), toupper);
        if(temp == "CREATE"){
            out.push_back(0);
        }
        else if(temp == "INSERT"){
            out.push_back(1);
        }
        else if(temp == "PRINT"){
            out.push_back(2);
        }
        else if(temp == "CONTAINS"){
            out.push_back(3);
        }
        else if(temp == "SEARCH"){
            out.push_back(4);
        }
        else if(temp == "HELP"){
            out.push_back(5);
        }
        else if(temp == "WHERE"){
            out.push_back(6);
        }
        else if(temp == "BETWEEN"){
            out.push_back(7);
        }
        else if(temp == "MATCH"){
            out.push_back(8);
        }
        else if(temp == "ASC"){
            out.push_back(9);
        }
        else if(temp == "DESC"){
            out.push_back(10);
        }
        else{
            if(validate_name(token)){
                out.push_back(11);                
            }
            else{
                throw invalid_argument("Unsupported name");
            }
        }                
    }
    return out;
};

void console_interface::parse(vector<int>& in){
    reset_state();
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

void console_interface::get_state(){
    cout << "State: " << state << "\n";
}

void console_interface::reset_state(){
    state = 0;
}

void console_interface::help(int command){
    switch(command){
        case -1:
            cout << "CREATE: CREATE set_name - creates a new set inside the dictionary;\n\n"
            << "INSERT: INSERT set_name value - inserts a new word (value) to the the set (set_name);\n\n"
            << "PRINT: PRINT set_name - prints the structure of the set (set_name);\n\n"
            << "CONTAINS: CONTAINS set_name value - checks if the word (value) exists in the set (set_name);\n\n"
            << "SEARCH: SEARCH set_name [WHERE queue] [ASC|DESC] - returns words from the set (set_name) "
            << "based on certain rules: no rule returns all words, WHERE BETWEEN 'from' 'to' filters between two words"
            << ", MATCH filters by mask, ASC|DESC determines the output order.\n\n";
            break;
        case 0:
            cout << "CREATE: CREATE set_name - creates a new set inside the dictionary.\n\n";
            break;
        case 1:
            cout << "INSERT: INSERT set_name value - inserts a new word (value) to the the set (set_name).\n\n";
            break;
        case 2:
            cout << "PRINT: PRINT set_name - prints the structure of the set (set_name).\n\n";
            break;
        case 3: 
            cout << "CONTAINS: CONTAINS set_name value - checks if the word (value) exists in the set (set_name).\n\n";
            break;
        case 4:
            cout << "SEARCH: SEARCH set_name [WHERE queue] [ASC|DESC] - returns words from the set (set_name) "
            << "based on certain rules: no rule returns all words, WHERE BETWEEN 'from' 'to' filters between two words"
            << ", MATCH filters by mask, ASC|DESC determines the output order.\n\n";
            break;
    }
}

void console_interface::execute(dictionary& env, vector<string>& tokens, vector<int>& prep_tokens){
    switch(state){
        case 2:
            env.create(tokens[1]);
            break;
        case 5:
            env.insert(tokens[1], tokens[2]);
            break;
        case 7:
            env.print(tokens[1]);
            break;
        case 10:
            env.contains(tokens[1], tokens[2]);
            break;
        case 12:
            env.search(tokens[1]);
            break;
        case 16:
            env.search_where_between(tokens[1], tokens[4], tokens[5]);
            break;
        case 18:
            env.search_where_match(tokens[1], tokens[4]);
            break;
        case 19:
            env.search(tokens[1], tokens[2]);
            break;
        case 20:
            env.search(tokens[1], tokens[2]);
            break;
        case 21:
            env.search_where_between(tokens[1], tokens[4], tokens[5], tokens[6]);
            break;
        case 22:
            env.search_where_between(tokens[1], tokens[4], tokens[5], tokens[6]);
            break;    
        case 23:
            env.search_where_match(tokens[1], tokens[4], tokens[5]);
            break;
        case 24:
            env.search_where_match(tokens[1], tokens[4], tokens[5]);
            break;
        case 25:
            help();
            break;
        case 26:
            help(prep_tokens[1]);
            break;
        default:
            throw invalid_argument("Invalid parser state");
            break;
    }
}

void console_interface::intro(){
    cout << "----------------------------------------------------\n"
    << "|             Trie dictionary, ver 0.2             |\n"
    <<"----------------------------------------------------\n"
    <<"|This specific database is designed to store words |\n"
    <<"|in a compact format and conditionally access them.|\n"
    <<"|In case of any quetions, enter 'HELP [command]',  |\n"
    <<"|to exit enter 'STOP'. Beware, the databaes exists |\n"
    <<"|only durind runtime, do not exit unless you are   |\n"
    <<"|finised your work.                                |\n"
    <<"----------------------------------------------------\n\n";
}