#include<sstream>
#include<iostream>
#include<string>
#include<map>
#include<unordered_set>
#include<queue>
#include<ctime>

using namespace std;
class friends_network{
    public:
    unordered_map <string,unordered_set<string>> friends_graph;
    void add_user(string new_user){
        friends_graph[new_user]={};
    }
    void add_friend(string user1, string user2){
        friends_graph[user1].insert(user2);
        friends_graph[user2].insert(user1);
    }
    void list_friends(string user){
        vector <string> friends;
        for (auto x: friends_graph[user]){
            friends.push_back(x);
        }
        sort(friends.begin(),friends.end());
        for (auto x:friends){
            cout<<x<<"\n";
        }
    }
    void suggest_friends(string user, int N){
        unordered_map <string,int> friendoffriend;
        for (auto f: friends_graph[user]){
            for (auto fof : friends_graph[f]) {
                if (fof!=user and friends_graph[user].count(fof)==0) friendoffriend[fof]++;
            }
        }
        
        // vector <pair<int,string>> recommendation;

        // for (auto x:friendoffriend){
        //     recommendation.push_back({x.second,x.first});
        // }
        // int total_recommendations=recommendation.size();
        // for (auto& x : recommendation){
        //     x.first=-x.first;
        // }
        // sort(recommendation.begin(),recommendation.end());
        // int printed=0;
        // if (min(N,total_recommendations)==0){
        //     cout<<"No friends suggestion\n";
        //     return;
        // }
        // cout<<"Here are the top "<<min(N,total_recommendations)<<" friends you can make\n";
        // for (auto x: recommendation){
        //     if (printed==N) break;
        //     cout<<"USERNAME: "<<x.second<<" MUTUAL FRIENDS:"<<-x.first<<"\n";
        // }

        struct comp_suggestions {
        bool operator()(pair<int,string>& a,pair<int,string>& b) {
            // i have made a min heap wrt mutual counts and a max heap wrt alphabetical name
            // if mutual counts are different, the one with FEWER mutuals has higher priority
            if (a.first != b.first) {
                return a.first > b.first;
            }
            // if mutual counts are same, the one that is LATER alphabetically has higher priority
            return a.second < b.second;
        }
        };

        priority_queue<pair<int,string>,vector<pair<int,string>>,comp_suggestions> recommendation;
        if (N==-1){
            for (auto x:friendoffriend){
            recommendation.push({x.second,x.first});
            }
        }
        else if (N!=0) {
            for (auto x: friendoffriend){
                if (recommendation.size()<N) {
                    recommendation.push({x.second,x.first});
                }
                else if (x.second>recommendation.top().first){
                    recommendation.pop();
                    recommendation.push({x.second,x.first});
                }
            }
        }
        vector <pair<int,string>> suggestion_vector;
        while (!recommendation.empty())
        {
            suggestion_vector.push_back(recommendation.top());
            recommendation.pop();
        }
        reverse(suggestion_vector.begin(),suggestion_vector.end());
        int total_recommendations=suggestion_vector.size();
        if (min(N,total_recommendations)==0){
            cout<<"No friends suggestion\n";
            return;
        }
        cout<<"Here are the top "<<min(N,total_recommendations)<<" friends you can make\n";
        for (int i=0;i<min(N,total_recommendations);i++){
            auto x=suggestion_vector[i];
            cout<<"USERNAME: "<<x.second<<" MUTUAL FRIENDS:"<<x.first<<"\n";
            // recommendation.pop();
        }
    }
    int degree_of_seperation(string user1, string user2){
        if (user1==user2) return 0;
        queue<pair<string,int>> q;
        unordered_map<string,bool> vis;
        vis[user1]=true;
        q.push({user1,0});
        while(!q.empty()){
            auto [user,d]=q.front();
            q.pop();
            if (user==user2) return d;
            for (auto x: friends_graph[user]){
                if (!vis[x]){
                    vis[x]=true;
                    q.push({x,d+1});
                }
            }
        }
        return -1;
    }
};

struct Node{
    string post;
    time_t time_created;
    int height;
    Node* left;
    Node* right;
    Node(string p,time_t post_creation_time){
        post=p;
        height=0;
        right=nullptr;
        left=nullptr;
        time_created=post_creation_time;
    }
};

class AVLTree {
private:
    Node* root;

    int height(Node* N) {
        if (N == nullptr)
            return -1;
        return N->height;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        // Return new root
        return x;
    }

