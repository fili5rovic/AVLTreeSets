#include <iostream>
#include <queue>
#include <stack>
#include <sstream>

using namespace std;

//<editor-fold desc="Ispisi">
const char topLeftCorner = '\xDA';
const char bottomLeftCorner = '\xC0';
const char topRightCorner = '\xBF';
const char bottomRightCorner = '\xD9';
const char middleLeftCorner = '\xC3';
const char middleRightCorner = '\xB4';
const char horizontalLine = '\xC4';
const char verticalLine = '\xB3';
const char intersection = '\xC5';
const char middleDown = '\xC2';
const char middleUp = '\xC1';


string printline(int n) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += '\xC4';
    }
    return s;
}

string printspace(int n) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += ' ';
    }
    return s;
}

void upperTableHeading(int n, bool closing = true, bool end = true) {
    cout << topLeftCorner << printline(n);
    if (closing) cout << topRightCorner;
    if (end) cout << endl;
}

void lowerTableHeading(int n, bool closing = true, bool end = true) {
    cout << bottomLeftCorner << printline(n);
    if (closing) cout << bottomRightCorner;
    if (end) cout << endl;
}

//</editor-fold>
class Node {
    int key, balance;
    Node *left, *right;
    bool isLeft;
public:
    Node(int key) : key(key), left(nullptr), right(nullptr), isLeft(false), balance(0) {}

    Node *getLeft() const {
        return this->left;
    }

    // Milo's book
    void rightRotation() {
        Node *x = this;
        Node *y = x->getLeft();
        Node *temp = y->getRight();
        y->setRight(x);
        x->setLeft(temp);
    }

    // Milo's book
    void leftRotation() {
        Node *x = this;
        Node *y = x->getRight();
        Node *temp = y->getLeft();
        y->setLeft(x);
        x->setRight(temp);
    }

    int getKey() const {
        return key;
    }

    bool isNodeLeft() const {
        return this->isLeft;
    }

    Node *getRight() const {
        return this->right;
    }

    int getBalance() const {
        return this->balance;
    }

    void setBalance(int b) {
        this->balance = b;
    }

    void setRight(Node *right) {
        this->right = right;
    }

    void setLeft(Node *left) {
        this->left = left;
    }

    void setIsLeft(bool ok) {
        this->isLeft = ok;
    }

    void setKey(int k) {
        this->key = k;
    }
};

class TreeSet {
    char nameTag;
    Node *root;
public:
    TreeSet(char nameTag) : root(nullptr), nameTag(nameTag) {}

    TreeSet() : root(nullptr) {}

    TreeSet(int key) : root(new Node(key)) {}

    void add(int k) {
        Node *temp = new Node(k);
        if (!root) {
            root = temp;
            return;
        }
        Node *curr = root;
        while (curr != nullptr) {
            if (k > curr->getKey()) {
                if (curr->getRight() == nullptr) {
                    temp->setIsLeft(false);
                    curr->setRight(temp);
                    return;
                }
                curr = curr->getRight();
            } else {
                if (curr->getLeft() == nullptr) {
                    temp->setIsLeft(true);
                    curr->setLeft(temp);
                    return;
                }
                curr = curr->getLeft();
            }
        }
        //curr = temp;
    }

    char getNameTag() {
        return this->nameTag;
    }

    void setNameTag(char tag) {
        this->nameTag = tag;
    }

    void printTreeInOrder() {
        stack<Node *> stack;
        Node *curr = root;
        while (curr != nullptr || !stack.empty()) {
            while (curr != nullptr) {
                stack.push(curr);
                curr = curr->getLeft();
            }
            curr = stack.top();
            stack.pop();
            cout << curr->getKey() << " ";

            curr = curr->getRight();
        }
        cout << endl;
    }

