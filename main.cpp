#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

const string datafile = "data.base";

struct Record
{
    string name;
    unsigned int age;
};

void Print(const vector<Record>& table)
{
    cout << "(name, age)\n";

    for (Record row : table)
    {
        cout << row.name << ", " << to_string(row.age) << '\n';
    }
}

vector<string> ScanInput(const string& command)
{
    vector<string> line;
    stringstream buffer(command);

    string word;

    while (buffer >> word)
    {
        line.push_back(word);
    }

    return line;
}

void Insert(Record& data)
{
    ofstream file(datafile, ios::app);

    file << data.name << ", " << data.age << '\n';
}

vector<Record> Parse()
{
    vector<Record> table;
    ifstream file(datafile);

    string line;
    // skip header
    getline(file, line);

    while (getline(file, line))
    {
        stringstream buffer(line);
        string name, age;
        Record record;

        getline(buffer, name, ',');
        getline(buffer, age);

        record.name = name;
        try 
        {
            record.age = stoi(age);
            table.push_back(record);
        }
        catch (const invalid_argument& e) 
        {
            cout << "Warning: skipping corrupted record for '" << name << "'\n";
        }
    }

    return table;
}

int main()
{
    vector<Record> database = Parse();
    string command;
    
    while (true)
    {
        cout << ": ";
        getline(cin, command);

        if (command == "print")
        {
            Print(database);
            continue;
        }

        else if (command == "exit")
            break;

        vector<string> params = ScanInput(command);

        if (params[0] == "insert")
        {
            Record record;
            record.name = params[1];
            record.age  = stoi(params[2]);

            database.push_back(record);
            Insert(record);
        }
    }
}