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

#define LENMIL 10
#define STDMAXBUF 256
#define MAXMEMBUF 1500
#define LENLEV 1

class Member
{
	string ID;
	string Password;
	string Name;
	string Phone_Number;
	string Address;
	char Mileage[LENMIL + 1];
	char Level[LENLEV + 1];
	string key;

public:
	Member();
	Member(const Member &m);
	Member(const char *ID);

	Member & operator = (const Member &m);
	bool operator == (const Member &m);
	bool operator != (const Member &m);

	friend istream & operator >> (istream &is, Member &m);
	friend ostream & operator << (ostream &os, Member &m);

	void update_id(const string new_id)
	{
		ID = new_id;
	}
	void update_password(const string new_password)
	{
		Password = new_password;
	}
	void update_name(const string new_name)
	{
		Name = new_name;
	}
	void update_phonenumber(const string new_phonenumber)
	{
		Phone_Number = new_phonenumber;
	}
	void update_address(const string new_address)
	{
		Address = new_address;
	}
	void update_mileage(const char *new_mileage)
	{
		memcpy(Mileage, new_mileage, LENMIL);
	}
	void update_level(const char *new_level)
	{
		memcpy(Level, new_level, LENLEV);
	}
	int get_length()
	{
		return ID.size() + Password.size() + Name.size() + Phone_Number.size() + Address.size() + strlen(Mileage) + strlen(Level);
	}
	string get_pwd()
	{
		return Password;
	}
	char get_level()
	{
		return Level[0];
	}
	bool Pack (IOBuffer & Buffer) const;
	bool Unpack (IOBuffer &);
	char *Key();
};

istream & operator >> (istream &is, Member &m);
ostream & operator << (ostream &os, Member &m);

void showMember();
void MemberTest();

int SearchMember(char *RecordId, Member *m);
int InsertMember(char *RecordId, int num);
int DeleteMember(char *RecordId, int num);
int UpdateMember(char *RecordId, int num);

int SearchingPwd(char *Id, char *Pwd);
int set_memnum();
void make_Member();