//============================================================================
// Name        : Course List Search	
// Author      : Enrique Zarate
// Version     : 1.0
// Description : Code that opens file and adds all data into data structure.
//============================================================================

#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <sstream>

// #include "CSVparser.hpp"

using namespace std;

//GLOBAL DEFINITIONS

// forward declarations
double strToDouble(string str, char ch);

//Structure for Courses
struct Course {
    string courseID; // unique identifier
    string title;
    string preRequisite1;
    string preRequisite2;
    Course() {

    }
};

// Node Structure for Trees
struct Node {
    Course course;
    Node* left;
    Node* right;

//Default Constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    //initialize with a given course
    Node(Course aCourse) : Node() {
        this->course = aCourse;
    }
};



//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void preOrder(Node* node);
    void postOrder(Node* node);
    Node* removeNode(Node* node, string courseID);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Node* node, Course course);
    void PostOrder();
    void PreOrder();
    void Remove(string courseID);
    Course Search(string courseID);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // FixMe (1): initialize housekeeping variables
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}


/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // FixMe (2): In order root
    // call inOrder fuction and pass root 
    this->inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // FixMe (3): Post order root
    // postOrder root
    this->postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // FixMe (4): Pre order root
    // preOrder root
    this->preOrder(root);
}


void BinarySearchTree::Insert(Node* node, Course course) {
    // FIXME (5) Implement inserting a bid into the tree
    // if root equarl to null ptr
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        this->addNode(root, course);
    }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string courseID) {
    // FIXME (6) Implement removing a course from the tree
    // remove node root courseID
    this->Remove(courseID);

}



/**
 * Search for a Course
 */
Course BinarySearchTree::Search(string courseID) {
    Node* current = root;
    while (current != nullptr) {
        if (current->course.courseID.compare(courseID) == 0) {
            return current->course;
        }
        if (courseID.compare(current->course.courseID) < 0) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    Course course;
    return course;
    
}

/**
 * Add a Course to some node (recursive)
 *
 * @param node Current node in tree
 * @param course Course to be added
 */

void BinarySearchTree::addNode(Node* node, Course course) {
    if (node->course.courseID.compare(course.courseID) > 0) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        else {
            this->addNode(node->left, course);
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            this->addNode(node->right, course);
        }
    }
}



void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->course.courseID << ": "
            << node->course.title << " | "
            << node->course.preRequisite1 << " | "
            << node->course.preRequisite2 << endl;
        inOrder(node->right);
    }
}

void BinarySearchTree::postOrder(Node* node) {
    if (node != nullptr) {
        postOrder(node->left);
        postOrder(node->right);
        cout << node->course.courseID << ": "
            << node->course.title << " | "
            << node->course.preRequisite1 << " | "
            << node->course.preRequisite2 << endl;
    }

}

void BinarySearchTree::preOrder(Node* node) {
    if (node != nullptr) {
        cout << node->course.courseID << ": "
            << node->course.title << " | "
            << node->course.preRequisite1 << " | "
            << node->course.preRequisite2 << endl;
        preOrder(node->left);
        preOrder(node->right);
    }
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the course information to the console (std::out)
 *
 * @param course struct containing the course info
 */
void displayCourse(Course course) {
    cout << course.courseID << ": " << course.title << " | " << course.preRequisite1 << " | "
        << course.preRequisite2 << endl;
    return;
}

void loadCourses(string courseID, string title, string pr1, string pr2, BinarySearchTree* bst) {
    // Create a data structure and add to the collection of bids
    
    Course course;
    course.courseID = courseID;
    course.title = title;
    course.preRequisite1= pr1 ;
    course.preRequisite2 = pr2 ;
    cout << course.courseID << " " << course.title << " " << course.preRequisite1 << " " << course.preRequisite2 << endl;
    Node* node = nullptr;
    bst->Insert(node, course);
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}


int main() {
    int userInput;
    userInput = -1;
    
    // Define a binary search tree to hold all courses
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;

    while (userInput != 9) {
        cout << "Welcome to the course planner." << endl;
        cout << "What would you like to do?" << endl;
        cout << endl;
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course" << endl;
        cout << "9. Exit" << endl;
        cin >> userInput;

        switch (userInput) {

        case 1: 
                {ifstream courseFile;
                courseFile.open("ABCU_Advising_Program_Input.txt");
                string nextline;
                string id;
                string title;
                string pr1;
                string pr2;
                while (getline(courseFile, nextline)) {
                    stringstream line;
                    line << nextline;
                    getline(line, id, ',');
                    getline(line, title, ',');
                    getline(line, pr1, ',');
                    getline(line, pr2, ',');
                    //cout << id << " " << title << " " << pr1 << " " << pr2 << endl;
                    loadCourses(id, title, pr1, pr2, bst);
                }
                courseFile.close();
                break;
            }
        case 2:
            bst->InOrder();
            break;
        case 3:
            string userCourseSearch;
            cout << "What course are you looking for details on?" << endl;
            cout << "Please enter the course ID:";
            cin >> userCourseSearch;
            int i;
            for (i = 0; i < userCourseSearch.length(); i++) {
                if (isalpha(userCourseSearch[i])) {
                    userCourseSearch[i] = toupper(userCourseSearch[i]);
                }
            }
            course = bst->Search(userCourseSearch);

            if (!course.courseID.empty()) {
                cout << endl;
                displayCourse(course);
                cout << endl;
            }
            else {
                cout << "Course ID " << userCourseSearch << " not found." << endl;
            }
        }
    }

}