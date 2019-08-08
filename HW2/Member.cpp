#include "Member.h"
#include "Lecture.h"
#include "Purchase.h"
#include <sstream>

Member::Member()
{
}

Member::Member(const Member &m)
{
	update_id(m.ID);
	update_password(m.Password);
	update_name(m.Name);
	update_phonenumber(m.Phone_Number);
	update_address(m.Address);
	update_mileage(m.Mileage);
	update_level(m.Level);
}

Member::Member(const char *ID)
{
	update_id(ID);
}

Member & Member::operator = (const Member &m)
{
	update_id(m.ID);
	update_password(m.Password);
	update_name(m.Name);
	update_phonenumber(m.Phone_Number);
	update_address(m.Address);
	update_mileage(m.Mileage);
	update_level(m.Level);

	return *this;
}

bool Member::operator == (const Member &m)
{
	if(!ID.compare(m.ID))
		return true;

	return false;
}

bool Member::operator != (const Member &m)
{
	if(!ID.compare(m.ID))
		return false;

	return true;
}

istream & operator >> (istream &is, Member &m)
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
	m.update_id(token);

	getline(iss, token, '|');
	m.update_password(token);

	getline(iss, token, '|');
	m.update_name(token);

	getline(iss, token, '|');
	m.update_phonenumber(token);

	getline(iss, token, '|');
	m.update_address(token);

	getline(iss, token, '|');
	m.update_mileage(token.data());

	getline(iss, token, '|');
	m.update_level(token.data());

	return is;
}

ostream & operator << (ostream &os, Member &m)
{
	string mileage(m.Mileage, LENMIL);
	string level(m.Level, LENLEV);

	cout << "ID : " << m.ID << endl;
	cout << "Password : " << m.Password << endl;
	cout << "Name : " << m.Name << endl;
	cout << "Phone Number : " << m.Phone_Number << endl;
	cout << "Address : " << m.Address << endl;
	cout << "Mileage : " << mileage << endl;
	cout << "Level : " << level << endl;

	return os;
}

bool Member::Pack(IOBuffer & Buffer) const
{
	int numBytes;

	Buffer.Clear();

	string s_mileage(Mileage, LENMIL);
	string s_level(Level, LENLEV);

	numBytes = Buffer.Pack(ID.c_str());
	if(numBytes == -1) return false;
	numBytes = Buffer.Pack(Password.c_str());
	if(numBytes == -1) return false;
	numBytes = Buffer.Pack(Name.c_str());
	if(numBytes == -1) return false;
	numBytes = Buffer.Pack(Phone_Number.c_str());
	if(numBytes == -1) return false;
	numBytes = Buffer.Pack(Address.c_str());
	if(numBytes == -1) return false;
	numBytes = Buffer.Pack(s_mileage.c_str());
	if(numBytes == -1) return false;
	numBytes = Buffer.Pack(s_level.c_str());
	if(numBytes == -1) return false;

	return true;
}

bool Member::Unpack(IOBuffer & Buffer)
{
	int numBytes;
	char buf[STDMAXBUF];

	numBytes = Buffer.Unpack(buf);
	if(numBytes == -1) return false;
	ID = buf;
	numBytes = Buffer.Unpack(buf);
	if(numBytes == -1) return false;
	Password = buf;
	numBytes = Buffer.Unpack(buf);
	if(numBytes == -1) return false;
	Name = buf;
	numBytes = Buffer.Unpack(buf);
	if(numBytes == -1) return false;
	Phone_Number = buf;
	numBytes = Buffer.Unpack(buf);
	if(numBytes == -1) return false;
	Address = buf;
	numBytes = Buffer.Unpack(Mileage, LENMIL);
	if(numBytes == -1) return false;
	numBytes = Buffer.Unpack(Level, LENLEV);
	if(numBytes == -1) return false;

	return true;
}

void showMember()
{
	ifstream ifs("listOfMember.txt");
	if(ifs.fail())
	{
		cout << "File Open error!" << endl;
		return;
	}

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	for(int i = 0; i < 10; i++)
	{
		Member m;
		ifs >> m;
		cout << m;
	}
}

