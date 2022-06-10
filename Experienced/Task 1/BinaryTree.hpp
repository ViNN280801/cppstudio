#pragma once

#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <memory>

#define __GENERATE__ALL__SYMBOLS__

using std::cout;
using std::endl;
using std::shared_ptr;
using std::string;
using std::vector;

// Deleting allocated memory for __ptr and zeroing out pointer
template <typename T>
inline void clearPtr(T *__ptr)
{
    delete __ptr;
    __ptr = nullptr;
}

class BinaryTree
{
private:
    struct Node
    {
        string value;

        // Points on left root of tree
        shared_ptr<Node> leftRoot;
        // Points on right root of tree
        shared_ptr<Node> rightRoot;

        // Ctors
        explicit Node() : leftRoot(nullptr), rightRoot(nullptr) {}
        explicit Node(const string &__value) : value(__value), leftRoot(nullptr), rightRoot(nullptr) {}

        // Virtual destructor
        virtual ~Node() = default;

        // Returns max depth from two roots
        int max() const
        {
            const int left_depth = leftRoot ? leftRoot->max() : 0;
            const int right_depth = rightRoot ? rightRoot->max() : 0;

            return (left_depth > right_depth ? left_depth : right_depth) + 1;
        }
    };

    // Main node (root of binary tree)
    shared_ptr<Node> root;

