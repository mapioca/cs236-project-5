//
// Created by moisa on 6/15/2021.
//

#include "Header.h"

Header::Header(std::vector<std::string> attributesList) {
    attributes = attributesList;
}

void Header::addToHeader(const std::string& attribute) {
    attributes.push_back(attribute);
}

std::string Header::printAttributeByIndex(int index) {
    return attributes.at(index);
}

int Header::getSize() {
    return (int)attributes.size();
}

std::vector<std::string> Header::getAttributes() {
    return attributes;
}

void Header::addToUniqueColumns(int index) {
    uniqueColumns.push_back(index);
}

std::vector<int> Header::getUniqueColumns() {
    return uniqueColumns;
}

int Header::getUniqueColumnsSize() {
    return (int)uniqueColumns.size();
}

void Header::setUniqueColumns(std::vector<int> vectorToPass) {
    uniqueColumns = vectorToPass;
}
