#include "BinaryTree.hpp"

int main()
{
    BinaryTree rndm_tree;
    rndm_tree.fillRandomData(10UL);
    cout << "Binary tree filled randomly: " << endl;
    rndm_tree.show();
    rndm_tree.printCountOfNodes();
    rndm_tree.printBranchesOfCertainNode(3);
    rndm_tree.printValueByNode(2);
    rndm_tree.printNodeByValue("1");
    rndm_tree.searchMin();
    rndm_tree.searchMax();
    cout << endl;

    BinaryTree bin_tree;
    cout << "Customly created binary tree: " << endl;

#ifdef GENERATE_ALL_SYMBOLS
    bin_tree.addNode("U");
    bin_tree.addNode("uU");
    bin_tree.addNode("Z");
    bin_tree.addNode("a");
    bin_tree.addNode("h");
    bin_tree.addNode("E");
    bin_tree.addNode("~");
    bin_tree.addNode("='");
    bin_tree.addNode("i");
#endif

#ifdef GENERATE_ONLY_DIGITS
    bin_tree.addNode("9");
    bin_tree.addNode("1");
    bin_tree.addNode("46");
    bin_tree.addNode("20");
    bin_tree.addNode("68");
    bin_tree.addNode("15");
    bin_tree.addNode("5");
    bin_tree.addNode("0");
    bin_tree.addNode("6");
    bin_tree.addNode("55");
    bin_tree.addNode("95");
#endif

    bin_tree.show();
    bin_tree.printCountOfNodes();
    bin_tree.printBranchesOfCertainNode(2);
    bin_tree.printValueByNode(2);
    bin_tree.printNodeByValue("1");
    bin_tree.searchMin();
    bin_tree.searchMax();

    cout << "Which value you want to delete from binary tree: ";
    string toRemove{};
    std::cin >> toRemove;
    bin_tree.removeNode(toRemove);

    cout << "\nBinary tree after removing " << toRemove << ": " << endl;
    bin_tree.show();

    return EXIT_SUCCESS;
}