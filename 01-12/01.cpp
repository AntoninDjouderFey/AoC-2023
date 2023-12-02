

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

std::vector<std::string> chiffres={"one","two","three"
    ,"four", "five", "six", "seven", "eigh", "nine"
};

/**
 * Loads data from a file.
 *
 * @param fichier The name of the file to load.
 * @return A vector of strings containing the loaded data.
 */
std::vector<std::string> load(std::string fichier) {
    std::vector<std::string> data;
    std::ifstream file(fichier);
    std::string line;
    while (std::getline(file, line)) {
        data.push_back(line);
    }
    return data;
}

char tochar(int i) {
    char c=i+48;
    return c;
}

std::string remplacement(std::string l) {
    //on créer une copie pour modifier l'original, car il ne faudrait pas faire la comparaison après qu'on aie modifier
    std::string l2=l;
    for (int i = 0; i < chiffres.size(); i++) {
        //trouve la position du premier caractère de chiffre
        size_t pos = l.find(chiffres.at(i));
        while (pos != std::string::npos ) {
            //il faut utiliser des ittérateurs pour fill
            auto begin = l2.begin() + pos;
            auto end = begin + chiffres.at(i).size();

            // Utilisation de std::replace avec des itérateurs
            std::fill(begin, end, tochar(i + 1));

            // Trouver la prochaine occurrence de la sous-chaîne
            pos = l.find(chiffres.at(i), pos + 1);
        }
    }
    return l2;
}

std::vector<std::string> grand_remplacement(std::vector<std::string> data) {
    for (auto& line : data) {
            line=remplacement(line);
    } return data;
}

/// @brief 
/// @param l 
/// @return 
int nbsecret(std::string l) {
    int n=0;
    //cherche le premier chiffre, puis le multiplie par 10
    for(int i=0 ;i<l.size();i++) {
        if (l.at(i)>='0' && l.at(i)<='9') {
            n+=(l.at(i)-'0')*10;
            break;
        }
    } //cherche le dernier chiffre et l'additionne
    for (int j=l.size()-1;j>=0;j--) {
        if (l.at(j)>='0' && l.at(j)<='9') {
            n+=(l.at(j)-'0');
            break;
        }
    } return n;
}

/// @brief 
/// @param data 
/// @return 
int calibrage(std::vector<std::string> data) {
    int result = 0;
    for (auto line : data) {
    // fait la somme de chaque nombre qu'on obtient sur chaque ligne
        result += nbsecret(line);
    }
    return result;
}

int main() {
    std::vector<std::string> data = load("input.txt");
    data=grand_remplacement(data);
    std::cout << calibrage(data) << std::endl;
    return 0;
}