    // For multiple use certainNode() method
    static int counter;

protected:
    // Generating random string and returns it
    string generateRandomString(const size_t lenght) const
    {
        /* Hint: You must declare at the top following line:
        #define __GENERATE__ALL__SYMBOLS__ for generate string consisting of all symbols
        or
        #define __GENERATE__ONLY__DIGITS__ for generate string consisting of only digits */

#ifdef __GENERATE__ALL__SYMBOLS__
        static constexpr char symbols[]{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`1234567890-=~!@#$%^&*()_+[]{}\\|/\'\",.<>:; "};
#endif

#ifdef __GENERATE__ONLY__DIGITS__
        static constexpr char onlyDigits[]{"1234567890"};
#endif

        // Declaring variable for store random string inside
        string rndmString{};

        // Generating random string
        for (size_t iter = 0; iter < lenght; iter++)
        {
#ifdef __GENERATE__ALL__SYMBOLS__
            rndmString += symbols[rand() % (sizeof(symbols) - 1)];
#endif

#ifdef __GENERATE__ONLY__DIGITS__
            rndmString += onlyDigits[rand() % (sizeof(onlyDigits) - 1)];

            // To avoid numbers like 03, 045, 00 etc.
            // At first, convert string to int
            // then clear string
            // then convert int to string
            int rndmNum = std::stoi(rndmString);
            rndmString.clear();
            rndmString = std::to_string(rndmNum);
#endif
        }

        return rndmString;
    }

    // Returns count of levels (nodes) of binary tree
    inline unsigned int count(shared_ptr<Node> node) const
    {
        if (node == nullptr)
            return 0U;
        else
            return (1U + count(node->leftRoot) + count(node->rightRoot));
    }

    struct cell_display
    {
        string str;
        bool flag;

        // Ctors
        explicit cell_display() : flag(false) {}
        explicit cell_display(const string &str) : str(str), flag(true) {}
    };

    /* Builds a vector of vectors of cell_display structs
    each vector of cell_display structs represents one row, starting at the root */
    vector<vector<struct cell_display>> getRowDisplay() const
    {
        // Build a vector of vectors of Node pointers
        vector<std::shared_ptr<Node>> travers{};
        vector<vector<std::shared_ptr<Node>>> rows{};

        if (root == nullptr)
            return vector<vector<struct cell_display>>();

        std::shared_ptr<Node> pNode = root;
        const size_t maxDepth = root->max();

        rows.resize(maxDepth);
        size_t depth = 0UL;

        while (true)
        {
            // Max-depth Nodes are always a __node or null
            // This special case blocks deeper traversal
            if (depth == maxDepth - 1)
            {
                rows[depth].push_back(pNode);
                if (depth == 0)
                    break;
                --depth;
                continue;
            }

            // At first go to left child.
            if (travers.size() == depth)
            {
                rows[depth].push_back(pNode);
                travers.push_back(pNode);
                if (pNode != nullptr)
                    pNode = pNode->leftRoot;
                ++depth;
                continue;
            }

            // If child count is odd -> go to right child.
            if (rows[depth + 1UL].size() % 2UL)
            {
                pNode = travers.back();
                if (pNode)
                    pNode = pNode->rightRoot;
                ++depth;
                continue;
            }

            // Exit loop if this is the root
            if (depth == 0)
                break;

            travers.pop_back();
            pNode = travers.back();
            --depth;
        }

        /* Using rows of Node pointers to populate rows of cell_display structs.
        All possible slots in the tree get a cell_display struct,
        so if there is no actual Node at a struct's location,
        its boolean "present" field is set to false.
        The struct also contains a string representation of
        its Node's value, created using a std::stringstream object. */
        vector<vector<struct cell_display>> rowsDisplay{};
        std::stringstream ss{};

        for (const auto &row : rows)
        {
            rowsDisplay.emplace_back();
            for (auto &p : row)
            {
                if (p != nullptr && p->value.size() != 0UL)
                {
                    ss << p->value;
                    rowsDisplay.back().push_back(cell_display(ss.str()));
                    ss = std::stringstream();
                }
                else
                    rowsDisplay.back().push_back(cell_display());
            }
        }

        return rowsDisplay;
    }

    /* Takes the vector of rows of cell_display structs
    generated by get_row_display and formats it into a test representation
    as a vector of strings */
    vector<string> rowFormat(const vector<vector<struct cell_display>> &__rowsDisplay) const
    {
        // First find the maximum value string length and put it in declared variable in follows line
        size_t cellWidth = 0UL;

        for (const auto &rowDisplay : __rowsDisplay)
        {
            for (const auto &a : rowDisplay)
            {
                if (a.flag && a.str.length() > cellWidth)
                    cellWidth = a.str.length();
            }
        }

        if (cellWidth % 2 == 0)
            ++cellWidth;

        // Allows __node nodes to be connected when they are all with size of a single character
        if (cellWidth < 3)
            cellWidth = 3;

        vector<string> formattedRows;
        size_t rowCount = __rowsDisplay.size();
        size_t rowElementCount = 1 << (rowCount - 1);
        size_t leftPad = 0;

        for (size_t r = 0; r < rowCount; ++r)
        {
            const auto &cd_row = __rowsDisplay[rowCount - r - 1UL]; // r reverse-indexes the row
            // "space" will be the number of rows of slashes needed to get
            // from this row to the next.  It is also used to determine other
            // text offsets.
            size_t space = (1UL << r) * (cellWidth + 1UL) / 2UL - 1UL;
            // "row" holds the line of text currently being assembled
            string row{};
            // iterate over each element in this row
            for (size_t c = 0UL; c < rowElementCount; ++c)
            {
                // add padding, more when this is not the leftmost element
                row += string(c ? leftPad * 2UL + 1UL : leftPad, ' ');

                if (cd_row[c].flag)
                {
                    // This position corresponds to an existing Node
                    const string &str = cd_row[c].str;

                    // Try to pad the left and right sides of the value string
                    // with the same number of spaces.  If padding requires an
                    // odd number of spaces, right-sided children get the longer
                    // padding on the right side, while left-sided children
                    // get it on the left side.
                    size_t longPadding = cellWidth - str.length();
                    size_t shortPadding = longPadding / 2UL;

                    longPadding -= shortPadding;
                    row += string(c % 2UL ? shortPadding : longPadding, ' ');
                    row += str;
                    row += string(c % 2UL ? longPadding : shortPadding, ' ');
                }
                else
                    // This position is empty, Nodeless...
                    row += string(cellWidth, ' ');
            }
            // A row of spaced-apart value strings is ready, add it to the result vector
            formattedRows.push_back(row);

            // The root has been added, so this loop is finsished
            if (rowElementCount == 1UL)
                break;

            // Add rows of forward- and back- slash characters, spaced apart
            // to "connect" two rows' Node value strings.
            // The "space" variable counts the number of rows needed here.
            size_t left_space = space + 1UL;
            size_t right_space = space - 1UL;

            for (size_t sr = 0UL; sr < space; ++sr)
            {
                string row{};
                for (size_t c = 0UL; c < rowElementCount; ++c)
                {
                    if (c % 2UL == 0UL)
                    {
                        row += string(c ? left_space * 2UL + 1UL : left_space, ' ');
                        row += cd_row[c].flag ? '/' : ' ';
                        row += string(right_space + 1UL, ' ');
                    }
                    else
                    {
                        row += string(right_space, ' ');
                        row += cd_row[c].flag ? '\\' : ' ';
                    }
                }
                formattedRows.push_back(row);
                ++left_space;
                --right_space;
            }
            leftPad += space + 1UL;
            rowElementCount /= 2UL;
        }

        // Reverse the result, placing the root node at the beginning (top)
        std::reverse(formattedRows.begin(), formattedRows.end());

        return formattedRows;
    }

    /* Trims an equal number of space characters from
    the beginning of each string in the vector.
    At least one string in the vector will end up beginning
    with no space characters. */
    static void trimRows(vector<string> &rows)
    {
        if (!rows.size())
            return;

        auto minSpace = rows.front().length();

        for (const auto &row : rows)
        {
            auto i = row.find_first_not_of(' ');
            if (i == string::npos)
                i = row.length();
            if (i == 0)
                return;
            if (i < minSpace)
                minSpace = i;
        }

        for (auto &row : rows)
        {
            row.erase(0, minSpace);
        }
    }

    // Turns int number to string for splitting on digits for check -st, -nd, -rd and -th postfixes of digits
    string transformNumber(const int &__num) const
    {
        string digits{};
        digits = std::to_string(__num);

        if (digits[digits.size() - 1] == '1')
            digits += "st";
        else if (digits[digits.size() - 1] == '2')
            digits += "nd";
        else if (digits[digits.size() - 1] == '3')
            digits += "rd";
        else
            digits += "th";

        return digits;
    }

    // Adding node to the binary tree
    virtual void addNode(const string &__value, shared_ptr<Node> &__node)
    {
        if (__node == nullptr)
        {
            __node = std::make_shared<Node>(__value);
        }
        else
        {
#ifdef __GENERATE__ONLY__DIGITS__
            if (std::stoi(__value) < std::stoi(__node->value))
#endif
#ifdef __GENERATE__ALL__SYMBOLS__
                if (__value < __node->value)
#endif
                {
                    if (__node->leftRoot != nullptr)
                        addNode(__value, __node->leftRoot);
                    else
                        __node->leftRoot = std::make_shared<Node>(__value);
                }
#ifdef __GENERATE__ONLY__DIGITS__
                else if (std::stoi(__value) >= std::stoi(__node->value))
#endif
#ifdef __GENERATE__ALL__SYMBOLS__
                    else if (__value >= __node->value)
#endif
                    {
                        if (__node->rightRoot != nullptr)
                            addNode(__value, __node->rightRoot);
                        else
                            __node->rightRoot = std::make_shared<Node>(__value);
                    }
        }
    }

    // Returns certain node by node number
    shared_ptr<Node> certainNode(shared_ptr<Node> &__node, const int &__nodeNumber) const
    {
        static shared_ptr<Node> pnode;

        if (__node == nullptr)
            return nullptr;
        else
        {
            counter++;

            if (counter == __nodeNumber)
                pnode = __node;

            certainNode(__node->leftRoot, __nodeNumber);
            certainNode(__node->rightRoot, __nodeNumber);

            return pnode;
        }
    }

    // Returns node if __value exists in this binary tree
    shared_ptr<Node> certainNode(shared_ptr<Node> &__node, const string &__value) const
    {
        static shared_ptr<Node> pnode;

        if (__node == nullptr)
        {
            return nullptr;
        }
        else
        {
            if (__value == __node->value)
                pnode = __node;

            certainNode(__node->leftRoot, __value);
            certainNode(__node->rightRoot, __value);

            return pnode;
        }
    }

    // Returns number of node if __value exists in this binary tree
    unsigned int searchNodeNumberByValue(shared_ptr<Node> &__node, const string &__value) const
    {
        static unsigned int nodeNumber{};

        if (__node == nullptr)
            return 0U;
        else
        {
            counter++;
            if (__value == __node->value)
                nodeNumber = counter;

            searchNodeNumberByValue(__node->leftRoot, __value);
            searchNodeNumberByValue(__node->rightRoot, __value);

            return nodeNumber;
        }
    }

    // Returns count of branches of certain node
    unsigned int branches(shared_ptr<Node> &__node, const int &__nodeNumber) const
    {
        unsigned int countOfBranches{};

        if (counter != 0)
            counter = 0;

        static shared_ptr<Node> pnode = certainNode(__node, __nodeNumber);

        if (pnode->leftRoot != nullptr && pnode->rightRoot != nullptr)
            countOfBranches = 2;
        else if (pnode->leftRoot != nullptr || pnode->rightRoot != nullptr)
            countOfBranches = 1;
        else
            countOfBranches = 0;

        return countOfBranches;
    }

    // Returns minimal node in binary tree (lower left element)
    // Non-recursive function
    shared_ptr<Node> minValue(shared_ptr<Node> &__node) const
    {
        shared_ptr<Node> pnode = __node;

        while (pnode->leftRoot != nullptr)
        {
            pnode = pnode->leftRoot;
        }

        return pnode;
    }

    // Returns maximal element in binary tree (lower right element)
    // Recursive function
    shared_ptr<Node> maxValue(shared_ptr<Node> &__node) const
    {
        // Tree is empty
        if (__node == nullptr)
            return nullptr;
        // Tree is not empty
        else
        {
            if (__node->rightRoot == nullptr)
                return __node;
            else
                return maxValue(__node->rightRoot);
        }
    }

    // Returns previous node by node number
    static shared_ptr<Node> previousNode(shared_ptr<Node> &__node, const int &__nodeNumber)
    {
        static shared_ptr<Node> pprev;

        if (__node == nullptr)
            return nullptr;
        else
        {
            counter++;

            if (counter == (__nodeNumber - 1))
                pprev = __node;

            previousNode(__node->leftRoot, __nodeNumber);
            previousNode(__node->rightRoot, __nodeNumber);

            return pprev;
        }
    }

    // Returns next node
    static shared_ptr<Node> nextNode(shared_ptr<Node> &__node, const int &__nodeNumber)
    {
        static shared_ptr<Node> pnext;

        if (__node == nullptr)
            return nullptr;
        else
        {
            counter++;

            if (counter == (__nodeNumber + 1))
                pnext = __node;

            nextNode(__node->leftRoot, __nodeNumber);
            nextNode(__node->rightRoot, __nodeNumber);

            return pnext;
        }
    }

    // Removes node from binary tree by value
    shared_ptr<Node> removeNodeByValue(shared_ptr<Node> __node, const string &__value)
    {
        // If tree is emplty -> return null
        if (__node == nullptr)
            return nullptr;
        else
        {
#ifdef __GENERATE__ONLY__DIGITS__
            // If node value which we want to delete is smaller than the root's value, then it lies in left subtree
            if (std::stoi(__value) < std::stoi(__node->value))
                __node->leftRoot = removeNodeByValue(__node->leftRoot, __value);
            // If node value which we want to delete is greater than the root's value, then it lies in left subtree
            else if (std::stoi(__value) > std::stoi(__node->value))
                __node->rightRoot = removeNodeByValue(__node->rightRoot, __value);
#endif

#ifdef __GENERATE__ALL__SYMBOLS__
            // If node value which we want to delete is smaller than the root's value, then it lies in left subtree
            if (__value < __node->value)
                __node->leftRoot = removeNodeByValue(__node->leftRoot, __value);
            // If node value which we want to delete is greater than the root's value, then it lies in left subtree
            else if (__value > __node->value)
                __node->rightRoot = removeNodeByValue(__node->rightRoot, __value);
#endif
            // If node value equals __value -> found node which we want to delete
            else
            {
                // Case 1: Node has no child or has only 1 (left) child
                if (__node->rightRoot == nullptr)
                {
                    shared_ptr<Node> ptmp = __node->leftRoot;
                    return ptmp;
                }
                // Case 2: Node has no child or has only 1 (right) child
                else if (__node->leftRoot == nullptr)
                {
                    shared_ptr<Node> ptmp = __node->rightRoot;
                    return ptmp;
                }
                else
                {
                    // Case 3: Node has 2 children
                    // Smallest in the right subtree
                    shared_ptr<Node> ptmp = minValue(__node->rightRoot);
                    // Copy the inorder successor's data to this node
                    __node->value = ptmp->value;
                    // Delete the inorder successor
                    __node->rightRoot = removeNodeByValue(__node->rightRoot, ptmp->value);
                }
            }
        }
        return __node;
    }

public:
    // Zero-argument, default ctor
    explicit BinaryTree() : root(nullptr) {}

    // Ctor with main param (it is also copy ctor)
    explicit BinaryTree(const BinaryTree *&__binary_tree)
    {
        root = __binary_tree->root;
    }

    // Assignment operator
    BinaryTree &operator=(const BinaryTree *&__binary_tree)
    {
        // Checking self-assignment
        if (this == __binary_tree)
        {
            return *this;
        }

        root = __binary_tree->root;

        return *this;
    }

    // Getter for max depth
    int getMaxDepth() const { return root ? root->max() : 0; }

    // Printing binary tree
    void show() const
    {
        const int d = getMaxDepth();

        // Check if tree is empty
        if (d == 0)
        {
            cout << "Tree is empty " << endl;
            return;
        }

        // This tree is not empty, so get a list of node values
        const auto rowDisp = getRowDisplay();

        // Format these into a text representation
        auto formattedRows = rowFormat(rowDisp);

        // Trim excess space characters from the left sides of the text
        trimRows(formattedRows);

        for (const auto &row : formattedRows)
        {
            cout << ' ' << row << endl;
        }
    }

    // Adding node to tree
    virtual void addNode(const string &__value) final
    {
        addNode(__value, root);
    }

    // Filling binary tree with random data
    void fillRandomData(const size_t &__countOfRoots)
    {
        // Using current time as seed for random generator
        srand(time(nullptr));

        // Declaring variable, which will contain different strings
        string rndmString{};

        for (size_t iter = 0; iter < __countOfRoots; iter++)
        {
#ifdef __GENERATE__ALL__SYMBOLS__
            rndmString = generateRandomString(static_cast<size_t>(1 + rand() % 2));
#endif

#ifdef __GENERATE__ONLY__DIGITS__
            rndmString = generateRandomString(static_cast<size_t>(1 + rand() % 2));
#endif
            addNode(rndmString, root);
        }
    }

    // Printing count of nodes
    inline void printCountOfNodes() const
    {
        unsigned int nodes{count(root)};
        cout << "Count of nodes = " << nodes << endl;
    }

    // Printing branches of certain node (keep in mind that the countdown starts from 0)
    inline void printBranchesOfCertainNode(const int &__nodeNumber)
    {
        unsigned int branchesCount{branches(root, __nodeNumber)};

        if (static_cast<unsigned int>(__nodeNumber) == 0 || static_cast<unsigned int>(__nodeNumber) >= count(root))
            branchesCount = 0U;

        cout << "Count of branches on node " << __nodeNumber << " is " << branchesCount << endl;
    }

    // Printing value of certain node. Searching by node number
    void printValueByNode(const int &__nodeNumber)
    {
        if (counter != 0)
            counter = 0;

        string str{};
        shared_ptr<Node> pnode = certainNode(root, __nodeNumber);

        if (__nodeNumber == 0 || static_cast<unsigned int>(__nodeNumber) >= count(root))
            pnode->value = "empty data";

        str = transformNumber(__nodeNumber);
        cout << "Value of " << str << " node is " << pnode->value << endl;
    }

    // Printing node with searching by value
    void printNodeByValue(const string &__value)
    {
        if (counter != 0)
            counter = 0;

        string str{};
        unsigned int nodeNumber = searchNodeNumberByValue(root, __value);

        if (nodeNumber == 0)
            cout << "The binary tree does not contain value " << __value << endl;
        else
        {
            str = transformNumber(nodeNumber);
            cout << "The value \"" << __value << "\" is in " << str << " node " << endl;
        }
    }

    // Printing min value from binary tree
    inline void searchMin()
    {
        shared_ptr<Node> pnode = minValue(root);
        cout << "Min value = " << pnode->value << endl;
    }

    // Printing max value from binary tree
    inline void searchMax()
    {
        shared_ptr<Node> pnode = maxValue(root);
        cout << "Max value = " << pnode->value << endl;
    }

    // Removes element in binary tree by value
    void removeNode(const string &__value)
    {
        if (counter != 0)
            counter = 0;

        if ((root == nullptr) || (root->value.size() == 0UL))
            cout << "There is no value " << __value << endl;
        else
            removeNodeByValue(root, __value);
    }

    // Virtual destructor
    virtual ~BinaryTree() = default;
};

int BinaryTree::counter = 0;