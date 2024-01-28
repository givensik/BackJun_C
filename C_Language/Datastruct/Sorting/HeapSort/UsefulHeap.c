#include <stdio.h>
#include <stdlib.h>

#include "UsefulHeap.h"

void HeapInit(Heap * ph, PriorityComp pc){
	ph->numOfData = 0;
	ph->comp = pc;
}

int HIsEmpty(Heap * ph){
	if(ph->numOfData > 0){
		return FALSE;
	}else{
		return TRUE;
	}
}

int GetParentIDX(int idx){
	return idx/2;
}

int GetLChildIDX(int idx){
	return idx*2;
}
int GetRChildIDX(int idx){
	return GetLChildIDX(idx)+1;
}

// 우선순위가 높은 자식 노드의 인덱스를 출력
// 자식노드가 없음 -> 0, 자식 노드가 하나 -> 1
int GetHiPriChildIDX(Heap * ph, int idx){
	// printf("numOfData = %d\n", ph->numOfData);
	// printf("부모 노드 인덱스 = %d일때\n",idx);
	// printf("왼쪽 자식 노드 %c\n",ph->heapArr[GetLChildIDX(idx)]);
	// printf("오른쪽 자식 노드 %c\n",ph->heapArr[GetLChildIDX(idx)+1]);
	// 왼쪽 자식 노드의 인덱스가 힙의 마지막 노드의 인덱스보다 크면 안됨
	if(GetLChildIDX(idx) > ph->numOfData){
		return 0;
	}else if(GetLChildIDX(idx) == ph->numOfData){ // 왼쪽 자식의 인덱스가 마지막 노드의 인덱스랑 같으면 왼쪽 자식 노드만 있는거 인데..? 삭제한거면 마지막 노드가 올라간 상태로 가정해야하는 거 아닌가?
		// printf("노드 하나라 왼쪽 노드\n");
		return GetLChildIDX(idx);
	}else{// 자식 노드 둘 다 있으면
		// 오른쪽 자식 노드의 우선순위가 높을 때
		// ph->comp(ph->heapArr[GetLChildIDX(idx)].data, ph->heapArr[GetRChildIDX(idx)].data);
		if(ph->comp(ph->heapArr[GetLChildIDX(idx)], ph->heapArr[GetRChildIDX(idx)]) < 0){
			// printf("오른쪽이 우선순위 높음\n");
			return GetRChildIDX(idx);
		}else{
			// printf("왼쪽이 우선순위 높음\n");
			return GetLChildIDX(idx);
		}
	}
}


void HInsert(Heap * ph, HData data){
	// printf("HINSERT %c\n", data);
	int idx = ph->numOfData + 1;
	// HeapElem nelem = {data, pr};

	// idx가 1이 아닐때 = 1이면 루트 노드임
	while(idx != 1){
		// 새로 추가하는 원소의 우선순위가 부모보다 높을 때
		// pr < (ph->heapArr[GetParentIDX(idx)]).pr => 왼쪽 데이터의 우선 순위가 높을 때
		if(ph->comp(data, ph->heapArr[GetParentIDX(idx)]) > 0){
			// idx에 부모 노드의 값을 저장
			ph->heapArr[idx] = ph->heapArr[GetParentIDX(idx)];
			// 부모노드의 인덱스를 idx로 저장 
			idx = GetParentIDX(idx);
		}else{// 만약 부모 노드보다 우선순위가 낮다면 반복문 멈추기
			break;
		}
	}

	ph->heapArr[idx] = data;
	ph->numOfData += 1;		
}

HData HDelete(Heap * ph){
	
	// printf("Delete \n");
	// 지울 데이터 값 -> 루트 노드의 데이터
	HData retData = ph->heapArr[1];

	// 임시로 마지막 노드를 저장
	HData lastElem = ph->heapArr[ph->numOfData]; 
	
	int parentIdx = 1;
	int childIdx;

	// 루트 노드부터 우선 순위가 높은 자식 노드랑 비교 교환? 을 하지 않고 우선 순위만 비교하면서 인덱스 값의 값을 찾아감
	int i = 10;
	while(i>0){
		// printf("parentIdx = %d\n", parentIdx);
		childIdx = GetHiPriChildIDX(ph, parentIdx);
		if(childIdx == 0 ){
			break;
		}
		// printf("lastnode = %c,  ChildIdx = %c \n", lastElem,ph->heapArr[childIdx]);
		
		// if(parentIdx == ph->numOfData){
		// 	printf("parentIdx = %d, numOfData = %d\n -> 멈춤",parentIdx, ph->numOfData);
		// 	break;
		// }
		
		// 마지막 노드의 우선순위가 자식 노드보다 더 높을 때 -> 멈추기
		// if(lastElem.pr <= (ph->heapArr[childIdx]).pr)
		
		if(ph->comp(lastElem, ph->heapArr[childIdx]) >= 0){
			// printf("lastnode pr >= 자식노드 pr \n");
			break;
		}
		// 마지막 노드의 우선순위가 더 높을 때 -> 부모 노드에 자식 노드를 넣고 부모노드로 올라간 자식 노드의 인덱스를 부모인덱스로 설정
		ph->heapArr[parentIdx] = ph->heapArr[childIdx];
		parentIdx = childIdx;
		i--;
	}

	ph->heapArr[parentIdx] = lastElem;
	ph->numOfData -= 1;

	return retData;
}