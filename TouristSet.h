#ifndef TOURISTSET_H
#define TOURISTSET_H

#include <string>
#include <vector>

using namespace std;

class TouristSet {
    private:
        vector<string> elements;

        bool elementExists(const string& element) const;
        int findElementIndex(const string& element) const;

    public:

        TouristSet();
        TouristSet(const vector<string>& initialElements);

        void add(const string& element);
        bool remove(const string& element);
        bool contains(const string& element) const;
        void clear();

        TouristSet Union(const TouristSet& other) const;
        TouristSet Except(const TouristSet& other) const;
        TouristSet Intersect(const TouristSet& other) const;

        vector<string> getElements() const;
        size_t size() const;
        bool isEmpty() const;
        void print() const;

};


#endif