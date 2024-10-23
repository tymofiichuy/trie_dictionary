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
        else if(token == "SEARCH"){
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
            cout << "CREATE: CREATE set_name - create new set inside dictionarty;\n\n"
            << "INSERT: INSERT set_name value - inserts new word (value) to the set (set_name);\n\n"
            << "PRINT: PRINT set_name - prints set (set_name) structure;\n\n"
            << "CONTAINS: CONTAINS set_name value - checks set (set_name) for the word (value) existance;\n\n"
            << "SEARCH: SEARCH set_name [WHERE queue] [ASC|DESC] - returns words from the set (set_name) "
            << "by some rule: no rule - all words, WHERE BETWEEN - from word 'from' to 'to'"
            << ", MATCH - by mask, ASC|DESC corresponds to output order.\n\n";
            break;
        case 0:
            cout << "CREATE: CREATE set_name - create new set inside dictionarty.\n\n";
            break;
        case 1:
            cout << "INSERT: INSERT set_name value - inserts a new word (value) to the set (set_name).\n\n";
            break;
        case 2:
            cout << "PRINT: PRINT set_name - prints set (set_name) structure.\n\n";
            break;
        case 3: 
            cout << "CONTAINS: CONTAINS set_name value - checks set (set_name) for the word (value) existance.\n\n";
            break;
        case 4:
            cout << "SEARCH: SEARCH set_name [WHERE queue] [ASC|DESC] - returns words from the set (set_name)"
            << "by some rule: no rule - all words, WHERE BETWEEN - from word 'from' to 'to'"
            << ", MATCH - by mask, ASC|DESC corresponds to output order.\n\n";
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
    << "|             Trie dictionary, ver 0.1             |\n"
    <<"----------------------------------------------------\n"
    <<"|This specific database is designed to store words |\n"
    <<"|in a compact format and conditionally access them.|\n"
    <<"|In case of any quetions, entrer 'HELP [command]', |\n"
    <<"|to exit enter 'STOP'. Beware, the databaes exists |\n"
    <<"|only durind runtime, do not exit unless you are   |\n"
    <<"|finised your work.                                |\n"
    <<"----------------------------------------------------\n\n";
}