void MemberTest()
{
	ifstream ifs("listOfMember.txt");

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> MemberFile(buffer);

	MemberFile.Create("fileOfMember.dat", ios::out | ios::trunc);
	for(int i = 0; i < n; i++)
	{
		Member m;
		ifs >> m;
		int recaddr;
		if((recaddr = MemberFile.Write(m)) == -1)
			cout << "Write Error!" << endl;
	}
	MemberFile.Close();

	MemberFile.Open("fileOfMember.dat", ios::in);
	for(int i = 0; i < 10; i++)
	{
		Member m;
		MemberFile.Read(m);
		cout << m;
	}
	MemberFile.Close();
}

int SearchMember(char *RecordId, Member *m)
{
	int ret = -1;
	int recaddr;
	Member mem;
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> MemberFile(buffer);

	MemberFile.Open("fileOfMember.dat", ios::in);
	while((recaddr = MemberFile.Read(mem)) != -1)
	{
		if(mem == RecordId)
		{
			*m = mem;
			ret = recaddr;
			break;
		}
	}
	MemberFile.Close();

	return ret;
}

int InsertMember(char *RecordId, int num)
{
	Member m;
	string buf;
	int level;
	char s_level[2];

	m.update_id(string(RecordId));

	cout << "Password를 입력하세요 : ";
	cin >> buf;
	m.update_password(buf);

	cout << "Name을 입력하세요 : ";
	cin >> buf;
	m.update_name(buf);

	cout << "Phone Number를 입력하세요 : ";
	cin >> buf;
	m.update_phonenumber(buf);

	cout << "Address를 입력하세요 : ";
	cin >> buf;
	m.update_address(buf);

	cout << "Mileage를 입력하세요 : ";
	cin >> buf;

	if (buf.size() != LENMIL)
		return -1;

	m.update_mileage(buf.c_str());

	cout << "Level을 입력하세요 : ";
	cin >> level;

	if (level != 1 && level != 9)
		return -1;

	s_level[0] = level + '0';
	s_level[1] = '\0';
	m.update_level(s_level);

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> MemberFile(buffer);
	MemberFile.Open("fileOfMember.dat", ios::in | ios::out | ios::app);
	if (MemberFile.Write(m) == -1) {
		cout << "Write Error!" << endl;
	}
	MemberFile.Close();

	DelimFieldBuffer buffer1('|', STDMAXBUF);
	TextIndexedFile<Member> mmdIdxedFile(buffer1, 11, num);
	mmdIdxedFile.Open("fileOfMember");

	mmdIdxedFile.Append(m);
	mmdIdxedFile.Close();

	return 1;
}

int DeleteMember(char *RecordId, int num)
{
	bool flag = false;
	int idx = 0, recaddr, ifs_last;
	Member m;
	Member *member_record = new Member[MAXMEMBUF];
	ifstream ifs("fileOfMember.dat");

	if(ifs.fail())
	{
		cout << "Open Error!" << endl;
		return -1;
	}
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> MemberFile(buffer);
	MemberFile.Open("fileOfMember.dat", ios::in);

	ifs.clear();
	ifs.seekg(0, ifs.end);
	ifs_last = ifs.tellg();
	ifs.seekg(0, ifs.beg);
	while(ifs.tellg() < ifs_last)
	{
		MemberFile.Read(m);
		if(m != RecordId)
		{
			member_record[idx++] = m;
		}
		else
		{
			flag = true;
			ifs.seekg(m.get_length(), ifs.cur);
		}
		ifs.seekg(m.get_length(), ifs.cur);
	}
	MemberFile.Close();

	if(flag == false)
		return -1;

	MemberFile.Create("fileOfMember.dat", ios::out | ios::trunc);
	for(int i = 0; i < idx; i++)
	{
		if((recaddr = MemberFile.Write(member_record[i])) == -1)
			cout << "Write Error!" << endl;
	}
	MemberFile.Close();
	ifs.close();

	DeletePurchase(RecordId);

	TextIndex MemberIndex(num - 1);

	MemberFile.Open("fileOfMember.dat", ios::in);
	while(1)
	{
		Member m;
		int recaddr = MemberFile.Read(m);
		if(recaddr == -1) break;
		MemberIndex.Insert(m.Key(), recaddr);
	}
	MemberFile.Close();

	TextIndexBuffer idxbuf(11, num - 1);
	BufferFile MemIdxFile(idxbuf);
	MemIdxFile.Create("fileOfMember.ind", ios::out | ios::trunc);
	MemIdxFile.Rewind();
	idxbuf.Pack(MemberIndex);
	int result = MemIdxFile.Write();
	MemIdxFile.Close();

	return 1;
}

