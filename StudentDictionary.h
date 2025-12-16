#ifndef STUDENTDICTIONARY_H
#define STUDENTDICTIONARY_H

#include <string>
#include <vector>
#include <utility>

using namespace std;

struct StudentInfo {
    string firstName;
    int score1;
    int score2;
};

class StudentDictionary {
    private:
        struct DictEntry {
            string key;
            StudentInfo value;
            DictEntry* next;

            DictEntry(const string& k, const StudentInfo& v) : key(k), value(v), next(nullptr) {}
        };
        
        static const int TABLE_SIZE = 101;
        DictEntry** table;
        int count; 

        int hashFunction(const string& key) const;

        void clearTable();
        DictEntry* findEntry(const string& key) const;

    public:
        StudentDictionary();
        ~StudentDictionary();

        bool insert(const string& key, const StudentInfo& value);
        bool remove(const string& key); 
        bool contains(const string& key) const;
        StudentInfo* get (const string& key) const;

        vector<string> getAllKeys() const;
        vector<pair<string, StudentInfo>> getAllEntries() const;
        int size() const;
        bool isEmpty() const;
        void clear();

        bool loadFromFile(const string& filename);

        vector<string> getFailedStudents() const;
};

















#endif