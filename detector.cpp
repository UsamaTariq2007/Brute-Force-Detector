#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

int main() {
    int threshold = 3;
    ifstream file("auth.log.txt");

    if (!file) {
        cout << "auth.log.txt file nahi mili!" << endl;
        cin.get();
        return 1;
    }

    map<string, int> counts;
    string line;

    while (getline(file, line)) {
        if (line.find("Failed password") != string::npos) {
            size_t pos = line.find(" from ");
            if (pos != string::npos) {
                size_t start = pos + 6;
                size_t end = line.find(' ', start);
                string ip = line.substr(start, end - start);
                counts[ip]++;
            }
        }
    }

    cout << "IP ki attempts:" << endl;
    for (map<string, int>::iterator it = counts.begin(); it != counts.end(); ++it) {
        cout << it->first << " -> " << it->second;
        if (it->second > threshold)
            cout << "  [SUSPICIOUS]";
        cout << endl;
    }

    cin.get();
    return 0;
}
