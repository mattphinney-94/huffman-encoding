// Assignment 3.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class huffNode
{
public:
    int freq;
    char letter;

    huffNode* left;
    huffNode* right;

    huffNode(int freq, char letter)
    {
        this->freq = freq;
        this->letter = letter;
        this->left = NULL;
        this->right = NULL;
    }
};

class minHeap {
public:
    int maxSize = 100, elements = 0;
    huffNode* pq[100];
    bool overflow = false, underflow = false;

    minHeap() {
        for (int i = 0; i < maxSize; i++)
            this->pq[i] = NULL;
    }

    int size()
    {
        return elements;
    }

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

    void heapify(int idx)
    {
        int parent = idx;
        int leftChild = idx * 2 + 1;
        int rightChild = idx * 2 + 2;

        if (leftChild < size() and pq[leftChild]->freq < pq[idx]->freq)
        {
            parent = leftChild;
        }

        // If right child is less than left child, it will "override" the value stored in parent from left child
        if (rightChild < size() and pq[rightChild]->freq < pq[idx]->freq)
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

int main()
{
    minHeap* min_heap = new minHeap();

    int num[14] = { 10, 30, 20, 35, 50, 40, 45, 60, 75, 80, 95, 70, 98, 92 };
    int heap_size = 14;

    // Adding minheap values
    for (int i = 0; i < heap_size; i++)
    {
        min_heap->insert_node(new Node(num[i]));

    }

    // Printing minheap values
    for (int i = 0; i < heap_size; i++)
    {
        cout << min_heap->pq[i]->ID << ',';
    }

    cout << endl;

    min_heap->insert_node(new Node(25));

    for (int i = 0; i < min_heap->size() + 1; i++)
    {
        cout << min_heap->pq[i]->ID << ',';
    }

    cout << endl;

    // Get the id value of the deleted node
    int key = min_heap->delete_node()->ID; 
    cout << key;



    return 0;
}



