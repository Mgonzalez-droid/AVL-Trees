#include <iostream>
#include<vector>

//============= Node ===========================

struct Node{

public:
    Node* right;
    Node* left;
    int id_;
    std::string name_;
    
    Node(){
        this->right = NULL;
        this->left = NULL;
    }
};

//============= AVL Tree =======================

class AVL_Tree{
private:
    //INDEPENDENTLY ADDED
    
    int height(Node* node){
            if(node == NULL){
                return 0;
            } else{
                int lengthOfLeft = height(node->left);
                int lengthOfRight = height(node->right);
                return 1 + std::max(lengthOfLeft, lengthOfRight);
            }
    }
    
    Node* findMinNode(Node* node){
        Node* current = node;
  
        while (current->left != NULL){
            current = current->left;
        }
        return current;
    }
    
    int difference(Node* node) {
       int leftHeight = height(node->left);
       int rightHeight = height(node->right);
       int b_factor = leftHeight - rightHeight;
       return b_factor;
    }
    
    Node* balanceTree(Node* node) {
       int b_factor = difference(node);
       if (b_factor > 1) {
          if (difference(node->left) > 0)
              node = rotateRight(node);
          else
              node = rotateLeftRight(node);
       } else if (b_factor < -1) {
          if (difference(node->right) > 0)
              node = rotateRightLeft(node);
          else
              node = rotateLeft(node);
       }
       return node;
    }
    
    //rotations
    
    Node* rotateLeft(Node *node){
        Node* grandChild = node -> right -> left;
        Node* newParent = node -> right;
        newParent -> left = node;
        node -> right = grandChild;
        return newParent;
    }

    Node* rotateRight(Node *node){
        Node* grandChild = node -> left -> right;
        Node* newParent = node -> left;
        newParent -> right = node;
        node -> left = grandChild;
        return newParent;
    }

    Node* rotateLeftRight(Node *node){
        node -> left = rotateLeft(node -> left);
        node = rotateRight(node);
        return node;
    }
    
    Node* rotateRightLeft(Node *node){
        node -> right = rotateRight(node -> right);
        node = rotateLeft(node);
        return node;
    }
    
public:
    
    AVL_Tree(Node* root){
        root = NULL;
    }
    /*
    int getHeight(Node* node){
        int h = height(node);
        return h;
    }
     */
    
    //PROJECT SPEC.
     
     Node* insert(Node* node, std::string NAME, int ID)
     {
         if(node == NULL){
             node = new Node;
             node->name_ = NAME;
             node->id_ = ID;
             std::cout<<"successful"<<std::endl;
             return node;
         } else{
             if(ID != node -> id_){
                 if(ID < node->id_){
                     node -> left = insert(node -> left, NAME, ID);
                     node = balanceTree(node);
                 } else {
                     node -> right = insert(node -> right, NAME, ID);
                     node = balanceTree(node);
                 }
             } else{
                 std::cout<<"unsuccessful"<<std::endl;
             }
         }
         return node;
     }
    
     Node* remove(Node* node, int ID){
         if(node == NULL){
            std::cout<<"unsuccessful"<<std::endl;
             return node;
         }
         if(ID < node->id_){
             node -> left = remove(node -> left, ID);
         } else if(ID > node->id_){
             node -> right = remove(node -> right, ID);
         }
         if(node ->id_ == ID){
             if(node -> left == NULL || node -> right == NULL){
                 Node* t = NULL;
                 if(node -> left == NULL && node -> right != NULL){
                     t = node -> right;
                 }
                 if(node -> left != NULL && node -> right == NULL){
                     t = node -> right;
                 }
                 if(t == NULL){
                     t = node;
                     node = NULL;
                     //addition
                     std::cout<<"successful"<<std::endl;
                 } else{
                     *node = *t;
                     //addition
                     std::cout<<"successful"<<std::endl;
                 }
             } else{
                 Node* t = findMinNode(node -> right);
                 node->id_ = t->id_;
                 node -> name_ = t -> name_;
                 node->right = remove(node->right, t->id_);
             }
         }
         if (node == NULL){
             return node;
         }
         
         //std::cout<<"successful"<<std::endl;
         
         node = balanceTree(node);
         
         return node;
     }
     
    void search(Node* node, std::string NAME){
            std::vector<int> n;
            n = presearch(n, node, NAME);
            postSearch(n);
    }

    std::vector<int> presearch(std::vector<int> n, Node* node, std::string s){
        if(node == NULL){
            return n;
        }
        if(s == node ->name_){
            n.push_back(node->id_);
            return n;
        }
        n = presearch(n,node->left, s);
        n = presearch(n,node->right, s);
        return n;
    }
    
    void postSearch(std::vector<int> n){
        if(n.size() == 0){
            std::cout << "unsuccessful"<<std::endl;
        } else{
            for(int i = 0; i < n.size(); i++){
                std::cout<<n[i]<<std::endl;
            }
        }
    }

    void search(Node* node, int ID){
        if(node == NULL){
            std::cout << "unsuccessful"<<std::endl;
        } else{
            if (node ->id_ == ID) {
                std::cout <<node ->name_ << std::endl;
            } else{
                if(ID < node->id_ ){
                    search(node -> left, ID);
                } else{
                    search(node -> right, ID);
                }
            }
        }
    }

    void printInorder(Node* node){ //L Ro R
        if(node == NULL)
            return;
        
        printInorder(node->left);
        if(node->left != NULL)
            std::cout<<", ";
        
        std::cout<<node->name_;
        if(node->right != NULL)
            std::cout<<", ";
            
        printInorder(node->right);
    }

