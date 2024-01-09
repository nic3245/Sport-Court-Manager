

#ifndef Repository_h
#define Repository_h


#include <vector>
#include <algorithm>
#include <string>
using namespace std;

template <typename T>
class Repository {

private:
    vector<T>  repo;

public:

    Repository() {}

    vector<T> getAll(){return repo;}
    //pushes an object into the repo object
    void push(T object){
        //update if the item is allready there
        bool is_new_object = true;
        for (int i = 0; i < repo.size(); i++) {
            T old_object = repo[i];
            if(old_object == object){
                repo[i] = object;
                is_new_object = false;
            }
        }
        //add new object
        if(is_new_object){
            repo.push_back(object);
        }
    }
    //pushes multiple items into the vector
    void push_items(vector<T>  repo_in){
        for(int i=0; i < repo_in.size();i++){
            push(repo_in[i]);
        }
    }


    //removes a object from the vector
    void remove(T object){
        for (int i = 0; i < repo.size(); i++) {
            T old_object = repo[i];
            if(old_object == object){
                repo.erase(repo.begin() + i);
            }
        }
    }


    //removes multiple items from the vector
    void remove_items(vector<T>  repo_in){
        for(int i=0; i < repo_in.size();i++){
            remove(repo_in[i]);
        }
    }
    //returns the size of the vector
    int item_count(){
        return repo.size();
    }


};





#endif

