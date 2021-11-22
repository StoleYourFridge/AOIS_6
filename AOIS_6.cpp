#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Table_Note
{
    int numeral_key_word;
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
    cout << "Numeral Key word : " << numeral_key_word << endl;
    cout << "Hash : " << hash << endl;
    cout << "Key word : " << key_word << endl;
    cout << "Data : " << data << endl << "----------------------------------" << endl;
}
class Hash_table
{
    int table_size;
    int current_notes_amount;
    vector<Table_Note*>table;
    bool encode_checker(string &key_word);
    int numeral_key_word(string &key_word);
    int hash_function(int numeral_key_word);
    void clear();
    
public:
    Hash_table(int table_size);
    ~Hash_table();
    void push(string &key_word, string &data);
    void delete_with_key(string& key_word);
    void find_with_key(string& key_word);
    void output();
};
Hash_table::Hash_table(int table_size) : table(table_size, NULL), table_size(table_size), current_notes_amount(0) {}
bool Hash_table::encode_checker(string& key_word)
{
    int min_key_word_size = 2;
    if (key_word.size() < min_key_word_size) return false;
    int first_letter_code = (int)(key_word[0]), second_letter_code = (int)(key_word[1]), a_code = (int)('a'), A_code = (int)('A'), z_code = (int)('z'), Z_code = (int)('Z');
    if (first_letter_code < A_code || (first_letter_code > Z_code && first_letter_code < a_code) || first_letter_code > z_code) return false;
    if (second_letter_code < A_code || (second_letter_code > Z_code && second_letter_code < a_code) || second_letter_code > z_code) return false;
    return true;
}
int Hash_table::numeral_key_word(string& key_word)
{
    return (int)(key_word[0]) + 2 * (int)(key_word[1]);
}
int Hash_table::hash_function(int numeral_key_word)
{
    return numeral_key_word % table_size;
}
void Hash_table::push(string& key_word, string& data)
{
    if (!encode_checker(key_word)) return;
    Table_Note* Note = new Table_Note;
    Note->key_word = key_word;
    Note->data = data;
    Note->numeral_key_word = numeral_key_word(key_word);
    Note->hash = hash_function(Note->numeral_key_word);
    Note->next = NULL;
    Table_Note* example = table[Note->hash], *previous = NULL;
    while (example != NULL)
    {
        if (example->key_word == key_word) {
            cout << Note ->key_word << " deny!" << endl;
            delete Note;
            return;
        }
        previous = example;
        example = example->next;
    }
    if (previous == NULL) {
        table[Note->hash] = Note;
    }
    else {
        previous->next = Note;
    }
    current_notes_amount++;
}
void Hash_table::delete_with_key(string& key_word)
{
    int hash_we_try_to_delete = hash_function(numeral_key_word(key_word));
    Table_Note* deleting = table[hash_we_try_to_delete], *previous = NULL;
    while (deleting != NULL)
    {
        if (deleting->key_word == key_word && previous == NULL){
            table[hash_we_try_to_delete] = deleting->next;
            delete deleting;
            deleting = table[hash_we_try_to_delete];
            current_notes_amount--;
        }
        else if (deleting->key_word == key_word && previous != NULL) {
            previous->next = deleting->next;
            delete deleting;
            deleting = previous->next;
            current_notes_amount--;
        }
        else {
            previous = deleting;
            deleting = deleting->next;
        }
    }
}
void Hash_table::find_with_key(string& key_word)
{
    int hash_we_try_to_delete = hash_function(numeral_key_word(key_word));
    Table_Note* looking_for = table[hash_we_try_to_delete];
    while (looking_for != NULL)
    {
        if (looking_for->key_word == key_word) looking_for->print();
        looking_for = looking_for->next;
    }
}
void Hash_table::output()
{
    cout << "Total notes : " << current_notes_amount << endl;
    for (int i = 0; i < table.size(); i++)
    {
        Table_Note* example = table[i];
        while (example != NULL)
        {
            example->print();
            example = example->next;
        }
    }
}
void Hash_table::clear()
{
    for (int i = 0; i < table.size(); i++)
    {
        Table_Note* deleting = table[i];
        while (deleting != NULL)
        {
            table[i] = table[i]->next;
            delete deleting;
            deleting = table[i];
        }
    }
}
Hash_table::~Hash_table()
{
    clear();
    table.clear();
}

int main()
{
    Hash_table math(35);
    string a = "Reangle";
    string a_opr = "ctvybumiop,";
    string b = "Rengle";
    string b_opr = "tv7ybuniomp,";
    string c = "Recaftangle";
    string c_opr = "tv7ybuniomp,";
    string d = "rtbuin";
    math.push(a, a_opr);
    math.push(b, b_opr);
    math.push(c, c_opr);
    math.output();
    math.delete_with_key(c);
    math.output();
    return 0;
}

