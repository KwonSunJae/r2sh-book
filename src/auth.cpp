
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


class Users{
    public:
    string uId;
    string uName;
    vector<string> uR2shs;
    string uPenalty;
    Users(){
        vector<string> t;
        Users("","",t,"0000-00-00");
    };
    Users(string uid, string uname, vector<string> ur2shs, string upenalty){
        uId = uid;
        uName= uname;
        for (int i=0; i<ur2shs.size(); i++){
            uR2shs.push_back(ur2shs[i]);
        }
        uPenalty = upenalty;

    }
};
class userService{
public:
    vector<Users> list;
    int n;
    
};
int main (int argc, char** argv){

    

}