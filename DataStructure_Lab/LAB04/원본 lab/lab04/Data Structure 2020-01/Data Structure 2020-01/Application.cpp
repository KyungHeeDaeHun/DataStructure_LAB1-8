#include "pch.h"
#include "Application.h"


Application::Application()
{
	m_Command = 0;
}


Application::~Application()
{
}

void Application::Run()
{
	while (1)
	{
		GetCommand();

		switch (m_Command)
		{
		case 1:		// read a record and add to list.
			AddItem();
			break;
		case 2:		//delete
			DeleteItem();
			break;
		case 3:		//replace
			ReplaceItem();
			break;
		case 4:	//search by binary search.
			SearchByID_BinaryS();
			break;
		case 5:		// display all the records in list on screen.
			DisplayAllItem();
			break;
		case 6:		// make empty list.
			MasterList.MakeEmpty();
			break;
		case 7:		// load list data from a file.
			ReadDataFromFile();
			break;
		case 8:		// save list data into a file.
			WriteDataToFile();
			break;
		case 9:
			AddtItem();
			break;
		case 10:
			DequeueFromtItemList();
			break;
		case 11:
			PrinttItemList();
			break;
		case 12:		// save list data into a file.
			AddPhoto();
			break;
		case 13:
			DeletePhoto();
			break;
		case 14:
			DisplayAllPhoto();
			break;
		case 15:
			DisplayAllsItem();
			break;
		case 16:
			DisplayAllDetailsItem();
			break;
		case 0:
			return;
		default:
			cout << "\tIllegal selection...\n";
			break;
		}
	}
}

void Application::GetCommand()
{
	cout << endl << endl;
	cout << "\t--num--- Command ----- " << endl;
	cout << "\t-------MasterList----- " << endl;
	cout << "\t   1 : Add item" << endl;
	cout << "\t   2 : Delete item" << endl;
	cout << "\t   3 : Replace item" << endl;
	cout << "\t   4 : Search item by Binary Search" << endl;
	cout << "\t   5 : Print all on screen" << endl;
	cout << "\t   6 : Make empty list" << endl;
	cout << "\t   7 : Get from file" << endl;
	cout << "\t   8 : Put to file " << endl;
	cout << "\t-------TempList------- " << endl;
	cout << "\t   9 : AddtItem" << endl;
	cout << "\t   10 : DequeueFromtItemList" << endl;
	cout << "\t   11 : PrinttItemList" << endl;
	cout << "\t-------ContainerList-- " << endl;
	cout << "\t   12 : AddPhoto" << endl;
	cout << "\t   13 : DeletePhoto" << endl;
	cout << "\t   14 : DisplayAllPhoto" << endl;
	cout << "\t   15 : DisplayAllsItem" << endl;
	cout << "\t   16 : DisplayAllDetailsItem" << endl;
	cout << "\t---------------------- " << endl;
	cout << "\t   0 : Quit" << endl;

	cout << endl << "\t Choose a Command--> ";
	cin >> m_Command;
	cout << endl;
}

int Application::AddItem()
{
	// 입력받은 레코드를 리스트에 add, 리스트가 full일 경우는 add하지 않고 0을 리턴
	if (MasterList.IsFull())
	{
		cout << "List is full" << endl;
		return 0;
	}

	ItemType item;

	item.SetRecordFromKB();
	MasterList.Add(item);

	
	ContainerType tmpContainer;
	tmpContainer.SetId(item.GetContainerID());
	SimpleItemType tmpsItem;
	tmpsItem.SetId(item.GetId());
	tmpsItem.SetName(item.GetName());
	
	if (ContainerList.Get(tmpContainer) == 1) { //Container 존재할때
		tmpContainer.AddsItem(tmpsItem);
		ContainerList.Replace(tmpContainer);
	}
	else { //Container 존재하지 않을때
		tmpContainer.AddsItem(tmpsItem);
		ContainerList.Add(tmpContainer);
	}
	return 1;
}

