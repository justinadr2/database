#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const string datafile = "data.data";

void Print(const vector<vector<string>>& table)
{
    cout << "(name, age)\n";

    for (const auto& row : table)
    {
        cout << row[0] << ", " << row[1] << '\n';
    }
}

vector<string> ScanInput(const string& command)
{
    vector<string> line;
    stringstream buffer(command);

    string word;

    while (buffer >> word)
        line.push_back(word);

    return line;
}

void Insert(const vector<string>& data)
{
    ofstream file(datafile, ios::app);

    file << data[1] << ", " << data[2] << '\n';
}

vector<vector<string>> Parse()
{
    vector<vector<string>> table;
    ifstream file(datafile);

    string line;
    getline(file, line);

    while (getline(file, line))
    {
        stringstream buffer(line);
        string name, age;

        getline(buffer, name, ',');
        getline(buffer, age);

        if (!age.empty() && age[0] == ' ')
            age.erase(0, 1);

        table.push_back({ name, age });
    }

    return table;
}

int main()
{
    string command;
    
    while (true)
    {
        cout << ": ";
        getline(cin, command);

        if (command == "print")
        {
            vector<vector<string>> table = Parse();
            Print(table);
            continue;
        }

        else if (command == "exit")
            break;

        vector<string> tokens = ScanInput(command);

        if (tokens[0] == "insert")
        {
            string name = tokens[1];
            string age  = tokens[2];

            if (!name.empty() && name.back() == ',')
                name.pop_back();

            Insert({ "", name, age });
        }
    }
}