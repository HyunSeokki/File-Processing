#include "Member.h"
#include "Lecture.h"
#include "Purchase.h"
#include <sstream>

Purchase::Purchase()
{
}

Purchase::Purchase(const Purchase &p)
{
	update_purchaseid(p.Purchase_ID);
	update_lectureid(p.Lecture_ID);
	update_memberid(p.Member_ID);
	update_mileage(p.Mileage);
}

Purchase::Purchase(const char *ID)
{
	update_purchaseid(ID);
}

Purchase & Purchase::operator = (const Purchase &p)
{
	update_purchaseid(p.Purchase_ID);
	update_lectureid(p.Lecture_ID);
	update_memberid(p.Member_ID);
	update_mileage(p.Mileage);

	return *this;
}

bool Purchase::operator == (const Purchase &p)
{
	if (!memcmp(Purchase_ID, p.Purchase_ID, LENPUR))
		return true;

	return false;
}

bool Purchase::operator != (const Purchase &p)
{
	if (!memcmp(Purchase_ID, p.Purchase_ID, LENPUR))
		return false;

	return true;
}

istream & operator >> (istream &is, Purchase &p)
{
	string st;

	is.exceptions(istream::failbit | istream::badbit);

	try {
		getline(is, st);
	}
	catch (istream::failure e)
	{
		//error
		return is;
	}
	istringstream iss(st);
	string token;

	getline(iss, token, '|');
	p.update_purchaseid(token.data());

	getline(iss, token, '|');
	p.update_lectureid(token.data());

	getline(iss, token, '|');
	p.update_memberid(token);

	getline(iss, token, '|');
	p.update_mileage(token.data());


	return is;
}

ostream & operator << (ostream &os, Purchase &p)
{
	string purchase_id(p.Purchase_ID, LENPUR);
	string lecture_id(p.Lecture_ID, LENLEC);
	string mileage(p.Mileage, LENMIL);

	cout << "Purchase ID : " << purchase_id << endl;
	cout << "Lecture ID : " << lecture_id << endl;
	cout << "Member ID : " << p.Member_ID << endl;
	cout << "Mileage : " << mileage << endl;

	return os;
}

