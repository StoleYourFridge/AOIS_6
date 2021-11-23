#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

bool checker(string number);
class Table_Note
{
    int numeral_key_word;
    int hash;
    bool collision;
    bool U;
    bool T;
    bool D;
    string key_word;
    string data;
    Table_Note* next;
    void print();
    friend class Hash_table;
};
class Hash_table
{
    int table_size;
    int current_notes_amount;
    vector<Table_Note*>table;
    bool encode_checker(string& key_word);
    int numeral_key_word(string& key_word);
    int hash_function(int numeral_key_word);
    void clear();

public:
    Hash_table(int table_size);
    ~Hash_table();
    void push(string& key_word, string& data);
    void delete_with_key(string& key_word);
    void find_with_key(string& key_word);
    void output();
};
void task();

