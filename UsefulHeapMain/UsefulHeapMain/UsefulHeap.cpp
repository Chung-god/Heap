#include "UsefulHeap.h"

void HeapInit(Heap* ph,PriorityComp pc) {
	ph->numOfData = 0;
	ph->comp = pc;
}
int HIsEmpty(Heap* ph) {
	if (ph->numOfData == 0)
		return TRUE;
	else
		return FALSE;;
}

int GetParentIDX(int idx) {
	return idx / 2;
}

int GetLChildIDX(int idx) {
	return idx * 2;
}

int GetRChildIDX(int idx) {
	return idx * 2 + 1;
}

//�ΰ��� �ڽ� ��� �� ���� �켱������ �ڽ� ��� �ε��� �� ��ȯ
int GetHiPriChildIDX(Heap* ph, int idx) {
	if (GetLChildIDX(idx) > ph->numOfData)//NULL ���̸� ��ȯ = �ڽ��� ���ٸ� 
		return 0;
	else if (GetLChildIDX(idx) == ph->numOfData)
		return GetLChildIDX(idx); //�ڽĳ�尡 �ϳ� ���϶� 
	else {
		if (ph->comp(ph->heapArr[GetLChildIDX(idx)],
			ph->heapArr[GetRChildIDX(idx)]) < 0)
			return GetRChildIDX(idx);
		else
			return GetLChildIDX(idx);
	}
}


void HInsert(Heap* ph, HData data) {
	int idx = ph->numOfData + 1;

	while (idx != 1) {
		if(ph->comp(data,ph->heapArr[GetParentIDX(idx)])>0){
			ph->heapArr[idx] = ph->heapArr[GetParentIDX(idx)];
			idx = GetParentIDX(idx);
		}
		else break;
	}
	ph->heapArr[idx] = data;
	ph->numOfData += 1;
}
HData HDelete(Heap* ph) {
	HData retData = ph->heapArr[1]; //�켱������ ���� ���� ������
	HData lastElem = ph->heapArr[ph->numOfData];

	int parentIdx = 1;
	int childIdx;

	//�켱������ ���� �ڽ� ��带 �������� �ݺ��� ����
	while (childIdx = GetHiPriChildIDX(ph, parentIdx)) {
		if(ph->comp(lastElem,ph->heapArr[childIdx])>=0) //�ڽ� ��庸�� �켱������ ���� �� ���� 
			break;
		//������ ��庸�� �켱 ������ ������ �񱳴�� ����� ��ġ�� �� ���� �ø�
		ph->heapArr[parentIdx] = ph->heapArr[childIdx];
		//������ ��尡 ����� ��ġ ������ �� ���� ����
		parentIdx = childIdx;
	}
	ph->heapArr[parentIdx] = lastElem;
	ph->numOfData -= 1;
	return retData;
}