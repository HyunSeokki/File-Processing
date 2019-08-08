#include "main.h"

int main()
{
	int input;

	while (true)
	{
		cout << "===================================================" << endl;
		cout << "\t\t�޴��� �����ϼ���." << endl;
		cout << "1. showMember" << endl;
		cout << "2. showLecture" << endl;
		cout << "3. showPurchase" << endl;
		cout << "4. MemberTest" << endl;
		cout << "5. LectureTest" << endl;
		cout << "6. PurchaseTest" << endl;
		cout << "7. LecturePurchaseSystem" << endl;
		cout << "8. EXIT" << endl;
		cout << "\n\t�ش��ϴ� �޴��� ��ȣ�� �Է��ϼ���." << endl;
		cout << "===================================================" << endl;
		cin.clear();

		cout << "Input : ";
		cin >> input;

		if (input == 1)
			showMember();

		else if (input == 2)
			showLecture();

		else if (input == 3)
			showPurchase();

		else if (input == 4)
			MemberTest();

		else if (input == 5)
			LectureTest();

		else if (input == 6)
			PurchaseTest();

		else if (input == 7)
			LecturePurchaseSystem();

		else if (input == 8)
			exit(0);

		else
		{
			system("cls");
			continue;
		}
		cout << "Press Enter key to continue." << endl;
		cin.ignore();	cin.get();
		system("cls");
	}

	return 0;
}

