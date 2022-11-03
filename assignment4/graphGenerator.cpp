#include "graphGenerator.h"
#include "util.h"
#include "graph.h"

#include <iostream>

void createGraphs(StringArr* contents) {
    int curBegin = -1;
    for (int i = 0; i < contents->length; i++) {
        if (contents->arr[i].compare("new graph") == 0) {
            if (curBegin != -1) {
                Graph g(contents, curBegin, i - 1);
                g.printMatrix();
                std::cout << std::endl;
            }
            curBegin = i;
        } else if (i == contents->length - 1) {
            Graph g(contents, curBegin, i);
            g.printMatrix();
            std::cout << std::endl;
        }
    }
}