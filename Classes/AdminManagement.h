#pragma once

#include "Admin.h"
#include <list>
#include <fstream>
#include <direct.h>
using namespace std;

class AdminManagement
{
private:
    list<Admin> AdminMgm;
    int AdminNums;
public:
    AdminManagement(){
        InputAdminsFromFile();
        AdminNums=AdminMgm.size();
    }
    int get_AdminNums()
    {
        return AdminNums;
    }
    void AddAdmin(Admin &admin)
    {
        AdminMgm.push_back(admin);
        AdminNums++;
    }
    void DeleteAdmin(Admin &admin)
    {
        AdminMgm.remove(admin);
        AdminNums--;
    }
    void ModifyAdmin(Admin &oldAdmin, Admin &newAdmin)
    {
        DeleteAdmin(oldAdmin);
        AddAdmin(newAdmin);
    }
    bool FindAdmin(int account,Admin &ret)
    {
        for (list<Admin>::iterator it = AdminMgm.begin(); it != AdminMgm.end(); it++) {
            if (it->get_account() == account) {
                ret=*it;
                return true;
            }
        }
        return false;
    }
    bool LoginAdmin(int acc,string pas){
        Admin AdminToLogin;
        FindAdmin(acc,AdminToLogin);
        return AdminToLogin.Check(pas);
    }
    bool OutputAdminsToFile()
    {
        ofstream outfile;
        outfile.open("C:\\Users\\wuwei\\Desktop\\QT\\build-Library-Desktop_Qt_5_13_1_MinGW_64_bit-Debug\\debug\\Admin\\data.txt");
        list<Admin>::iterator it;
        for (it = AdminMgm.begin(); it != AdminMgm.end(); it++) {
            outfile << it->get_account() << "\t";
            outfile << it->get_password() << "\t";
            outfile << it->get_name() << "\t";
            outfile << it->get_id() << "\t";
            outfile << endl;
        }
        outfile.close();
        return true;
    }
    bool InputAdminsFromFile()
    {
        char data[1024];
        ifstream infile;
        infile.open("C:\\Users\\wuwei\\Desktop\\QT\\build-Library-Desktop_Qt_5_13_1_MinGW_64_bit-Debug\\debug\\Admin\\data.txt");
        while (!infile.eof()) {
            infile.getline(data, 200);
            string temp[20];
            int j = 0;
            for (int i = 0; data[i] != '\0'; i++) {
                if (data[i] != '\t') {
                    temp[j] += data[i];
                } else {
                    j++;
                    continue;
                }
            }
            // infile.close();
            Admin newAdmin(atoll(temp[0].c_str()), temp[1], temp[2], atoi(temp[3].c_str()));
            AddAdmin(newAdmin);
        }
        infile.close();
        AdminMgm.pop_back(); //删除最后一个空节点
        return true;
    }
};
