#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <windows.h>
#endif
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h> 
#include <stdio.h>
#include <time.h> 
#include <chrono> 
#include <queue>
#include <algorithm>

using namespace std::chrono;
using namespace std;

// Class that would store the tv series object;
class TvSeries
{
public:
    string tconst;
    string name;
    string startYear;
    string endYear;
    string genres;
    TvSeries();
    TvSeries(string tconst, string name, string startYear, string endYear, string genres);
    void Print();
};

// TvSeries default constructor
TvSeries::TvSeries()
{
    string tconst = "";
    string name = "";
    string startYear = "";
    string endYear = "";
    string genres = "";
}

//Tv series constructor
TvSeries::TvSeries(string tconst, string name, string startYear, string endYear, string genres)
{
    this->tconst = tconst;
    this->name = name;
    this->startYear = startYear;
    this->endYear = endYear;
    this->genres = genres;
}

// Print all the information of a Tv series
void TvSeries::Print()
{
    // If the information is empty, the tv series is not available
    if (tconst == "")
    {
        cout << "Show not available" << endl;
        return;
    }
    cout << "tConst = " << tconst << endl;
    cout << "Name = " << name << endl;


    cout << "Start Year = " << startYear << endl;
    // if the end year of the show is available
    if (endYear != "\\N")
        cout << "End Year = " << endYear << endl;
    // if the end year of the show is not available
    else
        cout << "End Year = Not Available" << endl;
    cout << "Genres = ";
    // If the genres category is available print them all.
    if (genres != "\\N")
    {
        for (unsigned int i = 0; i < genres.size(); i++)
        {
            if (genres[i] != '\"' && genres[i] != ',')
                cout << genres[i];
            if (genres[i] == ',')
                cout << ", ";
        }
        cout << "." << endl;
    }
    // if genres are not available 
    else
        cout << "Not Available" << endl;
    cout << "--------------------------------------------" << endl;
}

// Class that would contain the node for the map
class MNode {
public:
    string key;
    TvSeries value;
    MNode* left;
    MNode* right;
    MNode();
    MNode(string name, TvSeries x);
    MNode(string name, TvSeries x, MNode* left, MNode* right);
    ~MNode();
};

// Destructor of the Node class
MNode::~MNode()
{
    if (left)
        delete left;
    if (right)
        delete right;

}

// Default constructor of the Node class
MNode::MNode()
{
    key = "";
    value;
    left = nullptr;
    right = nullptr;
}

// Constructor of node class
MNode::MNode(string name, TvSeries x)
{
    key = name;
    value = x;
    left = nullptr;
    right = nullptr;
}

// Constructor of node class
MNode::MNode(string name, TvSeries x, MNode* left, MNode* right)
{
    key = name;
    value = x;
    this->left = left;
    this->right = right;
}

// Class for the map object
class Map {
public:
    MNode* root;
    Map();
    MNode* insert(const string key, TvSeries value, MNode* root);
    void inOrder(MNode* root);
    MNode* find(const string key, MNode* root);
    void findMultipleOccurrences(const string key, vector<TvSeries>& shows, MNode* root);
    MNode* randomNode(MNode* root);
    void randomNodeHelper(MNode* root, MNode*& temp, int random, int& count);
    TvSeries operator[](const string key);
    ~Map();
};

// Destructor of the map class
Map::~Map()
{
    if (root)
        delete root;
}

// Default constructor for the map class
Map::Map()
{
    root = nullptr;
}

// Recursive function to insert a Tv series into the map
MNode* Map::insert(const string key, TvSeries value, MNode* root)
{
    // If the root is not existent
    if (root == nullptr)
        // Create a new node and place it
        return new MNode(key, value);
    // If the name of the series is greater than the root
    if (key.compare(root->key) > 0)
        // Check right of root
        root->right = insert(key, value, root->right);
    else
        // Check left of root
        root->left = insert(key, value, root->left);
    return root;
}

// Recursive function to print all info on the map
void Map::inOrder(MNode* root)
{
    if (!root)
        return;
    inOrder(root->left);
    root->value.Print();
    inOrder(root->right);
}

// Recursive function to find a given key inside the map
MNode* Map::find(const string key, MNode* root)
{
    // if found or end of map return null
    if (!root || key.compare(root->key) == 0)
        return root;
    // if key is greater than the key of the root
    if (key.compare(root->key) > 0)
        // check right of root
        return find(key, root->right);
    else
        // check left of root
        return find(key, root->left);
}

// overload operator that would find a key and return the value
TvSeries Map::operator[](const string key)
{
    MNode* temp = find(key, root);
    if (temp)
        return temp->value;
    return TvSeries();
}

