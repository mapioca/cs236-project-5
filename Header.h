//
// Created by moisa on 6/15/2021.
//

#ifndef PROJECT5_HEADER_H
#define PROJECT5_HEADER_H


#include <iostream>
#include <vector>

class Header {
public:
    Header()= default;;
    Header(std::vector<std::string> attributesList);
    void addToHeader(const std::string& attribute);
    std::string printAttributeByIndex(int index);
    int getSize();
    std::vector<std::string> getAttributes();
    void addToUniqueColumns(int index);
    std::vector<int> getUniqueColumns();
    int getUniqueColumnsSize();
    void setUniqueColumns(std::vector<int> uniqueColumnsVectorToPass);

    void setColumnMatches(std::vector<int> columnMatch);

private:
    std::vector<std::string> attributes;
    std::vector<int> uniqueColumns;
};


#endif //PROJECT5_HEADER_H
