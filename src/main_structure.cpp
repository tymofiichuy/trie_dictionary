//part 2
#include<iostream>
#include "trie_dictionary.hpp"

void dictionary::create(string& set_name){
    cout << "CREATE " << set_name << "\n\n";
}

void dictionary::insert(string& set_name, string& value){
    cout << "INSERT " << set_name << " " << value << "\n\n";
}

void dictionary::print(string& set_name){
    cout << "PRINT " << set_name << "\n\n";
}

void dictionary::contains(string& set_name, string& value){
    cout << "CONTAINS " << set_name << " " << value << "\n\n";
}

void dictionary::search(string& set_name, string order){
    cout << "SEARCH " << set_name;
    if(order != "NULL"){
        cout << " " << order << "\n\n";
    }
    else{
        cout << "\n\n";
    }
}

void dictionary::search_where_between(string& set_name, string& from, string& to, string order){
    cout << "SEARCH " << set_name << " WHERE BETWEEN " << from << " " << to;
    if(order != "NULL"){
        cout << " " << order << "\n\n";
    }
    else{
        cout << "\n\n";
    }
}

void dictionary::search_where_match(string& set_name, string& pattern, string order){
    cout << "SEARCH " << set_name << " WHERE MATCH " << pattern;
    if(order != "NULL"){
        cout << " " << order << "\n\n";
    }
    else{
        cout << "\n\n";
    }
}