#include "main.h"

int main()
{
	int input;

	while(true)
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

		if(input == 1)
			showMember();

		else if(input == 2)
			showLecture();

		else if(input == 3)
			showPurchase();

		else if(input == 4)
			MemberTest();

		else if(input == 5)
			LectureTest();

		else if(input == 6)
			PurchaseTest();

		else if(input == 7)
			LecturePurchaseSystem();

		else if(input == 8)
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
	int instruction = 0, input, recaddr;
	char selected_menu[4][5] ={ "검색", "삽입", "삭제", "수정" };
	char selected_record[3][5] ={ "회원", "강의", "구매" };
	char RecordId[256];
	Member m;
	Lecture l;
	Purchase p;

	system("cls");
	cout << "===================================================" << endl;
	cout << "\t\t메뉴를 선택하세요." << endl;
	cout << "1. 레코드 검색" << endl;
	cout << "2. 레코드 삽입" << endl;
	cout << "3. 레코드 삭제" << endl;
	cout << "4. 레코드 수정" << endl;
	cout << "\n\t해당하는 메뉴의 번호만 입력하세요." << endl;
	cout << "===================================================" << endl;
	cin.clear();

	cout << "Input : ";
	cin >> input;

	if(input < 1 || input > 4)
	{
		cout << "" <<endl;
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

	if(input < 1 || input > 3)
	{
		cout << "" <<endl;
		return;
	}

	instruction += input;

	if(instruction == 11)
	{
		cout << selected_record[input - 1] << " ID를 입력하세요 : ";
		cin >> RecordId;
		recaddr = SearchMember(RecordId, &m);
		if(recaddr == -1)
			cout << "해당 레코드가 존재하지 않습니다." << endl;
		else
			cout << m;
	}

	else if(instruction == 12)
	{
		cout << selected_record[input - 1] << " ID를 입력하세요 : ";
		cin >> RecordId;
		recaddr = SearchLecture(RecordId, &l);
		if(recaddr == -1)
			cout << "해당 레코드가 존재하지 않습니다." << endl;
		else
			cout << l;
	}

	else if(instruction == 13)
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

		if(1 <= input && input <= 3)
		{
			recaddr = SearchPurchase(RecordId, &p, input);
			if(recaddr == -1)
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

	else if(instruction == 21)
	{
		cout << selected_record[input - 1] << " ID를 입력하세요 : ";
		cin >> RecordId;

		recaddr = SearchMember(RecordId, &m);

		if(recaddr == -1)
		{
			if(InsertMember(RecordId) == -1)
				cout << "삽입이 실패했습니다." << endl;
			else
				cout << "삽입이 성공했습니다." << endl;
		}
		else
		{
			cout << "해당 ID가 존재합니다." << endl;
		}
	}

	else if(instruction == 22)
	{
		cout << selected_record[input - 1] << " ID를 입력하세요 : ";
		cin >> RecordId;

		recaddr = SearchLecture(RecordId, &l);

		if(recaddr == -1)
		{
			if(InsertLecture(RecordId) == -1)
				cout << "삽입이 실패했습니다." << endl;
			else
				cout << "삽입이 성공했습니다." << endl;
		}
		else
		{
			cout << "해당 ID가 존재합니다." << endl;
		}
	}

	else if(instruction == 23)
	{
		cout << selected_record[input - 1] << " ID를 입력하세요 : ";
		cin >> RecordId;

		recaddr = SearchPurchase(RecordId, &p, 3);

		if(recaddr == -1)
		{
			if(InsertPurchase(RecordId) == -1)
				cout << "삽입이 실패했습니다." << endl;
			else
				cout << "삽입이 성공했습니다." << endl;
		}
		else
		{
			cout << "해당 ID가 존재합니다." << endl;
		}
	}

	else if(instruction == 31)
	{
		cout << selected_record[input - 1] << " ID를 입력하세요 : ";
		cin >> RecordId;

		recaddr = DeleteMember(RecordId);

		if(recaddr == -1)
			cout << "해당 레코드가 존재하지 않습니다." << endl;
		else
			cout << "해당 레코드가 삭제되었습니다." << endl;
	}

	else if(instruction == 32)
	{
		cout << selected_record[input - 1] << " ID를 입력하세요 : ";
		cin >> RecordId;

		recaddr = DeleteLecture(RecordId);

		if(recaddr == -1)
			cout << "해당 레코드가 존재하지 않습니다." << endl;
		else
			cout << "해당 레코드가 삭제되었습니다." << endl;
	}

	else if(instruction == 33)
	{
		cout << selected_record[input - 1] << " ID를 입력하세요 : ";
		cin >> RecordId;

		recaddr = DeletePurchase(RecordId);

		if(recaddr == -1)
			cout << "해당 레코드가 존재하지 않습니다." << endl;
		else
			cout << "해당 레코드가 삭제되었습니다." << endl;
	}

	else if(instruction == 41)
	{
		cout << selected_record[input - 1] << " ID를 입력하세요 : ";
		cin >> RecordId;

		recaddr = UpdateMember(RecordId);

		if(recaddr == -1)
			cout << "해당 레코드가 존재하지 않습니다." << endl;
		else
			cout << "해당 레코드가 수정되었습니다." << endl;
	}

	else if(instruction == 42)
	{
		cout << selected_record[input - 1] << " ID를 입력하세요 : ";
		cin >> RecordId;

		recaddr = UpdateLecture(RecordId);

		if(recaddr == -1)
			cout << "해당 레코드가 존재하지 않습니다." << endl;
		else
			cout << "해당 레코드가 수정되었습니다." << endl;
	}

	else if(instruction == 43)
	{
		cout << selected_record[input - 1] << " ID를 입력하세요 : ";
		cin >> RecordId;

		recaddr = UpdatePurchase(RecordId);

		if(recaddr == -1)
			cout << "해당 레코드가 존재하지 않습니다." << endl;
		else
			cout << "해당 레코드가 수정되었습니다." << endl;
	}
}