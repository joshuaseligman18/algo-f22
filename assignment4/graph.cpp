#include "graph.h"

#include "util.h"
#include "node.h"
#include "graphNode.h"

#include <regex>
#include <iostream>
#include <sstream>

Graph::Graph(StringArr* data, int beginIndex, int endIndex) {
    numVertices = 0;
    vertexList = nullptr;

    for (int i = beginIndex; i <= endIndex; i++) {
        // Get the first 5 characters. Should be "add v" or "add e"
        std::string prefix = data->arr[i].substr(0, 5);

        if (prefix.compare("add v") == 0) {
            // Create a vertex
            createVertex(data->arr[i]);
        } else if (prefix.compare("add e") == 0) {
            // Add the edge
            createEdge(data->arr[i]);
        }
    }

    std::cout << numVertices << std::endl;

    // Create a matrix of size numVertices x numVertices
    matrix = new bool[numVertices * numVertices];

    // Initialize the matrix to be all false
    for (int i = 0; i < numVertices * numVertices; i++) {
        matrix[i] = false;
    }
}

Graph::~Graph() {
    delete [] matrix;

    // Go through all created vertices
    Node<GraphNode*>* cur = vertexList;
    while (cur != nullptr) {
        Node<GraphNode*>* toBeDeleted = cur;
        cur = cur->next;

        // Delete the graph node and the linked list node
        delete toBeDeleted->data;
        delete toBeDeleted;
    }
}

void Graph::createVertex(std::string vertexInfo) {
    char* ptr;
    ptr = strtok(vertexInfo.data(), " ");

    bool idNext = false;
    int vertexId;

    while (ptr != NULL) {
        std::stringstream ss(ptr);
        if (idNext) {
            // Get the id and break
            ss >> vertexId;

            // Change back to false and let the strtok function break the loop
            idNext = false;
        } else if (ss.str().compare("vertex") == 0) {
            // We know the next segment is going to be the id of the vertex
            idNext = true;
        }

        // Check the next word
        ptr = strtok(NULL, " ");
    }

    // Create the graph node
    GraphNode* newGraphNode = new GraphNode(vertexId, numVertices);

    // Create the regular node and store it in the list at the front to keep O(1) time
    Node<GraphNode*>* newNode = new Node<GraphNode*>(newGraphNode);
    newNode->next = vertexList;
    vertexList = newNode;

    // Increment the number of vertices
    numVertices++;
}

void Graph::createEdge(std::string edgeInfo) {
    // Variable to store the match results
    std::smatch m;
    // Regular expression looks for a number followed by a space, hyphen, space, and another number
    std::regex e("\\d+ - \\d+");

    // Try to find the match
    std::regex_search(edgeInfo, m, e);

    bool firstId = true;

    int id1 = INT_MIN;
    int id2 = INT_MIN;

    char* ptr;
    // Only work with the substring that is the vertices
    ptr = strtok(edgeInfo.substr(m.position(), m.length()).data(), " - ");
    while (ptr != NULL) {
        std::stringstream ss(ptr);
        if (firstId) {
            // Store the id of the first vertex
            ss >> id1;
            firstId = false;
        } else {
            // Store the id of the second vertex
            ss >> id2;
        }
        ptr = strtok(NULL, " - ");
    }

    GraphNode* v1 = getGraphNode(id1);
    if (v1 == nullptr) {
        // Create an error message if the vertex was not found
        std::stringstream ss;
        ss << "Vertex " << id1 << " does not exist";
        throw std::invalid_argument(ss.str());
    }

    GraphNode* v2 = getGraphNode(id2);
    if (v2 == nullptr) {
        // Create an error message if the vertex was not found
        std::stringstream ss;
        ss << "Vertex " << id2 << " does not exist";
        throw std::invalid_argument(ss.str());
    }

    // Add each vertex to the neighbors list
    v1->addNeighbor(v2);
    v2->addNeighbor(v1);

    std::cout << "Created edge " << v1->getId() << " - " << v2->getId() << std::endl;
}

void Graph::printMatrix() {
    // Iterate through each row
    for (int i = 0; i < numVertices; i++) {
        // Iterate through each column
        for (int j = 0; j < numVertices; j++) {
            // Print out the value at the given location
            std::cout << matrix[i * numVertices + j] << " ";
        }
        std::cout << std::endl;
    }
}

GraphNode* Graph::getGraphNode(int nodeId) {
    // Start at the head of the list
    Node<GraphNode*>* cur = vertexList;

    // Assume not found
    bool found = false;

    while (cur != nullptr && !found) {
        // Set found to true if the id matches
        if (cur->data->getId() == nodeId) {
            found = true;
        } else {
            // Otherwise move on to the next node
            cur = cur->next;
        }
    }

    // Return the graph node
    return cur->data;
}