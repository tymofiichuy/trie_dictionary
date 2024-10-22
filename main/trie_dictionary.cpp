#include<iostream>
#include "trie_dictionary.hpp"

int main(){
    string in = "";
    vector<string> raw_tokens;
    vector<int> prepared_tokens;
    console_interface inter;
    while (true){
        getline(cin, in);
        if(in == "STOP"){
            break;
        }
        raw_tokens = inter.tokenize_input(in);
        prepared_tokens = inter.prepare_tokens(raw_tokens);
        try{
            inter.parse(prepared_tokens);            
        }
        catch(invalid_argument error){
            cout << error.what() << "\n";
        }
        inter.get_state();
    }
}