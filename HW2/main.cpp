#include "main.h"

int main()
{
	int input;

	while (true)
	{
		cout << "===================================================" << endl;
		cout << "\t\t메뉴를 선택하세요." << endl;
		cout << "1. showMember" << endl;
		cout << "2. showLecture" << endl;
		cout << "3. showPurchase" << endl;
		cout << "4. MemberTest" << endl;
		cout << "5. LectureTest" << endl;
		cout << "6. PurchaseTest" << endl;
		cout << "7. LecturePurchaseSystem" << endl;
		cout << "8. EXIT" << endl;
		cout << "\n\t해당하는 메뉴의 번호만 입력하세요." << endl;
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
	char selected_menu[4][5] = { "검색", "삽입", "삭제", "수정" };
	char selected_record[3][5] = { "회원", "강의", "구매" };
	char selected_level[2][20] = { "관리자 모드", "사용자 모드" };
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
	cout << "\t\t메뉴를 선택하세요.(" << selected_level[access_level == 1 ? 0 : 1] << ")" << endl;
	cout << "1. 레코드 검색" << endl;
	cout << "2. 레코드 삽입" << endl;
	cout << "3. 레코드 삭제" << endl;
	cout << "4. 레코드 수정" << endl;
	cout << "\n\t해당하는 메뉴의 번호만 입력하세요." << endl;
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
	cout << "\t" << selected_menu[input - 1] << "할 레코드를 선택하세요." << endl;
	cout << "1. 회원 레코드" << endl;
	cout << "2. 강의 레코드" << endl;
	cout << "3. 구매 레코드" << endl;
	cout << "\n\t해당하는 메뉴의 번호만 입력하세요." << endl;
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
			cout << "관리자 모드를 사용해주세요." << endl;
		}
		else
		{
			cout << selected_record[input - 1] << " ID를 입력하세요 : ";
			cin >> RecordId;
			recaddr = SearchMember(RecordId, &m);
			if (recaddr == -1)
				cout << "해당 레코드가 존재하지 않습니다." << endl;
			else
				cout << m;
		}
	}

	else if (instruction == 12)
	{
		cout << selected_record[input - 1] << " ID를 입력하세요 : ";
		cin >> RecordId;
		recaddr = SearchLecture(RecordId, &l);
		if (recaddr == -1)
			cout << "해당 레코드가 존재하지 않습니다." << endl;
		else
			cout << l;
	}

	else if (instruction == 13)
	{
		if (access_level == 9)
		{
			if (SearchUserPurchase(Login_id) == -1)
				cout << "해당 레코드가 존재하지 않습니다." << endl;
		}
		else
		{
			system("cls");

			cout << "===================================================" << endl;
			cout << "\t 검색할 ID를 선택하세요." << endl;
			cout << "1. 회원 ID" << endl;
			cout << "2. 강의 ID" << endl;
			cout << "3. 구매 ID" << endl;
			cout << "\n\t해당하는 메뉴의 번호만 입력하세요." << endl;
			cout << "===================================================" << endl;
			cout << "Input : ";
			cin >> input;

			cout << selected_record[input - 1] << " ID를 입력하세요 : ";
			cin >> RecordId;

			if (1 <= input && input <= 3)
			{
				recaddr = SearchPurchase(RecordId, &p, input);
				if (recaddr == -1)
					cout << "해당 레코드가 존재하지 않습니다." << endl;
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
			cout << "관리자 모드를 사용해주세요." << endl;
		}
		else
		{
			cout << selected_record[input - 1] << " ID를 입력하세요 : ";
			cin >> RecordId;

			recaddr = SearchMember(RecordId, &m);

			if (recaddr == -1)
			{
				if (InsertMember(RecordId, mem_num) == -1)
					cout << "삽입이 실패했습니다." << endl;
				else
				{
					mem_num++;
					cout << "삽입이 성공했습니다." << endl;					
				}					
			}
			else
			{
				cout << "해당 ID가 존재합니다." << endl;
			}
		}
	}

	else if (instruction == 22)
	{
		if (access_level == 9)
		{
			cout << "관리자 모드를 사용해주세요." << endl;
		}
		else
		{
			cout << selected_record[input - 1] << " ID를 입력하세요 : ";
			cin >> RecordId;

			recaddr = SearchLecture(RecordId, &l);

			if (recaddr == -1)
			{
				if (InsertLecture(RecordId,lec_num) == -1)
					cout << "삽입이 실패했습니다." << endl;
				else
				{
					lec_num++;
					cout << "삽입이 성공했습니다." << endl;
				}					
			}
			else
			{
				cout << "해당 ID가 존재합니다." << endl;
			}
		}
	}

	else if (instruction == 23)
	{
		if (access_level == 9)
		{
			cout << selected_record[input - 1] << " ID를 입력하세요 : ";
			cin >> RecordId;

			recaddr = SearchPurchase(RecordId, &p, 3);

			if (recaddr == -1)
			{
				if (InsertUserPurchase(RecordId, Login_id) == -1)
					cout << "삽입이 실패했습니다." << endl;
				else
				{
					pur_num++;
					cout << "삽입이 성공했습니다." << endl;
				}					
			}
			else
			{
				cout << "해당 ID가 존재합니다." << endl;
			}
		}
		else
		{
			cout << selected_record[input - 1] << " ID를 입력하세요 : ";
			cin >> RecordId;

			recaddr = SearchPurchase(RecordId, &p, 3);

			if (recaddr == -1)
			{
				if (InsertPurchase(RecordId) == -1)
					cout << "삽입이 실패했습니다." << endl;
				else
				{
					pur_num++;
					cout << "삽입이 성공했습니다." << endl;
				}					
			}
			else
			{
				cout << "해당 ID가 존재합니다." << endl;
			}
		}
	}

	else if (instruction == 31)
	{
		cout << selected_record[input - 1] << " ID를 입력하세요 : ";
		cin >> RecordId;

		if (access_level == 9)
		{
			if (strcmp(RecordId, Login_id))
				cout << "자신의 회원정보만 삭제 가능합니다." << endl;
			else
			{
				recaddr = DeleteMember(RecordId, mem_num);

				if (recaddr == -1)
					cout << "해당 레코드가 존재하지 않습니다." << endl;
				else
				{
					mem_num--;
					cout << "해당 레코드가 삭제되었습니다." << endl;
				}					
			}
		}
		else
		{
			recaddr = DeleteMember(RecordId, mem_num);

			if (recaddr == -1)
				cout << "해당 레코드가 존재하지 않습니다." << endl;
			else
			{
				mem_num--;
				cout << "해당 레코드가 삭제되었습니다." << endl;
			}			
		}
	}

	else if (instruction == 32)
	{
		if (access_level == 9)
		{
			cout << "관리자 모드를 사용해주세요." << endl;
		}
		else
		{
			cout << selected_record[input - 1] << " ID를 입력하세요 : ";
			cin >> RecordId;

			recaddr = DeleteLecture(RecordId, lec_num);
			
			if (recaddr == -1)
				cout << "해당 레코드가 존재하지 않습니다." << endl;
			else
			{
				lec_num--;
				cout << "해당 레코드가 삭제되었습니다." << endl;
			}				
		}
	}

	else if (instruction == 33)
	{
		cout << selected_record[input - 1] << " ID를 입력하세요 : ";
		cin >> RecordId;

		if (access_level == 9)
		{
			if (strcmp(RecordId, Login_id))
				cout << "자신의 회원정보만 삭제 가능합니다." << endl;
			else
			{
				recaddr = DeletePurchase(RecordId);

				if (recaddr == -1)
					cout << "해당 레코드가 존재하지 않습니다." << endl;
				else
				{
					pur_num--;
					cout << "해당 레코드가 삭제되었습니다." << endl;
				}					
			}
		}
		else
		{
			recaddr = DeletePurchase(RecordId);

			if (recaddr == -1)
				cout << "해당 레코드가 존재하지 않습니다." << endl;
			else
			{
				pur_num--;
				cout << "해당 레코드가 삭제되었습니다." << endl;
			}				
		}
	}

	else if (instruction == 41)
	{
		cout << selected_record[input - 1] << " ID를 입력하세요 : ";
		cin >> RecordId;

		if (access_level == 9)
		{
			if (strcmp(RecordId, Login_id))
				cout << "자신의 회원정보만 수정 가능합니다." << endl;
			else
				UpdateMember(RecordId, mem_num);
		}
		else
		{
			recaddr = UpdateMember(RecordId, mem_num);

			if (recaddr == -1)
				cout << "해당 레코드가 존재하지 않습니다." << endl;
			else
				cout << "해당 레코드가 수정되었습니다." << endl;
		}
	}

	else if (instruction == 42)
	{
		if (access_level == 9)
		{
			cout << "관리자 모드를 사용해주세요." << endl;
		}
		else
		{
			cout << selected_record[input - 1] << " ID를 입력하세요 : ";
			cin >> RecordId;

			recaddr = UpdateLecture(RecordId, lec_num);

			if (recaddr == -1)
				cout << "해당 레코드가 존재하지 않습니다." << endl;
			else
				cout << "해당 레코드가 수정되었습니다." << endl;
		}
	}

	else if (instruction == 43)
	{
		cout << selected_record[input - 1] << " ID를 입력하세요 : ";
		cin >> RecordId;

		if (access_level == 9)
		{
			recaddr = UpdateUserPurchase(RecordId, Login_id);

			if (recaddr == -1)
				cout << "해당 레코드가 존재하지 않거나 자신의 회원정보가 아닙니다." << endl;
			else
				cout << "해당 레코드가 수정되었습니다." << endl;
		}
		else
		{
			recaddr = UpdatePurchase(RecordId);

			if (recaddr == -1)
				cout << "해당 레코드가 존재하지 않습니다." << endl;
			else
				cout << "해당 레코드가 수정되었습니다." << endl;
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