#ifndef _UNSORTEDLIST_H
#define _UNSORTEDLIST_H

#include <iostream>
#include <fstream>	
#include <string>
using namespace std;

#include "ItemType.h"

#define MAXSIZE 5

/**
*	array based simple unsorted list.
*/
class ArrayList
{
public:
	/**
	*	default constructor.
	*/
	ArrayList()
	{
		m_Length = 0;
		ResetList();
	}

	/**
	*	destructor.
	*/
	~ArrayList()	{}

	/**
	*	@brief	Make list empty.
	*	@pre	none.
	*	@post	clear list.
	*/
	void MakeEmpty();

	/**
	*	@brief	Get a number of records in current list.
	*	@pre	none.
	*	@post	none.
	*	@return	number of records in current list.
	*/
	int GetLength();

	/**
	*	@brief	Check capacity of list is full.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if list capacity reached to the upper bound, otherwise return false.
	*/
	bool IsFull();

	/**
	*	@brief	add a new data into list.
	*	@pre	list should be initialized.
	*	@post	added the new record into the list.
	*	@param	data	new data.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int Add(ItemType data);

	/**
	*	@brief	Initialize list iterator.
	*	@pre	list should be initialized.
	*	@post	iterator is reset.
	*/
	void ResetList();

	/**
	*	@brief	move list iterator to the next item in list and get that item.
	*	@pre	list and list iterator should not be initialized. 
	*	@post	iterator is moved to next item.
	*	@param	data	get current iterator's item. it does not need to be initialized.
	*	@return	index of current iterator's item if is not end of list, oterwise return -1.
	*/
	int GetNextItem(ItemType& data);


	bool IsEmpty() {
		if (m_Length == 0)
			return true;
		return false;
	}

	int Get(ItemType& data) {
		for (m_CurPointer = 0; m_CurPointer < m_Length; ++m_CurPointer) {
			if (data == m_Array[m_CurPointer]) {
				return m_CurPointer;
			}
		}
		return -1;
	}

	int Delete(ItemType data) {
		bool isFind = false;
		for (m_CurPointer = 0; m_CurPointer < m_Length; ++m_CurPointer) {
			if (!isFind) {
				if (data == m_Array[m_CurPointer]) {
					isFind = true;
				}
			}
			else {
				m_Array[m_CurPointer - 1] = m_Array[m_CurPointer];
			}
		}

		m_Length--;
		if (isFind) {
			return 1;
		}
		else {
			return -1;
		}
	}

	//���ؾȵ�.
	int Replace(ItemType data) {
		for (m_CurPointer = 0; m_CurPointer < m_Length; ++m_CurPointer) {
			if (data == m_Array[m_CurPointer]) {
				m_Array[m_CurPointer] = data;
				return 1;
			}
		}
		return -1;
	}

private:
	ItemType m_Array[MAXSIZE];  ///< list array.
	int m_Length;				///< number of elements in list.
	int m_CurPointer;			///< iterator pointer.
};

#endif	// _UNSORTEDLIST_H