    void printPreorder(Node* node){ //Ro L R
        if(node == NULL){
            return;
        }
        
        std::cout<<node->name_;
        
        if(node->left  != NULL)
            std::cout<<", ";
        
        printPreorder(node->left);
        
        if(node->right  != NULL)
            std::cout<<", ";
        
        printPreorder(node->right);
    }

    void printPostorder(Node* node){ //L R Ro
        if(node == NULL)
            return;
        
        printPostorder(node->left);
        
        if(node->left  != NULL)
            std::cout<<", ";
        
        printPostorder(node->right);
        
        if(node->right != NULL)
            std::cout<<", ";
        
        std::cout<<node->name_;
    }

    void printLevelCount(Node* node){
        int h = height(node);
        std::cout<<h<<std::endl;
    }

    Node* removeInorder(Node* node, int N){
        if(node == NULL || N < 0){
            return node;
        }
        
        if(N == 0){
            if(node != NULL){
                node -> left = remove(node->left, node->left->id_);
            }
        }
        
        N--;
        
        if(N == 0){
            if(node != NULL){
                node = remove(node, node -> id_);
            }
        }
        
        N--;
        
        if(N == 0){
            if(node != NULL){
                node -> right = remove(node->right, node->right -> id_);
            }
        }
        
        return node;
    }

};

///============= Main =======================

Node* root;
AVL_Tree tree(root);
std::vector<std::string> words;

void parseString(std::string input){
    
    std::string method = "";
    std::string name = "";
    std::string id = "";
    
    int i = 0;
    
    while(!std::isspace(input[i]) && i < input.length()){
        method = method + input[i];
        i = i + 1;
    }
    
    if(input.length() > i + 1)
        i = i + 1;
    
    if(input[i] == '\"'  && i < input.length()){
        i = i + 1;
        while((input[i] != '\"' && i < input.length()) && (std::isalpha(input[i]) || std::isspace(input[i]))){
            name = name + input[i];
            i = i + 1;
        }
        if((std::ispunct(input[i]) && std::isalpha(input[i + 1])) || std::isdigit(input[i])){
            words.push_back("QUIT");
            return;
        }
        if(input.length() > i + 2)
            i = i + 2;
        //else
            //return;
    } else{
        if(!std::isdigit(input[i]) && i > input.length()){
            words.push_back("QUIT");
            return;
        }
    }
    
    if(std::isdigit(input[i])){
        while(std::isdigit(input[i]) && i < input.length()){
                id = id + input[i];
                i = i + 1;
        }
        
        if(std::isalpha(input[i]) || std::ispunct(input[i]) || std::isspace(input[i])){
            words.push_back("QUIT");
            return;
        }
    } else if(std::isalpha(input[i]) || (std::ispunct(input[i]) && i > input.length()) || std::isspace(input[i])){
        words.push_back("QUIT");
        return;
    }
    
    words.push_back(method);
    if(name != ""){
        words.push_back(name);
    }
    if(id != ""){
        words.push_back(id);
    }
}

void removeTrailingZeros(std::string input){
    std::string word = "";
    for (auto c : input){
        if(std::isdigit(c)){
            if(word.empty() && c == '0'){
                //do nothing
            } else{
                word = word + c;
            }
        }
    }
}

bool checkNumber(std::string s){
    std::string::const_iterator i = s.begin();
    while (i != s.end() && std::isdigit(*i)){
        ++i;
    }
    return !s.empty() && i == s.end();
}

void functions(){
    if(words[0] == "insert"){
        if(words[2].length()==8){
            removeTrailingZeros(words[2]);
            root = tree.insert(root, words[1], std::stoi(words[2]));
        } else{
            std::cout<<"unsuccessful"<<std::endl;
        }
        words.clear();
    }
        
    if(words[0] == "remove"){
        if(words[2].length()==8){
            removeTrailingZeros(words[2]);
            root = tree.remove(root, std::stoi(words[1]));
        }else{
            std::cout<<"unsuccessful"<<std::endl;
        }
        words.clear();
    }
    
    if(words[0] == "removeInorder"){
        root = tree.removeInorder(root, std::stoi(words[1]));
        
        words.clear();
    }
    
    if(words[0] == "search"){
        if(checkNumber(words[1])){
            if(words[2].length()==8){
                removeTrailingZeros(words[2]);
                tree.search(root, std::stoi(words[1]));
            }else{
                std::cout<<"unsuccessful"<<std::endl;
            }
        }
        else
            tree.search(root, words[1]);
        
        words.clear();
    }

    if(words[0] == "printInorder"){
        tree.printInorder(root);
        std::cout<<std::endl;
        words.clear();
    }
    
    if(words[0] == "printPreorder"){
        tree.printPreorder(root);
        std::cout<<std::endl;
        words.clear();
    }
    
    if(words[0] == "printPostorder"){
        tree.printPostorder(root);
        std::cout<<std::endl;
        words.clear();
    }
    
    if(words[0] == "printLevelCount"){
        tree.printLevelCount(root);
        words.clear();
    }
    
    if(words[0] == "QUIT"){
        std::cout<<"unsuccessful"<<std::endl;
        words.clear();
    }
}

int main(){
    int sentinal = 0;
    std::string input;
    std::cin>>sentinal;
    std::cin >> std::ws;
    while(sentinal != 0){
        std::getline(std::cin, input);
        parseString(input);
        functions();
        sentinal--;
    }
}
