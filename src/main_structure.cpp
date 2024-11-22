//part 2
#include<iostream>
#include "trie_dictionary.hpp"

trie_node::trie_node(char ch, bool term):terminator(term),value(ch){
    edges = new trie_node*[alphabet_size]();
}

trie_node::trie_node(const trie_node& in):terminator(in.terminator), value(in.value), alphabet_size(in.alphabet_size){
    edges = new trie_node*[alphabet_size];
    for(int i = 0; i < alphabet_size; i++){
        if(in.edges[i]){
            edges[i] = new trie_node(*in.edges[i]);
        }
        else{
            edges[i] = nullptr;
        }
    }
}

void trie_node::delete_node(){
    for(int i = 0; i < alphabet_size; i++){
        if(edges[i]){
            delete edges[i];
        }
    }
    delete[] edges;
}

trie_node::~trie_node(){
    delete_node();
}

int trie_node::get_char_index(char ch){
    if(ch >= '0' && ch <= '9'){
        return ch - '0';
    }
    else if(ch >= 'A' && ch <= 'Z'){
        //ch - 65 + 10
        return ch - 'A' + 10;
    }
    else if(ch >= 'a' && ch <= 'z'){
        //ch - 97 + 10 + 26
        return ch - 'a' + 36;
    }
    else{
        throw invalid_argument("Invalid character: " + string(1, ch));
    } 
}

int trie_node::add_edge(char ch, bool term){
    int index;
    try{
        index = get_char_index(ch);
    }
    catch(invalid_argument){
        throw;
    }
    if(edges[index] == nullptr){
        trie_node* node = new trie_node(ch, term);
        edges[index] = node; 
    }
    return index;   
}

trie::trie(string nm):name(nm){
    root = new trie_node('#', true);
}

trie::trie(const trie& in):name(in.name){
    root = new trie_node(*in.root);
}

trie::~trie(){
    root->delete_node();
}

void trie::insert_word(string word){
    int index;
    string::iterator last = word.end() - 1;
    trie_node* curr = root;
    for(string::iterator iter = word.begin(); iter != word.end(); iter++){
        try{
            if(iter == last){
                index = curr->add_edge(*iter, true);
            }
            else{
                index = curr->add_edge(*iter, false);
            }
                        
        }
        catch(invalid_argument){
            throw;
        }
        curr = curr->edges[index];
    }
}

bool trie::search_word(string word){
    int index;
    trie_node* curr = root;    
    for(string::iterator iter = word.begin(); iter != word.end(); iter++){
        try{
            index = curr->get_char_index(*iter);
        }
        catch(invalid_argument){
            throw;
        }
        if(curr->edges[index]){
            curr = curr->edges[index];
        }
        else{
            return false;
        }
    }
    return curr->terminator;
}

void trie_node::print_word_from(string& prev){
    prev += value;
    if(terminator){
        cout << prev << "\n";
    }
    for(int i = 0; i < alphabet_size; i++){
        if(edges[i]){
            edges[i]->print_word_from(prev);
        }
    }
    prev.pop_back();
}

void trie_node::print_tree_from(int width, bool silent){
    vector<int> next;
    if(!silent){
        for(int i = 0; i < width; i++){
            cout << " ";
        }
        cout << "|-" << value;
        if(terminator){
            cout << ".\n";
        }
        else{
            cout <<"\n";
        }        
    }
    for(int i = 0; i < alphabet_size; i++){
        if(edges[i]){
            next.push_back(i);
        }
    }
    while(next.size() > 1){
        int call = next.back();
        next.pop_back();
        edges[call]->print_tree_from(width+2, false);
    }
    if(next.size() == 1){
        int call = next.back();
        next.pop_back();
        edges[call]->print_tree_from(width+2, false);
    }
}

void trie::print_all_words(){
    string prev = "";
    root->print_word_from(prev);
}

void trie::print_tree(){
    vector<int> sep;
    cout << "#\n";
    root->print_tree_from(-2, true);
}

void dictionary::create(string& set_name){
    trie t(set_name);
    sets.push_back(t);
    cout << "Set " << set_name << " has been created\n\n";
}

void dictionary::insert(string& set_name, string& value){
    bool flag = false;
    for(vector<trie>::iterator iter = sets.begin(); iter != sets.end(); iter++){
        if(iter->name == set_name){
            iter->insert_word(value);
            flag = true;
        }
    }
    if(!flag){
        cout << "Unable to find set " << set_name << "\n\n";
    }
    else{
        cout << "String " << value << " has been added to " << set_name << "\n\n";
    }
}

void dictionary::print(string& set_name){
    for(vector<trie>::iterator iter = sets.begin(); iter != sets.end(); iter++){
        if(iter->name == set_name){
            iter->print_tree();
            cout << "\n";
            return;
        }
    }
    cout << "Unable to find set " << set_name << "\n\n";
    //cout << "PRINT " << set_name << "\n\n";
}

void dictionary::contains(string& set_name, string& value){
    for(vector<trie>::iterator iter = sets.begin(); iter != sets.end(); iter++){
        if(iter->name == set_name){
            if(iter->search_word(value)){
                cout << "TRUE\n\n";
            }
            else{
                cout << "FALSE\n\n";
            }
            return;
        }
    }
    cout << "Unable to find set " << set_name << "\n\n";
}

void dictionary::search(string& set_name, string order){
    if(order != "NULL"){
        cout << "Not implemented yet\n\n";
    }
    else{
        for(vector<trie>::iterator iter = sets.begin(); iter != sets.end(); iter++){
            if(iter->name == set_name){
                iter->print_all_words();
                cout << "\n";
                return;
            }
        }
        cout << "Unable to find set " << set_name << "\n\n";
    }
}

void dictionary::search_where_between(string& set_name, string& from, string& to, string order){
    cout << "SEARCH " << set_name << " WHERE BETWEEN " << from << " " << to;
    if(order != "NULL"){
        cout << " " << order << "\n\n";
    }
    else{
        ;
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