    // 02_BinTree_src materijali
    void printTree() {

        queue<Node *> q;
        int i, line_len = 62, first_skip = line_len, in_between_skip;
        cout << topLeftCorner << printline(line_len - 2) << topRightCorner << endl;
        cout << verticalLine << printspace((line_len - 16) / 2 ) << "PRINT TREE (" << this->nameTag << ")"
             << printspace((line_len - 16) / 2 ) << verticalLine << endl;
        cout << middleLeftCorner << printline(line_len - 2) << middleRightCorner << endl;
        q.push(this->root);
        int treeHeight = getHeight(this->root);
        for (i = 0; i <= treeHeight; i++) {
            int j = 1 << i, k, l;
            in_between_skip = first_skip;
            first_skip = (first_skip - 2) / 2;
            for (k = 0; k < first_skip; k++)
                putchar(' ');
            for (k = 0; k < j; k++) {
                Node *btn = q.front();
                q.pop();
                if (btn) {
                    q.push(btn->getLeft());
                    q.push(btn->getRight());
                    printf("%2d", btn->getKey());
                } else {
                    q.push(nullptr);
                    q.push(nullptr);
                    printf("  ");
                }
                for (l = 0; l < in_between_skip; l++)
                    putchar(' ');
            }
            cout << endl << endl;
        }
        cout << bottomLeftCorner << printline(line_len - 2) << bottomRightCorner << endl;
    }

    // Materijali iz knjige
    Node *insert(int k) {
        if (!root) {
            root = new Node(k);
            return root;
        }
        updateTreeBalance();
        Node *fp = nullptr;
        Node *fx = nullptr;
        Node *q = nullptr;
        Node *p = this->root;
        Node *x = p;
        while (p != nullptr) {
            if (k == p->getKey()) {
                return p;
            } else if (k < p->getKey()) {
                q = p->getLeft();
            } else {
                q = p->getRight();
            }
            if (q != nullptr) {
                if (q->getBalance() != 0) {
                    fx = p;
                    x = q;
                }
            }
            fp = p;
            p = q;
        }
        q = new Node(k);
        q->setBalance(0);
        if (k < fp->getKey()) {
            fp->setLeft(q);

        } else {
            fp->setRight(q);
        }
        if (k < x->getKey()) {
            p = x->getLeft();
        } else {
            p = x->getRight();
        }

        Node *y;
        y = p;
        while (p != q) {
            if (k < p->getKey()) {
                p->setBalance(1);
                p = p->getLeft();
            } else {
                p->setBalance(-1);
                p = p->getRight();
            }
        }
        int imbal = 0;
        if (k < x->getKey()) {
            imbal = 1;
        } else {
            imbal = -1;
        }
        if (x->getBalance() == 0) {
            x->setBalance(imbal);
            return q;
        }
        if (x->getBalance() != imbal) {
            x->setBalance(0);
            return q;
        }
        if (y->getBalance() == imbal) {
            p = y;
            if (imbal == 1) {
                x->rightRotation();
            } else {
                x->leftRotation();
            }
            x->setBalance(0);
            y->setBalance(0);
        } else {
            if (imbal == 1) {
                p = y->getRight();
                y->leftRotation();
                x->setLeft(p);
                x->rightRotation();
            } else {
                p = y->getLeft();
                x->setRight(p);
                y->rightRotation();
                x->leftRotation();
            }
            if (p->getBalance() == 0) {
                x->setBalance(0);
                y->setBalance(0);
            } else {
                if (p->getBalance() == imbal) {
                    x->setBalance(-imbal);
                    y->setBalance(0);
                } else {
                    x->setBalance(0);
                    y->setBalance(imbal);
                }
                p->setBalance(0);
            }
        }
        if (fx == nullptr) {
            this->root = p;
        } else {
            if (x == fx->getRight()) {
                fx->setRight(p);
            } else {
                fx->setLeft(p);
            }
        }
        return q;
    }