int Application::AddItem(ItemType& item)
{
	// 입력받은 레코드를 리스트에 add, 리스트가 full일 경우는 add하지 않고 0을 리턴
	if (MasterList.IsFull())
	{
		cout << "List is full" << endl;
		return 0;
	}

	MasterList.Add(item);

	ContainerType tmpContainer;
	tmpContainer.SetId(item.GetContainerID());
	SimpleItemType tmpsItem;
	tmpsItem.SetId(item.GetId());
	tmpsItem.SetName(item.GetName());

	if (ContainerList.Get(tmpContainer) == 1) { //Container 존재할때
		tmpContainer.AddsItem(tmpsItem);
		ContainerList.Replace(tmpContainer);
	}
	else { //Container 존재하지 않을때
		tmpContainer.AddsItem(tmpsItem);
		ContainerList.Add(tmpContainer);
	}

	return 1;
}

void Application::DisplayAllItem()
{
	ItemType data;

	cout << "\n\tCurrent list" << endl;

	// list의 모든 데이터를 화면에 출력
	MasterList.ResetList();
	int length = MasterList.GetLength();
	int curIndex = MasterList.GetNextItem(data);
	while (curIndex < length && curIndex != -1)
	{
		cout << data;
		curIndex = MasterList.GetNextItem(data);
	}
}

int Application::OpenInFile(char * fileName)
{
	m_InFile.open(fileName);	// file open for reading.

	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if (!m_InFile)	return 0;
	else	return 1;
}

int Application::OpenOutFile(char * fileName)
{
	m_OutFile.open(fileName);	// file open for writing.

	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if (!m_OutFile)	return 0;
	else	return 1;
}

int Application::ReadDataFromFile()
{
	int index = 0;
	ItemType data;	// 읽기용 임시 변수

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Input file Name : ";
	cin >> filename;

	// file open, open error가 발생하면 0을 리턴
	if (!OpenInFile(filename))
		return 0;

	// 파일의 모든 내용을 읽어 list에 추가
	while (!m_InFile.eof())
	{
		// array에 학생들의 정보가 들어있는 structure 저장
		data.ReadDataFromFile(m_InFile);
		MasterList.Add(data);
	}

	m_InFile.close();	// file close

	// 현재 list 출력
	//DisplayAllItem();

	return 1;
}

int Application::WriteDataToFile()
{
	ItemType data;	// 쓰기용 임시 변수

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Output file Name : ";
	cin >> filename;

	// file open, open error가 발생하면 0을 리턴
	if (!OpenOutFile(filename))
		return 0;

	// list 포인터를 초기화
	MasterList.ResetList();

	// list의 모든 데이터를 파일에 쓰기
	int length = MasterList.GetLength();
	int curIndex = MasterList.GetNextItem(data);
	while (curIndex < length && curIndex != -1)
	{
		data.WriteDataToFile(m_OutFile);
		curIndex = MasterList.GetNextItem(data);
	}

	m_OutFile.close();	// file close

	return 1;
}

int Application::SearchById_SequenS()
{
	ItemType item;
	item.SetIdFromKB(); //id입력받는다.

	if (MasterList.Get(item)) //0이 아니면(찾으면)
	{
		cout << "<============ Item FOUND !==========>" << endl;
		cout << item;
		cout << "<====================================>" << endl;
		return 1;	//성공(1)을 리턴
	}
	cout << "<======== ITEM Not Found!==========>" << endl;
	return 0;	//실패(0)을 리턴
}

int Application::DeleteItem()
{
	int pre = MasterList.GetLength();//이전 item개수를 받아온다.
	ItemType item;
	item.SetIdFromKB();

	MasterList.Delete(item);

	//Container 동기화
	ContainerType tmpContainer;
	tmpContainer.SetId(item.GetContainerID());
	SimpleItemType tmpsItem;
	tmpsItem.SetId(item.GetId());
	ContainerList.Get(tmpContainer);
	tmpContainer.DeletesItem(tmpsItem);
	ContainerList.Replace(tmpContainer);
	
	if (pre > MasterList.GetLength()) //이전 item개수보다 현재 item개수가 많아지면 제거성공
	{
		cout << "<========DELETE SUCCESS !===========>" << endl;
		return 1;
	}

	cout << "<========DELETE FAIL !=======>" << endl;
	return 0;
}

