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

//두개의 자식 노드 중 높은 우선순위의 자식 노드 인덱스 값 변환
int GetHiPriChildIDX(Heap* ph, int idx) {
	if (GetLChildIDX(idx) > ph->numOfData)//NULL 값이면 반환 = 자식이 없다면 
		return 0;
	else if (GetLChildIDX(idx) == ph->numOfData)
		return GetLChildIDX(idx); //자식노드가 하나 뿐일때 
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
	HData retData = ph->heapArr[1]; //우선순위가 가장 높은 데이터
	HData lastElem = ph->heapArr[ph->numOfData];

	int parentIdx = 1;
	int childIdx;

	//우선순위가 높은 자식 노드를 시작으로 반복문 시작
	while (childIdx = GetHiPriChildIDX(ph, parentIdx)) {
		if(ph->comp(lastElem,ph->heapArr[childIdx])>=0) //자식 노드보다 우선순위가 높은 때 끝남 
			break;
		//마지막 노드보다 우선 순위가 높으니 비교대상 노드의 위치를 한 레벨 올림
		ph->heapArr[parentIdx] = ph->heapArr[childIdx];
		//마지막 노드가 저장될 위치 정보를 한 레벨 내림
		parentIdx = childIdx;
	}
	ph->heapArr[parentIdx] = lastElem;
	ph->numOfData -= 1;
	return retData;
}
