#include "BinaryTree.hpp"

int BinaryTree::counter = 0;

string BinaryTree::generateRandomString(const size_t &length) const
{
#ifdef GENERATE_ALL_SYMBOLS
    static constexpr char symbols[]{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`1234567890-=~!@#$%^&*()_+[]{}\\|/\'\",.<>:; "};
#endif

#ifdef GENERATE_ONLY_DIGITS
    static constexpr char onlyDigits[]{"1234567890"};
#endif
    // Declaring variable for store random string inside
    string rndmString{""};
    // Generating random string
    for (size_t i{0UL}; i < length; i++)
    {
#ifdef GENERATE_ALL_SYMBOLS
        rndmString += symbols[rand() % (sizeof symbols - 1)];
#endif

#ifdef GENERATE_ONLY_DIGITS
        rndmString += onlyDigits[rand() % (sizeof onlyDigits - 1)];

        // To avoid numbers like 03, 045, 00 etc.
        // At first, convert string to int
        // then clear string
        // then convert int to string
        int rndmNum{std::stoi(rndmString)};
        rndmString.clear();
        rndmString = std::to_string(rndmNum);
#endif
    }
    return rndmString;
}

vector<vector<struct BinaryTree::cell_display>> BinaryTree::getRowDisplay(void) const noexcept
{
    // Build a vector of vectors of Node pointers
    vector<shared_ptr<Node>> travers{};
    vector<vector<shared_ptr<Node>>> rows{};

    if (root == nullptr)
        return vector<vector<struct cell_display>>();

    shared_ptr<Node> pNode(root);
    const size_t maxDepth{root->max()};

    rows.resize(maxDepth);
    size_t depth{0UL};

    while (true)
    {
        // Max-depth Nodes are always a node or null
        // This special case blocks deeper traversal
        if (depth == maxDepth - 1)
        {
            rows.at(depth).push_back(pNode);
            if (depth == 0)
                break;
            --depth;
            continue;
        }

        // At first go to left child.
        if (travers.size() == depth)
        {
            rows.at(depth).push_back(pNode);
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
        if (depth == 0UL)
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
        for (const auto &p : row)
        {
            if ((p not_eq nullptr) and (p->value.size() not_eq 0UL))
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

vector<string> BinaryTree::rowFormat(const vector<vector<struct cell_display>> &rowsDisplay) const
{
    // First find the maximum value string length and put it in declared variable in follows line
    size_t cellWidth{0UL};

    for (const auto &rowDisplay : rowsDisplay)
    {
        for (const auto &a : rowDisplay)
        {
            if (a.flag and a.str.length() > cellWidth)
                cellWidth = a.str.length();
        }
    }

    if (cellWidth % 2 == 0)
        ++cellWidth;

    // Allows node nodes to be connected when they are all with size of a single character
    if (cellWidth < 3)
        cellWidth = 3;

    vector<string> formattedRows;
    size_t rowCount{rowsDisplay.size()};
    size_t rowElementCount{1UL << (rowCount - 1UL)};
    size_t leftPad{0UL};

    for (size_t r{0UL}; r < rowCount; ++r)
    {
        // r reverse-indexes the row
        const auto &cd_row{rowsDisplay.at(rowCount - r - 1UL)};
        // "space" will be the number of rows of slashes needed to get
        // from this row to the next.  It is also used to determine other
        // text offsets.
        size_t space{(1UL << r) * (cellWidth + 1UL) / 2UL - 1UL};
        // "row" holds the line of text currently being assembled
        string row{""};
        // iterate over each element in this row
        for (size_t c{0UL}; c < rowElementCount; ++c)
        {
            // add padding, more when this is not the leftmost element
            row += string(c ? leftPad * 2UL + 1UL : leftPad, ' ');

            if (cd_row.at(c).flag)
            {
                // This position corresponds to an existing Node
                const string &str{cd_row.at(c).str};

                // Try to pad the left and right sides of the value string
                // with the same number of spaces.  If padding requires an
                // odd number of spaces, right-sided children get the longer
                // padding on the right side, while left-sided children
                // get it on the left side.
                size_t longPadding{cellWidth - str.length()};
                size_t shortPadding{longPadding / 2UL};

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
        size_t left_space{space + 1UL};
        size_t right_space{space - 1UL};

        for (size_t sr{0UL}; sr < space; ++sr)
        {
            string row{};
            for (size_t c{0UL}; c < rowElementCount; ++c)
            {
                if (c % 2UL == 0UL)
                {
                    row += string(c ? left_space * 2UL + 1UL : left_space, ' ');
                    row += cd_row.at(c).flag ? '/' : ' ';
                    row += string(right_space + 1UL, ' ');
                }
                else
                {
                    row += string(right_space, ' ');
                    row += cd_row.at(c).flag ? '\\' : ' ';
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

void BinaryTree::trimRows(vector<string> &rows)
{
    if (not rows.size())
        return;

    size_t minSpace{rows.front().length()};

    for (const auto &row : rows)
    {
        auto i{row.find_first_not_of(' ')};
        if (i == string::npos)
            i = row.length();

        if (i == 0)
            return;

        if (i < minSpace)
            minSpace = i;
    }

    for (auto &row : rows)
    {
        row.erase(0UL, minSpace);
    }
}

string BinaryTree::transformNumber(const int &num) const noexcept
{
    string digits{std::to_string(num)};

    if (digits.at(digits.size() - 1) == '1')
        digits += "st";
    else if (digits.at(digits.size() - 1) == '2')
        digits += "nd";
    else if (digits.at(digits.size() - 1) == '3')
        digits += "rd";
    else
        digits += "th";

    return digits;
}

void BinaryTree::addNode(const string &value, shared_ptr<Node> &node)
{
    if (node == nullptr)
        node = std::make_shared<Node>(value);
    else
    {
#ifdef GENERATE_ONLY_DIGITS
        if (std::stoi(value) < std::stoi(node->value))
#endif
#ifdef GENERATE_ALL_SYMBOLS
            if (value < node->value)
#endif
            {
                if (node->leftRoot not_eq nullptr)
                    addNode(value, node->leftRoot);
                else
                    node->leftRoot = std::make_shared<Node>(value);
            }
#ifdef GENERATE_ONLY_DIGITS
            else if (std::stoi(value) >= std::stoi(node->value))
#endif
#ifdef GENERATE_ALL_SYMBOLS
                else if (value >= node->value)
#endif
                {
                    if (node->rightRoot not_eq nullptr)
                        addNode(value, node->rightRoot);
                    else
                        node->rightRoot = std::make_shared<Node>(value);
                }
    }
}

shared_ptr<BinaryTree::Node> BinaryTree::certainNode(shared_ptr<Node> &node, const int &nodeNumber) const
{
    static shared_ptr<Node> pnode;

    if (node == nullptr)
        return nullptr;
    else
    {
        counter++;

        if (counter == nodeNumber)
            pnode = node;

        certainNode(node->leftRoot, nodeNumber);
        certainNode(node->rightRoot, nodeNumber);

        return pnode;
    }
}

shared_ptr<BinaryTree::Node> BinaryTree::certainNode(shared_ptr<Node> &node, const string &value) const
{
    static shared_ptr<Node> pnode;

    if (node == nullptr)
        return nullptr;
    else
    {
        if (value == node->value)
            pnode = node;

        certainNode(node->leftRoot, value);
        certainNode(node->rightRoot, value);

        return pnode;
    }
}

uint BinaryTree::searchNodeNumberByValue(shared_ptr<Node> &node, const string &value) const
{
    static uint nodeNumber{0U};

    if (node == nullptr)
        return 0U;
    else
    {
        counter++;
        if (value == node->value)
            nodeNumber = counter;

        searchNodeNumberByValue(node->leftRoot, value);
        searchNodeNumberByValue(node->rightRoot, value);

        return nodeNumber;
    }
}

uint BinaryTree::branches(shared_ptr<Node> &node, const int &nodeNumber) const
{
    uint countOfBranches{0U};

    if (counter not_eq 0)
        counter = 0;

    static shared_ptr<Node> pnode{certainNode(node, nodeNumber)};

    if ((pnode->leftRoot not_eq nullptr) and (pnode->rightRoot not_eq nullptr))
        countOfBranches = 2U;
    else if ((pnode->leftRoot not_eq nullptr) or (pnode->rightRoot not_eq nullptr))
        countOfBranches = 1U;
    else
        countOfBranches = 0U;

    return countOfBranches;
}

shared_ptr<BinaryTree::Node> BinaryTree::minValue(shared_ptr<Node> &node) const
{
    shared_ptr<Node> pnode{node};

    while (pnode->leftRoot not_eq nullptr)
    {
        pnode = pnode->leftRoot;
    }

    return pnode;
}

shared_ptr<BinaryTree::Node> BinaryTree::maxValue(shared_ptr<Node> &node) const
{
    // Tree is empty
    if (node == nullptr)
        return nullptr;
    // Tree is not empty
    else
    {
        if (node->rightRoot == nullptr)
            return node;
        else
            return maxValue(node->rightRoot);
    }
}

shared_ptr<BinaryTree::Node> BinaryTree::previousNode(shared_ptr<Node> &node, const int &nodeNumber)
{
    static shared_ptr<Node> pprev;

    if (node == nullptr)
        return nullptr;
    else
    {
        counter++;

        if (counter == (nodeNumber - 1))
            pprev = node;

        previousNode(node->leftRoot, nodeNumber);
        previousNode(node->rightRoot, nodeNumber);

        return pprev;
    }
}

shared_ptr<BinaryTree::Node> BinaryTree::nextNode(shared_ptr<Node> &node, const int &nodeNumber)
{
    static shared_ptr<Node> pnext;

    if (node == nullptr)
        return nullptr;
    else
    {
        counter++;

        if (counter == (nodeNumber + 1))
            pnext = node;

        nextNode(node->leftRoot, nodeNumber);
        nextNode(node->rightRoot, nodeNumber);

        return pnext;
    }
}

shared_ptr<BinaryTree::Node> BinaryTree::removeNodeByValue(shared_ptr<Node> node, const string &value)
{
    // If tree is emplty -> return null
    if (node == nullptr)
        return nullptr;
    else
    {
#ifdef GENERATE_ONLY_DIGITS
        // If node value which we want to delete is smaller than the root's value, then it lies in left subtree
        if (std::stoi(value) < std::stoi(node->value))
            node->leftRoot = removeNodeByValue(node->leftRoot, value);
        // If node value which we want to delete is greater than the root's value, then it lies in left subtree
        else if (std::stoi(value) > std::stoi(node->value))
            node->rightRoot = removeNodeByValue(node->rightRoot, value);
#endif

#ifdef GENERATE_ALL_SYMBOLS
        // If node value which we want to delete is smaller than the root's value, then it lies in left subtree
        if (value < node->value)
            node->leftRoot = removeNodeByValue(node->leftRoot, value);
        // If node value which we want to delete is greater than the root's value, then it lies in left subtree
        else if (value > node->value)
            node->rightRoot = removeNodeByValue(node->rightRoot, value);
#endif
        // If node value equals value -> found node which we want to delete
        else
        {
            // Case 1: Node has no child or has only 1 (left) child
            if (node->rightRoot == nullptr)
            {
                shared_ptr<Node> ptmp{node->leftRoot};
                return ptmp;
            }
            // Case 2: Node has no child or has only 1 (right) child
            else if (node->leftRoot == nullptr)
            {
                shared_ptr<Node> ptmp{node->rightRoot};
                return ptmp;
            }
            else
            {
                // Case 3: Node has 2 children
                // Smallest in the right subtree
                shared_ptr<Node> ptmp{minValue(node->rightRoot)};
                // Copy the inorder successor's data to this node
                node->value = ptmp->value;
                // Delete the inorder successor
                node->rightRoot = removeNodeByValue(node->rightRoot, ptmp->value);
            }
        }
    }
    return node;
}

BinaryTree &BinaryTree::operator=(const BinaryTree *&binary_tree)
{
    // Checking self-assignment
    if (this == binary_tree)
        return *this;

    root = binary_tree->root;

    return *this;
}

void BinaryTree::show(void) const
{
    const size_t d{getMaxDepth()};

    // Check if tree is empty
    if (d == 0)
    {
        cout << "Tree is empty " << endl;
        return;
    }

    // This tree is not empty, so get a list of node values
    const auto rowDisp{getRowDisplay()};

    // Format these into a text representation
    auto formattedRows{rowFormat(rowDisp)};

    // Trim excess space characters from the left sides of the text
    trimRows(formattedRows);

    for (const auto &row : formattedRows)
    {
        cout << ' ' << row << endl;
    }
}

void BinaryTree::fillRandomData(const size_t &countOfRoots)
{
    // Using current time as seed for random generator
    srand(time(nullptr));

    // Declaring variable, which will contain different strings
    string rndmString{""};

    for (size_t i{0UL}; i < countOfRoots; i++)
    {
#ifdef GENERATE_ALL_SYMBOLS
        rndmString = generateRandomString(static_cast<size_t>(1 + rand() % 2));
#endif

#ifdef GENERATE_ONLY_DIGITS
        rndmString = generateRandomString(static_cast<size_t>(1 + rand() % 2));
#endif
        addNode(rndmString, root);
    }
}

void BinaryTree::printCountOfNodes() const
{
    uint nodes{count(root)};
    cout << "Count of nodes = " << nodes << endl;
}

void BinaryTree::printBranchesOfCertainNode(const int &nodeNumber)
{
    uint branchesCount{branches(root, nodeNumber)};

    if ((static_cast<uint>(nodeNumber) == 0) or (static_cast<uint>(nodeNumber) >= count(root)))
        branchesCount = 0U;

    cout << "Count of branches on node " << nodeNumber << " is " << branchesCount << endl;
}

void BinaryTree::printValueByNode(const int &nodeNumber)
{
    if (counter not_eq 0)
        counter = 0;

    shared_ptr<Node> pnode{certainNode(root, nodeNumber)};
    if ((nodeNumber == 0) or (static_cast<uint>(nodeNumber) >= count(root)))
        pnode->value = "empty data";
    cout << "Value of " << transformNumber(nodeNumber) << " node is " << pnode->value << endl;
}

void BinaryTree::printNodeByValue(const string &value)
{
    if (counter not_eq 0)
        counter = 0;

    uint nodeNumber{searchNodeNumberByValue(root, value)};
    if (nodeNumber == 0)
        cout << "The binary tree does not contain value " << value << endl;
    else
        cout << "The value \"" << value << "\" is in " << transformNumber(nodeNumber) << " node " << endl;
}

void BinaryTree::searchMin(void)
{
    shared_ptr<Node> pnode{minValue(root)};
    cout << "Min value = " << pnode->value << endl;
}

void BinaryTree::searchMax(void)
{
    shared_ptr<Node> pnode = maxValue(root);
    cout << "Max value = " << pnode->value << endl;
}

void BinaryTree::removeNode(const string &value)
{
    if (counter not_eq 0)
        counter = 0;

    if ((root == nullptr) or (root->value.size() == 0UL))
        cout << "There is no value " << value << endl;
    else
        removeNodeByValue(root, value);
}