// Recursive function that would return 
// a vector with multiple keys that contain the given key
void Map::findMultipleOccurrences(const string key, vector<TvSeries>& shows, MNode* root)
{
    if (!root)
        return;
    findMultipleOccurrences(key, shows, root->left);
    // if the key is inside the map key push the value on the vector
    if (root->key.find(key) != string::npos)
        shows.push_back(root->value);
    findMultipleOccurrences(key, shows, root->right);
}

// Function to find a random node in the map
MNode* Map::randomNode(MNode* root)
{
    int count = 0;
    srand(time(0));
    // 146350 == number of tv series
    int random = std::rand() % (146350 + 1 - 1) + 1;
    MNode* temp = nullptr;
    randomNodeHelper(root, temp, random, count);
    return temp;
}

// inorder check of the tree until we find the desire random node
void Map::randomNodeHelper(MNode* root, MNode*& temp, int random, int& count)
{
    if (!root)
        return;
    randomNodeHelper(root->left, temp, random, count);
    count++;
    if (count == random)
    {
        temp = root;
        return;
    }
    randomNodeHelper(root->right, temp, random, count);
}

class BST
{
public:
    struct Node
    {
        TvSeries value;
        Node* left;
        Node* right;
        int height;
        Node(TvSeries x) : value(x), height(1), left(nullptr), right(nullptr) {}
    };
    //Tree functions
    BST() : root(nullptr) {}
    ~BST();
    Node* insert(Node* root, TvSeries value);
    void inorderTraversal(Node* root);
    void levelorderTraversal(Node* root);
    void deleteTree(Node* root);
    //Search functions
    Node* search(Node* root, string name);
    Node* searchRandom(Node* root);
    void find(Node* root, string name, vector<TvSeries>&);
    //AVL functions
    void updateHeight(Node* root);
    int balanceFactor(Node* root);
    Node* balance(Node* root, int balanceFactor);
    Node* rotateLeft(Node* root);
    Node* rotateRight(Node* root);
    //Utility functions
    int getHeight(Node* root);
    Node* getRoot();
    void setRoot(BST::Node* root_);
private:
    Node* root;
};

BST::~BST()
{
    deleteTree(root);
}

