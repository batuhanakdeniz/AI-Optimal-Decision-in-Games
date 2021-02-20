#include<iostream>
#include<fstream>
#include<vector>

using namespace std;



class Node{
    int state[9][9];
    vector<Node *> child;               //Children
    int child_num;
    vector<int> available_locations;    //Takes Available locations 
    vector<int> available_numbers;      //Takes available numbers for locations
    int nums_possible[9];               //It's size is 9 it will use for getting possible numbers according to the order in array
    int number_possible;                //It takes how many possible number are there
    bool end;                           //Is it end
    bool isMax;                         //Whose turn
    int score;                          //Takes for every node score
public:
    Node();
    Node(int given_state[][9]){
        for(int x=0;x<9;x++)
            for(int y=0;y<9;y++)
                this->state[x][y] = given_state[x][y];
    }
    //GET AND SET
    int get_child_num(){ return this->child_num;}
    void set_child_num(int child_num){   this->child_num = child_num;}
    vector<int> get_available_locations(){ return available_locations;}
    void set_nums_possible(int i){ nums_possible[i]=1;}
    int* get_nums_possible(){ return nums_possible;}
    void set_number_possible(){
        this->number_possible=0;
        for(int i=0;i<9;i++)
            if(nums_possible[i]==1)    
                number_possible++;
    }
    vector<int> get_available_numbers(){ return available_numbers;}
    int get_number_possible(){  return number_possible;}
    vector<Node *> get_child(){return child;}
    int get_score(){return this->score;}
    void set_score(int i){ this->score = i;}
    bool get_end(){ return end;}
    void set_isMax(bool isMax){ this->isMax = isMax;}
    bool get_isMax(){   return isMax;}
    //METHODS
    void create_Available_Node(bool);
    void findAvailable_locations();
    void possible_num(int);
    //TEST
    /******************
    void print_node(){
        for(int x=0;x<9;x++){
            for(int y=0;y<9;y++){
                cout<< this->state[x][y]<<"\t";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    //TEST
    void print_all(){
        this->print_node();
        for(vector<Node *>::size_type it = 0;it!=child.size();++it){
            child[it]->print_node();
        }
    }
    //TEST
    void print_possible_nums(int location){
       // cout<<"Possible number for location: "<<location+11<<endl;
        for(int i=0;i<9;i++){
            if(nums_possible[i]==1)
                cout<< i+1 <<endl;
        }
        cout<<"*********"<<endl;
    }
    ****************************/
    //TEST
};void Node::possible_num(int location){  //For every locations it finds possible number can be put
    int x = location / 10;
    int y = location % 10; 
    for(int i=0;i<9;i++)    nums_possible[i]=1; //nums_possible array implemented with 1 for every value 
    //COLUMNS
    for(int i=0;i<9;i++){               //Checking colums if there is a number in this column it will be changed with 0 in nums_possible array
        if(state[x][i]!=0)    nums_possible[state[x][i]-1] = 0;
    }
    //ROWS
    for(int i=0;i<9;i++){               //Checking rows if there is a number in this column it will be changed with 0 in nums_possible array
        if(state[i][y]!=0)    nums_possible[state[i][y]-1] = 0;
    }
    //IN BOX
    for(int i=x-x%3;i<x-x%3+3;i++){     //Checking box if there is a number in this column it will be changed with 0 in nums_possible array
        for(int k=y-y%3;k<y-y%3+3;k++){
            if(state[i][k]!=0)  nums_possible[state[i][k]-1] = 0;
        }
    }
    for(int i=0;i<9;i++){  
        if(nums_possible[i] == 1){
            this->available_numbers.push_back(i+1);
        }   
    }
    //IS IT END NODE
    bool flag = true;
    for(int i=0;i<9;i++)
        if(nums_possible[i] != 0) flag = false;
    this->end = flag;
}

void Node::findAvailable_locations(){   //Finding 0s in state
    int counter=0;
    for(int x=0;x<9;x++){
        for(int y=0;y<9;y++){
            if(this->state[x][y]==0){
                available_locations.push_back(10*x + y);
                counter++;
            }
        }
    }
    //IS IT END NODE
    if(counter==0){
        end = true;
        score = 1;
    }

    //TEST FİND AVAİLABLE LOCATİONS
    /******************************
    cout<<endl;
    for(vector<Node *>::size_type it = 0;it!=available_locations.size();++it){
            cout<<available_locations[it]<<"\t";
    }
    cout<<endl;
    *******************************/
    //TEST FİND AVAİLABLE LOCATİONS   
}

void Node::create_Available_Node(bool isMax){               //This function creating available nodes
    findAvailable_locations();                              //Firstly, it finds available locations
    int x,y;                                                //These parameters for getting location
    int temp_state[9][9];                                   //temporary state to send changed form of state 
    for(int i=0;i<available_locations.size();i++){          //For every available locations 
        for(int i=0;i<9;i++){                               //temporary state to send changed form of state 
            for(int k=0;k<9;k++){
                temp_state[i][k] = this->state[i][k]; 
            }
        }
        int temp_location = available_locations[i];
        possible_num(temp_location);                        //possible numbers are taken with function
        set_number_possible();                              //It provide
        int temp_number_possible = get_number_possible();
        if(temp_number_possible == 0){                  //If there is no possible number for a spesific location this node will not be created
            this->end = true;
            continue;
        }   
        int temp_pos_nums[temp_number_possible]; 
        int z=0;
        for(int l=0;l<9;l++){
            if(nums_possible[l]==1){
                temp_pos_nums[z] = l+1;
                z++;
            }           
        }
        for(int k=0;k<temp_number_possible;k++){    //It creates the children nodes
            if(state[temp_location/10][temp_location%10] == 0)   temp_state[temp_location/10][temp_location%10] = temp_pos_nums[k];
            Node *temp = new Node(temp_state);
            temp->set_isMax(isMax);
            if(temp->get_end()){                    //If it is end node it gives score according to who is winning 
                if(isMax){  
                    temp->set_score(10);
                }
                else{
                    temp->set_score(-10);
                }
            }
            child.push_back(temp);
        }
    }
} 


int minimax(Node *root, bool isMax){                //Basic minimax algorithm is implemented
    //if it is end return the score of the node
  
    root->create_Available_Node(isMax);
    vector<Node *> temp_child =root->get_child();
    vector<int> temp_available_nums = root->get_available_numbers();
    if(root->get_end() == true) {                   // If the taken node is end node it will return score this score is given in creating part
        return root->get_score();}   
    
    if (isMax){                                     //If Max's turn
        int best = -100;
        for(vector<Node *>::size_type i = 0; i != temp_child.size(); i++){
                int temp = minimax(temp_child[i],false);
                best = max(best, temp);
        }
        return best;
    } 
    else{
        int best = +100;
        for(vector<Node *>::size_type i = 0; i != temp_child.size(); i++){
                int temp = minimax(temp_child[i],true);
                best = min(best, temp);
        }
        return best;
    }
}

int main(int argc, char* argv[]){
    //FILE READING OPERATIONS
    //***********************
    ifstream ReadText(argv[1]);
    int grid[9][9];
    int x=0,y=0;
    for(x=0;x<9;x++){
        for(y=0;y<9;y++){
            ReadText>>grid[x][y];
            if(ReadText.eof())  break;
        }
        if(ReadText.eof())  break;
    }
    //***********************
    Node *root = new Node(grid);
    int result = minimax(root,true);
    if(result == 10)        cout << "1" << endl;
    else    cout << "2" <<endl;
    return 0;
}