void LecturePurchaseSystem()
{
	int instruction = 0, input, recaddr, access_level, want_key_int, want_key_search;	
	char selected_menu[4][5] = { "�˻�", "����", "����", "����" };
	char selected_record[3][5] = { "ȸ��", "����", "����" };
	char selected_level[2][20] = { "������ ���", "����� ���" };
	char RecordId[256], Login_id[256], Login_pwd[256], want_key_char = 0;
	string want_key_str;

	Member m;
	Lecture l;
	Purchase p;

	if(!make_flag)
	{
		mem_num = set_memnum();
		lec_num = set_lecnum();
		//pur_num = set_purnum();
		pur_num = 100;
		make_Member();
		make_Lecture();
		make_Purchase();
		Make_indexfile(mem_num, lec_num);
		make_flag = true;
	}
	
	while (true)
	{
		cout << "Login ID : ";
		cin >> Login_id;
		cout << "Password : ";
		cin >> Login_pwd;
		
		access_level = SearchingPwd(Login_id, Login_pwd);
		if (access_level == 0)
		{
			cout << "Wrong Id or Password." << endl;
			continue;
		}
		break;
	}

	system("cls");
	cout << "===================================================" << endl;
	cout << "\t\t�޴��� �����ϼ���.(" << selected_level[access_level == 1 ? 0 : 1] << ")" << endl;
	cout << "1. ���ڵ� �˻�" << endl;
	cout << "2. ���ڵ� ����" << endl;
	cout << "3. ���ڵ� ����" << endl;
	cout << "4. ���ڵ� ����" << endl;
	cout << "\n\t�ش��ϴ� �޴��� ��ȣ�� �Է��ϼ���." << endl;
	cout << "===================================================" << endl;
	cin.clear();

	cout << "Input : ";
	cin >> input;

	if (input < 1 || input > 4)
	{
		cout << "" << endl;
		return;
	}
	instruction = input * 10;

	system("cls");
	cout << "===================================================" << endl;
	cout << "\t" << selected_menu[input - 1] << "�� ���ڵ带 �����ϼ���." << endl;
	cout << "1. ȸ�� ���ڵ�" << endl;
	cout << "2. ���� ���ڵ�" << endl;
	cout << "3. ���� ���ڵ�" << endl;
	cout << "\n\t�ش��ϴ� �޴��� ��ȣ�� �Է��ϼ���." << endl;
	cout << "===================================================" << endl;
	cin.clear();

	cout << "Input : ";
	cin >> input;

	if (input < 1 || input > 3)
	{
		cout << "" << endl;
		return;
	}

	instruction += input;

	if (instruction == 11)
	{
		if (access_level == 9)
		{
			cout << "������ ��带 ������ּ���." << endl;
		}
		else
		{
			cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
			cin >> RecordId;
			recaddr = SearchMember(RecordId, &m);
			if (recaddr == -1)
				cout << "�ش� ���ڵ尡 �������� �ʽ��ϴ�." << endl;
			else
				cout << m;
		}
	}

	else if (instruction == 12)
	{
		cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
		cin >> RecordId;
		recaddr = SearchLecture(RecordId, &l);
		if (recaddr == -1)
			cout << "�ش� ���ڵ尡 �������� �ʽ��ϴ�." << endl;
		else
			cout << l;
	}

	else if (instruction == 13)
	{
		if (access_level == 9)
		{
			if (SearchUserPurchase(Login_id) == -1)
				cout << "�ش� ���ڵ尡 �������� �ʽ��ϴ�." << endl;
		}
		else
		{
			// key�� �Է¹޾� �ش� key�� �������� b-tree�� ���� �˻��ϴ� ����.
			// SearchingbyID�Լ��� Search, Insert, Modify, Delete���� ��� ���Ǳ� ������
			// ���ȭ �Ͽ� �����ϱ� ���ϰ� �����Ͽ���.

			cout << "==================================" << endl;
			cout << "Finding ID's key (1<= key <=127)" << endl;;
			cout << "==================================" << endl;

			cin >> want_key_str;
			want_key_int = atoi(want_key_str.c_str());
			if(want_key_int < 1 || want_key_int > 127)
			{
				cout << "You have wrong key." << endl;
				return ;
			}
			want_key_char = (char)want_key_int;
			world_key = want_key_char;
			
			want_key_search = bt.Search(want_key_char);

			if(want_key_search != -1)
			{
				Purchase p_temp;
				DelimFieldBuffer buffer('|', 1200);
				RecordFile <Purchase> PurchaseFile(buffer);
				PurchaseFile.Open("fileOfPurchase.dat", ios::in);
				PurchaseFile.Read(p_temp, want_key_search);
				PurchaseFile.Close();
				cout << p_temp;
			}
			else
				cout << "Not founded: " << want_key_str << endl;
			
			getchar();		
		}
	}

	else if (instruction == 21)
	{
		if (access_level == 9)
		{
			cout << "������ ��带 ������ּ���." << endl;
		}
		else
		{
			cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
			cin >> RecordId;

			recaddr = SearchMember(RecordId, &m);

			if (recaddr == -1)
			{
				if (InsertMember(RecordId, mem_num) == -1)
					cout << "������ �����߽��ϴ�." << endl;
				else
				{
					mem_num++;
					cout << "������ �����߽��ϴ�." << endl;					
				}					
			}
			else
			{
				cout << "�ش� ID�� �����մϴ�." << endl;
			}
		}
	}

	else if (instruction == 22)
	{
		if (access_level == 9)
		{
			cout << "������ ��带 ������ּ���." << endl;
		}
		else
		{
			cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
			cin >> RecordId;

			recaddr = SearchLecture(RecordId, &l);

			if (recaddr == -1)
			{
				if (InsertLecture(RecordId,lec_num) == -1)
					cout << "������ �����߽��ϴ�." << endl;
				else
				{
					lec_num++;
					cout << "������ �����߽��ϴ�." << endl;
				}					
			}
			else
			{
				cout << "�ش� ID�� �����մϴ�." << endl;
			}
		}
	}

	else if (instruction == 23)
	{
		if (access_level == 9)
		{
			cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
			cin >> RecordId;

			recaddr = SearchPurchase(RecordId, &p, 3);

			if (recaddr == -1)
			{
				if (InsertUserPurchase(RecordId, Login_id) == -1)
					cout << "������ �����߽��ϴ�." << endl;
				else
				{
					pur_num++;
					cout << "������ �����߽��ϴ�." << endl;
				}					
			}
			else
			{
				cout << "�ش� ID�� �����մϴ�." << endl;
			}
		}
		else
		{
			cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
			cin >> RecordId;

			recaddr = SearchPurchase(RecordId, &p, 3);

			if (recaddr == -1)
			{
				if (InsertPurchase(RecordId) == -1)
					cout << "������ �����߽��ϴ�." << endl;
				else
				{
					pur_num++;
					cout << "������ �����߽��ϴ�." << endl;
				}					
			}
			else
			{
				cout << "�ش� ID�� �����մϴ�." << endl;
			}
		}
	}

	else if (instruction == 31)
	{
		cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
		cin >> RecordId;

		if (access_level == 9)
		{
			if (strcmp(RecordId, Login_id))
				cout << "�ڽ��� ȸ�������� ���� �����մϴ�." << endl;
			else
			{
				recaddr = DeleteMember(RecordId, mem_num);

				if (recaddr == -1)
					cout << "�ش� ���ڵ尡 �������� �ʽ��ϴ�." << endl;
				else
				{
					mem_num--;
					cout << "�ش� ���ڵ尡 �����Ǿ����ϴ�." << endl;
				}					
			}
		}
		else
		{
			recaddr = DeleteMember(RecordId, mem_num);

			if (recaddr == -1)
				cout << "�ش� ���ڵ尡 �������� �ʽ��ϴ�." << endl;
			else
			{
				mem_num--;
				cout << "�ش� ���ڵ尡 �����Ǿ����ϴ�." << endl;
			}			
		}
	}

	else if (instruction == 32)
	{
		if (access_level == 9)
		{
			cout << "������ ��带 ������ּ���." << endl;
		}
		else
		{
			cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
			cin >> RecordId;

			recaddr = DeleteLecture(RecordId, lec_num);
			
			if (recaddr == -1)
				cout << "�ش� ���ڵ尡 �������� �ʽ��ϴ�." << endl;
			else
			{
				lec_num--;
				cout << "�ش� ���ڵ尡 �����Ǿ����ϴ�." << endl;
			}				
		}
	}

	else if (instruction == 33)
	{		
		if (access_level == 9)
		{
			cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
			cin >> RecordId;

			if (strcmp(RecordId, Login_id))
				cout << "�ڽ��� ȸ�������� ���� �����մϴ�." << endl;
			else
			{
				recaddr = DeletePurchase(RecordId);

				if (recaddr == -1)
					cout << "�ش� ���ڵ尡 �������� �ʽ��ϴ�." << endl;
				else
				{
					pur_num--;
					cout << "�ش� ���ڵ尡 �����Ǿ����ϴ�." << endl;
				}					
			}
		}
		else
		{
			//recaddr = DeletePurchase(RecordId);
			recaddr = DeleteKey();
			if (recaddr == -1)
				cout << "�ش� ���ڵ尡 �������� �ʽ��ϴ�." << endl;
			else
			{
				pur_num--;
				cout << "�ش� ���ڵ尡 �����Ǿ����ϴ�." << endl;
			}				
		}
	}

	else if (instruction == 41)
	{
		cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
		cin >> RecordId;

		if (access_level == 9)
		{
			if (strcmp(RecordId, Login_id))
				cout << "�ڽ��� ȸ�������� ���� �����մϴ�." << endl;
			else
				UpdateMember(RecordId, mem_num);
		}
		else
		{
			recaddr = UpdateMember(RecordId, mem_num);

			if (recaddr == -1)
				cout << "�ش� ���ڵ尡 �������� �ʽ��ϴ�." << endl;
			else
				cout << "�ش� ���ڵ尡 �����Ǿ����ϴ�." << endl;
		}
	}

	else if (instruction == 42)
	{
		if (access_level == 9)
		{
			cout << "������ ��带 ������ּ���." << endl;
		}
		else
		{
			cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
			cin >> RecordId;

			recaddr = UpdateLecture(RecordId, lec_num);

			if (recaddr == -1)
				cout << "�ش� ���ڵ尡 �������� �ʽ��ϴ�." << endl;
			else
				cout << "�ش� ���ڵ尡 �����Ǿ����ϴ�." << endl;
		}
	}

	else if (instruction == 43)
	{
		if (access_level == 9)
		{
			cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
			cin >> RecordId;

			recaddr = UpdateUserPurchase(RecordId, Login_id);

			if (recaddr == -1)
				cout << "�ش� ���ڵ尡 �������� �ʰų� �ڽ��� ȸ�������� �ƴմϴ�." << endl;
			else
				cout << "�ش� ���ڵ尡 �����Ǿ����ϴ�." << endl;
		}
		else
		{
			recaddr = UpdatePurchase();

			if (recaddr == -1)
				cout << "�ش� ���ڵ尡 �������� �ʽ��ϴ�." << endl;
			else
				cout << "�ش� ���ڵ尡 �����Ǿ����ϴ�." << endl;
		}
	}
}

