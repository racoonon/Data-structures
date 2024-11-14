//SNUverse.h
#pragma once

//You can feel free to add functions or variables if you want to.
//But, you should maintain the given functions and variables.
#include <vector>
#include <string>

using namespace std;

class Account {
public:
    Account(const string& ID); //constructor

    string Get_ID() const; //return ID
    vector<string> Get_followingList() const; //return following list
    vector<string> Get_followerList() const; //return follower list

    bool Add_following(const string& ID); //add ID to following list
    bool Add_follower(const string& ID); //add ID to follower list
    bool Delete_following(const string& ID); //delete ID from following list
    bool Delete_follower(const string& ID); //delete ID from follower list

private:
    string ID; //ID of account
    vector<string> FollowingList; //following list of account
    vector<string> FollowerList; //follower list of account
};

class SNUverse {
public:
    SNUverse(); //default constructor
    ~SNUverse(); //default destructor

    void Create_account(const string& ID); //create account with ID
    void Delete_account(const string& ID); //delete account with ID

    void Follow(const string& src_ID, const string& dest_ID);//If A follows B, In A's account: B is following, In B's account: A is follower
    void Unfollow(const string& src_ID, const string& dest_ID); 
    void Recommend_friend(const string& src_ID); //print recommended friend list of src_ID
    void Common_friends(const string& src_ID, const string& dest_ID); //print common friends of src_ID and dest_ID

    void Print(int mode) const ; //Print [mode- 0: following list, 1: follower list] of all accounts

    bool isReachable(const string& src_ID, const string& dest_ID) const; //through traversing followings
    int Distance(const string& src_ID, const string& dest_ID) const; //through traversing followings
    bool dfs(const string& current, const string& dest_ID, vector<string>& visited) const; // 개인적으로 추가

private:
    vector<Account> AccountList;

    vector<Account>::iterator Get_account(const string& ID); // return normal iterator
    vector<Account>::const_iterator Get_const_account(const string& ID) const; // return the const iterator
};
