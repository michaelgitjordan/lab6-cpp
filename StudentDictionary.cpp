#include "StudentDictionary.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <clocale>
#include <cwchar>
#include <limits>

using namespace std;

StudentDictionary::StudentDictionary() : count(0) {
    table = new DictEntry*[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = nullptr;
    }
}

StudentDictionary::~StudentDictionary() {
    clearTable();
    delete[] table;
}

int StudentDictionary::hashFunction(const std::string& key) const {
    unsigned int hash = 0;
    int prime = 31;
    
    for (size_t i = 0; i < key.length(); i++) {
        //  unsigned char для корректной работы с русскими символами
        unsigned char c = static_cast<unsigned char>(key[i]);
        hash = (prime * hash + c) % TABLE_SIZE;
    }
    
    return static_cast<int>(hash);
}

void StudentDictionary::clearTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        DictEntry* entry = table[i];
        while (entry != nullptr) {
            DictEntry* prev = entry;
            entry = entry->next;
            delete prev;
        }
        table[i] = nullptr;
    }
    count = 0;
}

StudentDictionary::DictEntry* StudentDictionary::findEntry(const std::string& key) const {
    int index = hashFunction(key);
    DictEntry* entry = table[index];
    
    while (entry != nullptr) {
        if (entry->key == key) {
            return entry;
        }
        entry = entry->next;
    }
    
    return nullptr;
}

bool StudentDictionary::insert(const std::string& key, const StudentInfo& value) {
    if (contains(key)) {
        return false;
    }
    
    int index = hashFunction(key);
    DictEntry* newEntry = new DictEntry(key, value);
    
    newEntry->next = table[index];
    table[index] = newEntry;
    count++;
    
    return true;
}

bool StudentDictionary::remove(const std::string& key) {
    int index = hashFunction(key);
    DictEntry* entry = table[index];
    DictEntry* prev = nullptr;
    
    while (entry != nullptr) {
        if (entry->key == key) {
            if (prev == nullptr) {
                table[index] = entry->next;
            } else {
                prev->next = entry->next;
            }
            delete entry;
            count--;
            return true;
        }
        prev = entry;
        entry = entry->next;
    }
    
    return false;
}

bool StudentDictionary::contains(const std::string& key) const {
    return findEntry(key) != nullptr;
}

StudentInfo* StudentDictionary::get(const std::string& key) const {
    DictEntry* entry = findEntry(key);
    return (entry != nullptr) ? &(entry->value) : nullptr;
}

vector<string> StudentDictionary::getAllKeys() const {
    vector<string> keys;
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        DictEntry* entry = table[i];
        while (entry != nullptr) {
            keys.push_back(entry->key);
            entry = entry->next;
        }
    }
    
    return keys;
}

vector<pair<string, StudentInfo>> StudentDictionary::getAllEntries() const {
    vector<pair<string, StudentInfo>> entries;
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        DictEntry* entry = table[i];
        while (entry != nullptr) {
            entries.push_back(make_pair(entry->key, entry->value));
            entry = entry->next;
        }
    }
    
    return entries;
}

int StudentDictionary::size() const {
    return count;
}

bool StudentDictionary::isEmpty() const {
    return count == 0;
}

void StudentDictionary::clear() {
    clearTable();
}

bool StudentDictionary::loadFromFile(const std::string& filename) {
    ifstream file(filename, ios::binary); 
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << endl;
        return false;
    }
    
    clear();
    
    int N;

    if (!(file >> N)) {
        cerr << "Ошибка: не могу прочитать количество студентов" << endl;
        file.close();
        return false;
    }
    
    file.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (N > 500) {
        cerr << "Ошибка: количество абитуриентов превышает 500" << endl;
        file.close();
        return false;
    }
    
    if (N <= 0) {
        cerr << "Ошибка: некорректное количество студентов: " << N << endl;
        file.close();
        return false;
    }
    
    for (int i = 0; i < N; i++) {
        string line;
        
        if (!getline(file, line)) {
            if (file.eof()) {
                cerr << "Ошибка: файл закончился раньше, чем ожидалось" << endl;
            } else {
                cerr << "Ошибка чтения строки " << i + 1 << endl;
            }
            file.close();
            return false;
        }
        
        if (line.empty()) {
            i--; 
            continue;
        }
        
        istringstream iss(line);
        string lastName, firstName;
        int score1, score2;
        
        if (!(iss >> lastName >> firstName >> score1 >> score2)) {
            cerr << "Ошибка формата строки: " << line << endl;
            continue; 
        }
        
        size_t start = lastName.find_first_not_of(" \t\r\n");
        size_t end = lastName.find_last_not_of(" \t\r\n");
        if (start != string::npos && end != string::npos) {
            lastName = lastName.substr(start, end - start + 1);
        }
        
        start = firstName.find_first_not_of(" \t\r\n");
        end = firstName.find_last_not_of(" \t\r\n");
        if (start != string::npos && end != string::npos) {
            firstName = firstName.substr(start, end - start + 1);
        }
        
        if (lastName.length() > 40) {
            cerr << "Предупреждение: фамилия '" << lastName 
                 << "' слишком длинная, обрезается до 20 символов" << endl;
            lastName = lastName.substr(0, 20);
        }
        
        if (firstName.length() > 30) {
            cerr << "Предупреждение: имя '" << firstName 
                 << "' слишком длинное, обрезается до 15 символов" << endl;
            firstName = firstName.substr(0, 15);
        }

        if (score1 < 0 || score1 > 100 || score2 < 0 || score2 > 100) {
            cerr << "Ошибка: некорректные баллы у абитуриента " 
                 << lastName << " " << firstName << ": " 
                 << score1 << " " << score2 << endl;
            continue;
        }
        
        StudentInfo info;
        info.firstName = firstName;
        info.score1 = score1;
        info.score2 = score2;
        
        if (!insert(lastName, info)) {
            cerr << "Ошибка: абитуриент с фамилией '" << lastName 
                 << "' уже существует" << endl;
        }
    }
    
    file.close();
    return true;
}

vector<string> StudentDictionary::getFailedStudents() const {
    vector<string> failed;
    
    vector<pair<string, StudentInfo>> entries = getAllEntries();
    
    for (const auto& entry : entries) {
        const string& lastName = entry.first;
        const StudentInfo& info = entry.second;
        
        if (info.score1 < 30 || info.score2 < 30) {
            failed.push_back(lastName + " " + info.firstName);
        }
    }
    
    sort(failed.begin(), failed.end());
    
    return failed;
}