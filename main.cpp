//Files werden nur gelesen, wenn sie im cmake-build-debug sind
//test

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define arrayLength 254
#define arrayDepth 7

using namespace std;


//toDo
//array Aktie
//aus void get entries, in zwei funktionen einteilen -> eines das durchgeht, eines das array macht
//abspeichern? durch hash durchegehen -> Bei Eintrag speichern
//importierte sachen abspeichern
//abspeichern in seperates file
//save file von json Form, über dateiname {key, dateiname} -> immer wieder importieren



class fileData{
public:
    string array[arrayLength][arrayDepth];
};

fileData *getEntries(fileData *tmp){

    //verfügbare files: AAPL.csv, AMZN.csv, BABA.csv (Alibaba), FB.csv, GOOG.csv, INTC.csv (Intel),
    // MSFT.csv, NTFL.csv, NVDA.csv (Nvidia), TCEHY.csv (Tencent), //alle im data dir gespeichert

    //string *entries = new string[arrayLength][arrayDepth];
    string filename, zeile, eintrag;

    cout << "\nChoose file: FORMAT: 'data/FILENAME.csv'\n";
    cin >> filename; //muss noch als path angegeben werden: data/"name des File".csv

    fstream FILE;
    FILE.open(filename);

    if (FILE.is_open()){
        cout << "\nFile offen";

        int i = 0; //for array
        int j = 0;

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

    return tmp;
}

void printArray(fileData *tmp){
    for (int i = 0; i < arrayLength; i++){
        cout << endl;
        for (int j = 0; j < arrayDepth; j++){
            cout << tmp -> array[i][j] << " / ";
        }
    }
}

int main () {
    fileData *test = new fileData;
    test = getEntries(test);
    printArray(test);
    return 0;
}