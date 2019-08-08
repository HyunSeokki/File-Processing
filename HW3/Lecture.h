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

#define LENLEC 12
#define STDMAXBUF 256
#define MAXLECBUF 1500

class Lecture
{
	char Lecture_ID[LENLEC + 1];
	string Subject;
	char Level;
	int Price;
	char Extension;
	int Due_date;
	string Name_of_teacher;
	string Textbook;
	string key;

public:
	Lecture();
	Lecture(const Lecture & l);
	Lecture(const char *ID);

	Lecture & operator = (const Lecture &l);
	bool operator == (const Lecture &l);
	bool operator != (const Lecture &l);

	friend istream & operator >> (istream &is, Lecture &l);
	friend ostream & operator << (ostream &os, Lecture &l);

	void update_lectureid(const char *new_lectureid)
	{
		memcpy(Lecture_ID, new_lectureid, LENLEC);
	}
	void update_subject(const string new_subject)
	{
		Subject = new_subject;
	}
	void update_level(const char new_level)
	{
		Level = new_level;
	}
	void update_price(const int new_price)
	{
		Price = new_price;
	}
	void update_extension(const char new_extension)
	{
		Extension = new_extension;
	}
	void update_duedate(const int new_duedate)
	{
		Due_date = new_duedate;
	}
	void update_nameofteacher(const string new_nameofteacher)
	{
		Name_of_teacher = new_nameofteacher;
	}
	void update_textbook(const string new_textbook)
	{
		Textbook = new_textbook;
	}
	int get_length()
	{
		char s_price[20], s_duedate[10];
		itoa(Price, s_price, 10);
		itoa(Due_date, s_duedate, 10);

		return strlen(Lecture_ID) + Subject.size() + 1 + strlen(s_price) +1 + strlen(s_duedate) + Name_of_teacher.size() + Textbook.size();
	}
	bool Pack (IOBuffer & Buffer) const;
	bool Unpack (IOBuffer &);
	char *Key();
};

istream & operator >> (istream &is, Lecture &l);
ostream & operator << (ostream &os, Lecture &l);

void showLecture();
void LectureTest();

int SearchLecture(char *RecordId, Lecture *l);
int InsertLecture(char *RecordId, int num);
int DeleteLecture(char *RecordId, int num);
int UpdateLecture(char *RecordId, int num);

int set_lecnum();
void make_Lecture();