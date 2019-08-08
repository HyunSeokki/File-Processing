#include "Member.h"
#include "Lecture.h"
#include "Purchase.h"
#include <sstream>
#include <stdlib.h>

Lecture::Lecture()
{
}

Lecture::Lecture(const Lecture &l)
{
	update_lectureid(l.Lecture_ID);
	update_subject(l.Subject);
	update_level(l.Level);
	update_price(l.Price);
	update_extension(l.Extension);
	update_duedate(l.Due_date);
	update_nameofteacher(l.Name_of_teacher);
	update_textbook(l.Textbook);
}

Lecture::Lecture(const char *ID)
{
	update_lectureid(ID);
}

Lecture & Lecture::operator = (const Lecture &l)
{
	update_lectureid(l.Lecture_ID);
	update_subject(l.Subject);
	update_level(l.Level);
	update_price(l.Price);
	update_extension(l.Extension);
	update_duedate(l.Due_date);
	update_nameofteacher(l.Name_of_teacher);
	update_textbook(l.Textbook);

	return *this;
}

bool Lecture::operator == (const Lecture &l)
{
	if(!memcmp(Lecture_ID, l.Lecture_ID, LENLEC))
		return true;

	return false;
}

bool Lecture::operator != (const Lecture &l)
{
	if(!memcmp(Lecture_ID, l.Lecture_ID, LENLEC))
		return false;

	return true;
}

istream & operator >> (istream &is, Lecture &l)
{
	string st;

	is.exceptions(istream::failbit | istream::badbit);

	try {
		getline(is, st);
	}
	catch(istream::failure e)
	{
		//error
		return is;
	}
	istringstream iss(st);
	string token;

	getline(iss, token, '|');
	l.update_lectureid(token.data());

	getline(iss, token, '|');
	l.update_subject(token);

	getline(iss, token, '|');
	l.update_level(token[0]);

	getline(iss, token, '|');
	l.update_price(atoi(token.data()));

	getline(iss, token, '|');
	l.update_extension(token[0]);

	getline(iss, token, '|');
	l.update_duedate(atoi(token.data()));

	getline(iss, token, '|');
	l.update_nameofteacher(token);

	getline(iss, token, '|');
	l.update_textbook(token);

	return is;
}

ostream & operator << (ostream &os, Lecture &l)
{
	string lecture_id(l.Lecture_ID, LENLEC);

	cout << "Lecutre ID : " << lecture_id << endl;
	cout << "Subject : " << l.Subject << endl;
	cout << "Level : " << l.Level << endl;
	cout << "Price : " << l.Price << endl;
	cout << "Extension : " << l.Extension << endl;
	cout << "Due date : " << l.Due_date << endl;
	cout << "Name of teacher : " << l.Name_of_teacher << endl;
	cout << "Textbook : " << l.Textbook << endl;

	return os;
}

bool Lecture::Pack(IOBuffer & Buffer) const
{
	int numBytes;

	Buffer.Clear();

	string s_lectureid(Lecture_ID, LENLEC);
	char s_price[20], s_duedate[10], temp[3];
	sprintf(temp, "%c", Level);
	string s_level(temp, 2);
	itoa(Price, s_price, 10);
	sprintf(temp, "%c", Extension);
	string s_extension(temp, 2);
	itoa(Due_date, s_duedate, 10);

	numBytes = Buffer.Pack(s_lectureid.c_str());
	if(numBytes == -1) return false;
	numBytes = Buffer.Pack(Subject.c_str());
	if(numBytes == -1) return false;
	numBytes = Buffer.Pack(s_level.c_str());
	if(numBytes == -1) return false;
	numBytes = Buffer.Pack(s_price);
	if(numBytes == -1) return false;
	numBytes = Buffer.Pack(s_extension.c_str());
	if(numBytes == -1) return false;
	numBytes = Buffer.Pack(s_duedate);
	if(numBytes == -1) return false;
	numBytes = Buffer.Pack(Name_of_teacher.c_str());
	if(numBytes == -1) return false;
	numBytes = Buffer.Pack(Textbook.c_str());
	if(numBytes == -1) return false;

	return true;
}

bool Lecture::Unpack(IOBuffer & Buffer)
{
	int numBytes;
	char buf[STDMAXBUF];
	char s_level[2], s_price[20], s_extension[2], s_duedate[3];

	numBytes = Buffer.Unpack(Lecture_ID, LENLEC);
	if(numBytes == -1) return false;
	numBytes = Buffer.Unpack(buf);
	if(numBytes == -1) return false;
	Subject = buf;
	numBytes = Buffer.Unpack(s_level, 2);
	if(numBytes == -1) return false;
	numBytes = Buffer.Unpack(s_price, 20);
	if(numBytes == -1) return false;
	numBytes = Buffer.Unpack(s_extension, 2);
	if(numBytes == -1) return false;
	numBytes = Buffer.Unpack(s_duedate, 3);
	if(numBytes == -1) return false;
	numBytes = Buffer.Unpack(buf);
	if(numBytes == -1) return false;
	Name_of_teacher = buf;
	numBytes = Buffer.Unpack(buf);
	if(numBytes == -1) return false;
	Textbook = buf;

	Level = s_level[0];
	Price = atoi(s_price);
	Extension = s_extension[0];
	Due_date = atoi(s_duedate);

	return true;
}