    void printTreeHeight() {
        queue<Node *> q;
        int i, line_len = 62, first_skip = line_len, in_between_skip;
        q.push(this->root);
        cout << topLeftCorner << printline(line_len - 2) << topRightCorner << endl;
        cout << verticalLine << printspace((line_len - 16) / 2 - 1) << "PRINT HEIGHT (" << this->nameTag << ")"
             << printspace((line_len - 16) / 2 - 1) << verticalLine << endl;
        cout << middleLeftCorner << printline(line_len - 2) << middleRightCorner << endl;
        int treeHeight = getHeight(this->root);
        int num = 0;
        for (i = 0; i <= treeHeight; i++) {
            int j = 1 << i, k, l;
            in_between_skip = first_skip;
            first_skip = (first_skip - 2) / 2;
            for (k = 0; k < first_skip; k++)
                putchar(' ');
            for (k = 0; k < j; k++) {
                Node *btn = q.front();
                q.pop();
                if (btn) {
                    q.push(btn->getLeft());
                    q.push(btn->getRight());
                    printf("%2d (%2d)", btn->getKey(), getHeight(btn));
                    num += 5;
                } else {
                    q.push(nullptr);
                    q.push(nullptr);
                    printf("  ");
                }
                for (l = 0; l < in_between_skip - num; l++)
                    putchar(' ');
                num = 0;
            }
            cout << endl << endl;
        }
        cout << bottomLeftCorner << printline(line_len - 2) << bottomRightCorner << endl;
    }

    void updateTreeBalance() {
        if (!this->root)
            return;
        queue<Node *> q;
        stack<Node *> stack;
        q.push(this->root);
        int treeHeight = getHeight(this->root);
        for (int i = 0; i <= treeHeight; i++) {
            int j = 1 << i, k, l;
            for (k = 0; k < j; k++) {
                Node *btn = q.front();
                q.pop();
                if (btn) {
                    q.push(btn->getLeft());
                    q.push(btn->getRight());
                    stack.push(btn);
                } else {
                    q.push(nullptr);
                    q.push(nullptr);
                }
            }
        }
        while (!stack.empty()) {
            Node *node = stack.top();
            stack.pop();
            updateBalance(node);
        }
    }

    void printTreeBalance() {
        updateTreeBalance();
        queue<Node *> q;
        int i, line_len = 62, first_skip = line_len, in_between_skip;
        cout << topLeftCorner << printline(line_len - 2) << topRightCorner << endl;
        cout << verticalLine << printspace((line_len - 16) / 2 - 1) << "PRINT BALANCE (" << this->nameTag << ")"
             << printspace((line_len - 16) / 2 - 2) << verticalLine << endl;
        cout << middleLeftCorner << printline(line_len - 2) << middleRightCorner << endl;
        q.push(this->root);
        int treeHeight = getHeight(this->root);
        int num = 0;
        for (i = 0; i <= treeHeight; i++) {
            int j = 1 << i, k, l;
            in_between_skip = first_skip;
            first_skip = (first_skip - 2) / 2;
            for (k = 0; k < first_skip; k++)
                putchar(' ');
            for (k = 0; k < j; k++) {
                Node *btn = q.front();
                q.pop();
                if (btn) {
                    q.push(btn->getLeft());
                    q.push(btn->getRight());
                    printf("%2d (%2d)", btn->getKey(), btn->getBalance());
                    num += 5;
                } else {
                    q.push(nullptr);
                    q.push(nullptr);
                    printf("  ");
                }
                for (l = 0; l < in_between_skip - num; l++)
                    putchar(' ');
                num = 0;
            }
            cout << endl << endl;
        }
        cout << bottomLeftCorner << printline(line_len - 2) << bottomRightCorner << endl;
    }

    void insertElements(int *a, int n) {
        for (int i = 0; i < n; ++i) {
            insert(a[i]);
        }
    }

    void updateBalance(Node *node) {
        if (!node) return;
        int leftHeight = getHeight(node->getLeft()) + 1;
        int rightHeight = getHeight(node->getRight()) + 1;

        if (leftHeight == -1) {
            if (rightHeight == -1)
                node->setBalance(leftHeight - rightHeight);
            else
                node->setBalance(-rightHeight);
        } else if (rightHeight == -1) {
            node->setBalance(leftHeight);
        } else {
            node->setBalance(leftHeight - rightHeight);
        }
    }

    int getHeight(Node *node) {
        if (node == nullptr) {
            return -1;
        }
        queue<Node *> q;
        q.push(node);
        int height = -1;
        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                Node *curr = q.front();
                q.pop();

                if (curr->getLeft()) {
                    q.push(curr->getLeft());
                }

                if (curr->getRight()) {
                    q.push(curr->getRight());
                }
            }

