// SNUverse.cpp
#include "SNUverse.h"
#include <iostream>
#include <utility> //You may use pair<T1, T2> if you want.

using namespace std;

//Account Implementation
Account::Account(const string& ID) : ID(ID) {}

string Account::Get_ID() const{ 
    return ID;
}

vector<string> Account::Get_followingList() const {
    return FollowingList;
}

vector<string> Account::Get_followerList() const {
    return FollowerList;
}


bool Account::Add_following(const string& dest_ID){ //add ID to the end of the following list
    //TODO
    bool found = false;
    for (const auto& fol : FollowingList) {
        if (fol == dest_ID) { // Followinglist �ȿ� ����
            found = true;
            break;
        }
    }
    
    if (!found) { // FollowingList�� �ƹ��͵� ���� ���� �����Ƿ�
        FollowingList.push_back(dest_ID);
    }

    return (!found);
}

bool Account::Add_follower(const string& dest_ID){ //add ID to the end of the follower list
    //TODO
    bool found = false;
    for (const auto& fol : FollowerList) {
        if (fol == dest_ID) { // Followerlist �ȿ� ����
            found = true;
            break;
        }
    }

    if (!found) { // FollowerList�� �ƹ��͵� ���� ���� �����Ƿ�
        FollowerList.push_back(dest_ID);
    }

    return (!found);
}

bool Account::Delete_following(const string& dest_ID){ //delete ID from following list
    //TODO
    bool found = false;
    for (auto it = FollowingList.begin(); it != FollowingList.end();) {
        if (*it == dest_ID) { // Followinglist�ȿ� ����
            FollowingList.erase(it);
            found = true;
            break;
        }
        else {
            ++it;
        }
    }

    return found;
}

bool Account::Delete_follower(const string& dest_ID) { //delete ID from follower list
    //TODO
    bool found = false;
    for (auto it = FollowerList.begin(); it != FollowerList.end();) {
        if (*it == dest_ID) { // Followinglist�ȿ� ����
            FollowerList.erase(it);
            found = true;
            break;
        }
        // ���� �߻� ���ɼ� �����
        else {
            ++it;
        }
    }

    return found;
}


//SNUverse implementation
SNUverse::SNUverse() {}

SNUverse::~SNUverse() {}

void SNUverse::Create_account(const string& ID) { //create account with ID
    //TODO
    bool found = false;
    for (auto it = AccountList.begin(); it != AccountList.end();) {
        if (it->Get_ID() == ID) {
            found = true;
            break;
        }
        else {
            ++it;
        }
    }

    if (found) { // Accountlist �ȿ� ����
        cout << "ID: " << ID << " already exists." << endl;
        return;
    }
    else { // Accountlist �ȿ� �������� ����
        AccountList.push_back(Account(ID));
        return;
    }
}

void SNUverse::Delete_account(const string& ID) { //delete account with ID
    //TODO
    bool found = false;
    for (auto it = AccountList.begin(); it != AccountList.end();) {
        if (it->Get_ID() == ID) { // Followinglist�ȿ� ����
            for (const auto& following : it->Get_followingList()) {
                Unfollow(it->Get_ID(), following); // Ư�� account�� Following �ϰ� �ִ� �ֵ�
            }
            for (const auto& follower : it->Get_followerList()) {
                Unfollow(follower, it->Get_ID()); // Ư�� account�� Follow�ϰ� �ִ� �ֵ�
            }
            AccountList.erase(it);
            found = true;
            return;
        }
        else {
            ++it;
        }
    }

    // Accountlist �ȿ� �������� ����
    cout << "ID: " << ID << " does not exist." << endl;
    return;
}

void SNUverse::Follow(const string& src_ID, const string& dest_ID) { //If A follows B, In A's account: B is following, In B's account: A is follower
    //TODO
    // �� �� list�ȿ� ����
    if (Get_account(src_ID) != AccountList.end() && Get_account(dest_ID) != AccountList.end()) {
        Get_account(src_ID)->Add_following(dest_ID);
        Get_account(dest_ID)->Add_follower(src_ID);
    }

    // �� �߿� �ϳ��� ������
    return;
}

