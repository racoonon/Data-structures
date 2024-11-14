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
        if (fol == dest_ID) { // Followinglist 안에 존재
            found = true;
            break;
        }
    }
    
    if (!found) { // FollowingList에 아무것도 없을 수도 있으므로
        FollowingList.push_back(dest_ID);
    }

    return (!found);
}

bool Account::Add_follower(const string& dest_ID){ //add ID to the end of the follower list
    //TODO
    bool found = false;
    for (const auto& fol : FollowerList) {
        if (fol == dest_ID) { // Followerlist 안에 존재
            found = true;
            break;
        }
    }

    if (!found) { // FollowerList에 아무것도 없을 수도 있으므로
        FollowerList.push_back(dest_ID);
    }

    return (!found);
}

bool Account::Delete_following(const string& dest_ID){ //delete ID from following list
    //TODO
    bool found = false;
    for (auto it = FollowingList.begin(); it != FollowingList.end();) {
        if (*it == dest_ID) { // Followinglist안에 존재
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
        if (*it == dest_ID) { // Followinglist안에 존재
            FollowerList.erase(it);
            found = true;
            break;
        }
        // 오류 발생 가능성 지우기
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

    if (found) { // Accountlist 안에 존재
        cout << "ID: " << ID << " already exists." << endl;
        return;
    }
    else { // Accountlist 안에 존재하지 않음
        AccountList.push_back(Account(ID));
        return;
    }
}

void SNUverse::Delete_account(const string& ID) { //delete account with ID
    //TODO
    bool found = false;
    for (auto it = AccountList.begin(); it != AccountList.end();) {
        if (it->Get_ID() == ID) { // Followinglist안에 존재
            for (const auto& following : it->Get_followingList()) {
                Unfollow(it->Get_ID(), following); // 특정 account가 Following 하고 있던 애들
            }
            for (const auto& follower : it->Get_followerList()) {
                Unfollow(follower, it->Get_ID()); // 특정 account를 Follow하고 있던 애들
            }
            AccountList.erase(it);
            found = true;
            return;
        }
        else {
            ++it;
        }
    }

    // Accountlist 안에 존재하지 않음
    cout << "ID: " << ID << " does not exist." << endl;
    return;
}

void SNUverse::Follow(const string& src_ID, const string& dest_ID) { //If A follows B, In A's account: B is following, In B's account: A is follower
    //TODO
    // 둘 다 list안에 존재
    if (Get_account(src_ID) != AccountList.end() && Get_account(dest_ID) != AccountList.end()) {
        Get_account(src_ID)->Add_following(dest_ID);
        Get_account(dest_ID)->Add_follower(src_ID);
    }

    // 둘 중에 하나라도 없으면
    return;
}

void SNUverse::Unfollow(const string& src_ID, const string& dest_ID) {
    //TODO
    if (Get_account(src_ID) != AccountList.end() && Get_account(dest_ID) != AccountList.end()) { // 둘 다 list안에 존재
        Get_account(src_ID)->Delete_following(dest_ID);
        Get_account(dest_ID)->Delete_follower(src_ID);
    }

    // 둘 중에 하나라도 없으면
    return;
}

void SNUverse::Recommend_friend(const string& src_ID) { //print recommended friend list of src_ID
    //TODO
    vector <string> recVec; // recommend friend vector
    // accountlist안에 존재
    if (Get_const_account(src_ID) != AccountList.end()) {
        // ID의 following list - 1차
        for (auto it_first : Get_const_account(src_ID)->Get_followingList()) {
            // 1차 친구들의 following list - 2차
            for (auto it_second : Get_const_account(it_first)->Get_followingList()) {
                // 자기 자신이 아니면 일단 추가
                if (it_second != src_ID) {
                    recVec.push_back(it_second);
                }
            }
        }
        // 전부 추가 후 1차 following list랑 겹치는 거 제외
        for (auto rec = recVec.begin(); rec != recVec.end();) {
            bool found = false;
            for (auto it_first : Get_const_account(src_ID)->Get_followingList()) {
                // 겹치는 게 있으면 삭제
                if (it_first == *rec) {
                    rec = recVec.erase(rec); // 삭제 후 새로운 반복자를 얻음
                    found = true;
                    break;
                }
            }
            // 겹치지 않을 때 반복자 증가
            if (!found) {
                ++rec;
            }

        }

        // recVec 완료
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

    // list에 없으면 아무 일도 일어나지 않음
    return; 
}


void SNUverse::Common_friends(const string& src_ID, const string& dest_ID){ //print common friends of src_ID and dest_ID
    //TODO
    vector <string> comVec; // common friend vector
    // 둘 다 accountlist안에 존재
    if (Get_const_account(src_ID) != AccountList.end() && Get_const_account(dest_ID) != AccountList.end()) {
        // 공통된 친구 있으면 comVec에 추가
        for (auto it_A : Get_const_account(src_ID)->Get_followingList()) {
            for (auto it_B : Get_const_account(dest_ID)->Get_followingList()) {
                if (it_A == it_B) {
                    comVec.push_back(it_A);
                }
            }
        }

        // 공통된 친구 없음
        if (comVec.size() == 0) {
            cout << "No common friends between " << src_ID << " and " << dest_ID << "." << endl;
        }
        // 공통된 친구 있음
        else {
            cout << src_ID << " & " << dest_ID << ": ";
            for (auto it : comVec) {
                cout << it << " ";
            }
            cout << endl;
        }
    }

    // 둘 중 하나라도 없으면 아무 일도 일어나지 않음
    return; 
}

void SNUverse::Print(int mode) const{
    //Mode 0: Print following list of all accounts
    //Mode 1: Print follower list of all accounts
    //TODO
    if (mode == 0) { // followinglist
        for (const auto& it : AccountList) {
            if (it.Get_followingList().size() == 0) { // followinglist에 아무도 없을 때
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
            if (it.Get_followerList().size() == 0) { // followerlist에 아무도 없을 때
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
    // 둘 중 하나라도 accountlist안에 존재하지 않으면
    if (Get_const_account(src_ID) == AccountList.end())
        return false;
    if (Get_const_account(dest_ID) == AccountList.end())
        return false;

    // 둘 다 존재하면
    vector<string> visited;
    return dfs(src_ID, dest_ID, visited);
}

int SNUverse::Distance(const string& src_ID, const string& dest_ID) const { //through traversing following list
    //TODO
    // 둘 중 하나라도 accountlist에 존재하지 않거나 not reachable
    if (!isReachable(src_ID, dest_ID)) {
        return -1;
    }

    // src_ID == dest_ID
    if (src_ID == dest_ID) {
        return 0;
    }

    // 그 외에는 BFS 사용해 최단 거리 구하기
    vector<pair<string,int>> distQueue;
    vector<string> visited;

    distQueue.push_back({src_ID, 0});
    visited.push_back(src_ID);

    while (!distQueue.empty()) {
        auto current = distQueue.front(); // 맨 앞 요소 반환
        distQueue.erase(distQueue.begin()); // queue의 pop 역할


        // 최종 출력은 currentID == destID일 때의 distance
        const string& currentID = current.first;
        int currentDistance = current.second;

        if (currentID == dest_ID) { // 종료조건
            return currentDistance;
        }

        // followinglist 기반으로 BFS 진행
        for (const auto& it_first : Get_const_account(currentID)->Get_followingList()) {
            // it_first가 방문되었는지 확인 
            auto it = visited.end();
            for (auto iter = visited.begin(); iter != visited.end(); ++iter) {
                if (*iter == it_first) { // it_first가 visited 
                    it = iter;
                    break;
                }
            }
            // it_first가 visited되지 않았으면 queue에 추가
            // it_first가 visited 되었으면 아무 일도 일어나지 않음
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
    // 값을 찾지 못하면 end 반환하므로 초기에 end로 설정
    auto it = AccountList.end();

    for (auto iter = AccountList.begin(); iter != AccountList.end(); ++iter) {
        if (iter->Get_ID() == ID) {
            it = iter; // 값 찾은 후 해당 iter을 it에 저장 후 for문 종료
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
            const_it = iter; // 값 찾은 후 해당 iter을 const_it 저장 후 for문 종료
            break;
        }
    }

    return const_it;
}

bool SNUverse::dfs(const string& current, const string& dest_ID, vector<string>& visited) const{
    // 만약 같은 ID면 끝
    if (current == dest_ID) {
        return true;
    }
    
    // 그래프가 순환구조일 경우 무한 루프가 발생할 수 있다는 점 유의
    visited.push_back(current);

    for (const auto& it_first : Get_const_account(current)->Get_followingList()) {
        // 1차적으로 자신의 following list에 목적지 노드가 있는지 확인
        if (it_first == dest_ID) {
            return true;
        }

        // 이웃을 기반으로 방문하지 않은 것에 대해 DFS 호출
        auto it = visited.end();
        for (auto iter = visited.begin(); iter != visited.end(); ++iter) {
            if (*iter == it_first) { // it_first가 visited 
                it = iter;
                break;
            }
        }
        // it_first가 visited되지 않았으면 재귀 호출
        // it_first가 visited 되었으면 아무 일도 일어나지 않음
        if (it == visited.end()) {
            if (dfs(it_first, dest_ID, visited)) {
                return true;
            }
        }
    }

    // 목적지에 도달하지 못했음을 반환
    return false;
}