    Node* leftRotate(Node* x) {
        // implement
        Node* y=x->right;
        Node* T2=y->left;
        
        x->right=T2;
        y->left=x;
        
        x->height=max(height(x->left),height(x->right))+1;
        y->height=max(height(y->right),height(y->left))+1;
        
        return y;
    }

    int getBalance(Node* N) {
        // implement
        return height(N->left)-height(N->right);
    }

    Node* insertHelper(Node* node, string post,time_t time_created) {
        // 1. Standard BST insertion
        if (node == nullptr)
            return new Node(post,time_created);

        if (time_created < node->time_created)
            node->left = insertHelper(node->left,post, time_created);
        else if (time_created > node->time_created)
            node->right = insertHelper(node->right,post, time_created);
        else // Duplicate time_createds are not allowed
            return node;

        // 2. Update height of this ancestor node
        node->height = 1 + max(height(node->left), height(node->right));

        // 3. Get the balance factor to check for imbalance
        int balance = getBalance(node);

        // 4. If unbalanced, perform rotations
        // Left Left Case
        if (balance > 1 && time_created < node->left->time_created)
            return rightRotate(node);

        // Right Right Case
        // implement
        if (balance<-1 && time_created>node->right->time_created){
            return leftRotate(node);
        }

        // Left Right Case
        // implement
        if (balance>1 && time_created>node->left->time_created){
            node->left=leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        // implement
        if (balance<-1 && time_created<node->right->time_created){
            node->right=rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void traversehelper(Node* node,int N,int &posts_printed){
        if (posts_printed==N) return;
        if (!node) return;
        traversehelper(node->right,N,posts_printed);
        if (posts_printed>=N) return;
        tm* post_tm=localtime(&node->time_created);
        char post_tm_buffer[80];
        strftime(post_tm_buffer, sizeof(post_tm_buffer), "%Y-%m-%d %H:%M:%S", post_tm);
        cout<<"Post content: "<<node->post<<" Post Time:"<<post_tm_buffer<<"\n";
        posts_printed++;
        traversehelper(node->left,N,posts_printed);
    }

    void deleteTree(Node* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

public:
    AVLTree() {
        root = nullptr;
    }

    ~AVLTree() {
        deleteTree(root);
    }

    void insert(string post) {
        time_t post_creation_time;
        time(&post_creation_time);
        root = insertHelper(root,post, post_creation_time);
    }
    void traverse(int N){
        int posts_printed=0;
        if (N==-1) traversehelper(root,INT_MAX,posts_printed);
        else traversehelper(root,N,posts_printed);
    }
};


class posttree{
    unordered_map <string,AVLTree> postmap;
    public: 
        void add_post(string user, string post){
            postmap[user].insert(post);
        }
        void output_posts(string user, int N){
            postmap[user].traverse(N);
        }
};

class SocialNet{
    posttree userposts;
    friends_network usernetwork;
    public:
    void add_user(string username){
        if (usernetwork.friends_graph.count(username)){
            cout<<"This username already exists, try a different username.\n";
            return;
        } 
        else usernetwork.add_user(username);
    }
    void add_friend(string username1, string username2){
        if (!usernetwork.friends_graph.count(username1)){
            cout<<username1<<" not found in the social network\n";
            return;
        }
        if (!usernetwork.friends_graph.count(username2)){
            cout<<username2<<" not found in the social network\n";
            return;
        }
        usernetwork.add_friend(username1,username2);
    }
    void listfriends(string username){
        if (!usernetwork.friends_graph.count(username)){
            cout<<username<<" not found in the social network\n";
            return;
        }
        usernetwork.list_friends(username);
    }
    void suggest_friends(string username,int N){
        if (!usernetwork.friends_graph.count(username)){
            cout<<username<<" not found in the social network\n";
            return;
        }
        usernetwork.suggest_friends(username,N);
    }
    void degree_of_seperation(string username1 ,string username2){

        if (!usernetwork.friends_graph.count(username1)){
            cout<<username1<<" not found in the social network\n";
            return;
        }
        if (!usernetwork.friends_graph.count(username2)){
            cout<<username2<<" not found in the social network\n";
            return;
        }
        int degree=usernetwork.degree_of_seperation(username1,username2);
        cout<<"The degree of seperation between "<<username1<<" and "<<username2<<" is "<<degree<<"\n";
    }
    void add_post(string username,string post){
        if (!usernetwork.friends_graph.count(username)){
            cout<<username<<" not found in the social network\n";
            return;
        }
        userposts.add_post(username,post);
    }
    void output_posts(string username, int N){
        if (!usernetwork.friends_graph.count(username)){
            cout<<username<<" not found in the social network\n";
            return;
        }
        userposts.output_posts(username,N);
    }
};
int main(){
    string command, username, message;
    SocialNet SocialNetwork;
    string input_line; // A string for storing the complete input line
    cout<<"Welcome to SocialNetwork\n";
    cout<<"Type EXIT to quit the program\n";
    while (true) {
        cout << ">> ";
        getline(cin, input_line);
        stringstream ss(input_line);
        command = "";   // Reset variables for each loop iteration
        username = "";
        message = "";

        ss >> command;  // Extract the first word as the command
        ss >> username; // Extract the second word as the filename

        // I have assumed the rest of the input as message (which can contain spaces),
        // use getline again on the stringstream. std::ws skips any leading whitespace.
        getline(ss >> ws, message);

        // Processing the commands
        if (command=="ADD_USER"){
            for (char &c : username) {
                c = std::toupper(static_cast<unsigned char>(c));
            }
            if (username==""){
                cout<<"username must be non empty\n";
            }
            else SocialNetwork.add_user(username);
        }
        else if (command=="ADD_FRIEND"){
            for (char &c : username) {
                c = std::toupper(static_cast<unsigned char>(c));
            }
            for (char &c : message) {
                c = std::toupper(static_cast<unsigned char>(c));
            }
            if (username=="" || message=="") {
                cout<<"Both usernames should be non empty\n";
            }
            if (username==message) {
                cout<<"Both <username> must be distinct, user cant be friend of self.\n";
            }
            else SocialNetwork.add_friend(username,message);
        }
        else if (command=="LIST_FRIENDS") {
            for (char &c : username) {
                c = std::toupper(static_cast<unsigned char>(c));
            }
            if (username==""){
                cout<<"username must be non empty\n";
            }
            else SocialNetwork.listfriends(username);
        }
        else if (command == "SUGGEST_FRIENDS") {
            int num=0;
            bool possible=true;
            for (char &c : username) {
                c = std::toupper(static_cast<unsigned char>(c));
            }
            for (int i = 0; i < message.length(); i++)
            {
                if (message[i]-'0'<0 || message[i]-'0'>9){
                    cout<<"INVALID COMMAND: SUGGEST_FRIENDS <username> <N> here <N> must be a non-negative integer\n";
                    possible=false;
                    break;
                }
                else num=10*num+(message[i]-'0');
            }
            if (message=="") {
                cout<<"Integer argument missing, the correct command is SUGGEST_FRIENDS <username> N\n";
            }
            else if (possible) SocialNetwork.suggest_friends(username,num);
        }
        else if (command=="DEGREES_OF_SEPERATION"){
            for (char &c : username) {
                c = std::toupper(static_cast<unsigned char>(c));
            }
            for (char &c : message) {
                c = std::toupper(static_cast<unsigned char>(c));
            }
            if (username=="" || message=="") {
                cout<<"Both usernames should be non empty\n";
            }
            SocialNetwork.degree_of_seperation(username,message);
        }
        else if (command == "ADD_POST") {
            for (char &c : username) {
                c = std::toupper(static_cast<unsigned char>(c));
            }
            if (username==""){
                cout<<"username must be non empty\n";
            }
            else SocialNetwork.add_post(username,message);
        }
        else if (command == "OUTPUT_POSTS") {
            int num=0;
            bool possible=true;
            for (char &c : username) {
                c = std::toupper(static_cast<unsigned char>(c));
            }
            if (message=="-1"){
                possible=true;
                num=-1;
            }
            else{
                for (int i = 0; i < message.length(); i++)
                {
                    if (message[i]-'0'<-1 || message[i]-'0'>9){
                        cout<<"INVALID COMMAND: OUTPUT_POSTS <username> <N> here <N> must be a integer greater than -2\n";
                        possible=false;
                        break;
                    }
                    else num=10*num+(message[i]-'0');
                }
            }
            if (message==""){
                cout<<"Integer argument missing, the correct command is SUGGEST_FRIENDS <username> N\n";
            }
            else if (possible) SocialNetwork.output_posts(username,num);
        }
        else if (command=="EXIT"){
            break;
        }
        else if (!command.empty()) {
            std::cout << "Unknown command: " << command << std::endl;
        }
    }
}