void showLecture()
{
	ifstream ifs("listOfLecture.txt");
	if(ifs.fail())
	{
		cout << "File Open error!" << endl;
		return;
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	for(int i=0; i<10; i++)
	{
		Lecture l;
		ifs >> l;
		cout << l;
	}
}

void LectureTest()
{
	ifstream ifs("listOfLecture.txt");

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Lecture> LectureFile(buffer);

	LectureFile.Create("fileOfLecture.dat", ios::out | ios::trunc);
	for(int i = 0; i < n; i++)
	{
		Lecture l;
		ifs >> l;
		int recaddr;
		if((recaddr = LectureFile.Write(l)) == -1)
			cout << "Write Error!" << endl;
	}
	LectureFile.Close();

	LectureFile.Open("fileOfLecture.dat", ios::in);

	for(int i = 0; i < 10; i++)
	{
		Lecture l;
		LectureFile.Read(l);
		cout << l;
	}
	LectureFile.Close();
}

int SearchLecture(char *RecordId, Lecture *l)
{
	int ret = -1;
	int recaddr;
	Lecture lec;
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Lecture> LectureFile(buffer);

	LectureFile.Open("fileOfLecture.dat", ios::in);
	while((recaddr = LectureFile.Read(lec)) != -1)
	{
		if(lec == RecordId)
		{
			*l = lec;
			ret = recaddr;
			break;
		}
	}
	LectureFile.Close();

	return ret;
}

int InsertLecture(char *RecordId, int num)
{
	Lecture l;
	int integer;
	string buf;

	if(strlen(RecordId) != LENLEC)
		return -1;
	else
		l.update_lectureid(RecordId);

	cout << "Subject를 입력하세요 : ";
	cin >> buf;
	l.update_subject(buf);

	cout << "Level을 입력하세요 : ";
	cin >> buf;
	if(buf[0] != 'A' && buf[0] != 'B' && buf[0] != 'C' && buf[0] != 'D')
		return -1;
	else
		l.update_level(buf[0]);

	cout << "Price를 입력하세요 : ";
	cin >> integer;
	l.update_price(integer);

	cout << "Extension을 입력하세요 : ";
	cin >> buf;
	if(buf[0] != 'Y' && buf[0] != 'N')
		return -1;
	else
		l.update_extension(buf[0]);

	cout << "Due date를 입력하세요 : ";
	cin >> integer;
	if(integer != 30 && integer != 60 && integer != 90)
		return -1;
	else
		l.update_duedate(integer);

	cout << "Name of teacher를 입력하세요 : ";
	cin >> buf;
	l.update_nameofteacher(buf);

	cout << "Textbook을 입력하세요 : ";
	cin >> buf;
	l.update_textbook(buf);

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Lecture> LectureFile(buffer);
	LectureFile.Open("fileOfLecture.dat", ios::in | ios::out | ios::app);
	if(LectureFile.Write(l) == -1) {
		cout << "Write Error!" << endl;
	}
	LectureFile.Close();

	DelimFieldBuffer buffer1('|', STDMAXBUF);
	TextIndexedFile<Lecture> mmdIdxedFile(buffer1, 12, num);
	mmdIdxedFile.Open("fileOfLecture");

	mmdIdxedFile.Append(l);
	mmdIdxedFile.Close();

	return 1;
}

int DeleteLecture(char *RecordId, int num)
{
	bool flag = false;
	int idx = 0, recaddr, ifs_last;
	string buf;
	Lecture l, update_l;
	Lecture *lecture_record = new Lecture[MAXLECBUF];
	ifstream ifs("fileOfLecture.dat");

	if(ifs.fail())
	{
		cout << "Open Error!" << endl;
		return -1;
	}
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Lecture> LectureFile(buffer);
	LectureFile.Open("fileOfLecture.dat", ios::in);

	ifs.clear();
	ifs.seekg(0, ifs.end);
	ifs_last = ifs.tellg();
	ifs.seekg(0, ifs.beg);
	while(ifs.tellg() < ifs_last)
	{
		LectureFile.Read(l);
		if(l != RecordId)
		{
			lecture_record[idx++] = l;
		}
		else
		{
			flag = true;
			ifs.seekg(l.get_length(), ifs.cur);
		}
		ifs.seekg(l.get_length(), ifs.cur);
	}
	LectureFile.Close();

	if(flag == false)
		return -1;

	LectureFile.Create("fileOfLecture.dat", ios::out | ios::trunc);
	for(int i = 0; i < idx; i++)
	{
		if((recaddr = LectureFile.Write(lecture_record[i])) == -1)
			cout << "Write Error!" << endl;
	}
	LectureFile.Close();
	ifs.close();

	DeletePurchase(RecordId);

	TextIndex LectureIndex(num - 1);

	LectureFile.Open("fileOfLecture.dat", ios::in);
	while(1)
	{
		Lecture l;
		int recaddr = LectureFile.Read(l);
		if(recaddr == -1) break;
		LectureIndex.Insert(l.Key(), recaddr);
	}
	LectureFile.Close();

	TextIndexBuffer lecidxbuf(12, num - 1);
	BufferFile LecIdxFile(lecidxbuf);
	LecIdxFile.Create("fileOfLecture.ind", ios::out | ios::trunc);
	LecIdxFile.Rewind();
	lecidxbuf.Pack(LectureIndex);
	int result = LecIdxFile.Write();
	LecIdxFile.Close();

	return 1;
}

int UpdateLecture(char *RecordId, int num)
{
	bool flag = false;
	int idx = 0, integer, recaddr;
	string buf;
	Lecture l, update_l;
	Lecture *lecture_record = new Lecture[MAXLECBUF];

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Lecture> LectureFile(buffer);
	LectureFile.Open("fileOfLecture.dat", ios::in);
	while(recaddr = LectureFile.Read(l) != -1)
	{
		if(l != RecordId)
		{
			lecture_record[idx++] = l;
		}
		else
		{
			flag = true;

			if(strlen(RecordId) != LENLEC)
				return -1;
			else
				l.update_lectureid(RecordId);

			cout << "Subject를 입력하세요 : ";
			cin >> buf;
			l.update_subject(buf);

			cout << "Level을 입력하세요 : ";
			cin >> buf;
			if(buf[0] != 'A' && buf[0] != 'B' && buf[0] != 'C' && buf[0] != 'D')
				return -1;
			else
				l.update_level(buf[0]);

			cout << "Price를 입력하세요 : ";
			cin >> integer;
			l.update_price(integer);

			cout << "Extension을 입력하세요 : ";
			cin >> buf;
			if(buf[0] != 'Y' && buf[0] != 'N')
				return -1;
			else
				l.update_extension(buf[0]);

			cout << "Due date를 입력하세요 : ";
			cin >> integer;
			if(integer != 30 && integer != 60 && integer != 90)
				return -1;
			else
				l.update_duedate(integer);

			cout << "Name of teacher를 입력하세요 : ";
			cin >> buf;
			l.update_nameofteacher(buf);

			cout << "Textbook을 입력하세요 : ";
			cin >> buf;
			l.update_textbook(buf);

			lecture_record[idx++] = l;
		}
	}
	LectureFile.Close();

	if(flag == false)
		return -1;

	LectureFile.Create("fileOfLecture.dat", ios::out | ios::trunc);
	for(int i = 0; i < idx; i++)
	{
		if((recaddr = LectureFile.Write(lecture_record[i])) == -1)
			cout << "Write Error!" << endl;
	}
	LectureFile.Close();

	TextIndex LectureIndex(num);

	LectureFile.Open("fileOfLecture.dat", ios::in);
	while(1)
	{
		Lecture l;
		int recaddr = LectureFile.Read(l);
		if(recaddr == -1) break;
		LectureIndex.Insert(l.Key(), recaddr);
	}
	LectureFile.Close();

	TextIndexBuffer lecidxbuf(12, num);
	BufferFile LecIdxFile(lecidxbuf);
	LecIdxFile.Create("fileOfLecture.ind", ios::out | ios::trunc);
	LecIdxFile.Rewind();
	lecidxbuf.Pack(LectureIndex);
	int result = LecIdxFile.Write();
	LecIdxFile.Close();

	return 1;
}

char * Lecture::Key() {
	key.assign(Lecture_ID, 12);
	return (char *)(key.c_str());
}

int set_lecnum()
{
	ifstream ifs("listOfLecture.txt");
	if (ifs.fail())
	{
		cout << "File Open error!" << endl;
		return -1;
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	return n;
}

void make_Lecture()
{
	ifstream ifs("listOfLecture.txt");

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Lecture> LectureFile(buffer);

	LectureFile.Create("fileOfLecture.dat", ios::out | ios::trunc);
	for(int i = 0; i < n; i++)
	{
		Lecture l;
		ifs >> l;
		int recaddr;
		if((recaddr = LectureFile.Write(l)) == -1)
			cout << "Write Error!" << endl;
	}
	LectureFile.Close();
}