//------------------------------------
// Created by Linghan 2017-01-03
//------------------------------------

#include <QApplication>
#include <QTime>
#include <Windows.h>
#include <time.h>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlError>
#include <QtSql>

#include "function.h"
#include "mainwindow.h"

#define getcolor(i,j,k) frame.at<Vec3b>(i,j)[k]
#define gettime() clock() / CLOCKS_PER_SEC

using namespace std;
using namespace cv;

const int tracking_avi_w = 1017;
const int tracking_avi_h = 648;
const int plan_avi_w = 312;
const int plan_avi_h = 500;
vector<PlayerRec> vector_null;
bool isInit[2] = { false, false };
vector<PlayerRec> last_frame_pos[2];
int imgIndex;

//----------SQL USAGE GLOBALS-----------
QSqlDatabase db;
int posses[25]={0};
int now_posses=-1,last_posses=-1;
int second_posses = -1;
int Distance;
int Player_distance;
int out_flag=-1;
int doorkeeper_flag = -1;
int event=1;
int tranflag=0;
int against_flag = 0;
int success_flag = 0;

SYSTEMTIME operator-(const SYSTEMTIME& pSr, const SYSTEMTIME& pSl)
{
    SYSTEMTIME t_res;
    FILETIME v_ftime;
    ULARGE_INTEGER v_ui;
    __int64 v_right, v_left, v_res;
    SystemTimeToFileTime(&pSr, &v_ftime);
    v_ui.LowPart = v_ftime.dwLowDateTime;
    v_ui.HighPart = v_ftime.dwHighDateTime;
    v_right = v_ui.QuadPart;

    SystemTimeToFileTime(&pSl, &v_ftime);
    v_ui.LowPart = v_ftime.dwLowDateTime;
    v_ui.HighPart = v_ftime.dwHighDateTime;
    v_left = v_ui.QuadPart;

    v_res = v_right - v_left;

    v_ui.QuadPart = v_res;
    v_ftime.dwLowDateTime = v_ui.LowPart;
    v_ftime.dwHighDateTime = v_ui.HighPart;
    FileTimeToSystemTime(&v_ftime, &t_res);
    return t_res;
}

