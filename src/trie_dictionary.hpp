#include<vector>
#include<string>
using namespace std;

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
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 26}/*HELP*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}/*HELP value*/,
                         };
public:
    void intro();
    vector<string> tokenize_input(string& in);
    vector<int> prepare_tokens(vector<string>& in);
    void parse(vector<int>& in);
    void execute();

    void get_state();
    void reset_state();
    //void help(int command);

    friend class trie;
};

class trie{
//for later
};