int Application::ReplaceItem()
{
	ItemType item;
	item.SetRecordFromKB(); //키보드로부터 정보를 입력받음

	ItemType origin;
	origin.SetId(item.GetId());
	MasterList.Get(origin); //해당 item의 id와 일치하는 것을 가져온다. 이전내용과 비교를 위해
	MasterList.Replace(item); //해당 item의 id와 일치하는 것을 찾아 바꾼다.

	//Container 동기화
	ContainerType tmpContainer;
	SimpleItemType tmpsItem;

	//기존 내용 삭제
	tmpContainer.SetId(origin.GetContainerID());
	tmpsItem.SetId(origin.GetId());
	ContainerList.Get(tmpContainer);
	tmpContainer.DeletesItem(tmpsItem);
	ContainerList.Replace(tmpContainer);

	//갱신 된 내용 추가
	tmpContainer.SetId(item.GetContainerID());
	tmpsItem.SetId(item.GetId());
	tmpsItem.SetName(item.GetName());
	if (ContainerList.Get(tmpContainer) == 1) { //Container 존재할때
		tmpContainer.AddsItem(tmpsItem);
		ContainerList.Replace(tmpContainer);
	}
	else { //Container 존재하지 않을때
		tmpContainer.AddsItem(tmpsItem);
		ContainerList.Add(tmpContainer);
	}

	return 0;
}

int Application::SearchByID_BinaryS()
{
	ItemType item;

	item.SetIdFromKB();	//id를 입력받는다
	if (MasterList.GetByBinarySearch(item))	//이진탐색에 성공했다면
	{
		cout << "<============I FOUND ITEM !==========>" << endl;
		cout << item;
		cout << "<====================================>" << endl;
		return 1;	//성공(1)을 반환
	}
	//발견 못할시
	cout << "<========I CAN'T FIND ITEM !==========>" << endl;
	return 0;	//실패(0)을 반환
}

void Application::AddtItem()
{
	ItemType tmpItem;
	tmpItem.SetIdFromKB();
	tmpItem.SetKindFromKB();
	tmpItem.SetDateFromKB();
	tmpItem.SetNameFromKB();
	tmpItem.SetNumFromKB();
	TempList.AddtItem(tmpItem);
}

void Application::DequeueFromtItemList()
{
	ItemType tmpItem;
	TempList.DequeueFromtItemList(tmpItem);
	tmpItem.SetContainerIDFromKB();
	AddItem(tmpItem);
}

void Application::PrinttItemList()
{
	TempList.PrinttItemList();
}

void Application::AddPhoto()
{
	ContainerType tmpContainer;
	tmpContainer.SetIdFromKB();
	
	string photo;
	cout << "photo : ";
	cin >> photo;

	ContainerList.Get(tmpContainer);
	tmpContainer.AddPhoto(photo);

	ContainerList.Replace(tmpContainer);
}

void Application::DeletePhoto()
{
	ContainerType tmpContainer;
	tmpContainer.SetIdFromKB();

	string photo;
	cout << "photo : ";
	cin >> photo;

	ContainerList.Get(tmpContainer);
	tmpContainer.DeletePhoto(photo);

	ContainerList.Replace(tmpContainer);
}

void Application::DisplayAllPhoto()
{
	ContainerType tmpContainer;
	tmpContainer.SetIdFromKB();

	ContainerList.Get(tmpContainer);

	tmpContainer.DisplayAllPhoto();
}

void Application::DisplayAllsItem()
{
	ContainerType tmpContainer;
	tmpContainer.SetIdFromKB();

	ContainerList.Get(tmpContainer);

	tmpContainer.DisplayAllsItem();
}

void Application::DisplayAllDetailsItem()
{
	ContainerType tmpContainer;
	tmpContainer.SetIdFromKB();

	ContainerList.Get(tmpContainer);

	tmpContainer.DisplayAllDetailsItem(MasterList);
}
