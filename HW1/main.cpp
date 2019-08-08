#include "main.h"

int main()
{
	int input;

	while(true)
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
	char selected_menu[4][5] ={ "�˻�", "����", "����", "����" };
	char selected_record[3][5] ={ "ȸ��", "����", "����" };
	char RecordId[256];
	Member m;
	Lecture l;
	Purchase p;

	system("cls");
	cout << "===================================================" << endl;
	cout << "\t\t�޴��� �����ϼ���." << endl;
	cout << "1. ���ڵ� �˻�" << endl;
	cout << "2. ���ڵ� ����" << endl;
	cout << "3. ���ڵ� ����" << endl;
	cout << "4. ���ڵ� ����" << endl;
	cout << "\n\t�ش��ϴ� �޴��� ��ȣ�� �Է��ϼ���." << endl;
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
	cout << "\t" << selected_menu[input - 1] << "�� ���ڵ带 �����ϼ���." << endl;
	cout << "1. ȸ�� ���ڵ�" << endl;
	cout << "2. ���� ���ڵ�" << endl;
	cout << "3. ���� ���ڵ�" << endl;
	cout << "\n\t�ش��ϴ� �޴��� ��ȣ�� �Է��ϼ���." << endl;
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
		cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
		cin >> RecordId;
		recaddr = SearchMember(RecordId, &m);
		if(recaddr == -1)
			cout << "�ش� ���ڵ尡 �������� �ʽ��ϴ�." << endl;
		else
			cout << m;
	}

	else if(instruction == 12)
	{
		cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
		cin >> RecordId;
		recaddr = SearchLecture(RecordId, &l);
		if(recaddr == -1)
			cout << "�ش� ���ڵ尡 �������� �ʽ��ϴ�." << endl;
		else
			cout << l;
	}

	else if(instruction == 13)
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

		if(1 <= input && input <= 3)
		{
			recaddr = SearchPurchase(RecordId, &p, input);
			if(recaddr == -1)
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

	else if(instruction == 21)
	{
		cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
		cin >> RecordId;

		recaddr = SearchMember(RecordId, &m);

		if(recaddr == -1)
		{
			if(InsertMember(RecordId) == -1)
				cout << "������ �����߽��ϴ�." << endl;
			else
				cout << "������ �����߽��ϴ�." << endl;
		}
		else
		{
			cout << "�ش� ID�� �����մϴ�." << endl;
		}
	}

	else if(instruction == 22)
	{
		cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
		cin >> RecordId;

		recaddr = SearchLecture(RecordId, &l);

		if(recaddr == -1)
		{
			if(InsertLecture(RecordId) == -1)
				cout << "������ �����߽��ϴ�." << endl;
			else
				cout << "������ �����߽��ϴ�." << endl;
		}
		else
		{
			cout << "�ش� ID�� �����մϴ�." << endl;
		}
	}

	else if(instruction == 23)
	{
		cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
		cin >> RecordId;

		recaddr = SearchPurchase(RecordId, &p, 3);

		if(recaddr == -1)
		{
			if(InsertPurchase(RecordId) == -1)
				cout << "������ �����߽��ϴ�." << endl;
			else
				cout << "������ �����߽��ϴ�." << endl;
		}
		else
		{
			cout << "�ش� ID�� �����մϴ�." << endl;
		}
	}

	else if(instruction == 31)
	{
		cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
		cin >> RecordId;

		recaddr = DeleteMember(RecordId);

		if(recaddr == -1)
			cout << "�ش� ���ڵ尡 �������� �ʽ��ϴ�." << endl;
		else
			cout << "�ش� ���ڵ尡 �����Ǿ����ϴ�." << endl;
	}

	else if(instruction == 32)
	{
		cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
		cin >> RecordId;

		recaddr = DeleteLecture(RecordId);

		if(recaddr == -1)
			cout << "�ش� ���ڵ尡 �������� �ʽ��ϴ�." << endl;
		else
			cout << "�ش� ���ڵ尡 �����Ǿ����ϴ�." << endl;
	}

	else if(instruction == 33)
	{
		cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
		cin >> RecordId;

		recaddr = DeletePurchase(RecordId);

		if(recaddr == -1)
			cout << "�ش� ���ڵ尡 �������� �ʽ��ϴ�." << endl;
		else
			cout << "�ش� ���ڵ尡 �����Ǿ����ϴ�." << endl;
	}

	else if(instruction == 41)
	{
		cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
		cin >> RecordId;

		recaddr = UpdateMember(RecordId);

		if(recaddr == -1)
			cout << "�ش� ���ڵ尡 �������� �ʽ��ϴ�." << endl;
		else
			cout << "�ش� ���ڵ尡 �����Ǿ����ϴ�." << endl;
	}

	else if(instruction == 42)
	{
		cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
		cin >> RecordId;

		recaddr = UpdateLecture(RecordId);

		if(recaddr == -1)
			cout << "�ش� ���ڵ尡 �������� �ʽ��ϴ�." << endl;
		else
			cout << "�ش� ���ڵ尡 �����Ǿ����ϴ�." << endl;
	}

	else if(instruction == 43)
	{
		cout << selected_record[input - 1] << " ID�� �Է��ϼ��� : ";
		cin >> RecordId;

		recaddr = UpdatePurchase(RecordId);

		if(recaddr == -1)
			cout << "�ش� ���ڵ尡 �������� �ʽ��ϴ�." << endl;
		else
			cout << "�ش� ���ڵ尡 �����Ǿ����ϴ�." << endl;
	}
}