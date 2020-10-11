#include "hellowords.h"
#include <iostream>
#include <fstream>
#include <random>

HelloWords::HelloWords() {
    std::random_device rd;
    _mt = std::mt19937_64(rd());
    _dis = std::uniform_int_distribution<unsigned>(0, _words.size() - 1);
}

int HelloWords::addWords(const std::string& filename, const std::string& type) {
    if (type == "one") {
        std::ifstream in(filename);
        if (!in) {
            std::cerr << "open file " << filename << " failed." << std::endl;
        }
        char buffer[1024];
        while (!in.eof()) {
            in.getline(buffer, sizeof(buffer), '\n');
            std::string line(buffer);
            int tabpos = line.find('\t');
            if (tabpos != -1) {
                _words.push_back(line.substr(tabpos + 1));
            }
        }
        in.close();
    } else {
        std::cerr << "unknow type " << type << std::endl;
        return -1;
    }

    _dis = std::uniform_int_distribution<unsigned>(0, _words.size() - 1);
    return 0;
}

const std::string& HelloWords::helloWords() {
    return _words[_dis(_mt)];
}
