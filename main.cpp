//Files werden nur gelesen, wenn sie im cmake-build-debug sind
//test

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "cmake-build-debug/classes/Hashtable.h"
#include "cmake-build-debug/classes/Aktie.h"
#include "cmake-build-debug/classes/HashNode.h"

#define arrayLength 254
#define arrayDepth 7

using namespace std;


//toDo array Aktie done
//toDo aus void get entries, in zwei funktionen einteilen -> eines das durchgeht, eines das array macht done

//abspeichern? durch hash durchegehen -> Bei Eintrag speichern
//importierte sachen abspeichern ?
//toDo abspeichern in seperates file, teilweise done
//save file über dateiname {key, dateiname} -> immer wieder importieren

bool addAktie(hashTable*, hashNode*);
hashNode* convertToNode(string, int);
void Menue(hashTable*, hashTable*, bool saveState);


class fileData{
public:
    string array[arrayLength][arrayDepth];
};


void getEntries(fileData *tmp){

    //verfügbare files: AAPL.csv, AMZN.csv, BABA.csv (Alibaba), FB.csv, GOOG.csv, INTC.csv (Intel),
    // MSFT.csv, NTFL.csv, NVDA.csv (Nvidia), TCEHY.csv (Tencent), //alle im data dir gespeichert

    string filename, zeile, eintrag;

    cout << "\nChoose file: FORMAT: 'data/FILENAME.csv'\n";
    cin >> filename; //muss noch als path angegeben werden: data/"name des File".csv

    fstream FILE;
    FILE.open(filename);

    if (FILE.is_open()){
        cout << "\nFile offen";

        int i = 0; //for array
        int j;

        while(getline(FILE, zeile)){ // var zeile: Eintrag bis newline-char

            j = 0;
            //cout << endl;
            //nach jedem Durchgang, eine neue Zeile

            stringstream zeileFormat(zeile); //wandelt string zeile in ein file-ähnliches Format

            while(getline(zeileFormat, eintrag, ',')){// var eintrag: Wert wird bis zu einem Komma eingelesen
                //cout << eintrag << " "; //debug
                //einfügen in Hashtabelle Zeile
                tmp -> array[i][j] = eintrag;
                j++;
            }
            i++;
        }
    } else cout << "\nFile nicht offen";

    //return tmp;
}

void printArray(fileData *tmp){ //printet alle Entries einer Node
    for (int i = 0; i < arrayLength; i++){
        cout << endl;
        for (int j = 0; j < arrayDepth; j++){
            cout << tmp -> array[i][j] << " /   ";
        }
    }
}

int main () {
    bool saveState = false;
    /*
    fileData *test = new fileData;
    test = getEntries(test);
    printArray(test); */


    hashTable nameTable;
    hashTable shortTable;

    cout << "Key: " << hashTable::hash(hashTable::toKey("Googles")) << endl;

    addAktie(&nameTable, convertToNode("Google", 10)); //10 ist ein random value
    addAktie(&nameTable, convertToNode("Facebook", 11));
    addAktie(&nameTable, convertToNode("Facebook", 12));

    nameTable.printAktieAt(hashTable::hash(hashTable::toKey("Facebook")), "Facebook");
    cout << "--------------------------------------" << endl;
    nameTable.printTable();
    cout << "--------------------------------------" << endl;
    /*string input;

    cout << "Enter Aktie to delete" << endl;;
    cin >> input;
    int hash = hashTable::hash(hashTable::toKey(input));
    nameTable.getNode(hash)->getAktie()->deleteAktie(&nameTable, &shortTable);*/

    Menue(&nameTable, &shortTable, saveState);

    cout << "--------------------------------------" << endl;
    nameTable.printTable();
    cout << "--------------------------------------" << endl;

    return 0;
}

void Menue(hashTable* nameTable, hashTable* shortTable, bool saveState)
{
    char input;
    do{ // Problem: man kommt aus der Schleife nicht raus
        cout << "Select Action: (a)dd | (d)elete | (p)rint | (v)alues | (i)mport | (s)ave | (e)xit" << endl;
        cin >> input;
        switch(input){
            case 'a':
            case 'A': break;
            case 'd':
            case 'D':   {string name;
                cout << "Enter Aktie to delete" << endl;;
                cin >> name;

                int hash = hashTable::hash(hashTable::toKey(name));
                nameTable->getNode(hash)->getAktie()->deleteAktie(nameTable, shortTable);
            }break;
            case 'p':
            case 'P': nameTable->printTable(); break;
            case 'i':
            case 'I': break;
            case 's':
            case 'S': {

                if(saveState) { remove("data/saveData.txt"); saveState = false;}
                nameTable ->saveTable(saveState);
                saveState = true;
            }   break;
            case 'e':
            case 'E': break;
            case 'v':
            case 'V': break; //values anhand von
            default: input = 0;
        }
    } while (input != 0 && input != 'e' && input != 'E'); //eingabe endet nach e oder E


}

bool addAktie(hashTable* myTable, hashNode* newNode){ //
    int myhash = myTable->hash(myTable->toKey(newNode->getAktie()->getName()));
    if(myTable->addAktie(myhash, newNode)){
        cout << "Aktie was added" << endl;
        return true;
    } else {
        cout << "Aktie couldnt be added" << endl;
        return false;
    }
}

hashNode* convertToNode(string name, int value){ //erstellt Hashnode mit neuer Aktie, gibt pointer zurück
    return new hashNode(new aktie(name, value));
}