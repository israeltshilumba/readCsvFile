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
    bool printAktieAt(int key, std::string name, bool mode);

    static int toKey(std::string name);
    static int hash(int key);
    static int seq(int key);
    static void swapAktie(hashNode* Node1, hashNode* Node2);

    hashNode* getNode(int key);
    hashNode* getNode(int key, std::string name, bool mode);
    void printTable();
    void saveTable(bool saveState);//new saves table in text file
    bool shuffle(int key, hashTable* Table);

    void clean();
    void cleanNode(int key);

protected:

private:
    hashNode* Tabelle[20];
};

#endif //READCSVFILE_HASHTABLE_H