void SNUverse::Unfollow(const string& src_ID, const string& dest_ID) {
    //TODO
    if (Get_account(src_ID) != AccountList.end() && Get_account(dest_ID) != AccountList.end()) { // �� �� list�ȿ� ����
        Get_account(src_ID)->Delete_following(dest_ID);
        Get_account(dest_ID)->Delete_follower(src_ID);
    }

    // �� �߿� �ϳ��� ������
    return;
}

void SNUverse::Recommend_friend(const string& src_ID) { //print recommended friend list of src_ID
    //TODO
    vector <string> recVec; // recommend friend vector
    // accountlist�ȿ� ����
    if (Get_const_account(src_ID) != AccountList.end()) {
        // ID�� following list - 1��
        for (auto it_first : Get_const_account(src_ID)->Get_followingList()) {
            // 1�� ģ������ following list - 2��
            for (auto it_second : Get_const_account(it_first)->Get_followingList()) {
                // �ڱ� �ڽ��� �ƴϸ� �ϴ� �߰�
                if (it_second != src_ID) {
                    recVec.push_back(it_second);
                }
            }
        }
        // ���� �߰� �� 1�� following list�� ��ġ�� �� ����
        for (auto rec = recVec.begin(); rec != recVec.end();) {
            bool found = false;
            for (auto it_first : Get_const_account(src_ID)->Get_followingList()) {
                // ��ġ�� �� ������ ����
                if (it_first == *rec) {
                    rec = recVec.erase(rec); // ���� �� ���ο� �ݺ��ڸ� ����
                    found = true;
                    break;
                }
            }
            // ��ġ�� ���� �� �ݺ��� ����
            if (!found) {
                ++rec;
            }

        }

        // recVec �Ϸ�
        if (recVec.size() == 0){
            cout << "No recommendation for " << src_ID << "." << endl;
        }
        else {
            cout << src_ID << ": ";
            for (auto rec : recVec) {
                cout << rec << " ";
            }
            cout << endl;
        }
    }

    // list�� ������ �ƹ� �ϵ� �Ͼ�� ����
    return; 
}


void SNUverse::Common_friends(const string& src_ID, const string& dest_ID){ //print common friends of src_ID and dest_ID
    //TODO
    vector <string> comVec; // common friend vector
    // �� �� accountlist�ȿ� ����
    if (Get_const_account(src_ID) != AccountList.end() && Get_const_account(dest_ID) != AccountList.end()) {
        // ����� ģ�� ������ comVec�� �߰�
        for (auto it_A : Get_const_account(src_ID)->Get_followingList()) {
            for (auto it_B : Get_const_account(dest_ID)->Get_followingList()) {
                if (it_A == it_B) {
                    comVec.push_back(it_A);
                }
            }
        }

        // ����� ģ�� ����
        if (comVec.size() == 0) {
            cout << "No common friends between " << src_ID << " and " << dest_ID << "." << endl;
        }
        // ����� ģ�� ����
        else {
            cout << src_ID << " & " << dest_ID << ": ";
            for (auto it : comVec) {
                cout << it << " ";
            }
            cout << endl;
        }
    }

    // �� �� �ϳ��� ������ �ƹ� �ϵ� �Ͼ�� ����
    return; 
}

void SNUverse::Print(int mode) const{
    //Mode 0: Print following list of all accounts
    //Mode 1: Print follower list of all accounts
    //TODO
    if (mode == 0) { // followinglist
        for (const auto& it : AccountList) {
            if (it.Get_followingList().size() == 0) { // followinglist�� �ƹ��� ���� ��
                cout << it.Get_ID() << " has no followings.";
            }
            else {
                cout << it.Get_ID() << ": ";
                for (const auto& fol : it.Get_followingList()) {
                    cout << fol << " ";
                }
            }
            cout << endl;
        }
    }
    else if (mode == 1) { // followerlist
        for (const auto& it : AccountList) {
            if (it.Get_followerList().size() == 0) { // followerlist�� �ƹ��� ���� ��
                cout << it.Get_ID() << " has no followers.";
            }
            else {
                cout << it.Get_ID() << ": ";
                for (const auto& fol : it.Get_followerList()) {
                    cout << fol << " ";
                }
            }
            cout << endl;
        }
    }
}

