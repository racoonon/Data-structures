//You can use this main function to test your code.
//You can change this main function as you want.
//We will not grade your main function
//Do not include this main function when you submit your code.
#include <iostream>
#include "SNUverse.h"
#include <string>

using namespace std;

int main(){
    string cmd;
    string src_id, dest_id;
    int mode;
    SNUverse verse = SNUverse();
    while (1){
        cin >> cmd;
        if (cmd == "create") {
            cin >> src_id;
            verse.Create_account(src_id);
        }
        else if (cmd == "delete") {
            cin >> src_id;
            verse.Delete_account(src_id);
        }
        else if (cmd == "print"){
            cin >> mode;
            verse.Print(mode);
        }
        else if (cmd == "follow"){
            cin >> src_id >> dest_id ;
            verse.Follow(src_id, dest_id);
        }
        else if (cmd == "unfollow"){
            cin >> src_id >> dest_id ;
            verse.Unfollow(src_id, dest_id);
        }
        else if (cmd == "recommend"){
            cin >> src_id;
            verse.Recommend_friend(src_id);
        }
        else if (cmd == "common"){
            cin >> src_id >> dest_id;
            verse.Common_friends(src_id, dest_id);
        }
        else if (cmd == "isreachable"){
            cin >> src_id >> dest_id;
            cout << verse.isReachable(src_id, dest_id) << endl;
        }
        else if (cmd == "distance"){
            cin >> src_id >> dest_id;
            cout << verse.Distance(src_id, dest_id) << endl;
        }
        else if (cmd == "exit"){
            return 0;
        }
    }
    return 0;
}