bool Purchase::Pack(IOBuffer & Buffer) const
{
	int numBytes;

	Buffer.Clear();

	string s_purchaseid(Purchase_ID, LENPUR);
	string s_lectureid(Lecture_ID, LENLEC);
	string s_mileage(Mileage, LENMIL);
	char temp[2];
	temp[0] = key;
	temp[1] = '\0';
	string KEY(temp, 1);

	numBytes = Buffer.Pack(s_purchaseid.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(s_lectureid.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(Member_ID.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(s_mileage.c_str());
	if (numBytes == -1) return false;
	numBytes = Buffer.Pack(KEY.c_str());
	if(numBytes == -1) return false;

	return true;
}

bool Purchase::Unpack(IOBuffer & Buffer)
{
	int numBytes;
	char buf[STDMAXBUF];
	char temp[2];

	numBytes = Buffer.Unpack(Purchase_ID, LENPUR);
	if (numBytes == -1) return false;
	numBytes = Buffer.Unpack(Lecture_ID, LENLEC);
	if (numBytes == -1) return false;
	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Member_ID = buf;
	numBytes = Buffer.Unpack(Mileage, LENMIL);
	if (numBytes == -1) return false;
	numBytes = Buffer.Unpack(temp, 2);
	key = temp[0];
	if(numBytes == -1) return false;

	return true;
}

string Purchase::getLectureid()
{
	string s_lectureid(Lecture_ID, LENLEC);
	return s_lectureid;
}

string Purchase::getMemberid()
{
	return Member_ID;
}

void showPurchase()
{
	ifstream ifs("listOfPurchase.txt");
	if (ifs.fail())
	{
		cout << "File Open error!" << endl;
		return;
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int i = 0; i < 10; i++)
	{
		Purchase p;
		ifs >> p;
		cout << p;
	}
}

void PurchaseTest()
{
	ifstream ifs("listOfPurchase.txt");

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Purchase> PurchaseFile(buffer);

	PurchaseFile.Create("fileOfPurchase.dat", ios::out | ios::trunc);
	for (int i = 0; i < n; i++)
	{
		Purchase p;
		ifs >> p;
		int recaddr;
		if ((recaddr = PurchaseFile.Write(p)) == -1)
			cout << "Write Error!" << endl;
	}
	PurchaseFile.Close();

	PurchaseFile.Open("fileOfPurchase.dat", ios::in);
	for (int i = 0; i < 10; i++)
	{
		Purchase p;
		PurchaseFile.Read(p);
		cout << p;
	}
	PurchaseFile.Close();
}

int SearchPurchase(char *RecordId, Purchase *p, int flag)
{
	int ret = -1;
	int recaddr;
	Purchase pur;
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Purchase> PurchaseFile(buffer);

	PurchaseFile.Open("fileOfPurchase.dat", ios::in);
	while ((recaddr = PurchaseFile.Read(pur)) != -1)
	{
		if (flag == 1)
		{
			if (pur.getMemberid() == RecordId)
			{
				*p = pur;
				ret = recaddr;
				break;
			}
		}

		else if (flag == 2)
		{
			if (pur.getLectureid() == RecordId)
			{
				*p = pur;
				ret = recaddr;
				break;
			}
		}

		else if (flag == 3)
		{
			if (pur == RecordId)
			{
				*p = pur;
				ret = recaddr;
				break;
			}
		}
	}
	PurchaseFile.Close();

	return ret;
}
/*
int InsertPurchase(char *RecordId)
{
	Purchase p;
	Lecture l;
	Member m;
	char buf[256];
	int ret;

	if (strlen(RecordId) != LENPUR)
		return -1;
	else
		p.update_purchaseid(RecordId);

	cout << "Lecture ID를 입력하세요 : ";
	cin >> buf;
	if (strlen(buf) != LENLEC)
		return -1;

	ret = SearchLecture(buf, &l);
	if (ret == -1)
		return -1;
	else
		p.update_lectureid(buf);

	cout << "Member ID를 입력하세요 : ";
	cin >> buf;
	ret = SearchMember(buf, &m);
	if (ret == -1)
		return -1;
	else
		p.update_memberid(string(buf));

	cout << "Mileage를 입력하세요 : ";
	cin >> buf;
	if (strlen(buf) != LENMIL)
		return -1;
	else
		p.update_mileage(buf);

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Purchase> PurchaseFile(buffer);
	PurchaseFile.Open("fileOfPurchase.dat", ios::in | ios::out | ios::app);
	if (PurchaseFile.Write(p) == -1) {
		cout << "Write Error!" << endl;
	}
	PurchaseFile.Close();

	return 1;
}
*/
int DeletePurchase(char *RecordId)
{
	bool flag = false;
	int idx = 0, recaddr, ifs_last;
	Purchase p;
	Purchase *purchase_record = new Purchase[MAXPURBUF];
	ifstream ifs("fileOfPurchase.dat");

	if (ifs.fail())
	{
		cout << "Open Error!" << endl;
		return -1;
	}

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Purchase> PurchaseFile(buffer);
	PurchaseFile.Open("fileOfPurchase.dat", ios::in);

	ifs.clear();
	ifs.seekg(0, ifs.end);
	ifs_last = ifs.tellg();
	ifs.seekg(0, ifs.beg);
	while (recaddr = PurchaseFile.Read(p) != -1)
	//while (ifs.tellg() < ifs_last)
	{
		if (p != RecordId && p.getLectureid() != RecordId && p.getMemberid() != RecordId)
		{
			purchase_record[idx++] = p;
		}
		else
		{
			flag = true;
		//	ifs.seekg(p.get_length(), ifs.cur);
		}
		//ifs.seekg(p.get_length(), ifs.cur);
	}
	PurchaseFile.Close();

	if (flag == false)
		return -1;

	PurchaseFile.Create("fileOfPurchase.dat", ios::out | ios::trunc);
	for (int i = 0; i < idx; i++)
	{
		if ((recaddr = PurchaseFile.Write(purchase_record[i])) == -1)
			cout << "Write Error!" << endl;
	}
	PurchaseFile.Close();
	ifs.close();

	return 1;
}
/*
int UpdatePurchase(char *RecordId)
{
	bool flag = false;
	int idx = 0, recaddr;
	string buf;
	Purchase p, update_p;
	Purchase *purchase_record = new Purchase[MAXPURBUF];

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Purchase> PurchaseFile(buffer);
	PurchaseFile.Open("fileOfPurchase.dat", ios::in);
	while (recaddr = PurchaseFile.Read(p) != -1)
	{
		if (p != RecordId)
		{
			purchase_record[idx++] = p;
		}
		else
		{
			flag = true;

			if (strlen(RecordId) != LENPUR)
				return -1;
			else
				p.update_purchaseid(RecordId);

			cout << "Lecture ID를 입력하세요 : ";
			cin >> buf;

			if (buf.size() != LENLEC)
				return -1;
			else
				p.update_lectureid(buf.c_str());

			cout << "Member ID를 입력하세요 : ";
			cin >> buf;
			p.update_memberid(buf);

			cout << "Mileage를 입력하세요 : ";
			cin >> buf;

			if (buf.size() != LENMIL)
				return -1;
			else
				p.update_mileage(buf.c_str());

			purchase_record[idx++] = p;
		}
	}
	PurchaseFile.Close();

	if (flag == false)
		return -1;

	PurchaseFile.Create("fileOfPurchase.dat", ios::out | ios::trunc);
	for (int i = 0; i < idx; i++)
	{
		if ((recaddr = PurchaseFile.Write(purchase_record[i])) == -1)
			cout << "Write Error!" << endl;
	}
	PurchaseFile.Close();

	return 1;
}
*/
int SearchUserPurchase(char *RecordId)
{
	int ret = -1;
	int recaddr;
	int cnt = 0;
	Purchase pur;
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Purchase> PurchaseFile(buffer);

	PurchaseFile.Open("fileOfPurchase.dat", ios::in);
	while ((recaddr = PurchaseFile.Read(pur)) != -1)
	{
		if (pur.getMemberid() == RecordId)
		{
			cout << pur << endl;
			ret++;
		}
	}
	PurchaseFile.Close();

	return ret;
}

int InsertUserPurchase(char *RecordId, char *Login_id)
{
	Purchase p;
	Lecture l;
	Member m;
	char buf[256];
	int ret;

	if (strlen(RecordId) != LENPUR)
		return -1;
	else
		p.update_purchaseid(RecordId);

	cout << "Lecture ID를 입력하세요 : ";
	cin >> buf;
	if (strlen(buf) != LENLEC)
		return -1;

	ret = SearchLecture(buf, &l);
	if (ret == -1)
		return -1;
	else
		p.update_lectureid(buf);


	p.update_memberid(string(Login_id));

	cout << "Mileage를 입력하세요 : ";
	cin >> buf;
	if (strlen(buf) != LENMIL)
		return -1;
	else
		p.update_mileage(buf);

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Purchase> PurchaseFile(buffer);
	PurchaseFile.Open("fileOfPurchase.dat", ios::in | ios::out | ios::app);
	if (PurchaseFile.Write(p) == -1) {
		cout << "Write Error!" << endl;
	}
	PurchaseFile.Close();

	return 1;
}

int DeleteUserPurchase(char *RecordId)
{
	bool flag = false;
	int idx = 0, recaddr, ifs_last;
	Purchase p;
	Purchase *purchase_record = new Purchase[MAXPURBUF];
	ifstream ifs("fileOfPurchase.dat");

	if (ifs.fail())
	{
		cout << "Open Error!" << endl;
		return -1;
	}

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Purchase> PurchaseFile(buffer);
	PurchaseFile.Open("fileOfPurchase.dat", ios::in);

	ifs.clear();
	ifs.seekg(0, ifs.end);
	ifs_last = ifs.tellg();
	ifs.seekg(0, ifs.beg);
	while (recaddr = PurchaseFile.Read(p) != -1)
	{
		if (p.getMemberid() == RecordId)
		{
			flag = true;
		}
		else
		{
			purchase_record[idx++] = p;
		}
	}
	/*
	while (ifs.tellg() < ifs_last)
	{
		if (p.getMemberid() == RecordId)
		{
			flag = true;
			ifs.seekg(p.get_length(), ifs.cur);
		}
		else
		{
			purchase_record[idx++] = p;
		}
	}
	*/
	PurchaseFile.Close();

	if (flag == false)
		return -1;

	PurchaseFile.Create("fileOfPurchase.dat", ios::out | ios::trunc);
	for (int i = 0; i < idx; i++)
	{
		if ((recaddr = PurchaseFile.Write(purchase_record[i])) == -1)
			cout << "Write Error!" << endl;
	}
	PurchaseFile.Close();
	ifs.close();

	return 1;
}

int UpdateUserPurchase(char *RecordId, char *Login_id)
{
	bool flag = false;
	int idx = 0, recaddr;
	string buf;
	Purchase p, update_p;
	Purchase *purchase_record = new Purchase[MAXPURBUF];

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Purchase> PurchaseFile(buffer);
	PurchaseFile.Open("fileOfPurchase.dat", ios::in);
	while (recaddr = PurchaseFile.Read(p) != -1)
	{
		if (p != RecordId)
		{
			purchase_record[idx++] = p;
		}
		else
		{
			if (p.getMemberid() != Login_id)
				return -1;

			flag = true;

			if (strlen(RecordId) != LENPUR)
				return -1;
			else
				p.update_purchaseid(RecordId);

			cout << "Lecture ID를 입력하세요 : ";
			cin >> buf;

			if (buf.size() != LENLEC)
				return -1;
			else
				p.update_lectureid(buf.c_str());

			cout << "Mileage를 입력하세요 : ";
			cin >> buf;

			if (buf.size() != LENMIL)
				return -1;
			else
				p.update_mileage(buf.c_str());

			purchase_record[idx++] = p;
		}
	}
	PurchaseFile.Close();

	if (flag == false)
		return -1;

	PurchaseFile.Create("fileOfPurchase.dat", ios::out | ios::trunc);
	for (int i = 0; i < idx; i++)
	{
		if ((recaddr = PurchaseFile.Write(purchase_record[i])) == -1)
			cout << "Write Error!" << endl;
	}
	PurchaseFile.Close();

	return 1;
}

int set_purnum()
{
	ifstream ifs("listOfPurchase.txt");
	if(ifs.fail())
	{
		cout << "File Open error!" << endl;
		return -1;
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	return n;
}

void make_Purchase()
{
	ifstream ifs("listOfPurchase.txt");

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Purchase> PurchaseFile(buffer);

	PurchaseFile.Create("fileOfPurchase.dat", ios::out | ios::trunc);
	for(int i = 0; i < 100; i++)
	{
		Purchase p;
		ifs >> p;
		p.update_key((char)i+1);
		int recaddr;
		if((recaddr = PurchaseFile.Write(p)) == -1)
			cout << "Write Error!" << endl;
	}
	PurchaseFile.Close();
	ifs.close();
}

char Purchase::Key() {
	return key;
}