void Make_indexfile(int mem_num, int lec_num)
{
	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> MemberFile(buffer);

	TextIndex MemberIndex(mem_num);

	MemberFile.Open("fileOfMember.dat", ios::in);
	while (1) 
	{
		Member m;
		int recaddr = MemberFile.Read(m);
		if (recaddr == -1) break;
		MemberIndex.Insert(m.Key(), recaddr);
	}
	MemberFile.Close();

	TextIndexBuffer idxbuf(11, mem_num);
	BufferFile MemIdxFile(idxbuf);
	MemIdxFile.Create("fileOfMember.ind", ios::out | ios::trunc);
	MemIdxFile.Rewind(); 
	idxbuf.Pack(MemberIndex);
	int result = MemIdxFile.Write();
	MemIdxFile.Close();

	//---------------------------------------

	DelimFieldBuffer buffer1('|', STDMAXBUF);
	RecordFile <Lecture> LectureFile(buffer1);

	TextIndex LectureIndex(lec_num);

	LectureFile.Open("fileOfLecture.dat", ios::in);
	while (1) 
	{
		Lecture l;
		int recaddr = LectureFile.Read(l);
		if (recaddr == -1) break;
		LectureIndex.Insert(l.Key(), recaddr);		
	}
	LectureFile.Close();

	TextIndexBuffer lecidxbuf(12, lec_num);
	BufferFile LecIdxFile(lecidxbuf);
	LecIdxFile.Create("fileOfLecture.ind", ios::out | ios::trunc);
	LecIdxFile.Rewind();
	lecidxbuf.Pack(LectureIndex);
	result = LecIdxFile.Write();
	LecIdxFile.Close();

	//---------------------------------------

	DelimFieldBuffer buffer2('|', 1200);
	RecordFile <Purchase> PurchaseFile(buffer2);
	result = bt.Create("fileOfPurchase.ind", ios::in | ios::out | ios::trunc);
	if(!result) 
	{ 
		cout << "Please delete fileOfPurchase.ind" << endl;
		return ; 
	}

	PurchaseFile.Open("fileOfPurchase.dat", ios::in);
	char key = 1;
	while(1) 
	{
		Purchase p;
		int recaddr = PurchaseFile.Read(p);
		if(recaddr == -1) break;
		p.update_key(key);
		bt.Insert(p.Key(), recaddr);
		key += 1;
		world_key++;
	}
	PurchaseFile.Close();
}

