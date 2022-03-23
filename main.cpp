#include <iostream>
#include <string>
#include <fstream>

#include "Hashtable.h"
#include "cmake-build-debug/classes/Aktie.h"
#include "cmake-build-debug/classes/HashNode.h"


using namespace std;

bool addAktie(hashTable*, hashNode*, hashTable*);
hashNode* convertToNode(aktie*);
void Menue(hashTable*, hashTable*, bool savestate);

int main()
{
    bool saveState = false; //wird zum speichern benötigt
    hashTable nameTable;
    hashTable shortTable;

    //addAktie(&nameTable, convertToNode("Google", "ggl", 10), &shortTable);
    //addAktie(&nameTable, convertToNode("Facebook", "fb", 11), &shortTable);
    //addAktie(&nameTable, convertToNode("Facebook", "fb", 12), &shortTable);
    //addAktie(&nameTable, convertToNode("Facebook", "fb", 13), &shortTable);
    //addAktie(&nameTable, convertToNode("Facebook", "fb", 14), &shortTable);
    //addAktie(&nameTable, convertToNode("Facebook", "fb", 15), &shortTable);

    //nameTable.print AktieAt(hashTable::hash(hashTable::toKey("Facebook")), "Facebook", true);
    cout << "--------------------------------------" << endl;
    nameTable.printTable();
    cout << "--------------------------------------" << endl;

    Menue(&nameTable, &shortTable, saveState);

    cout << "--------------End Table:--------------" << endl;
    nameTable.printTable();
    cout << "--------------End Table:--------------" << endl;
    shortTable.printTable();

    return 0;
}

void Menue(hashTable* nameTable, hashTable* shortTable, bool saveState)
{
    char input;
    do{
        cout << "Select Action: (a)dd | (d)elete | (p)rint | (i)mport | (s)ave | (e)xit | (c)lean" << endl;
        cin >> input;
        switch(input){
            case 'a':
            case 'A': /* --INSERT YOUR CODE HERE-- */{
                aktie *stock = new aktie;
                addAktie(nameTable, convertToNode(stock), shortTable);
                //cout << "\nDEBUG\n";
                //stock -> printArray();
            } break;
                //user weiß wo file ist //user Shortname u. longname //neues AktienObjekt/* Neue Aktien hinzufügen von csv */ break;
            case 'd':
            case 'D':   {
                char input2;
                string name;
                do{
                    cout << "Delete by Name or ShortName (N)/(S)" << endl;
                    cin >> input2;
                    if(input2 == 'S') input2 = 's';
                    if(input2 == 'N') input2 = 'n';
                } while (input2 != 's' && input2 != 'n');
                cout << "Enter Aktie to delete: ";
                cin >> name;
                cout << "--------------------------------------" << endl;
                switch(input2)
                {
                    case 's':   {hashNode* toDelte = shortTable->getNode(hashTable::hash(hashTable::toKey(name)), name, false);
                        if(toDelte != NULL) {
                            toDelte->getAktie()->deleteAktie(nameTable, shortTable);
                            cout << "   Succesfully deleted" << endl;
                        }}
                        break;
                    case 'n':   {hashNode* toDelete = nameTable->getNode(hashTable::hash(hashTable::toKey(name)), name, true);
                        if(toDelete != NULL){
                            toDelete->getAktie()->deleteAktie(nameTable, shortTable);
                            cout << "   Succesfully deleted" << endl;
                        }}
                        break;
                    default: cout << "Error at finding this aktie" << endl;
                }
                cout << "--------------------------------------" << endl;
            }break;
            case 'p':
            case 'P':   cout << "---------------LongTable--------------" << endl;
                nameTable->printTable();
                cout << "--------------ShortTable--------------" << endl;
                shortTable->printTable();
                cout << "--------------------------------------" << endl;
                break;
            case 'i':
            case 'I': /* --INSERT YOUR CODE HERE-- */{
                //string longName;
                //cin >> longName;
                //////////////////////
                char input2;
                string name;
                do{
                    cout << "Search by LongName or ShortName (N)/(S)" << endl;
                    cin >> input2;
                    if(input2 == 'S') input2 = 's';
                    if(input2 == 'N') input2 = 'n';
                } while (input2 != 's' && input2 != 'n');
                cout << "Enter Stock to import: ";
                cin >> name;
                cout << "--------------------------------------" << endl;
                switch(input2)
                {
                    case 's':   {
                        hashNode *addCSV = shortTable -> getNode(hashTable::hash(hashTable::toKey(name)), name, false);
                        addCSV -> getAktie() -> setFilename();
                        cout << "   Succesfully imported" << endl;
                    }
                        break;
                    case 'n':   {hashNode *addCSV = nameTable -> getNode(hashTable::hash(hashTable::toKey(name)), name, true);
                        addCSV -> getAktie() -> setFilename();
                        cout << "   Succesfully imported" << endl;
                    }
                        break;
                    default: cout << "Error at finding this stock" << endl;
                }
                ////////////////////////////
                //hashNode *addCSV = nameTable -> getNode(hashTable::hash(hashTable::toKey(longName)), longName, true);
                //addCSV -> getAktie() -> setFilename();
                //addCSV -> getAktie() -> printArray();
            } break; /* Hashtabelle von eigener Datei importieren */ break;
            case 's':
            case 'S': {/* --INSERT YOUR CODE HERE-- */
                remove("data/saveData.txt"); saveState = false;
                nameTable ->saveTable(saveState);
                saveState = true;
            }  break;
            case 'e':
            case 'E': break;
            case 'c':
            case 'C':   nameTable->clean(); system("cls");
                cout << "---------------LongTable--------------" << endl;
                nameTable->printTable();
                cout << "--------------ShortTable--------------" << endl;
                shortTable->printTable();
                cout << "--------------------------------------" << endl;
                break;
            default: break;
        }
    } while (input != 'e' && input != 'E');
}

bool addAktie(hashTable* nameTable, hashNode* newNode, hashTable* shortTable){
    hashNode* shortname = new hashNode(newNode->getAktie()); // Kopiert die Hashnode um sie in der zweiten Tabelle einfügen zu können mit eigener Depth

    int namehash = hashTable::hash(hashTable::toKey(newNode->getAktie()->getName()));
    int shorthash = hashTable::hash(hashTable::toKey(newNode->getAktie()->getShortName()));

    if(nameTable->addAktie(namehash, newNode)){
        cout << "!Aktie was added to nameTable!" << endl;

        if(shortTable->addAktie(shorthash, shortname)){
            cout << "!Aktie was added to shortTable!" << endl;
        } else {
            cout << "!Aktie couldnt be added to shortTable!" << endl;
        }
        return true;
    } else {
        cout << "!Aktie couldnt be added to nameTable!" << endl;
        return false;
    }
}

hashNode* convertToNode(aktie *stock){//erstellt Hashnode mit neuer Aktie, gibt pointer zurück
    return new hashNode(stock);
}

