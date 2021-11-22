#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Table_Note
{
    int hash;
    string key_word;
    string data;
    Table_Note* next;
    void print();
    friend class Hash_table;
};
void Table_Note::print()
{
    cout << "----------------------------------" << endl;
    cout << "Hash : " << hash << endl;
    cout << "Key word : " << key_word << endl;
    cout << "Data : " << data << endl << "----------------------------------" << endl;
}
class Hash_table
{
private:
    vector<Table_Note*>table;
    static int max_letter_massive_code;
    static int ASCII_letters_shift;
    bool encode_checker(string &key_word);
    int hash_function(string& key_word);
    void clear();
public:
    Hash_table();
    void push(string &key_word, string &data);
    void delete_with_key(string& key_word);
    void find_with_key(string& key_word);
    void output();
};
Hash_table::Hash_table() : table(max_letter_massive_code + 1, NULL) {}
bool Hash_table::encode_checker(string& key_word)
{
    if (key_word.size() == 0) return false;
    int first_letter_code = (int)(key_word[0]), a_code = (int)('a'), A_code = (int)('A'), z_code = (int)('z'), Z_code = (int)('Z');
    if (first_letter_code < A_code || (first_letter_code > Z_code && first_letter_code < a_code) || first_letter_code > z_code) return false;
    return true;
}
int Hash_table::hash_function(string& key_word)
{
    return (int)(key_word[0]) % ASCII_letters_shift - 1;
}
void Hash_table::push(string& key_word, string& data)
{
    if (!encode_checker(key_word)) return;
    Table_Note* Note = new Table_Note;
    Note->key_word = key_word;
    Note->data = data;
    Note->hash = hash_function(key_word);
    Note->next = table[Note->hash];
    table[Note->hash] = Note;
}
void Hash_table::delete_with_key(string& key_word)
{
    int hash_we_try_to_delete = hash_function(key_word);
    Table_Note* deleting = table[hash_we_try_to_delete], *previous = NULL;
    while (deleting != NULL)
    {
        if (deleting->key_word == key_word && previous == NULL){
            table[hash_we_try_to_delete] = deleting->next;
            delete deleting;
            deleting = table[hash_we_try_to_delete];
        }
        else if (deleting->key_word == key_word && previous != NULL) {
            previous->next = deleting->next;
            delete deleting;
            deleting = previous->next;
        }
        else {
            previous = deleting;
            deleting = deleting->next;
        }
    }
}
void Hash_table::find_with_key(string& key_word)
{
    int hash_we_try_to_delete = hash_function(key_word);
    Table_Note* looking_for = table[hash_we_try_to_delete];
    while (looking_for != NULL)
    {
        if (looking_for->key_word == key_word) looking_for->print();
        looking_for = looking_for->next;
    }
}
int Hash_table::max_letter_massive_code = 25;
int Hash_table::ASCII_letters_shift = 32;


int main()
{

    return 0;
}