int InsertPurchase(char *RecordId)
{
	Purchase p;
	Lecture l;
	Member m;
	char buf[256];
	int ret, recaddr, idx = 0;

	if(strlen(RecordId) != LENPUR)
		return -1;
	else
		p.update_purchaseid(RecordId);

	cout << "Lecture ID�� �Է��ϼ��� : ";
	cin >> buf;
	if(strlen(buf) != LENLEC)
		return -1;

	ret = SearchLecture(buf, &l);
	if(ret == -1)
		return -1;
	else
		p.update_lectureid(buf);

	cout << "Member ID�� �Է��ϼ��� : ";
	cin >> buf;
	ret = SearchMember(buf, &m);
	if(ret == -1)
		return -1;
	else
		p.update_memberid(string(buf));

	cout << "Mileage�� �Է��ϼ��� : ";
	cin >> buf;
	if(strlen(buf) != LENMIL)
		return -1;
	else
		p.update_mileage(buf);


	if(world_key < 1 || world_key > 127) //�ƽ�Ű�ڵ� ����. Key�� 1���� 127������ ���. �̿� ���� ���� ������ ���.
	{
		cout << "Exceed key's limit" << endl;
		return -1;
	}
	p.update_key(++world_key);
	cout << "New Key : " << world_key << endl;

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Purchase> PurchaseFile(buffer);
	PurchaseFile.Open("fileOfPurchase.dat", ios::in);
	while(1)
	{
		Purchase p_temp;
		if(PurchaseFile.Read(p_temp) == -1)
			break;
		purchase_arr[idx++] = p_temp;		
	}
	PurchaseFile.Close();

	PurchaseFile.Create("fileOfPurchase.dat", ios::out | ios::trunc);

	for(int i = 0; i<idx; i++)
	{
		recaddr = PurchaseFile.Write(purchase_arr[i]);
	}
	recaddr = PurchaseFile.Write(p); //���� ���Ե� ���ڵ带 ������ ���Ͽ� �߰�.
	PurchaseFile.Close();
	
	bt.Insert(p.Key(), recaddr); // ���� ���Ե� ���ڵ� B-tree�� �߰�.

	return 1;
}

