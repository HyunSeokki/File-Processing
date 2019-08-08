#include <iostream>
#include <string>
#include <fstream>
#include "indfile.h"
#include "buffile.h"
#include "tindbuff.h"
#include "textind.h"
#include "recfile.h"
#include "delim.h"
using namespace std;

#define LENPUR 16
#define LENLEC 12
#define LENMIL 10
#define STDMAXBUF 256
#define MAXPURBUF 15000

class Purchase
{
	char Purchase_ID[LENPUR + 1];
	char Lecture_ID[LENLEC + 1];
	string Member_ID;
	char Mileage[LENMIL + 1];
	char key;

public:
	Purchase();
	Purchase(const Purchase &p);
	Purchase(const char* ID);

	Purchase & operator = (const Purchase &p);
	bool operator == (const Purchase &p);
	bool operator != (const Purchase &p);

	friend istream & operator >> (istream &is, Purchase &p);
	friend ostream & operator << (ostream &os, Purchase &p);

	void update_purchaseid(const char *new_purchaseid)
	{
		memcpy(Purchase_ID, new_purchaseid, LENPUR);
	}
	void update_lectureid(const char *new_lectureid)
	{
		memcpy(Lecture_ID, new_lectureid, LENLEC);
	}
	void update_memberid(const string new_memberid)
	{
		Member_ID = new_memberid;
	}
	void update_mileage(const char *new_mileage)
	{
		memcpy(Mileage, new_mileage, LENMIL);
	}
	void update_key(const char new_key)
	{
		key = new_key;
	}
	int get_length()
	{
		return strlen(Purchase_ID) + strlen(Lecture_ID) + Member_ID.size() + strlen(Mileage);
	}
	bool Pack (IOBuffer & Buffer) const;
	bool Unpack (IOBuffer &);

	string getLectureid();
	string getMemberid();

	char Key();
};

istream & operator >> (istream &is, Purchase &p);
ostream & operator << (ostream &os, Purchase &p);

void showPurchase();
void PurchaseTest();

int SearchPurchase(char *RecordId, Purchase *p, int flag);
//int InsertPurchase(char *RecordId);
int DeletePurchase(char *RecordId);
//int UpdatePurchase(char *RecordId);

int SearchUserPurchase(char *RecordId);
int InsertUserPurchase(char *RecordId, char *Login_id);
int DeleteUserPurchase(char *RecordId);
int UpdateUserPurchase(char *RecordId, char *Login_id);

int set_purnum();
void make_Purchase();