bool SNUverse::isReachable(const string& src_ID, const string& dest_ID) const { //through traversing following list
    //TODO
    // �� �� �ϳ��� accountlist�ȿ� �������� ������
    if (Get_const_account(src_ID) == AccountList.end())
        return false;
    if (Get_const_account(dest_ID) == AccountList.end())
        return false;

    // �� �� �����ϸ�
    vector<string> visited;
    return dfs(src_ID, dest_ID, visited);
}

int SNUverse::Distance(const string& src_ID, const string& dest_ID) const { //through traversing following list
    //TODO
    // �� �� �ϳ��� accountlist�� �������� �ʰų� not reachable
    if (!isReachable(src_ID, dest_ID)) {
        return -1;
    }

    // src_ID == dest_ID
    if (src_ID == dest_ID) {
        return 0;
    }

    // �� �ܿ��� BFS ����� �ִ� �Ÿ� ���ϱ�
    vector<pair<string,int>> distQueue;
    vector<string> visited;

    distQueue.push_back({src_ID, 0});
    visited.push_back(src_ID);

    while (!distQueue.empty()) {
        auto current = distQueue.front(); // �� �� ��� ��ȯ
        distQueue.erase(distQueue.begin()); // queue�� pop ����


        // ���� ����� currentID == destID�� ���� distance
        const string& currentID = current.first;
        int currentDistance = current.second;

        if (currentID == dest_ID) { // ��������
            return currentDistance;
        }

        // followinglist ������� BFS ����
        for (const auto& it_first : Get_const_account(currentID)->Get_followingList()) {
            // it_first�� �湮�Ǿ����� Ȯ�� 
            auto it = visited.end();
            for (auto iter = visited.begin(); iter != visited.end(); ++iter) {
                if (*iter == it_first) { // it_first�� visited 
                    it = iter;
                    break;
                }
            }
            // it_first�� visited���� �ʾ����� queue�� �߰�
            // it_first�� visited �Ǿ����� �ƹ� �ϵ� �Ͼ�� ����
            if (it == visited.end()) {
                distQueue.push_back({it_first, currentDistance + 1 });
                visited.push_back(it_first);
            }
        }
    }
    return -1; 
}

vector<Account>::iterator SNUverse::Get_account(const string& ID){ //return normal iterator
    //TODO
    // ���� ã�� ���ϸ� end ��ȯ�ϹǷ� �ʱ⿡ end�� ����
    auto it = AccountList.end();

    for (auto iter = AccountList.begin(); iter != AccountList.end(); ++iter) {
        if (iter->Get_ID() == ID) {
            it = iter; // �� ã�� �� �ش� iter�� it�� ���� �� for�� ����
            break;
        }
    }
    
    return it;
}

vector<Account>::const_iterator SNUverse::Get_const_account(const string& ID) const{ //return the const iterator
    //TODO
    auto const_it = AccountList.end();

    for (auto iter = AccountList.begin(); iter != AccountList.end(); ++iter) {
        if (iter->Get_ID() == ID) {
            const_it = iter; // �� ã�� �� �ش� iter�� const_it ���� �� for�� ����
            break;
        }
    }

    return const_it;
}

bool SNUverse::dfs(const string& current, const string& dest_ID, vector<string>& visited) const{
    // ���� ���� ID�� ��
    if (current == dest_ID) {
        return true;
    }
    
    // �׷����� ��ȯ������ ��� ���� ������ �߻��� �� �ִٴ� �� ����
    visited.push_back(current);

    for (const auto& it_first : Get_const_account(current)->Get_followingList()) {
        // 1�������� �ڽ��� following list�� ������ ��尡 �ִ��� Ȯ��
        if (it_first == dest_ID) {
            return true;
        }

        // �̿��� ������� �湮���� ���� �Ϳ� ���� DFS ȣ��
        auto it = visited.end();
        for (auto iter = visited.begin(); iter != visited.end(); ++iter) {
            if (*iter == it_first) { // it_first�� visited 
                it = iter;
                break;
            }
        }
        // it_first�� visited���� �ʾ����� ��� ȣ��
        // it_first�� visited �Ǿ����� �ƹ� �ϵ� �Ͼ�� ����
        if (it == visited.end()) {
            if (dfs(it_first, dest_ID, visited)) {
                return true;
            }
        }
    }

    // �������� �������� �������� ��ȯ
    return false;
}