int DeleteKey() {
	int idx = 0, temp_int, recaddr;
	char temp_char;
	string temp;

	cout << "Want key : ";
	cin >> temp;

	temp_int = atoi(temp.c_str());
	temp_char = (char)temp_int;

	if(bt.Search(temp_char) == -1) //key�� ���� Ž�� ��, �ش� key�� ���ڵ尡 �����Ҷ��� b-tree�� data���� ���� ����.
	{ 
		cout << "this key doesn't exist in DB." << endl;
		return -1;
	}
	else 
	{
		DelimFieldBuffer buffer('|', STDMAXBUF);
		RecordFile<Purchase>PurchaseFile(buffer);
		PurchaseFile.Open("fileOfPurchase.dat", ios::in);
		while(1) 
		{
			Purchase p;
			if(PurchaseFile.Read(p) == -1)
				break;

			if(p.Key() == temp_char) 		
				continue;
			
			purchase_arr[idx++] = p;
		}
		PurchaseFile.Close();

		PurchaseFile.Create("fileOfPurchase.dat", ios::out | ios::trunc);
		for(int i = 0; i < idx; i++) 
		{
			/*
			�߰��� ���ڵ尡 �����Ǹ�, ������ ���ڵ��� �ּҿ��� ������ ��ġ�Ƿ�
			�� ��ȭ�� �ּҰ��� �ݿ�.
			*/
			recaddr = PurchaseFile.Write(purchase_arr[i]);
			BTreeNode<char> *BTNode = bt.FindLeaf(purchase_arr[i].Key());
			int find_key = true;
			for(int j = 0; j<BTNode->numKeys(); j++)
			{
				if(BTNode->Keys[j] == purchase_arr[i].Key()) 
				{
					BTNode->RecAddrs[j] = recaddr;
					find_key = false;
					break;
				}
			}
			if(find_key)
				BTNode->RecAddrs[BTNode->numKeys()] = recaddr;
			bt.Store(BTNode);
		}
		bt.Remove(temp_char);			// �����ؾ� �ϴ� ��带 B-tree�� ���� ����
		PurchaseFile.Close();
	}

	return 1;
}

int UpdatePurchase()
{
	int recaddr, idx = 0, temp_int, modify_address = 0;;
	char temp_char;
	string temp;
	DelimFieldBuffer buffer ('|', STDMAXBUF);
	RecordFile<Purchase>PurchaseFile(buffer);

	cout << "Want key : ";
	cin >> temp;

	temp_int = atoi(temp.c_str());
	temp_char = (char)temp_int;

	if(bt.Search(temp_char) == -1) //key�� ���� Ž�� ��, �ش� key�� ���ڵ尡 �����Ҷ��� b-tree�� data���� ���� ����.
	{
		cout << "this key doesn't exist in DB." << endl;
		return -1;
	}
	
	PurchaseFile.Open("fileOfPurchase.dat", ios::in);
	
	while(1)
	{
		Purchase p;
		if(PurchaseFile.Read(p) == -1)
			break;

		if(p.Key() == temp_char) {
			char update_temp[100];
			// �Էµ� key�� ��ġ�ϴ� Purchase ���ڵ带 ã������� ���� ����.

			cout << "Lecture ID�� �Է��ϼ��� : ";
			cin >> update_temp;

			if(strlen(update_temp) != LENLEC)
				return -1;
			else
				p.update_lectureid(update_temp);

			cout << "Member ID�� �Է��ϼ��� : ";
			cin >> temp;
			p.update_memberid(temp);

			cout << "Mileage�� �Է��ϼ��� : ";
			cin >> update_temp;

			if(strlen(update_temp) != LENMIL)
				return -1;
			else
				p.update_mileage(update_temp);

		}
		purchase_arr[idx++] = p;
	}
	PurchaseFile.Close();
	
	PurchaseFile.Create("fileOfPurchase.dat", ios::out | ios::trunc);
	for(int i=0; i<idx; i++)
	{
		recaddr=PurchaseFile.Write(purchase_arr[i]);
		if(world_key == purchase_arr[i].Key())
			modify_address = recaddr;	//������ ���ڵ��� recaddr.
										/*
										������ ���ڵ带 �ϴ� B-tree�� ���� ����.
										���ڵ尡 �����Ǹ�, ������ ���ڵ��� �ּҿ��� ������ ��ġ�Ƿ�
										�� ��ȭ�� �ּҰ��� �ݿ�.
										*/
		BTreeNode<char> *BTNode = bt.FindLeaf(purchase_arr[i].Key());
		bool find_key = true;
		for(int j=0; j<BTNode->numKeys(); j++) 
		{
			if(BTNode->Keys[j] == purchase_arr[i].Key()) 
			{
				BTNode->RecAddrs[j] = recaddr;
				find_key = false;
				break;
			}
		}
		if(find_key)
			BTNode->RecAddrs[BTNode->numKeys()] = recaddr;
		bt.Store(BTNode);
	}
	bt.Remove(world_key);			//������ ���ڵ带 B-tree���� ����.
	bt.Insert(world_key, modify_address);	//������ ���ڵ带 �ٽ� B-tree�� ����.

	PurchaseFile.Close();

	return 1;
}