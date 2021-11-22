#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

bool checker(string number)
{
    for (int i = 0; i < number.size(); i++)
    {
        if (number[i] != '1' && number[i] != '2' && number[i] != '3' && number[i] != '4' && number[i] != '5' && number[i] != '6' && number[i] != '7' && number[i] != '8' && number[i] != '9')
            return false;
    }
    return true;
}
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
    if (key_word.size() < min_key_word_size) {
        cout << "Deny!" << endl;
        return false;
    }
    int first_letter_code = (int)(key_word[0]), second_letter_code = (int)(key_word[1]), a_code = (int)('a'), A_code = (int)('A'), z_code = (int)('z'), Z_code = (int)('Z');
    if (first_letter_code < A_code || (first_letter_code > Z_code && first_letter_code < a_code) || first_letter_code > z_code) {
        cout << "Deny!" << endl;
        return false;
    }
    if (second_letter_code < A_code || (second_letter_code > Z_code && second_letter_code < a_code) || second_letter_code > z_code) {
        cout << "Deny!" << endl;
        return false;
    }
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
    if (!encode_checker(key_word)) return;
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
    if (!encode_checker(key_word)) return;
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

void task()
{
    string table_size_string;
    cout << "Enter table size : ";
    cin >> table_size_string;
    if (!checker(table_size_string)) {
        cout << "Enter something possible to work with!" << endl;
        return;
    }
    int table_size = stoi(table_size_string);
    if (table_size <= 20 || table_size > 100) {
        cout << "Enter something higher than 20 and lower than 100!" << endl;
        return;
    }
    Hash_table math(table_size);
    string a, a_def;
    a = "Infinity";
    a_def = "Number of points on a continuous line or as the size of the endless sequence of counting numbers";
    math.push(a, a_def);
    a = "Inequality";
    a_def = "Relation which makes a non-equal comparison between two numbers or other mathematical expressions";
    math.push(a, a_def);
    a = "Inequation";
    a_def = "Statement that an inequality holds between two values";
    math.push(a, a_def);
    a = "Division";
    a_def = "Method of distributing a group of things into equal parts";
    math.push(a, a_def);
    a = "Diagonal";
    a_def = "Straight line connecting the opposite corners of a polygon through its vertex";
    math.push(a, a_def);
    a = "Diameter";
    a_def = "The distance from one point on a circle through the center to another point on the circle";
    math.push(a, a_def);
    a = "Oval";
    a_def = "Figure constructed from two pairs of arcs, with two different radii";
    math.push(a, a_def);
    a = "Cube";
    a_def = "Solid three-dimensional figure, which has 6 square faces, 8 vertices and 12 edges";
    math.push(a, a_def);
    a = "Pyramid";
    a_def = "Polyhedron formed by connecting a polygonal base and a point, called the apex";
    math.push(a, a_def);
    a = "Addition";
    a_def = "Bringing two or more numbers (or things) together to make a new total";
    math.push(a, a_def);
    a = "Angle";
    a_def = "Figure formed by two rays, called the sides of the angle";
    math.push(a, a_def);
    a = "Multiplication";
    a_def = "Multiply means to add equal groups. When we multiply, the number of things in the group increases";
    math.push(a, a_def);
    a = "Square";
    a_def = "Result of multiplying a number by itself";
    math.push(a, a_def);
    a = "Radius";
    a_def = "Distance from the center outwards";
    math.push(a, a_def);
    bool sign = true;
    while (true)
    {
        cout << "What do you want?  :: 1)enter something :: 2)delete something :: 3)output all the information :: 4)find something :: 5)finish" << endl;
        int choice;
        string example_one, example_two;
        cin >> choice;
        switch (choice)
        {
        case 1: cout << "Enter key word : ";
            cin >> example_one;
            cout << "Enter data : ";
            cin.ignore();
            getline(cin, example_two);
            math.push(example_one, example_two);
            break;
        case 2: cout << "Enter key word : ";
            cin >> example_one;
            math.delete_with_key(example_one);
            break;
        case 3: math.output();
            break;
        case 4: cout << "Enter key word : ";
            cin >> example_one;
            math.find_with_key(example_one);
            break;
        case 5:
            return;
        default: cout << "Enter something posible to work with!" << endl;
            break;
        }
    }
}

int main()
{
    task();
    return 0;
}

