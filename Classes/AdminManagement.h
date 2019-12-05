#pragma once

#include "Admin.h"
#include <list>
#include <fstream>
#include <QFileDialog>
#include "QTextStream"
using namespace std;

class AdminManagement
{
private:
    list<Admin> AdminMgm;       //管理员列表
    int AdminNums;              //管理员总数
public:
    AdminManagement(){          //从文件构造
        InputAdminsFromFile();
        AdminNums=static_cast<int>((AdminMgm.size()));
    }
    int get_AdminNums()         //返回管理员数
    {
        return AdminNums;
    }
    void AddAdmin(Admin &admin) //新增管理员
    {
        AdminMgm.push_front(admin);
        AdminNums++;
    }
    void DeleteAdmin(int acc) //删除管理员
    {
        Admin temp;
        FindAdmin(acc,temp);
        AdminMgm.remove(temp);
        AdminNums--;
    }
    void DeleteAdmin(Admin &admin) //删除管理员
    {
        AdminMgm.remove(admin);
        AdminNums--;
    }
    void ModifyAdmin(Admin &oldAdmin, Admin &newAdmin)  //修改管理员
    {
        DeleteAdmin(oldAdmin);
        AddAdmin(newAdmin);
    }
    bool FindAdmin(int account,Admin &ret)  //按账号查找
    {
        for (list<Admin>::iterator it = AdminMgm.begin(); it != AdminMgm.end(); it++) {
            if (it->get_account() == account) {
                ret=*it;
                return true;
            }
        }
        return false;
    }
    bool FindAdmin(int account,Admin **ret)  //按账号查找
    {
        for (list<Admin>::iterator it = AdminMgm.begin(); it != AdminMgm.end(); it++) {
            if (it->get_account() == account) {
                *ret=&(*it);
                return true;
            }
        }
        return false;
    }
//    bool FindAdminByid(int id,Admin &ret)  //按工号查找
//    {
//        for (list<Admin>::iterator it = AdminMgm.begin(); it != AdminMgm.end(); it++) {
//            if (it->get_id() == id) {
//                ret=*it;
//                return true;
//            }
//        }
//        return false;
//    }
//    bool FindAdminByName(string name,Admin &ret)  //按姓名查找
//    {
//        for (list<Admin>::iterator it = AdminMgm.begin(); it != AdminMgm.end(); it++) {
//            if (it->get_name() == name) {
//                ret=*it;
//                return true;
//            }
//        }
//        return false;
//    }
    Admin& get_Admin_ByIndex(int i)
    {
        list<Admin>::iterator it=AdminMgm.begin();
        while(i--){
            it++;
        }
        return *it;
    }
    bool LoginAdmin(int acc,string pas) //管理系统登陆
    {
        Admin AdminToLogin;
        FindAdmin(acc,AdminToLogin);
        return AdminToLogin.Check(pas);
    }
    void ChangePas(Admin& ad,string pas)
    {
        Admin newad=ad;
        newad.set_password(pas);
        ModifyAdmin(ad,newad);
    }

    bool OutputAdminsToFile()       //将数据存储到文件
    {
        QFile file("admin_data.txt");
        file.open(QIODevice::WriteOnly);        //使用writeonly访问清空文件
        file.close();
        if (file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QTextStream stream(&file);
            stream.seek(file.size());
            stream.setCodec("utf-8");
            list<Admin>::iterator it;
            for (it = AdminMgm.begin(); it != AdminMgm.end(); it++) {
                stream << it->get_id() << "\t";
                stream << it->get_account() << "\t";
                stream << QString::fromStdString(it->get_name()) << "\t";
                stream << QString::fromStdString(it->get_password()) << "\t";
                stream << endl;
            }
            file.close();
        }

        //        ofstream outfile;
        //        outfile.open(":/data/Classes/Data/admin_data.txt");
        //        if(!outfile.is_open()){
        //            throw "GG";
        //        }
        //        list<Admin>::iterator it;
        //        for (it = AdminMgm.begin(); it != AdminMgm.end(); it++) {
        //            outfile << it->get_account() << "\t";
        //            outfile << it->get_password() << "\t";
        //            outfile << it->get_name() << "\t";
        //            outfile << it->get_id() << "\t";
        //            outfile << endl;
        //        }
        //        outfile.close();
        return true;
    }
    bool InputAdminsFromFile()      //从文件读取数据
    {
        AdminNums=0;
        AdminMgm.clear();
        QFile file("admin_data.txt");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            while (!file.atEnd())
            {
                QByteArray line = file.readLine();
                QString data(line);
                //string data=str.toStdString();
                QString temp[20];
                int j = 0;
                for (int i = 0; data[i] != '\0'; i++) {
                    if (data[i] != '\t') {
                        temp[j] += data[i];
                    } else {
                        j++;
                        continue;
                    }
                }
                Admin newAdmin(temp[0].toInt(), temp[1].toInt(), temp[2].toStdString(), temp[3].toStdString());
                AddAdmin(newAdmin);
            }
            file.close();
        }

        //        char data[1024];
        //        ifstream infile;
        //        infile.open(":/data/Classes/Data/admin_data.txt");
        //        if(!infile.is_open()){
        //            throw "GG";
        //        }
        //        while (!infile.eof()) {
        //            infile.getline(data, 200);
        //            string temp[20];
        //            int j = 0;
        //            for (int i = 0; data[i] != '\0'; i++) {
        //                if (data[i] != '\t') {
        //                    temp[j] += data[i];
        //                } else {
        //                    j++;
        //                    continue;
        //                }
        //            }
        //            // infile.close();

        //        }
        //        infile.close();
        // AdminMgm.pop_back(); //删除最后一个空节点
        return true;
    }
};