//-----------------SQL FEATURES-------------------------
void SQL_WholeChart_init()
{
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("mysql");
    db.setUserName("root");
    db.setPassword("TrackingPro");
    if(!db.open())
    {
        qDebug()<<"Error"<<db.lastError().text();
        exit(0);
    }
    QSqlQuery query(db);
    query=QSqlQuery::QSqlQuery(db);
    QString SQLString;
    SQLString="DROP TABLE IF EXISTS position";

    if(query.exec(SQLString))
    {
        cout<<"delete table success"<<endl;
    }
    else
    {
        cout<<"delete table failed"<<endl;
        db.close();
        exit(0);
    }
    SQLString="CREATE TABLE IF NOT EXISTS position (FRAME INTEGER NOT NULL, X1 FLOAT, Y1 FLOAT, X2 FLOAT, Y2 FLOAT, X3 FLOAT, Y3 FLOAT, X4 FLOAT, \
            Y4 FLOAT, X5 FLOAT, Y5 FLOAT, X6 FLOAT, Y6 FLOAT, X7 FLOAT, Y7  FLOAT, X8 FLOAT, Y8 FLOAT, X9 FLOAT, Y9 FLOAT, X10 FLOAT, Y10 FLOAT, X11 FLOAT, Y11 FLOAT, X12 FLOAT, Y12 FLOAT,X13 FLOAT, Y13 FLOAT, X14 FLOAT,Y14 FLOAT,X15 FLOAT,Y15 FLOAT,X16 FLOAT,Y16 FLOAT,X17 FLOAT,Y17 FLOAT, \
                        X18 FLOAT, Y18 FLOAT,X19 FLOAT, Y19 FLOAT, X20 FLOAT,Y20 FLOAT,X21 FLOAT,Y21 FLOAT,X22 FLOAT,Y22 FLOAT,X23 FLOAT,Y23 FLOAT,X24 FLOAT,Y24 FLOAT,X25 FLOAT,Y25 FLOAT,X26 FLOAT,Y26 FLOAT,X27 FLOAT,Y27 FLOAT,X28 FLOAT,Y28 FLOAT,X29 FLOAT,Y29 FLOAT,X30 FLOAT,Y30 FLOAT,TAG INTEGER NOT NULL, VIDEO INTEGER NOT NULL, PRIMARY KEY(TAG,VIDEO,FRAME));";
    if(query.exec(SQLString))
    {
        cout<<"create table 1 success"<<endl;
    }
    else
    {
        cout<<"create table 1 failed"<<endl;
        db.close();
        exit(0);
    }
    SQLString = "DROP TABLE IF EXISTS PlayerEvent";
    if (query.exec(SQLString))
    {
        cout << "delete table succeed" << endl;
    }
    else
    {
        cout << "delete table failed" << endl;
        db.close();
        exit(0);
    }
	SQLString = "CREATE TABLE IF NOT EXISTS PlayerEvent (ID INTEGER NOT NULL PRIMARY KEY AUTO_INCREMENT,TYPE INTEGER,PLAYER1 INTEGER,X1 FLOAT,Y1 FLOAT,PLAYER2 INTEGER,\
        X2 FLOAT,Y2 FLOAT,FRAME INTEGER,TAG INTEGER NOT NULL,VIDEO INTEGER NOT NULL, AGAINST INTEGER NOT NULL, SUCCESS INTEGER NOT NULL, LOOSE INTEGER NOT NULL);";
    if(query.exec(SQLString))
    {
        cout << "create table 2 succeed" << endl;
    }
    else
    {
        cout << "create table 2 failed" << endl;
        db.close();
        exit(0);
    }
    SQLString = "DROP TABLE IF EXISTS count";
    if (query.exec(SQLString))
    {
        cout << "delete table succeed" << endl;
    }
    else
    {
        cout << "delete table failed" << endl;
        db.close();
        exit(0);
    }
    SQLString = "CREATE TABLE IF NOT EXISTS count (TYPE INTEGER NOT NULL PRIMARY KEY AUTO_INCREMENT,\
                                    P1 INTEGER,P2 INTEGER,P3 INTEGER,P4 INTEGER,P5 INTEGER,P6 INTEGER,P7 INTEGER,P8 INTEGER,P9 INTEGER,P10 INTEGER,\
                                                                            P11 INTEGER,P12 INTEGER,P13 INTEGER,P14 INTEGER,P15 INTEGER,P16 INTEGER,P17 INTEGER,P18 INTEGER,P19 INTEGER,P20 INTEGER,\
                                                                                                                                                        P21 INTEGER,P22 INTEGER,P23 INTEGER,P24 INTEGER,P25 INTEGER,P26 INTEGER,P27 INTEGER,P28 INTEGER,P29 INTEGER,P30 INTEGER);";
    if (query.exec(SQLString))
    {
        cout << "create table 3 succeed" << endl;
    }
    else
    {
        cout << "create table 3 failed" << endl;
        db.close();
        exit(0);
    }
    stringstream strStream;

    for (int i = 0; i < 61; i++){
        SQLString = "insert into count values(";
        strStream.str("");
        strStream << i + 1;
        string temp="";
        temp+=strStream.str();
        QString numString=QString::fromStdString(temp);
        SQLString += numString;
        SQLString+=",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);";
        if(query.exec(SQLString))
        {
            cout<<"table line "<<i<<" complete"<<endl;
        }
        else
        {
            cout<<"table line "<<i<<" failed"<<endl;
            db.close();
            exit(0);
        }
    }
}
void SQL_init(string FileName)
{
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("mysql");
    db.setUserName("root");
    db.setPassword("TrackingPro");
    if(!db.open())
    {
        qDebug()<<"Error"<<db.lastError().text();
        exit(0);
    }
    QSqlQuery query(db);
    query=QSqlQuery::QSqlQuery(db);
    QString SQLString;
    QString FileNameString=QString::fromStdString(FileName);
    cout<<FileName<<endl;
    SQLString="DROP TABLE IF EXISTS "+FileNameString+"_position";

    if(query.exec(SQLString))
    {
        cout<<"delete table success"<<endl;
    }
    else
    {
        cout<<"delete table failed"<<endl;
        db.close();
        exit(0);
    }
    SQLString="CREATE TABLE IF NOT EXISTS "+FileNameString+"_position (FRAME INTEGER NOT NULL PRIMARY KEY AUTO_INCREMENT, X1 FLOAT, Y1 FLOAT, X2 FLOAT, Y2 FLOAT, X3 FLOAT, Y3 FLOAT, X4 FLOAT, \
            Y4 FLOAT, X5 FLOAT, Y5 FLOAT, X6 FLOAT, Y6 FLOAT, X7 FLOAT, Y7  FLOAT, X8 FLOAT, Y8 FLOAT, X9 FLOAT, Y9 FLOAT, X10 FLOAT, Y10 FLOAT, X11 FLOAT, Y11 FLOAT, X12 FLOAT, Y12 FLOAT,X13 FLOAT, Y13 FLOAT, X14 FLOAT,Y14 FLOAT,X15 FLOAT,Y15 FLOAT,X16 FLOAT,Y16 FLOAT,X17 FLOAT,Y17 FLOAT, \
                        X18 FLOAT, Y18 FLOAT,X19 FLOAT, Y19 FLOAT, X20 FLOAT,Y20 FLOAT,X21 FLOAT,Y21 FLOAT,X22 FLOAT,Y22 FLOAT,X23 FLOAT,Y23 FLOAT,X24 FLOAT,Y24 FLOAT,X25 FLOAT,Y25 FLOAT,X26 FLOAT,Y26 FLOAT,X27 FLOAT,Y27 FLOAT,X28 FLOAT,Y28 FLOAT,X29 FLOAT,Y29 FLOAT,X30 FLOAT,Y30 FLOAT);";
    if(query.exec(SQLString))
    {
        cout<<"create table 1 success"<<endl;
    }
    else
    {
        cout<<"create table 1 failed"<<endl;
        db.close();
        exit(0);
    }
    SQLString = "DROP TABLE IF EXISTS "+FileNameString+"_PlayerEvent";
    if (query.exec(SQLString))
    {
        cout << "delete table succeed" << endl;
    }
    else
    {
        cout << "delete table failed" << endl;
        db.close();
        exit(0);
    }
    SQLString = "CREATE TABLE IF NOT EXISTS "+FileNameString+"_PlayerEvent (ID INTEGER NOT NULL PRIMARY KEY AUTO_INCREMENT,TYPE INTEGER,		\
                                    PLAYER1 INTEGER,X1 FLOAT,Y1 FLOAT,PLAYER2 INTEGER,X2 FLOAT,Y2 FLOAT,FRAME INTEGER,  AGAINST INTEGER NOT NULL, SUCCESS INTEGER NOT NULL);";
    if (query.exec(SQLString))
    {
        cout << "create table 2 succeed" << endl;
    }
    else
    {
        cout << "create table 2 failed" << endl;
        db.close();
        exit(0);
    }
    SQLString = "DROP TABLE IF EXISTS "+FileNameString+"_count";
    if (query.exec(SQLString))
    {
        cout << "delete table succeed" << endl;
    }
    else
    {
        cout << "delete table failed" << endl;
        db.close();
        exit(0);
    }
}
void SQL_Process(string FileName)
{
    QSqlQuery query(db);
    query=QSqlQuery::QSqlQuery(db);
    QString SQLString;
    QString ParamString;
    stringstream strStream;
    QString FileNameString=QString::fromStdString(FileName);

    for(int i=0;i<imgIndex;i++)
    {
        last_posses=now_posses;
        int min=100000;
		int second_min = 2000000;
        SQLString="insert into "+FileNameString+"_position values(";
        strStream.str("");
        strStream<<i+1;
        //FULFILL
        for(int j=0;j<23;j++)
        {
            strStream<<","<<players[i][j].y_trans<<","<<players[i][j].x_trans;
        }
        for(int j=0;j<7;j++)
        {
            strStream<<","<<0;
            strStream<<","<<0;
        }
        strStream<<");";
        QString ParamStr=QString::fromStdString(strStream.str());
        SQLString+=ParamStr;
       if(query.exec(SQLString))
       {
           cout<<"Index "<<i<<" input complete"<<endl;
       }
       else
       {
           cout<<"Index "<<i<<" input failed"<<endl;
           db.close();
           exit(0);
           
       }
        //DISTANCE CHECK
	   
        for(int j=1;j<23;j++)
        {
            if(TrackingStatus[j]!=REGULAR)continue;
            Distance=(players[i][j].y_trans-players[i][0].y_trans)*(players[i][j].y_trans-players[i][0].y_trans)+
                    (players[i][j].x_trans-players[i][0].x_trans)*(players[i][j].x_trans-players[i][0].x_trans);
			
            if(Distance<min)
            {
                min=Distance;
                now_posses=j;
            }
			if (Distance<second_min && Distance>min)
			{
				second_min = Distance;
				second_posses = j;
			}
        }
        Player_distance = (players[i][now_posses].y_trans - players[i][second_posses].y_trans)*(players[i][now_posses].y_trans - players[i][second_posses].y_trans) +
			(players[i][now_posses].x_trans - players[i][second_posses].x_trans)*(players[i][now_posses].x_trans - players[i][second_posses].x_trans);
        //POSSESSION CHECK
        if(now_posses==-1)continue;
        if(last_posses==-1)last_posses=now_posses;
        if(players[i][now_posses].type == 0){
			if (abs(players[i][now_posses].type - players[i][last_posses].type) > 1) {
				SQLString = "insert into " + FileNameString + "_PlayerEvent (ID,TYPE,PLAYER1,X1,Y1,PLAYER2,X2,Y2,FRAME,AGAINST,SUCCESS)values(";
				strStream.str("");
				strStream << event++ << "," << 13 << "," << now_posses << "," << players[i][now_posses].y_trans << "," << players[i][now_posses].x_trans;
				strStream << "," << -1 << "," << -1 << "," << -1 << "," << i + 1 << ",";
				if (abs(players[i][now_posses].type - players[i][second_posses].type) > 1 && Player_distance < 100) {
					against_flag = 1;
				}
				success_flag = 1;
				strStream << against_flag << "," << success_flag << ");";
				QString ParamStr = QString::fromStdString(strStream.str());
				SQLString += ParamStr;
                cout<<SQLString.toStdString()<<endl;
				if (query.exec(SQLString))
				{
					cout << "PASSING INPUT " << last_posses << " " << now_posses << endl;
				}
				else
				{
					cout << "PASSING INPUT FAILED" << endl;
					db.close();
					exit(0);
				}
				//update MyClass set name='Mary' where id=1;
                SQLString = "update count set ";
				strStream.str("");
				strStream << "P" << now_posses << "= P" << now_posses << "+ 1 where type = " << 13 << ";";
                ParamStr = QString::fromStdString(strStream.str());
				SQLString += ParamStr;
                cout<<SQLString.toStdString()<<endl;
				if (query.exec(SQLString))
				{
					cout << "PASSING INPUT " << last_posses << " " << now_posses << endl;
				}
				else
				{
					cout << "PASSING INPUT FAILED" << endl;
					db.close();
					exit(0);
				}
			}
			else {
				SQLString = "insert into " + FileNameString + "_PlayerEvent (ID,TYPE,PLAYER1,X1,Y1,PLAYER2,X2,Y2,FRAME,AGAINST,SUCCESS)values(";
				strStream.str("");
				strStream << event++ << "," << 15 << "," << now_posses << "," << players[i][now_posses].y_trans << "," << players[i][now_posses].x_trans;
				strStream << "," << -1 << "," << -1 << "," << -1 << "," << i + 1 << ",";
				if (abs(players[i][now_posses].type - players[i][second_posses].type) > 1 && Player_distance < 100) {
					against_flag = 1;
				}
				success_flag = 1;
				strStream << against_flag << "," << success_flag << ");";
				QString ParamStr = QString::fromStdString(strStream.str());
				SQLString += ParamStr;
                cout<<SQLString.toStdString()<<endl;
				if (query.exec(SQLString))
				{
					cout << "PASSING INPUT " << last_posses << " " << now_posses << endl;
				}
				else
				{
					cout << "PASSING INPUT FAILED" << endl;
					db.close();
					exit(0);
				}
                SQLString = "update count set ";
				strStream.str("");
				strStream << "P" << now_posses << "= P" << now_posses << "+ 1 where type = " << 15 << ";";
                ParamStr = QString::fromStdString(strStream.str());
				SQLString += ParamStr;
                cout<<SQLString.toStdString()<<endl;
				if (query.exec(SQLString))
				{
					cout << "PASSING INPUT " << last_posses << " " << now_posses << endl;
				}
				else
				{
					cout << "PASSING INPUT FAILED" << endl;
					db.close();
					exit(0);
				}
			}
			continue;
		}	
        if(now_posses==last_posses)posses[now_posses]++;
        //Team1:1 2 Team2:3 4
		else {
			SQLString = "insert into " + FileNameString + "_PlayerEvent (ID,TYPE,PLAYER1,X1,Y1,PLAYER2,X2,Y2,FRAME,AGAINST,SUCCESS)values(";
			strStream.str("");
			strStream << event++;
			strStream << ",";
			strStream << 4;
			strStream << ",";
			strStream << now_posses;
			strStream << ",";
			strStream << players[i][now_posses].y_trans;
			strStream << ",";
			strStream << players[i][now_posses].x_trans;
			strStream << ",";
			strStream << -1;
			strStream << ",";
			strStream << -1;
			strStream << ",";
			strStream << -1;
			strStream << ",";
			strStream << i + 1;
			strStream << ",";
			if (abs(players[i][now_posses].type - players[i][second_posses].type) > 1 && Player_distance < 100) {
				against_flag = 1;
			}
			success_flag = 1;
			strStream << against_flag << "," << success_flag << ");";
			QString ParamStr = QString::fromStdString(strStream.str());
			SQLString += ParamStr;
            cout<<SQLString.toStdString()<<endl;
			if (query.exec(SQLString))
			{
				cout << "PASSING INPUT " << last_posses << " " << now_posses << endl;
			}
			else
			{
				cout << "PASSING INPUT FAILED" << endl;
				db.close();
				exit(0);
			}

            SQLString = "update count set ";
			strStream.str("");
			strStream << "P" << now_posses << "= P" << now_posses << "+ 1 where type = " << 4 << ";";
            ParamStr = QString::fromStdString(strStream.str());
			SQLString += ParamStr;
            cout<<SQLString.toStdString()<<endl;
			if (query.exec(SQLString))
			{
				cout << "PASSING INPUT " << last_posses << " " << now_posses << endl;
			}
			else
			{
				cout << "PASSING INPUT FAILED" << endl;
				db.close();
				exit(0);
			}

			if (abs(players[i][now_posses].type - players[i][last_posses].type) <= 1)
			{
				//PASSING
				if (Player_distance < 10000) {

					SQLString = "insert into " + FileNameString + "_PlayerEvent (ID,TYPE,PLAYER1,X1,Y1,PLAYER2,X2,Y2,FRAME,AGAINST,SUCCESS)values(";
					strStream.str("");
					strStream << event++;
					strStream << ",";
					strStream << 1;
					strStream << ",";
					strStream << last_posses;
					strStream << ",";
					strStream << players[i][last_posses].y_trans;
					strStream << ",";
					strStream << players[i][last_posses].x_trans;
					strStream << ",";
					strStream << now_posses;
					strStream << ",";
					strStream << players[i][now_posses].y_trans;
					strStream << ",";
					strStream << players[i][now_posses].x_trans;
					strStream << ",";
					strStream << i + 1;
					strStream << ",";
					if (abs(players[i][now_posses].type - players[i][second_posses].type) > 1 && Player_distance < 100) {
						against_flag = 1;
					}
					success_flag = 1;
					strStream << against_flag << "," << success_flag << ");";
					QString ParamStr = QString::fromStdString(strStream.str());
					SQLString += ParamStr;
                    cout<<SQLString.toStdString()<<endl;
					if (query.exec(SQLString))
					{
						cout << "PASSING INPUT " << last_posses << " " << now_posses << endl;
					}
					else
					{
						cout << "PASSING INPUT FAILED" << endl;
						db.close();
						exit(0);
					}
                    SQLString = "update count set ";
					strStream.str("");
					strStream << "P" << last_posses << "= P" << last_posses << "+ 1 where type = " << 1 << ";";
                    ParamStr = QString::fromStdString(strStream.str());
					SQLString += ParamStr;
                    cout<<SQLString.toStdString()<<endl;
					if (query.exec(SQLString))
					{
						cout << "PASSING INPUT " << last_posses << " " << now_posses << endl;
					}
					else
					{
						cout << "PASSING INPUT FAILED" << endl;
						db.close();
						exit(0);
					}
				}
				else {
					SQLString = "insert into " + FileNameString + "_PlayerEvent (ID,TYPE,PLAYER1,X1,Y1,PLAYER2,X2,Y2,FRAME,AGAINST,SUCCESS)values(";
					strStream.str("");
					strStream << event++;
					strStream << ",";
					strStream << 2;
					strStream << ",";
					strStream << last_posses;
					strStream << ",";
					strStream << players[i][last_posses].y_trans;
					strStream << ",";
					strStream << players[i][last_posses].x_trans;
					strStream << ",";
					strStream << now_posses;
					strStream << ",";
					strStream << players[i][now_posses].y_trans;
					strStream << ",";
					strStream << players[i][now_posses].x_trans;
					strStream << ",";
					strStream << i + 1;
					strStream << ",";
					if (abs(players[i][now_posses].type - players[i][second_posses].type) > 1 && Player_distance < 100) {
						against_flag = 1;
					}
					success_flag = 1;
					strStream << against_flag << "," << success_flag << ");";
					QString ParamStr = QString::fromStdString(strStream.str());
					SQLString += ParamStr;
                    cout<<SQLString.toStdString()<<endl;
					if (query.exec(SQLString))
					{
						cout << "PASSING INPUT " << last_posses << " " << now_posses << endl;
					}
					else
					{
						cout << "PASSING INPUT FAILED" << endl;
						db.close();
						exit(0);
					}

                    SQLString = "update count set ";
					strStream.str("");
					strStream << "P" << now_posses << "= P" << now_posses << "+ 1 where type = " << 2 << ";";
                    ParamStr = QString::fromStdString(strStream.str());
					SQLString += ParamStr;
                    cout<<SQLString.toStdString()<<endl;
					if (query.exec(SQLString))
					{
						cout << "PASSING INPUT " << last_posses << " " << now_posses << endl;
					}
					else
					{
						cout << "PASSING INPUT FAILED" << endl;
						db.close();
						exit(0);
					}
				}
				SQLString = "insert into " + FileNameString + "_PlayerEvent (ID,TYPE,PLAYER1,X1,Y1,PLAYER2,X2,Y2,FRAME,AGAINST,SUCCESS)values(";
				strStream.str("");
				strStream << event++;
				strStream << ",";
				strStream << 3;
				strStream << ",";
				strStream << now_posses;
				strStream << ",";
				strStream << players[i][now_posses].y_trans;
				strStream << ",";
				strStream << players[i][now_posses].x_trans;
				strStream << ",";
				strStream << last_posses;
				strStream << ",";
				strStream << players[i][last_posses].y_trans;
				strStream << ",";
				strStream << players[i][last_posses].x_trans;
				strStream << ",";
				strStream << i + 1;
				strStream << ",";
				if (abs(players[i][now_posses].type - players[i][second_posses].type) > 1 && Player_distance < 100) {
					against_flag = 1;
				}
				success_flag = 1;
				strStream << against_flag << "," << success_flag << ");";
				QString ParamStr = QString::fromStdString(strStream.str());
				SQLString += ParamStr;
                cout<<SQLString.toStdString()<<endl;
				if (query.exec(SQLString))
				{
					cout << "PASSING INPUT " << last_posses << " " << now_posses << endl;
				}
				else
				{
					cout << "PASSING INPUT FAILED" << endl;
					db.close();
					exit(0);
				}
                SQLString = "update count set ";
				strStream.str("");
				strStream << "P" << now_posses << "= P" << now_posses << "+ 1 where type = " << 3 << ";";
                ParamStr = QString::fromStdString(strStream.str());
				SQLString += ParamStr;
                cout<<SQLString.toStdString()<<endl;
				if (query.exec(SQLString))
				{
					cout << "PASSING INPUT " << last_posses << " " << now_posses << endl;
				}
				else
				{
					cout << "PASSING INPUT FAILED" << endl;
					db.close();
					exit(0);
				}
			}
			else {
				//STEAL
				SQLString = "insert into " + FileNameString + "_PlayerEvent (ID,TYPE,PLAYER1,X1,Y1,PLAYER2,X2,Y2,FRAME,AGAINST,SUCCESS)values(";
				strStream.str("");
				strStream << event++;
				strStream << ",";
				strStream << 10;
				strStream << ",";
				strStream << now_posses;
				strStream << ",";
				strStream << players[i][now_posses].y_trans;
				strStream << ",";
				strStream << players[i][now_posses].x_trans;
				strStream << ",";
				strStream << last_posses;
				strStream << ",";
				strStream << players[i][last_posses].y_trans;
				strStream << ",";
				strStream << players[i][last_posses].x_trans;
				strStream << ",";
				strStream << i + 1;
				strStream << ",";
				if (abs(players[i][now_posses].type - players[i][second_posses].type) > 1 && Player_distance < 100) {
					against_flag = 1;
				}
				success_flag = 1;
				strStream << against_flag << "," << success_flag << ");";
				QString ParamStr = QString::fromStdString(strStream.str());
				SQLString += ParamStr;
                cout<<SQLString.toStdString()<<endl;
				if (query.exec(SQLString))
				{
					cout << "STEAL INPUT " << now_posses << " " << last_posses << endl;
				}
				else
				{
					cout << "STEAL INPUT FAILED" << endl;
					db.close();
					exit(0);
				}
                SQLString = "update count set ";
				strStream.str("");
				strStream << "P" << now_posses << "= P" << now_posses << "+ 1 where type = " << 10 << ";";
                ParamStr = QString::fromStdString(strStream.str());
				SQLString += ParamStr;
                cout<<SQLString.toStdString()<<endl;
				if (query.exec(SQLString))
				{
					cout << "PASSING INPUT " << last_posses << " " << now_posses << endl;
				}
				else
				{
					cout << "PASSING INPUT FAILED" << endl;
					db.close();
					exit(0);
				}
			}
		}

        int FieldLeft,FieldRight,FieldUp,FieldDown;
        for(int j=0;j<4;j++)
        {
            if(j==0)
            {
                FieldLeft=dstpt[j].x;
                FieldRight=dstpt[j].x;
                FieldUp=dstpt[j].y;
                FieldDown=dstpt[j].y;
            }
            else
            {
                if(dstpt[j].x<FieldLeft)FieldLeft=dstpt[j].x;
                if(dstpt[j].x>FieldRight)FieldRight=dstpt[j].x;
                if(dstpt[j].y<FieldUp)FieldUp=dstpt[j].y;
                if(dstpt[j].y>FieldDown)FieldDown=dstpt[j].y;
                //cout<<FieldLeft<<" "<<FieldRight<<" "<<FieldUp<<" "<<FieldDown<<endl;
            }
        }
        //cout<<FieldLeft<<" "<<FieldRight<<" "<<FieldUp<<" "<<FieldDown<<endl;

        int FieldWidth=FieldRight-FieldLeft;
        int FieldHeight=FieldDown-FieldUp;
        int PlayGroundLeft=FieldLeft+FieldWidth*35/800;
        int PlayGroundRight=FieldRight-FieldWidth*35/800;
        int PlayGroundUp=FieldUp+FieldHeight*15/500;
        int PlayGroundDown=FieldDown-FieldHeight*15/500;
        int GoalUp=FieldUp+FieldHeight*225/500;
        int GoalDown=FieldDown-FieldHeight*225/500;
        int AreaUp=FieldUp+FieldHeight*110/500;
        int AreaDown=FieldDown-FieldHeight*110/500;

        if(players[i][0].x_trans<PlayGroundUp||players[i][0].x_trans>PlayGroundDown)
        {
            if(out_flag==-1)
            {
                //Side Out
                SQLString="insert into "+FileNameString+"_PlayerEvent (ID,TYPE,PLAYER1,X1,Y1,PLAYER2,X2,Y2,FRAME,AGAINST,SUCCESS)values(";
                strStream.str("");
                strStream<<event++;
                strStream<<",";
                strStream<<10;
                strStream<<",";
                strStream<<now_posses;
                strStream<<",";
                strStream<<players[i][now_posses].y_trans;
                strStream<<",";
                strStream<<players[i][now_posses].x_trans;
                strStream<<",";
                strStream<<-1;
                strStream<<",";
                strStream<<-1;
                strStream<<",";
                strStream<<-1;
                strStream<<",";
                strStream<<i+1;
                strStream<<",";
				if (abs(players[i][now_posses].type - players[i][second_posses].type) > 1 && Player_distance < 100) {
					against_flag = 1;
				}
				success_flag = 1;
				strStream << against_flag << "," << success_flag << ");";
                QString ParamStr=QString::fromStdString(strStream.str());
                SQLString+=ParamStr;
                cout<<SQLString.toStdString()<<endl;
                if(query.exec(SQLString))
                {
                    cout<<"SIDE OUT INPUT "<<now_posses<<endl;

                }
                else
                {
                    cout<<"SIDE OUT INPUT FAILED"<<endl;
                    db.close();
                    exit(0);
                }
                out_flag=1;
                SQLString = "update count set ";
				strStream.str("");
				strStream << "P" << now_posses << "= P" << now_posses << "+ 1 where type = " << 10 << ";";
                ParamStr = QString::fromStdString(strStream.str());
				SQLString += ParamStr;
                cout<<SQLString.toStdString()<<endl;
				if (query.exec(SQLString))
				{
					cout << "PASSING INPUT " << last_posses << " " << now_posses << endl;
				}
				else
				{
					cout << "PASSING INPUT FAILED" << endl;
					db.close();
					exit(0);
				}
            }
        }
        if(players[i][0].y_trans<PlayGroundLeft||players[i][0].y_trans>PlayGroundRight)
        {
            if(out_flag==-1)
            {
                if(players[i][0].x_trans<GoalDown&&players[i][0].x_trans>GoalUp)
                {
                    //GOAL
                    SQLString="insert into "+FileNameString+"_PlayerEvent (ID,TYPE,PLAYER1,X1,Y1,PLAYER2,X2,Y2,FRAME,AGAINST,SUCCESS)values(";
                    strStream.str("");
                    strStream<<event++;
                    strStream<<",";
                    strStream<<7;
                    strStream<<",";
                    strStream<<now_posses;
                    strStream<<",";
                    strStream<<players[i][now_posses].y_trans;
                    strStream<<",";
                    strStream<<players[i][now_posses].x_trans;
                    strStream<<",";
                    strStream<<-1;
                    strStream<<",";
                    strStream<<-1;
                    strStream<<",";
                    strStream<<-1;
                    strStream<<",";
                    strStream<<i+1;
                    strStream<<",";
					if (abs(players[i][now_posses].type - players[i][second_posses].type) > 1 && Player_distance < 100) {
						against_flag = 1;
					}
					success_flag = 1;
					strStream << against_flag << "," << success_flag << ");";
                    QString ParamStr=QString::fromStdString(strStream.str());
                    SQLString+=ParamStr;
                    cout<<SQLString.toStdString()<<endl;
                    if(query.exec(SQLString))
                    {
                        cout<<"GOAL INPUT "<<now_posses<<endl;
                    }
                    else
                    {
                        cout<<"GOAL INPUT FAILED"<<endl;
                        db.close();
                        exit(0);
                    }
                    SQLString = "update count set ";
					strStream.str("");
					strStream << "P" << now_posses << "= P" << now_posses << "+ 1 where type = " << 7 << ";";
                    ParamStr = QString::fromStdString(strStream.str());
					SQLString += ParamStr;
                    cout<<SQLString.toStdString()<<endl;
					if (query.exec(SQLString))
					{
						cout << "PASSING INPUT " << last_posses << " " << now_posses << endl;
					}
					else
					{
						cout << "PASSING INPUT FAILED" << endl;
						db.close();
						exit(0);
					}
                }
                if((players[i][0].x_trans<GoalUp&&players[i][0].x_trans>AreaUp)||(players[i][0].x_trans<AreaDown&&players[i][0].x_trans>GoalDown))
                {
                    //AREA OUT
                    SQLString="insert into "+FileNameString+"_PlayerEvent (ID,TYPE,PLAYER1,X1,Y1,PLAYER2,X2,Y2,FRAME,AGAINST,SUCCESS)values(";
                    strStream.str("");
                    strStream<<event++;
                    strStream<<",";
                    strStream<<7;
                    strStream<<",";
                    strStream<<now_posses;
                    strStream<<",";
                    strStream<<players[i][now_posses].y_trans;
                    strStream<<",";
                    strStream<<players[i][now_posses].x_trans;
                    strStream<<",";
                    strStream<<-1;
                    strStream<<",";
                    strStream<<-1;
                    strStream<<",";
                    strStream<<-1;
                    strStream<<",";
                    strStream<<i+1;
                    strStream<<",";
					if (abs(players[i][now_posses].type - players[i][second_posses].type) > 1 && Player_distance < 100) {
						against_flag = 1;
					}
					success_flag = 0;
					strStream << against_flag << "," << success_flag << ");";
                    ParamStr=QString::fromStdString(strStream.str());
                    SQLString+=ParamStr;
                    cout<<SQLString.toStdString()<<endl;
                    if(query.exec(SQLString))
                    {
                        cout<<"AREA OUT INPUT "<<now_posses<<endl;
                    }
                    else
                    {
                        cout<<"AREA OUT INPUT FAILED"<<endl;
                        db.close();
                        exit(0);
                    }
                    SQLString = "update count set ";
					strStream.str("");
					strStream << "P" << now_posses << "= P" << now_posses << "+ 1 where type = " << 7 << ";";
					QString ParamStr = QString::fromStdString(strStream.str());
					SQLString += ParamStr;
                    cout<<SQLString.toStdString()<<endl;
					if (query.exec(SQLString))
					{
						cout << "PASSING INPUT " << last_posses << " " << now_posses << endl;
					}
					else
					{
						cout << "PASSING INPUT FAILED" << endl;
						db.close();
						exit(0);
					}
                    //SIDE OUT AGAIN
                    SQLString="insert into "+FileNameString+"_PlayerEvent (ID,TYPE,PLAYER1,X1,Y1,PLAYER2,X2,Y2,FRAME,AGAINST,SUCCESS)values(";
                    strStream.str("");
                    strStream<<event++;
                    strStream<<",";
                    strStream<<10;
                    strStream<<",";
                    strStream<<now_posses;
                    strStream<<",";
                    strStream<<players[i][now_posses].y_trans;
                    strStream<<",";
                    strStream<<players[i][now_posses].x_trans;
                    strStream<<",";
                    strStream<<-1;
                    strStream<<",";
                    strStream<<-1;
                    strStream<<",";
                    strStream<<-1;
                    strStream<<",";
                    strStream<<i+1;
                    strStream<<",";
					if (abs(players[i][now_posses].type - players[i][second_posses].type) > 1 && Player_distance < 100) {
						against_flag = 1;
					}
					success_flag = 1;
					strStream << against_flag << "," << success_flag << ");";
                    ParamStr=QString::fromStdString(strStream.str());
                    SQLString+=ParamStr;
                    cout<<SQLString.toStdString()<<endl;
                    if(query.exec(SQLString))
                    {
                        cout<<"AREA OUT INPUT2 "<<now_posses<<endl;
                    }
                    else
                    {
                        cout<<"AREA OUT INPUT2 FAILED"<<endl;
                        db.close();
                        exit(0);
                    }
                    SQLString = "update count set ";
					strStream.str("");
					strStream << "P" << now_posses << "= P" << now_posses << "+ 1 where type = " << 10 << ";";
                    ParamStr = QString::fromStdString(strStream.str());
					SQLString += ParamStr;
                    cout<<SQLString.toStdString()<<endl;
					if (query.exec(SQLString))
					{
						cout << "PASSING INPUT " << last_posses << " " << now_posses << endl;
					}
					else
					{
						cout << "PASSING INPUT FAILED" << endl;
						db.close();
						exit(0);
					}
                }
                if(players[i][0].x_trans<AreaUp&&players[i][0].x_trans>GoalDown)
                {
                    //NORMAL BASELINE OUT
                    SQLString="insert into "+FileNameString+"_PlayerEvent (ID,TYPE,PLAYER1,X1,Y1,PLAYER2,X2,Y2,FRAME,AGAINST,SUCCESS)values(";
                    strStream.str("");
                    strStream<<event++;
                    strStream<<",";
                    strStream<<10;
                    strStream<<",";
                    strStream<<now_posses;
                    strStream<<",";
                    strStream<<players[i][now_posses].y_trans;
                    strStream<<",";
                    strStream<<players[i][now_posses].x_trans;
                    strStream<<",";
                    strStream<<-1;
                    strStream<<",";
                    strStream<<-1;
                    strStream<<",";
                    strStream<<-1;
                    strStream<<",";
                    strStream<<i+1;
                    strStream<<",";
					if (abs(players[i][now_posses].type - players[i][second_posses].type) > 1 && Player_distance < 100) {
						against_flag = 1;
					}
					success_flag = 1;
					strStream << against_flag << "," << success_flag << ");";
                    QString ParamStr=QString::fromStdString(strStream.str());
                    SQLString+=ParamStr;
                    cout<<SQLString.toStdString()<<endl;
                    if(query.exec(SQLString))
                    {
                        cout<<"BASELINE OUT INPUT "<<now_posses<<endl;
                    }
                    else
                    {
                        cout<<"BASELINE OUT INPUT FAILED"<<endl;
                        db.close();
                        exit(0);
                    }
                }
                out_flag=1;
                SQLString = "update count set ";
				strStream.str("");
				strStream << "P" << now_posses << "= P" << now_posses << "+ 1 where type = " << 10 << ";";
				QString ParamStr = QString::fromStdString(strStream.str());
				SQLString += ParamStr;
                cout<<SQLString.toStdString()<<endl;
				if (query.exec(SQLString))
				{
					cout << "PASSING INPUT " << last_posses << " " << now_posses << endl;
				}
				else
				{
					cout << "PASSING INPUT FAILED" << endl;
					db.close();
					exit(0);
				}
            }
        }
        if(players[i][0].y_trans>PlayGroundLeft&&players[i][0].y_trans<PlayGroundRight
                &&players[i][0].x_trans>PlayGroundUp&&players[i][0].x_trans<PlayGroundDown)
        {
            //Back into field
            out_flag=-1;
        }

    }
}
void SQL_Collection(string FileName)
{
    QSqlQuery query(db);
    query=QSqlQuery::QSqlQuery(db);
    QString SQLString;
    QString ParamString;
    stringstream strStream;
    QString FileNameString=QString::fromStdString(FileName);
    int Tag=FileName[1]-'0';
    int Video=(FileName[2]-'0')*10+(FileName[3]-'0');

    SQLString="ALTER TABLE "+FileNameString+"_position ADD COLUMN TAG INTEGER NOT NULL AFTER Y30";
    if(query.exec(SQLString))
    {
        cout<<"ALTER TABLE TAG SUCCESS"<<endl;
    }
    else
    {
        cout<<"ALTER TABLE TAG FAILED"<<endl;
        db.close();
        exit(0);
    }
    SQLString="ALTER TABLE "+FileNameString+"_position ADD COLUMN VIDEO INTEGER NOT NULL AFTER TAG";
    if(query.exec(SQLString))
    {
        cout<<"ALTER TABLE VIDEO SUCCESS"<<endl;
    }
    else
    {
        cout<<"ALTER TABLE VIDEO FAILED"<<endl;
        db.close();
        exit(0);
    }
    SQLString="UPDATE "+FileNameString+"_position SET TAG=";
    strStream.str("");
    strStream<<Tag<<", VIDEO="<<Video<<";";
    ParamString=QString::fromStdString(strStream.str());
    SQLString+=ParamString;
    if(query.exec(SQLString))
    {
        cout<<"CHANGE TAG VIDEO SUCCESS"<<endl;
    }
    else
    {
        cout<<"CHANGE TAG VIDEO FAILED"<<endl;
        db.close();
        exit(0);
    }
    SQLString="INSERT INTO position (SELECT * FROM "+FileNameString+"_position)";
    if(query.exec(SQLString))
    {
        cout<<"INSERT SUCCESS"<<endl;
    }
    else
    {
        cout<<"INSERT FAILED"<<endl;
        db.close();
        exit(0);
    }
    SQLString="ALTER TABLE "+FileNameString+"_PlayerEvent ADD COLUMN TAG INTEGER NOT NULL AFTER FRAME";
    if(query.exec(SQLString))
    {
        cout<<"ALTER TABLE TAG SUCCESS"<<endl;
    }
    else
    {
        cout<<"ALTER TABLE TAG FAILED"<<endl;
        db.close();
        exit(0);
    }
    SQLString="ALTER TABLE "+FileNameString+"_PlayerEvent ADD COLUMN VIDEO INTEGER NOT NULL AFTER TAG";
    if(query.exec(SQLString))
    {
        cout<<"ALTER TABLE VIDEO SUCCESS"<<endl;
    }
    else
    {
        cout<<"ALTER TABLE VIDEO FAILED"<<endl;
        db.close();
        exit(0);
    }
    SQLString="ALTER TABLE "+FileNameString+"_PlayerEvent ADD COLUMN LOOSE INTEGER NOT NULL AFTER SUCCESS";
    if(query.exec(SQLString))
    {
        cout<<"ALTER TABLE VIDEO SUCCESS"<<endl;
    }
    else
    {
        cout<<"ALTER TABLE VIDEO FAILED"<<endl;
        db.close();
        exit(0);
    }
    SQLString="UPDATE "+FileNameString+"_PlayerEvent SET TAG=";
    strStream.str("");
    strStream<<Tag<<", VIDEO="<<Video<<", LOOSE=0;";
    ParamString=QString::fromStdString(strStream.str());
    SQLString+=ParamString;
    if(query.exec(SQLString))
    {
        cout<<"CHANGE TAG VIDEO SUCCESS"<<endl;
    }
    else
    {
        cout<<"CHANGE TAG VIDEO FAILED"<<endl;
        db.close();
        exit(0);
    }
    SQLString="INSERT INTO PlayerEvent (SELECT * FROM "+FileNameString+"_PlayerEvent)";
    if(query.exec(SQLString))
    {
        cout<<"INSERT SUCCESS"<<endl;
    }
    else
    {
        cout<<"INSERT FAILED"<<endl;
        db.close();
        exit(0);
    }
}

