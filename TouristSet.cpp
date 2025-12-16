#include "TouristSet.h"
#include <algorithm>
#include <iostream>

using namespace std;

TouristSet::TouristSet() {}

TouristSet::TouristSet(const vector<string>& initialElements){
    for (const auto& element: initialElements) {
        add(element);
    }
}

bool TouristSet::elementExists(const string& element) const {
    return find(elements.begin(), elements.end(), element) != elements.end();
}

int TouristSet::findElementIndex(const string& element) const {
    auto it = find(elements.begin(), elements.end(), element);
    if (it != elements.end()){
        return distance(elements.begin(), it);
    }
    return -1;
}

void TouristSet::add(const string& element) {
    if (!elementExists(element)){
        elements.push_back(element);
    }
}

bool TouristSet::remove(const string& element) {
    int index = findElementIndex(element);
    if (index != -1) {
        elements.erase(elements.begin() + index);
        return true;
    }
    return false;
}

bool TouristSet::contains(const string& element) const{
    return elementExists(element);
}

void TouristSet::clear() {
    elements.clear();
}

TouristSet TouristSet::Union(const TouristSet& other) const {
    TouristSet result = *this;

    for (const auto& element : other.elements) {
        result.add(element);
    }
    return result;
}

TouristSet TouristSet::Except(const TouristSet& other) const {
    TouristSet result;

    for (const auto& element : elements) {
        if (!other.contains(element)){
            result.add(element);
        }
    }
    return result;
}

TouristSet TouristSet::Intersect(const TouristSet& other) const {
    TouristSet result;

    for (const auto& element : elements){
        if (other.contains(element)){
            result.add(element);
        }
    }
    return result;
}

vector<string> TouristSet::getElements() const{
    return elements;
}

size_t TouristSet::size() const{
    return elements.size();
}

bool TouristSet::isEmpty() const{
    return elements.empty();
}

void TouristSet::print() const{
    cout << "В множестве " << elements.size() << " элементов. ";

    if(elements.empty()){
        cout << "Пусто";
    } else {
        for (size_t i = 0; i < elements.size(); i++){
            cout << elements[i];
            if (i < elements.size() - 1) {
                cout << ", ";
            }
        }
    }
    cout << endl;
}