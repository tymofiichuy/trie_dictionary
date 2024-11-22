#include<vector>
#include<string>
using namespace std;

class trie_node{
private:
    char value;
    trie_node** edges;
    bool terminator;
    int alphabet_size = 62;
    //alphabet: 0 - 9, A - Z, a - z
    int get_char_index(char ch);
public:
    int add_edge(char ch, bool term);
    void print_word_from(string& prev);
    void print_tree_from(int width, bool silent);
    void delete_node();

    trie_node(char ch, bool term = true);
    trie_node(const trie_node& in);    
    ~trie_node();

    friend class trie;
};

class trie{
private:
    string name;
    trie_node* root;
public:
    void insert_word(string word);
    bool search_word(string word);
    void print_all_words();
    void print_tree();

    trie(string name);
    trie(const trie& in);
    ~trie();

    friend class dictionary;
};

class dictionary{
private:
    vector<trie> sets;
public:
    void create(string& set_name);
    void insert(string& set_name, string& value);
    void print(string& set_name);
    void contains(string& set_name, string& value);
    void search(string& set_name, string order = "NULL");
    void search_where_between(string& set_name, string& from, string& to, string order = "NULL");
    void search_where_match(string& set_name, string& pattern, string order = "NULL");
};

class console_interface{
private:
    //states:
    // -1 - ERROR, incorrect command
    // 0 - NULL, entry point 
    //
    // 1 - CREATE
    // 2 - CREATE set_name
    //
    // 3 - INSERT
    // 4 - INSERT set_name
    // 5 - INSERT set_name value
    //
    // 6 - PRINT
    // 7 - PRINT set_name
    //
    // 8 - CONTAINS
    // 9 - CONTAINS set_name
    // 10 - CONTAINS set_name value
    //
    // 11 - SEARCH
    // 12 - SEARCH set_name
    // 13 - SEARCH set_name WHERE
    // 14 - SEARCH set_name WHERE BETWEEN
    // 15 - SEARCH set_name WHERE BETWEEN from
    // 16 - SEARCH set_name WHERE BETWEEN from to
    // 17 - SEARCH set_name WHERE MATCH
    // 18 - SEARCH set_name WHERE MATCH pattern 
    // 19 - SEARCH set_name ASC
    // 20 - SEARCH set_name DESC
    // 21 - SEARCH set_name WHERE BETWEEN from to ASC
    // 22 - SEARCH set_name WHERE BETWEEN from to DESC
    // 23 - SEARCH set_name WHERE MATCH pattern ASC
    // 24 - SEARCH set_name WHERE MATCH pattern DESC
    //
    // 25 - HELP
    // 26 - HELP value

    //in:
    // 0 - CREATE
    // 1 - INSERT
    // 2 - PRINT
    // 3 - CONTAINS
    // 4 - SEARCH
    // 5 - HELP
    // 6 - WHERE
    // 7 - BETWEEN
    // 8 - MATCH
    // 9 - ASC
    // 10 - DESC
    // 11 - value

    // can be omitted
    // char alphabet[62] = {
    // 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    // 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    // '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
    // };

    int state = 0;

    int terminal[15] = {2, 5, 7, 10, 12, 16, 18, 19, 20, 21, 22, 23, 24, 25, 26};

    int program[27][12] = {{1, 3, 6, 8, 11, 25, -1, -1, -1, -1, -1, -1}/*NULL*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2}/*CREATE*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}/*CREATE set_name*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}/*INSERT*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5}/*INSERT set_name*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}/*INSERT set_name value*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 7}/*PRINT*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}/*PRINT set_name*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 9}/*CONTAINS*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 10}/*CONTAINS set_name*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}/*CONTAINS set_name value*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 12}/*SEARCH*/,
                          {-1, -1, -1, -1, -1, -1, 13, -1, -1, 19, 20, -1}/*SEARCH set_name*/,
                          {-1, -1, -1, -1, -1, -1, -1, 14, 17, -1, -1, -1}/*SEARCH set_name WHERE*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15}/*SEARCH set_name WHERE BETWEEN*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 16}/*SEARCH set_name WHERE BETWEEN from*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, 21, 22, -1}/*SEARCH set_name WHERE BETWEEN from to*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 18}/*SEARCH set_name WHERE MATCH*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, 23, 24, -1}/*SEARCH set_name WHERE MATCH pattern*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}/*SEARCH set_name ASC*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}/*SEARCH set_name DESC*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}/*SEARCH set_name WHERE BETWEEN from to ASC*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}/*SEARCH set_name WHERE BETWEEN from to DESC*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}/*SEARCH set_name WHERE MATCH pattern ASC*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}/*SEARCH set_name WHERE MATCH pattern DESC*/,
                          {26, 26, 26, 26, 26, -1, -1, -1, -1, -1, -1, -1}/*HELP*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}/*HELP command*/,
                         };

    bool validate_name(string& in);
public:
    void intro();
    vector<string> tokenize_input(string& in);
    vector<int> prepare_tokens(vector<string>& in);
    void parse(vector<int>& in);
    void execute(dictionary& env, vector<string>& tokens, vector<int>& prep_tokens);

    void get_state();
    void reset_state();
    void help(int command = -1);

    friend class dictionatry;
};