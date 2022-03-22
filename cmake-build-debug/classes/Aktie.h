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
        aktie(std::string name, int num);
        virtual ~aktie();

        bool printAktie(); //schreibt name und number
        std::string getName();

        void deleteAktie(hashTable* nameTable, hashTable* shortTable);

    protected:

    private:
        std::string a_name;
        int a_num;
        //new -> Hier ist das csv File in Form eines Arrays gespeichert
        std::string entries[arrayLength][arrayDepth];
};

#endif // AKTIE_H