//--------------------------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow win;
    win.show();
    QTextStream cout(stdout,  QIODevice::WriteOnly); // cout需要这一步,printf不需要

    string filePath = "D:/testvideo";
    vector<string> files;
    string file_name[100] = { "" };
    //获取该路径下的所有mp4文件

    getFiles(filePath, "mp4", files);

    int size_of_mp4_files = files.size();
    int processed_file_count = 0;
    SQL_WholeChart_init();
    Mat transMat;
    while (processed_file_count < size_of_mp4_files){
        Sleep(1000);
        files.clear();
        getFiles(filePath, "mp4", files);
        size_of_mp4_files = files.size();



        for (int i = processed_file_count; i < size_of_mp4_files; i++){
            file_name[i] = files[i].c_str();
//            int tag;
//            tag = getFileAngle(file_name[i]);
            stringstream VideoTag;
            VideoTag.str("");
            for(int j=0;j<file_name[i].length()-1;j++)
            {
                char nameItem=file_name[i][j];
                if(nameItem>='0'&&nameItem<='9')VideoTag<<nameItem;
            }

            trackPro(files[i].c_str(), transMat, win);
            //SQL FUNCTION
            //if(processed_file_count==0)


            SQL_init(VideoTag.str());
            SQL_Process(VideoTag.str());
            SQL_Collection(VideoTag.str());
            //cout << files[i].c_str() << endl;
            processed_file_count++;
        }

        //如果视频处理完、则等待
        while (processed_file_count >= size_of_mp4_files){
            Sleep(5000);
            printf("wait\t");
            files.clear();
            getFiles(filePath, "mp4", files);
            size_of_mp4_files = files.size();
        }
    }

    return a.exec();
}