            height++;
        }
        return height;
    }

    void deleteTree() {
        stack<Node *> stack;
        Node *curr = root, *curr_old;
        while (curr != nullptr || !stack.empty()) {
            while (curr != nullptr) {
                stack.push(curr);
                curr = curr->getLeft();
            }
            curr = stack.top();
            curr_old = stack.top();
            stack.pop();
            curr = curr->getRight();
            delete curr_old;
        }
    }

    bool exists(int key) {
        stack<Node *> stack;
        Node *curr = root;
        while (curr != nullptr || !stack.empty()) {
            while (curr != nullptr) {
                stack.push(curr);
                curr = curr->getLeft();
            }
            curr = stack.top();
            stack.pop();
            if (curr->getKey() == key)
                return true;
            curr = curr->getRight();
        }
        return false;
    }

    int numberOfElements() {
        queue<Node *> queue;
        Node *curr = root;
        int len = 0;
        while (curr != nullptr || !queue.empty()) {
            while (curr != nullptr) {
                queue.push(curr);
                curr = curr->getLeft();
            }
            curr = queue.front();
            queue.pop();
            len++;
            curr = curr->getRight();
        }
        return len;
    }

    int *getElementsFromTree() {
        int *arr = new int[this->numberOfElements()];
        queue<Node *> queue;
        Node *curr = root;
        int br = 0;
        while (curr != nullptr || !queue.empty()) {
            while (curr != nullptr) {
                queue.push(curr);
                curr = curr->getLeft();
            }
            curr = queue.front();
            queue.pop();
            arr[br++] = curr->getKey();
            curr = curr->getRight();
        }
        return arr;
    }

    Node *getRoot() { return root; }
};


void newMenu(int line_len, int strlen, string options[], int pomeraj = 7) {
    cout << endl;
    upperTableHeading(line_len);
    cout << verticalLine << printspace((line_len - options[0].length()) / 2) << options[0]
         << printspace((line_len - options[0].length()) / 2) << verticalLine << endl;
    cout << middleLeftCorner << printline(line_len) << middleRightCorner << endl;
    for (int i = 1; i < strlen; ++i) {
        cout << verticalLine << printspace(pomeraj) << options[i]
             << printspace((line_len - options[i].length()) - pomeraj) << verticalLine << endl;
        if (i < strlen - 1)
            cout << middleLeftCorner << printline(line_len) << middleRightCorner << endl;
    }
    lowerTableHeading(line_len);
}

void newMessage(string poruka = "", int line_len = 40) {
    cout << endl;
    upperTableHeading(line_len);
    cout << verticalLine << printspace((line_len - poruka.length()) / 2) << poruka
         << printspace((line_len - poruka.length()) / 2) << verticalLine << endl;
    lowerTableHeading(line_len);
}
void mainMenuWithConditions(TreeSet *set1, TreeSet *set2) {
    int line_len = 41, pomeraj = 10;
    bool s1 = set1 != nullptr;
    bool s2 = set2 != nullptr;
    string options[8]{"MAIN MENU",
                      "(1) Create a new set",
                      "(2) Add elements",
                      "(3) Check for element",
                      "(4) Set subtraction",
                      "(5) Print sets",
                      "(6) Delete sets",
                      "(0) Exit"};
    cout << endl;
    upperTableHeading(line_len);
    cout << verticalLine << printspace((line_len - options[0].length()) / 2) << options[0]
         << printspace((line_len - options[0].length()) / 2) << verticalLine << endl;
    cout << middleLeftCorner << printline(line_len) << middleRightCorner << endl;
    if (!s1 || !s2) { // Kreiraj novi skup
        cout << verticalLine << printspace(pomeraj) << options[1]
             << printspace((line_len - options[1].length()) - pomeraj) << verticalLine << endl;

        cout << middleLeftCorner << printline(line_len) << middleRightCorner << endl;
    }
    if (s1 || s2) { // Dodaj elemente u skup
        cout << verticalLine << printspace(pomeraj) << options[2]
             << printspace((line_len - options[2].length()) - pomeraj) << verticalLine << endl;

        cout << middleLeftCorner << printline(line_len) << middleRightCorner << endl;
    }
    if (s1 || s2) { // proveri element
        cout << verticalLine << printspace(pomeraj) << options[3]
             << printspace((line_len - options[3].length()) - pomeraj) << verticalLine << endl;

        cout << middleLeftCorner << printline(line_len) << middleRightCorner << endl;
    }
    if (s1 && s2) { // razlika skupova
        cout << verticalLine << printspace(pomeraj) << options[4]
             << printspace((line_len - options[4].length()) - pomeraj) << verticalLine << endl;
        cout << middleLeftCorner << printline(line_len) << middleRightCorner << endl;
    }
    if (s1 || s2) { // ispis skupova
        cout << verticalLine << printspace(pomeraj) << options[5]
             << printspace((line_len - options[5].length()) - pomeraj) << verticalLine << endl;
        cout << middleLeftCorner << printline(line_len) << middleRightCorner << endl;
    }
    if (s1 || s2) { // brisanje skupa
        cout << verticalLine << printspace(pomeraj) << options[6]
             << printspace((line_len - options[6].length()) - pomeraj) << verticalLine << endl;
        cout << middleLeftCorner << printline(line_len) << middleRightCorner << endl;
    }
    cout << verticalLine << printspace(pomeraj) << options[7]
         << printspace((line_len - options[7].length()) - pomeraj) << verticalLine << endl;


    lowerTableHeading(line_len);
}

