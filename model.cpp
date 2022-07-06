#include "model.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

Model::Model(const char* filename) {
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if (in.fail()) return;
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if(!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec3f v;
            for(int i =0; i < 3; i++) iss >> v.raw[i];
            verts.push_back(v);
        }else if (!line.compare(0, 2, "f ")) {
            std::vector<int> f;
            int itrash, idx;
            iss >> trash;
            while(iss >> idx >> trash >> itrash >> trash >> itrash) {
                idx--;
                f.push_back(idx);
            }
            faces.push_back(f);
        }
    }
    std::cerr << "# v# " << verts.size() << " f# "  << faces.size() << std::endl;
}

Model::~Model() {}

int Model::nfaces() {
    return (int)faces.size();
}

std::vector<int> Model::face(int idx) {
    return faces[idx];
}

Vec3f Model::vert(int i) {
    return verts[i];
}