int UpdateMember(char *RecordId, int num)
{
	bool flag = false;
	int idx = 0, recaddr, ifs_last;
	string buf;
	Member m, update_m;
	Member *member_record = new Member[MAXMEMBUF];

	DelimFieldBuffer buffer('|', 1000);
	RecordFile <Member> MemberFile(buffer);
	while(recaddr = MemberFile.Read(m) != -1)
	{
		if(m != RecordId)
		{
			member_record[idx++] = m;
		}
		else
		{
			flag = true;
			update_m.update_id(string(RecordId));

			cout << "Password를 입력하세요 : ";
			cin >> buf;
			update_m.update_password(buf);

			cout << "Name을 입력하세요 : ";
			cin >> buf;
			update_m.update_name(buf);

			cout << "Phone Number를 입력하세요 : ";
			cin >> buf;
			update_m.update_phonenumber(buf);

			cout << "Address를 입력하세요 : ";
			cin >> buf;
			update_m.update_address(buf);

			cout << "Mileage를 입력하세요 : ";
			cin >> buf;
			if(buf.size() != LENMIL)
				return -1;
			else
				update_m.update_mileage(buf.c_str());

			member_record[idx++] = update_m;
		}
	}
	MemberFile.Close();

	if(flag == false)
		return -1;

	MemberFile.Create("fileOfMember.dat", ios::out | ios::trunc);
	for(int i = 0; i < idx; i++)
	{
		if((recaddr = MemberFile.Write(member_record[i])) == -1)
			cout << "Write Error!" << endl;
	}
	MemberFile.Close();

	TextIndex MemberIndex(num);

	MemberFile.Open("fileOfMember.dat", ios::in);
	while(1)
	{
		Member m;
		int recaddr = MemberFile.Read(m);
		if(recaddr == -1) break;
		MemberIndex.Insert(m.Key(), recaddr);
	}
	MemberFile.Close();

	TextIndexBuffer idxbuf(11, num);
	BufferFile MemIdxFile(idxbuf);
	MemIdxFile.Create("fileOfMember.ind", ios::out | ios::trunc);
	MemIdxFile.Rewind();
	idxbuf.Pack(MemberIndex);
	int result = MemIdxFile.Write();
	MemIdxFile.Close();
	return 1;
}

int SearchingPwd(char *Id, char *Pwd)
{
	int idx = 0, recaddr, ifs_last;
	Member m;
	Member *member_record = new Member[MAXMEMBUF];
	ifstream ifs("fileOfMember.dat");

	if(ifs.fail())
	{
		cout << "Open Error!" << endl;
		return -1;
	}
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> MemberFile(buffer);
	MemberFile.Open("fileOfMember.dat", ios::in);

	ifs.clear();
	ifs.seekg(0, ifs.end);
	ifs_last = ifs.tellg();
	ifs.seekg(0, ifs.beg);
	while(ifs.tellg() < ifs_last)
	{
		MemberFile.Read(m);
		
		if(m == Id && m.get_pwd() == string(Pwd))
		{
			MemberFile.Close();
			ifs.close();
			
			return (int)(m.get_level() - '0');
		}
		
		ifs.seekg(m.get_length(), ifs.cur);
	}
	MemberFile.Close();
	ifs.close();

	return 0;
}

char *Member::Key() {
	key.assign(ID.c_str(), strlen(ID.c_str()));
	return (char *)(key.c_str());
}

int set_memnum()
{
	ifstream ifs("listOfMember.txt");
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

void make_Member()
{
	ifstream ifs("listOfMember.txt");

	int n;
	ifs >> n;
	ifs.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> MemberFile(buffer);

	MemberFile.Create("fileOfMember.dat", ios::out | ios::trunc);
	for(int i = 0; i < n; i++)
	{
		Member m;
		ifs >> m;
		int recaddr;
		if((recaddr = MemberFile.Write(m)) == -1)
			cout << "Write Error!" << endl;
	}
	MemberFile.Close();
}