void BST::deleteTree(Node* root)
{
    if (root == nullptr)
        return;
    else
    {
        //nodes are stored on the heap
        //uses a postorder traversal to visit each node, then deletes
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

//calling updateHeight and balance outside of insertion would take O(n) time; requires full traversal
//calling inside insertion takes O(logn) time; only checks nodes in path of recursive calls 
BST::Node* BST::insert(Node* root, TvSeries value)
{
    //base case, reached c
    if (root == nullptr)
    {
        root = new Node(value);
        return new Node(value);
    }
    //recurisvely move down desired path depending on comparison of keys
    else if (value.name < root->value.name)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);
    //after traveling down a path and inserting a node, when the base case is reached we travel back up and check balance factors
    //new node was added, so update the height of the current node in the path
    updateHeight(root);
    //before returning and moving up to the next level, check the ancestor of the inserted node for imbalance 
    root = balance(root, balanceFactor(root));
    return root;
}

int BST::getHeight(Node* root)
{
    if (root == nullptr)
        return 0;
    else
        return root->height;
}

void BST::updateHeight(Node* root)
{
    int lHeight = getHeight(root->left);
    int rHeight = getHeight(root->right);
    //height of the root node is the height of the + 1
    root->height = max(lHeight, rHeight) + 1;
}

int BST::balanceFactor(Node* root)
{
    if (root == nullptr)
        return 0;
    else
        //balance factor = height of left subtree - height of right subtree
        //getHeight checks to see if root->left or root->right are nullptrs
        return getHeight(root->left) - getHeight(root->right);
}

BST::Node* BST::balance(Node* root, int bf)
{
    //type of rotation used is based on balance factor of parent and child
    if (bf == 2)
    {
        if (balanceFactor(root->left) == 1)
            //left left imbalance, fix with right rotation
            root = rotateRight(root);
        else
        {
            //BF of left child is -1; left right imbalance, fix with left right rotation
            //first perform left rotation on the left child, then right rotation on the root of the subtree (get new root after rotating)
            root->left = rotateLeft(root->left);
            root = rotateRight(root);
        }
    }
    else if (bf == -2)
    {
        if (balanceFactor(root->right) == -1)
            //right right imbalance, fix with left rotation
            root = rotateLeft(root);
        else
        {
            //BF of right child is +1; right left imbalance, fix with right left rotation
            //first perform right rotation on the right child, then left roation on the root
            root->right = rotateRight(root->right);
            root = rotateLeft(root);
        }
    }
    //root of tree passed in may change depending on the pivot, so return the new root
    return root;
}

BST::Node* BST::rotateLeft(Node* root)
{
    //A is the root of the subtree, B is its child, and C is its possible grandchild 
    //C is the left subtree of B
    Node* A = root;
    Node* B = A->right;
    Node* C = B->left;
    B->left = A;
    A->right = C;
    //A and B positions pivoted by 1, so update height 
    updateHeight(A);
    updateHeight(B);
    //after rotating, B becomes the new root of the subtree
    return B;
}

BST::Node* BST::rotateRight(Node* root)
{
    //when rotating parent (A) with child (B), need to account for right subtree (C) of the child
    //when B becomes new root, subtree C is inherited by A to prevent overlap
    Node* A = root;
    Node* B = A->left;
    Node* C = B->right;
    B->right = A;
    A->left = C;
    updateHeight(A);
    updateHeight(B);
    return B;
}

void BST::inorderTraversal(Node* root)
{
    if (root == nullptr)
        return;
    else
    {
        inorderTraversal(root->left);
        root->value.Print();
        inorderTraversal(root->right);
    }
}

void BST::levelorderTraversal(Node* root)
{
    if (root == nullptr)
        return;
    else
    {
        queue<Node*> q;
        q.push(root);
        while (!q.empty())
        {
            Node* current = q.front();
            current->value.Print();
            q.pop();
            if (current->left != nullptr)
                q.push(current->left);
            if (current->right != nullptr)
                q.push(current->right);
        }
    }
}

BST::Node* BST::search(Node* root, string name)
{
    //bases cases; stop searching down path when what is searched for is found or it does not exist
    //nullptr returned when the desired key does not exist in the tree
    if (root == nullptr || root->value.name == name)
        return root;
    else if (name < root->value.name)
        return search(root->left, name);
    else
        return search(root->right, name);
}

void BST::find(Node* root, string name, vector<TvSeries>& container)
{
    //inorder traversal checks every node in the tree
    if (root == nullptr)
        return;
    else
    {
        //if a node contains part of what is being found, add it to the container 
        find(root->left, name, container);
        if (root->value.name.find(name) != string::npos)
            container.push_back(root->value);
        find(root->right, name, container);
    }
}

BST::Node* BST::searchRandom(Node* root)
{
    if (root == nullptr)
        return nullptr;
    //randomly generates a number between 0 and the height of the tree
    srand(time(0));
    int levels = std::rand() % getHeight(root);
    Node* current = root;
    vector<int> path;

    //fills the vector with 1's and 0's
    for (int i = 0; i < levels; i++)
    {
        int direction = std::rand() % 2;
        path.push_back(direction);
    }

    //vector represents the path to traverse, with 0 = left and 1 = right
    for (int i = 0; i < levels; i++)
    {
        Node* temp = current;
        if (path[i] == 0)
            current = current->left;
        else
            current = current->right;
        //subtree not always garaunteed to be max height, so stop in case of nullptr
        if (current == nullptr)
            return temp;
    }
    //return the node retrieved from the path
    return current;
}

BST::Node* BST::getRoot()
{
    return root;
}

void BST::setRoot(BST::Node* root_)
{
    root = root_;
}

// Method to read a file and save it in the map
void ReadFile(Map& map, BST& avl, int option)
{
    string line;
    string tconst, name, sYear, eYear, genres;
    MNode* root = map.root;
    BST::Node* rootTree = avl.getRoot();
    ifstream file("shows.txt");
    int i = 0;
    int quarter = 146350 / 10;
    int math = 0;
    int percentage = 0;
    if (file.is_open())
    {
        cout << "Loading the data set..." << endl;
        // read the first line
        getline(file, line);
        // while the file contains tabs
        while (getline(file, line, '\t'))
        {
            // print the loading screen
            if (i == math)
            {
                cout << "Loading...[||||||||" << percentage << "%|||||||]" << endl;
                percentage += 10;
                math += quarter;
            }
            // save the contents of the file in variables
            tconst = line;
            getline(file, line, '\t');
            name = line;
            getline(file, line, '\t');
            sYear = line;
            getline(file, line, '\t');
            eYear = line;
            getline(file, line);
            genres = line;
            // create the objects
            TvSeries test(tconst, name, sYear, eYear, genres);
            if (option == 1)
                // insert the objects into the map
                root = map.insert(name, test, root);
            else
                // insert the objects into the tree
                rootTree = avl.insert(rootTree, test);
            i++;
        }
    }
    file.close();
    if (option == 1)
        map.root = root;
    else
        avl.setRoot(rootTree);
    cout << "Loading 100%..." << endl << "Loading completed!" << endl;
}

// Method to access the IMDB website
void visitWebsite(MNode* temp, BST::Node* tempTree, int option)
{
    string webpage = "https://www.imdb.com/title/";
    // if the user chose a map
    if (option == 1)
        webpage += temp->value.tconst;
    // if the user chose a tree
    else
        webpage += tempTree->value.tconst;
    // if the user is using windows os
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    ShellExecuteA(NULL, ("open"), webpage.c_str(), NULL, NULL, SW_SHOWNORMAL);
    // if the user is using mac os
#elif __APPLE__
    string mac = "open " + webpage;
    system(mac.c_str());
#endif
}

int main()
{
    int option = 0;
    int input = 0;
    int choice;
    double math;
    bool available;
    bool mapLoaded = false;
    bool avlLoaded = false;
    bool loadingDone = false;
    string structure = "";
    MNode* root = nullptr;
    BST::Node* treeRoot = nullptr;
    string show;
    vector<TvSeries> shows;
    Map map;
    BST avl;
    MNode* temp = nullptr;
    BST::Node* tempTree = nullptr;
    cout << "---Welcome to BingeHacker v1.0---" << endl;
    cout << "---This program contains information on television programs---" << endl;
    cout << "---There are over 140,000 shows stored from IDMb---" << endl;
    while (option != 3)
    {
        // Main menu
        cout << "Please select one of the following options:" << endl;
        cout << "1. Save the data of the shows using a Map Structure." << endl;
        cout << "2. Save the data of the shows using a AVL tree Structure." << endl;
        cout << "3. Exit the program." << endl;
        cin >> option;
        input = 0;
        // While the input is not valid
        while (!cin || option < 1 || option > 3)
        {
            cin.clear();
            cout << "Please select a valid option." << endl;
            std::cin.ignore(256, '\n');
            cin >> option;
        }
        // if the user wants to exit the program
        if (option == 3)
        {
            cout << "Thanks for using the program!" << endl;
            return 0;
        }
        else
        {
            // timer
            auto start = high_resolution_clock::now();
            // read the file
            if (option == 1)
                structure = "map";
            else
                structure = "AVL Tree";
            if (!mapLoaded && option == 1)
            {
                ReadFile(map, avl, option);
                mapLoaded = true;
                loadingDone = true;
            }
            else if (!avlLoaded && option == 2)
            {
                ReadFile(map, avl, option);
                avlLoaded = true;
                loadingDone = true;
            }
            else if ((mapLoaded && option == 1) || (avlLoaded && option == 2))
                cout << "Data already loaded on the " << structure << "." << endl;
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);
            if (loadingDone && ((mapLoaded && option == 1) || (avlLoaded && option == 2)))
            {
                math = ((double)duration.count()) / 1000;
                cout << "Time taken to add save all shows into the " << structure;
                cout << ": " << math << " seconds" << endl;
                loadingDone = false;
            }
            while (input != 4 && input != 5)
            {
                // reset all variables
                input = 0;
                available = true;
                choice = 0;
                temp = nullptr;
                tempTree = nullptr;
                math = 0;
                shows.clear();
                // menu
                cout << "--------------------------------------------" << endl;
                cout << "Please select one of the following options:" << endl;
                cout << "1. Search for a show by name." << endl;
                cout << "2. Search for multiple shows by a keyword." << endl;
                cout << "3. Find a random show." << endl;
                cout << "4. Change the data structure used." << endl;
                cout << "5. Exit the program." << endl;
                cin >> input;
                // check for correct input
                while (!cin || input < 1 || input > 5)
                {
                    cin.clear();
                    cout << "Please select a valid option." << endl;
                    std::cin.ignore(256, '\n');
                    cin >> input;
                }
                // if the user wants to exit the program
                if (input == 5)
                {
                    cout << "Thanks for using the program!" << endl;
                    return 0;
                }
                // If the user wants to change the structure used
                else if (input == 4)
                    break;
                // if the user decides to look for a show by name
                else if (input == 1)
                {
                    cout << "--------------------------------------------------" << endl;
                    cout << "The names are case-sensitive" << endl;
                    cout << "Write the name of the show you would like to look for: ";
                    cin.ignore();
                    // get the name of the show
                    getline(cin, show);
                    // if the name is smaller/greater than the smallest/greater name on the map
                    if (show.size() < 1 || show.size() > 136)
                    {
                        // the show is not in the map
                        cout << "Show not available" << endl;
                        available = false;
                    }
                    else
                    {
                        // timer
                        auto start1 = high_resolution_clock::now();
                        // find the show
                        if (option == 1)
                            temp = map.find(show, map.root);
                        else
                            tempTree = avl.search(avl.getRoot(), show);
                        auto stop1 = high_resolution_clock::now();
                        auto duration1 = duration_cast<microseconds>(stop1 - start1);
                        math = ((double)duration1.count()) / 1000000;
                        cout << "Time taken to find the show in the " << structure;
                        cout << ": " << setprecision(7) << fixed << math << " seconds" << endl;
                        cout << "--------------------------------------------" << endl;
                        // if the show is on the map, print it
                        if (option == 1 && temp)
                            temp->value.Print();
                        // if not print error
                        else if (option == 1 && !temp)
                        {
                            cout << "Show not available" << endl;
                            available = false;
                        }
                        // if show is on the tree print it
                        else if (option != 1 && tempTree)
                            tempTree->value.Print();
                        // if not print error
                        else if (option != 1 && !tempTree)
                        {
                            cout << "Show not available" << endl;
                            available = false;
                        }
                    }
                    // if the show is on the map
                    if (available)
                    {
                        // menu
                        cout << "Would you like to go to the IMDB website for the show?" << endl;
                        cout << "1. Yes" << endl;
                        cout << "2. No" << endl;
                        cin >> choice;
                        // while choice is not valid
                        while (!cin || choice < 1 || choice > 2)
                        {
                            cin.clear();
                            cout << "Please select a valid option." << endl;
                            std::cin.ignore(256, '\n');
                            cin >> choice;
                        }
                        // if they want to go to the webpage
                        if (choice == 1)
                            visitWebsite(temp, tempTree, option);
                    }
                }
                else if (input == 2)
                {
                    cout << "--------------------------------------------" << endl;
                    cout << "The names are case-sensitive" << endl;
                    cout << "Write the key that you would like to look for: ";
                    cin.ignore();
                    // get the key
                    getline(cin, show);
                    // if the ket is smaller/greater than the smallest/greater name on the map
                    if (show.size() < 1 || show.size() > 136)
                        // the key does not belongs to any show
                        cout << "No shows with given key" << endl;
                    else
                    {
                        // timer
                        auto start2 = high_resolution_clock::now();
                        // find all shows
                        if (option == 1)
                            map.findMultipleOccurrences(show, shows, map.root);
                        else
                            avl.find(avl.getRoot(), show, shows);
                        cout << "--------------------------------------------" << endl;
                        // if the vector is empty
                        if (shows.size() == 0)
                            cout << "No shows with given key" << endl;
                        else
                        {
                            // print all shows
                            for (unsigned int i = 0; i < shows.size(); i++)
                            {
                                shows[i].Print();
                            }
                        }
                        auto stop2 = high_resolution_clock::now();
                        auto duration2 = duration_cast<milliseconds>(stop2 - start2);
                        math = ((double)duration2.count()) / 1000;
                        cout << "Time taken to find all the shows in the " << structure;
                        cout << ": " << math << " seconds" << endl;
                    }
                }
                else if (input == 3)
                {
                    cout << "--------------------------------------------" << endl;
                    // timer
                    auto start3 = high_resolution_clock::now();
                    // find random node on map
                    if (option == 1)
                    {
                        temp = map.randomNode(map.root);
                        temp->value.Print();
                    }
                    // find random node on tree
                    else
                    {
                        tempTree = avl.searchRandom(avl.getRoot());
                        tempTree->value.Print();
                    }
                    auto stop3 = high_resolution_clock::now();
                    auto duration3 = duration_cast<milliseconds>(stop3 - start3);
                    math = ((double)duration3.count()) / 1000;
                    cout << "Time taken to find the random show in the " << structure;
                    cout << ": " << math << " seconds" << endl;
                    // menu
                    cout << "Would you like to go to the IMDB website for the show?" << endl;
                    cout << "1. Yes" << endl;
                    cout << "2. No" << endl;
                    cin >> choice;
                    // while the choice is not valid
                    while (!cin || choice < 1 || choice > 2)
                    {
                        cin.clear();
                        cout << "Please select a valid option." << endl;
                        std::cin.ignore(256, '\n');
                        cin >> choice;
                    }
                    // if the user wants to go to the webpage
                    if (choice == 1)
                        visitWebsite(temp, tempTree, option);
                }
            }
        }
    }
}

