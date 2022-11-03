#pragma once

#include "node.h"
#include "graphNode.h"
#include "util.h"

class Graph {
    public:
        // Constructor for a a graph that takes in the range of where to find the graph info in the data (endIndex is inclusive in the range)
        Graph(StringArr* data, int beginIndex, int endIndex);

        // Destructor for a graph
        ~Graph();

        // Function to print out the matrix
        void printMatrix();

        // Gets the graph node of the given id, nullptr if not found
        GraphNode* getGraphNode(int nodeId);

    private:
        // Creates a vertex for the linked objects
        void createVertex(std::string vertexInfo);

        // Creates an edge for the linked objects
        void createEdge(std::string edgeInfo);

        // Creates the matrix representation of the graph based on the nodes already created
        void createMatrix();

        // The number of vertices in the graph
        int numVertices;

        // Stores a pointer to the head of a linked list containing all the vertices
        Node<GraphNode*>* vertexList;

        // The matrix representation of the graph
        bool* matrix;
};