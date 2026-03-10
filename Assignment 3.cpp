#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <iomanip>
using namespace std;

// Create a class for nodes to store letter and frequency
class huffNode
{
public:
    char letter;
    int freq;

    huffNode* left;
    huffNode* right;

    huffNode(char letter, int freq)
    {
        this->freq = freq;
        this->letter = letter;
        this->left = NULL;
        this->right = NULL;
    }
};

// Create a minHeap class, which will be used to
// grab the lowest frequency count nodes when building our Huffman tree.
class minHeap {
public:
    int maxSize = 100, elements = 0;
    huffNode* pq[100];
    bool overflow = false, underflow = false;

    minHeap() {
        for (int i = 0; i < maxSize; i++)
            this->pq[i] = NULL;
    }

    // Return heap size
    int size()
    {
        return elements;
    }

    // Insert a new node if the heap is not full
    void insert_node(huffNode* tmpnode)
    {
        if (size() < maxSize)
        {
            // Insert node at the bottom of the heap.
            int pos = size();

            // Compare the node to its parents value until the parent has a value
            // less than the value of the new node.
            // pq[(pos - 1) / 2] points to the parent of the node at pos
            while (pos > 0 and tmpnode->freq < pq[(pos - 1) / 2]->freq)
            {
                // Swap new node value with parent node value.
                // To be clear, the nodes stay in the same "position."
                // It's the values that are swapping.
                pq[pos] = pq[(pos - 1) / 2];

                // Now swap position to equal the parent nodes position.
                pos = (pos - 1) / 2;
            }

            pq[pos] = tmpnode;
            elements++;
        }
        else
        {
            overflow = true;

            return;
        }
    }

    // Delete and return a node
    huffNode* delete_node()
    {
        if (size() > 0)
        {
            huffNode* tmpnode = pq[0];

            pq[0] = pq[elements - 1];
            pq[elements - 1] = NULL;
            elements--;

            heapify(0);
            return tmpnode;
        }

        else
        {
            underflow = true;
        }
        return NULL;
    }

    // Properly place each inserted node into the heap
    void heapify(int idx)
    {
        int parent = idx;
        int leftChild = idx * 2 + 1;
        int rightChild = idx * 2 + 2;

        if (leftChild < size() and pq[leftChild]->freq < pq[parent]->freq)
        {
            parent = leftChild;
        }

        // If right child is less than left child, it will "override" the value stored in parent from left child
        if (rightChild < size() and pq[rightChild]->freq < pq[parent]->freq)
        {
            parent = rightChild;
        }

        if (parent != idx)
        {
            huffNode* tmpnode = pq[parent];
            pq[parent] = pq[idx];
            pq[idx] = tmpnode;
            heapify(parent);
        }

        return;
    }
};

// Recursively search through our Huffman tree
void find_codes(huffNode* currentNode, string currentCode, map<char, pair<int, string>>& letterMap)
{
    // Return if we get to the end of the tree, i.e. if we get to a null node
    if (currentNode == NULL)
    {
        return;
    }

    // If the node isn't NULL, but both of it's children are, then we know we've found a leaf, i.e. a letter
    if (currentNode->left == NULL and currentNode->right == NULL)
    {
        letterMap[currentNode->letter] = make_pair(currentNode->freq, currentCode);
    }

    find_codes(currentNode->left, currentCode + "0", letterMap);
    find_codes(currentNode->right, currentCode + "1", letterMap);
}


int main()
{
    // Create a minHeap class instance called heap
    minHeap heap;

    // Add nodes for all letters, allong with their frequency counts
    heap.insert_node(new huffNode('A', 77));
    heap.insert_node(new huffNode('B', 17));
    heap.insert_node(new huffNode('C', 32));
    heap.insert_node(new huffNode('D', 42));
    heap.insert_node(new huffNode('E', 120));
    heap.insert_node(new huffNode('F', 24));
    heap.insert_node(new huffNode('G', 17));
    heap.insert_node(new huffNode('H', 50));
    heap.insert_node(new huffNode('I', 76));
    heap.insert_node(new huffNode('J', 4));
    heap.insert_node(new huffNode('K', 7));
    heap.insert_node(new huffNode('L', 42));
    heap.insert_node(new huffNode('M', 24));
    heap.insert_node(new huffNode('N', 67));
    heap.insert_node(new huffNode('O', 67));
    heap.insert_node(new huffNode('P', 20));
    heap.insert_node(new huffNode('Q', 5));
    heap.insert_node(new huffNode('R', 59));
    heap.insert_node(new huffNode('S', 67));
    heap.insert_node(new huffNode('T', 85));
    heap.insert_node(new huffNode('U', 37));
    heap.insert_node(new huffNode('V', 12));
    heap.insert_node(new huffNode('W', 22));
    heap.insert_node(new huffNode('X', 4));
    heap.insert_node(new huffNode('Y', 22));
    heap.insert_node(new huffNode('Z', 2));

    // Create the Huffman tree
    while (heap.size() > 1)
    {
        // Delete the two smallest nodes, by frequency. Store them in huffNode pointers.
        huffNode* left = heap.delete_node();
        huffNode* right = heap.delete_node();

        // Create a new node, which will be the parent of the two smallest nodes, forming a subtree.
        // This node will have '#' for it's letter value, indicating it is not a letter/not part of our Huffman code
        huffNode* parent = new huffNode('#', left->freq + right->freq);

        // Set the removed nodes to be children of the new parent node.
        parent->left = left;
        parent->right = right;

        // Add our new node to the heap
        heap.insert_node(parent);
    }

    // The last node left will be the root of our Huffman tree. 
    // By accessing it's decnedants (it's children, it's children's children, etc.) we can access the nodes of all of our letters.
    huffNode* huffRoot = heap.delete_node();

    // Create an empty map to store the letters and their codes
    map<char, pair<int, string>> letterCodes = {};

    // Use find_codes to fill the letterCodes map
    find_codes(huffRoot, "", letterCodes);

    // Print table header
    cout << left
        << setw(10) << "Letter"
        << setw(12) << "Frequency"
        << setw(12) << "Code"
        << setw(10) << "Length"
        << setw(12) << "Freq X Len"
        << endl;

    cout << "______   __________   ______     ________  ____________" << endl;

    // Print each letter and it's associated details
    for (auto& p : letterCodes)
    {
        cout << left
            << setw(10) << p.first
            << setw(12) << p.second.first
            << setw(12) << p.second.second
            << setw(10) << p.second.second.length()
            << setw(12) << p.second.first * p.second.second.length()
            << endl;
    }

    return 0;
}



