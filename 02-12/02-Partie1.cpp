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
    }
    return s;
}

int main() {
    std::string fichier="input2.txt";
    std::vector<std::string> data=load(fichier);
    int S;
    S=sommeID(data);
    std::cout<<S<<std::endl;
    return 0;
}