string trimSpaces(const std::string &inputString) {
    // Find the position of the first non-space character from the beginning
    size_t startPos = inputString.find_first_not_of(" \t\n\r");

    // Find the position of the first non-space character from the end
    size_t endPos = inputString.find_last_not_of(" \t\n\r");

    if (startPos == std::string::npos) {
        // If the string is all spaces, return an empty string
        return "";
    }

    // Extract the substring without leading and trailing spaces
    return inputString.substr(startPos, endPos - startPos + 1);
}

int countSpaces(const std::string &inputString) {
    int spaceCount = 0;
    for (char c: inputString) {
        if (std::isspace(c)) { // Check if the character is a space character
            spaceCount++;
        }
    }
    return spaceCount;
}

void handleCreateSet(TreeSet *&set1, TreeSet *&set2) {
    if (set1 != nullptr && set2 != nullptr)
        return;
    char newChar;
    newMessage("Enter identifier for a new set (char):", 50);
    while (true) {
        cout << "->";
        cin >> newChar;
        if (set1 == nullptr) {
            if (set2 != nullptr && set2->getNameTag() == newChar) {
                cout << endl << "You entered an identifier which already exists. Try again." << endl;
            } else break;
        } else {
            if (set2 == nullptr && set1->getNameTag() == newChar) {
                cout << endl << "You entered an identifier which already exists. Try again." << endl;
            } else break;
        }
    }
    if (set1 == nullptr)
        set1 = new TreeSet(newChar);
    else if (set2 == nullptr)
        set2 = new TreeSet(newChar);
    string msg = "Empty set " + string(1, newChar) + " created successfully. ";
    newMessage(msg);
}

void handleInsertElements(TreeSet *set1, TreeSet *set2) {
    if (set1 == nullptr && set2 == nullptr)
        return;
    TreeSet *curr;
    istringstream iss;

    char name;
    string inputStr;
    if(set2 == nullptr) {
        curr = set1;
    } else if(set1 == nullptr) {
        curr = set2;
    } else {
        while (true) {
            newMessage(" Enter set id (char)");
            cout << "->";
            cin >> name;
            if (set1 != nullptr && set1->getNameTag() == name) {
                curr = set1;
                break;
            } else if (set2 != nullptr && set2->getNameTag() == name) {
                curr = set2;
                break;
            } else cout << "You entered invalid set id. Try again." << endl;
        }
    }
    newMessage("Enter set elements divided by space", 49);
    cout << "->";
    cin.ignore();
    getline(cin, inputStr);
    inputStr = trimSpaces(inputStr);
    if(inputStr.empty())
        return;
    iss.str(inputStr);
    int num = 0, len = countSpaces(inputStr) + 1;
    int *arr = new int[len];
    int i = 0;
    while (iss >> num) {
        arr[i++] = num;
    }
    cout << endl;
    curr->insertElements(arr, len);
    curr->printTree();
    iss.clear();
    delete[] arr;
}

