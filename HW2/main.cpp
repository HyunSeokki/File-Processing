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
	int instruction = 0, input, recaddr, access_level;
	int mem_num = 0, lec_num = 0, pur_num = 0;
	char selected_menu[4][5] = { "�˻�", "����", "����", "����" };
	char selected_record[3][5] = { "ȸ��", "����", "����" };
	char selected_level[2][20] = { "������ ���", "����� ���" };
	char RecordId[256], Login_id[256], Login_pwd[256];
	
	Member m;
	Lecture l;
	Purchase p;

	make_Member();
	make_Lecture();
	make_Purchase();
	mem_num = set_memnum();
	lec_num = set_lecnum();
	pur_num = set_purnum();
	Make_indexfile(mem_num, lec_num);

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
			system("cls");

			cout << "===================================================" << endl;
			cout << "\t �˻��� ID�� �����ϼ���." << endl;
			cout << "1. ȸ�� ID" << endl;
			cout << "2. ���� ID" << endl;
			cout << "3. ���� ID" << endl;
			cout << "\n\t�ش��ϴ� �޴��� ��ȣ�� �Է��ϼ���." << endl;
			cout << "===================================================" << endl;
			cout << "Input : ";
			cin >> input;

			cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
			cin >> RecordId;

			if (1 <= input && input <= 3)
			{
				recaddr = SearchPurchase(RecordId, &p, input);
				if (recaddr == -1)
					cout << "�ش� ���ڵ尡 �������� �ʽ��ϴ�." << endl;
				else
					cout << p;
			}
			else
			{
				cout << "" << endl;
				return;
			}
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
		cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
		cin >> RecordId;

		if (access_level == 9)
		{
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
		cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
		cin >> RecordId;

		if (access_level == 9)
		{
			recaddr = UpdateUserPurchase(RecordId, Login_id);

			if (recaddr == -1)
				cout << "�ش� ���ڵ尡 �������� �ʰų� �ڽ��� ȸ�������� �ƴմϴ�." << endl;
			else
				cout << "�ش� ���ڵ尡 �����Ǿ����ϴ�." << endl;
		}
		else
		{
			recaddr = UpdatePurchase(RecordId);

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
}