#ifndef READCSVFILE_HASHTABLE_H
#define READCSVFILE_HASHTABLE_H


#include <string>

class aktie;
class hashNode;

#include "HashNode.h"
#include "Aktie.h"

class hashTable
{
public:
    hashTable();
    virtual ~hashTable();
    bool addAktie(int hashkey, hashNode* Node);
    bool printAktieAt(int key, std::string name);

    static int toKey(std::string name);
    static int hash(int key);
    static int seq(int key);

    hashNode* getNode(int key);
    hashNode* getNode(int key, std::string name);
    void printTable();
    void saveTable(bool saveState);
protected:

private:
    hashNode* Tabelle[20];
};


#endif //READCSVFILE_HASHTABLE_H
