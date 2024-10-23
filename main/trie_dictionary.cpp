#include<iostream>
#include "trie_dictionary.hpp"

int main(){
    string in = "";
    vector<string> raw_tokens;
    vector<int> prepared_tokens;
    console_interface inter;
    dictionary env;
    bool prep = false;
    bool parse = false;

    inter.intro();
    while (true){
        getline(cin, in);
        if(in == "STOP"){
            break;
        }
        raw_tokens = inter.tokenize_input(in);
        try{
            prep = true;
            prepared_tokens = inter.prepare_tokens(raw_tokens);            
        }
        catch(invalid_argument error){
            prep = false;
            cout << error.what() << "\n";
        }
        try{
            parse = true;
            inter.parse(prepared_tokens);
            //inter.get_state();           
        }
        catch(invalid_argument error){
            parse = false;
            cout << error.what() << "\n";
        }
        
        if(prep && parse){
            try{
                inter.execute(env, raw_tokens, prepared_tokens);                
            }
            catch(invalid_argument error){
                cout << error.what();
                cout << ", enter 'HELP' for help." << endl;
            }
        }
    }
}