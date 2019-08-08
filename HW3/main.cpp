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
	int instruction = 0, input, recaddr, access_level, want_key_int, want_key_search;	
	char selected_menu[4][5] = { "검색", "삽입", "삭제", "수정" };
	char selected_record[3][5] = { "회원", "강의", "구매" };
	char selected_level[2][20] = { "관리자 모드", "사용자 모드" };
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
			// key를 입력받아 해당 key를 바탕으로 b-tree를 통해 검색하는 과정.
			// SearchingbyID함수는 Search, Insert, Modify, Delete에서 모두 사용되기 때문에
			// 모듈화 하여 재사용하기 편하게 구현하였다.

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
		if (access_level == 9)
		{
			cout << selected_record[input - 1] << " ID를 입력하세요 : ";
			cin >> RecordId;

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
			//recaddr = DeletePurchase(RecordId);
			recaddr = DeleteKey();
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
		if (access_level == 9)
		{
			cout << selected_record[input - 1] << " ID를 입력하세요 : ";
			cin >> RecordId;

			recaddr = UpdateUserPurchase(RecordId, Login_id);

			if (recaddr == -1)
				cout << "해당 레코드가 존재하지 않거나 자신의 회원정보가 아닙니다." << endl;
			else
				cout << "해당 레코드가 수정되었습니다." << endl;
		}
		else
		{
			recaddr = UpdatePurchase();

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

	cout << "Lecture ID를 입력하세요 : ";
	cin >> buf;
	if(strlen(buf) != LENLEC)
		return -1;

	ret = SearchLecture(buf, &l);
	if(ret == -1)
		return -1;
	else
		p.update_lectureid(buf);

	cout << "Member ID를 입력하세요 : ";
	cin >> buf;
	ret = SearchMember(buf, &m);
	if(ret == -1)
		return -1;
	else
		p.update_memberid(string(buf));

	cout << "Mileage를 입력하세요 : ";
	cin >> buf;
	if(strlen(buf) != LENMIL)
		return -1;
	else
		p.update_mileage(buf);


	if(world_key < 1 || world_key > 127) //아스키코드 제한. Key는 1부터 127까지만 허용. 이에 대한 것은 보고서에 기술.
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
	recaddr = PurchaseFile.Write(p); //새로 삽입된 레코드를 데이터 파일에 추가.
	PurchaseFile.Close();
	
	bt.Insert(p.Key(), recaddr); // 새로 삽입된 레코드 B-tree에 추가.

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

	if(bt.Search(temp_char) == -1) //key를 통한 탐색 후, 해당 key의 레코드가 존재할때만 b-tree와 data파일 수정 시작.
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
			중간의 레코드가 삭제되면, 나머지 레코드의 주소에도 영향을 미치므로
			이 변화된 주소값을 반영.
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
		bt.Remove(temp_char);			// 삭제해야 하는 노드를 B-tree로 부터 제거
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

	if(bt.Search(temp_char) == -1) //key를 통한 탐색 후, 해당 key의 레코드가 존재할때만 b-tree와 data파일 수정 시작.
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
			// 입력된 key와 일치하는 Purchase 레코드를 찾았을경우 정보 수정.

			cout << "Lecture ID를 입력하세요 : ";
			cin >> update_temp;

			if(strlen(update_temp) != LENLEC)
				return -1;
			else
				p.update_lectureid(update_temp);

			cout << "Member ID를 입력하세요 : ";
			cin >> temp;
			p.update_memberid(temp);

			cout << "Mileage를 입력하세요 : ";
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
			modify_address = recaddr;	//수정된 레코드의 recaddr.
										/*
										수정된 레코드를 일단 B-tree로 부터 삭제.
										레코드가 삭제되면, 나머지 레코드의 주소에도 영향을 미치므로
										이 변화된 주소값을 반영.
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
	bt.Remove(world_key);			//수정된 레코드를 B-tree에서 삭제.
	bt.Insert(world_key, modify_address);	//수정된 레코드를 다시 B-tree에 삽입.

	PurchaseFile.Close();

	return 1;
}