#ifndef AKTIE_H
#define AKTIE_H

#include <string>

class hashTable;
class hashNode;

#include "Hashtable.h"
#include "HashNode.h"

#define arrayLength 254
#define arrayDepth 7

class aktie
{
public:
    aktie();
    //aktie(std::string name, std::string shortname, int num);
    virtual ~aktie();

    bool printAktie();
    int getAnum();
    std::string getName();
    std::string getShortName();
    void printArray();//new
    bool deleteAktie(hashTable* nameTable, hashTable* shortTable);
    void getEntries();
    std::string entries[arrayLength][arrayDepth];
    void setFilename();

protected:

private:
    std::string a_name;

    std::string filename; //new for filename
    std::string shortName;
    std::string longName;
    int a_num;
    /*
    std::string a_name;
    std::string a_shortname;
    int a_num;*/
    /* --INSERT YOUR CODE HERE-- */
    // Die Daten der Aktien
};


#endif // AKTIE_H
