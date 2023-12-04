#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>

std::vector<std::string> load(std::string fichier) {
    std::vector<std::string> data;
    std::ifstream file(fichier);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            data.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "Erreur d'ouverture du fichier : " << fichier << std::endl;
    }

    return data;
}


bool estCorrect(std::string ligne) {

    for (int i=0;i<ligne.size();i++) {
        if (ligne.at(i) >= '0' && ligne.at(i) <= '9') {
            int d = ligne.at(i) - '0';
            if ((i + 1) < ligne.size()) {
                if (ligne.at(i + 1) >= '0' && ligne.at(i + 1) <= '9') {
                    d = d * 10 + (ligne.at(i + 1) - '0');
                    i += 1;
                }
            }
            if (ligne.at(i+2)=='r') {
                if (d>12) {return false;}
            }
            if (ligne.at(i+2)=='g') {
                if (d>13) {return false;}
            }
            if (ligne.at(i+2)=='b') {
                if (d>14) {return false;}
            }
        }
    }
    return true;
}

int sommeID(std::vector<std::string> data) {
    int s=0;
    for (int i=0;i<data.size();i++) {
        if (estCorrect(data.at(i))) {s+=i+1;}
        //pour la partie 2, on efface les lignes inutiles, 
        //par ailleurs cette supression de ligne fait que le programme ne fonctionne pas pour la partie 1
        else {data.erase(data.begin()+i);}
    }
    return s;
}

std::vector<int> antomin(std::string ligne) {
    int r=0;
    int g=0;
    int b=0;
    for (int i=0;i<ligne.size();i++) {
        if (ligne.at(i) >= '0' && ligne.at(i) <= '9') {
            int d = ligne.at(i) - '0';
            if ((i + 1) < ligne.size()) {
                if (ligne.at(i + 1) >= '0' && ligne.at(i + 1) <= '9') {
                    d = d * 10 + (ligne.at(i + 1) - '0');
                    i += 1;
                }
            }
            if (ligne.at(i+2)=='r') {
                if (r<d) {r=d;}
            }
            if (ligne.at(i+2)=='g') {
                if (g<d) {g=d;}
            }
            if (ligne.at(i+2)=='b') {
                if (b<d) {b=d;}
            }
        }
    } std::vector<int> tab={r,g,b};
    return tab;
}

std::vector<std::vector<int>> Conc(std::vector<std::string> data) {
    std::vector<std::vector<int>> nvTab;
    for (int i=0;i<data.size();i++) {
        nvTab.push_back(antomin(data.at(i)));
    }
    return nvTab;
}

int Prod (std::vector<int> T) {
    int p=1;
    for (int i=0;i<T.size();i++) {
        p=p*T.at(i);
    }
    return p;
}

int ProdFin(std::vector<std::vector<int>> tab) {
    int s=0;
    for (int i=0;i<tab.size();i++) {
        s+=Prod(tab.at(i));
    } return s;
}

int main() {
    std::string fichier="input2.txt";
    std::vector<std::string> data=load(fichier);
    int S;
    S=sommeID(data);
    std::vector<std::vector<int>> M=Conc(data);
    int Z=ProdFin(M);
    std::cout<<Z<<std::endl;
    return 0;
}

