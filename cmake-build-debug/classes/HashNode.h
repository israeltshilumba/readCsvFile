#ifndef READCSVFILE_HASHNODE_H
#define READCSVFILE_HASHNODE_H


class aktie;
class hashTable;

#include "Hashtable.h"
#include "Aktie.h"

class hashNode
{
public:
    hashNode(aktie* Aktie);
    virtual ~hashNode();
    hashNode insertNode(int Depth, aktie* Aktie);

    int getDepth();
    void changeDepth(int value);
    aktie* getAktie();
    aktie* getAnum();
    void setAktie(aktie* newAktie);
    // new: damit alle Eintrage einer Aktie geprintet werden
    // std::string entries[arrayLength][arrayDepth];
private:
    int n_Depth;
    aktie* n_Aktie;
};


#endif //READCSVFILE_HASHNODE_H