void handleCheckExistence(TreeSet *set1, TreeSet *set2) {
    if (set1 == nullptr && set2 == nullptr) return;
    TreeSet *currSet;
    char name;
    if(set2 == nullptr) {
        currSet = set1;
    } else if(set1 == nullptr) {
        currSet = set2;
    } else {
        while (true) {
            newMessage(" Enter set id (char)");
            cout << "->";
            cin >> name;
            if (set1 != nullptr && set1->getNameTag() == name) {
                currSet = set1;
                break;
            } else if (set2 != nullptr && set2->getNameTag() == name) {
                currSet = set2;
                break;
            } else cout << "You entered invalid set id. Try again." << endl;
        }
    }
    int elem;
    newMessage("Enter element", 19);
    cout << "->";
    cin >> elem;
    if (currSet->exists(elem)) {
        newMessage("Key exists in tree. ", 60);
    } else {
        newMessage("Key doesn't exist in tree.", 60);
    }
    currSet->printTree();
}

void handleDifference(TreeSet *&diff, TreeSet *set1, TreeSet *set2) {
    bool add;
    char name;
    int *arr1, *arr2, *arr;
    if (set1 == nullptr || set2 == nullptr)
        return;
    TreeSet *firstSet, *secondSet;
    while (true) {
        newMessage("Enter first set id (char):");
        cout << "->";
        cin >> name;
        if (set1 != nullptr && set1->getNameTag() == name) {
            firstSet = set1;
            secondSet = set2;
            break;
        } else if (set2 != nullptr && set2->getNameTag() == name) {
            firstSet = set2;
            secondSet = set1;
            break;
        } else cout << "You entered an invalid set id. Try again." << endl;
    }
    diff = new TreeSet('Z');
    arr1 = firstSet->getElementsFromTree();
    arr2 = secondSet->getElementsFromTree();
    add = true;
    for (int i = 0; i < firstSet->numberOfElements(); ++i) {
        add = true;
        for (int j = 0; j < secondSet->numberOfElements(); ++j) {
            if (arr1[i] == arr2[j]) {
                add = false;
                break;
            }
        }
        if (add) {
            diff->insert(arr1[i]);
        }
    }
    firstSet->printTree();
    secondSet->printTree();
    diff->printTree();
    diff->deleteTree();
    delete diff;
    diff = nullptr;
}

void handlePrintSets(TreeSet *set1, TreeSet *set2) {
    if (set1 == nullptr && set2 == nullptr) return;
    if (set1 != nullptr) {
        set1->printTreeInOrder();
        set1->printTree();
        set1->printTreeBalance();
        set1->printTreeHeight();
    }
    if (set2 != nullptr) {
        set2->printTreeInOrder();
        set2->printTree();
        set2->printTreeBalance();
        set2->printTreeHeight();
    }
}

void handleDeleteSet(TreeSet *&set1, TreeSet *&set2) {
    char name;
    if (set1 == nullptr && set2 == nullptr)
        return;
    while (true) {
        newMessage(" Enter set id (char)");
        cout << "->";
        cin >> name;
        if (set1 != nullptr && set1->getNameTag() == name) {
            set1->deleteTree();
            set1 = nullptr;
            break;
        } else if (set2 != nullptr && set2->getNameTag() == name) {
            set2->deleteTree();
            set2 = nullptr;
            break;
        } else cout << "You entered invalid set id. Try again." << endl;
    }
    newMessage(" Set deleted successfully.");
}

void mainMenu() {
    int red_br = -1, i = 0, num, len;
    TreeSet *set1 = nullptr, *set2 = nullptr, *diff = new TreeSet('.');
    while (true) {
        mainMenuWithConditions(set1, set2);
        cout << "->";
        cin >> red_br;
        switch (red_br) {
            case 1:
                handleCreateSet(set1,set2);
                break;
            case 2:
                handleInsertElements(set1,set2);
                break;
            case 3:
                handleCheckExistence(set1,set2);
                break;
            case 4:
                handleDifference(diff,set1,set2);
                break;
            case 5:
                handlePrintSets(set1,set2);
                break;
            case 6:
                handleDeleteSet(set1,set2);
                break;
            case 0:
                newMessage(" Program ended successfully.");
                return;
            default:
                break;
        }
    }
}


int main() {
    mainMenu();
}
