// 자기 참조 구조체로 연결 리스트 생성
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20

typedef struct NODE {  //NODE 자료형 정의
	char name[SIZE];
	int age;
	struct NODE* link;  //자기 참조 구조체 선언
} NODE;

int main(void) {
	NODE* list = NULL;  //list의 초기값은 반드시 NULL 값을로 설정
	NODE* p_prev = NULL, * p, * p_next;  //p_prev 초깃값을 반드시 NULL로 설정
	char buffer[SIZE];
	int age;

	//연결 리스트 생성
	while(1) {
		printf("\n성명 입력(그냥 [ENTER]를 치면 종료) : ");
		gets(buffer, SIZE);  //줄 바꿈 문자를 NULL로 변환하여 반환
		if (buffer[0] == '\0')  //성명을 입력하지 않고 엔터키를 누를 경우
			break;  //반복문을 빠져나가 프로그램 종료

		//동적 메모리 할당
		p = (NODE*)malloc(sizeof(NODE));
		//동적으로 생성된 구조체 주소를 반환하고 이 주소를 포인터 p에 저장
		//malloc()함수는 메모리에 동적으로 생성된 구조체주소를 반환하고 반환된 주소를 포인터 p에 저장
		strcpy_s(p->name, sizeof(p->name), buffer);  //문자열 복사 함수 사용
		//strcpy함수를 사용하여 p를 통해 구조체에 사용자가 입력한 성명을 복사함
		printf("나이 입력 : ");
		gets(buffer, SIZE);
		age = atoi(buffer);  //atoi() 함수로 입력받은 문자열(나이)을 정수로 변환
		p->age = age;

		if (list == NULL)  //리스트가 빈 경우
			list = p;  //새로운 노드를 첫 번째 노드로 생성
		else   //리스트가 비지 않은 경우
			p_prev->link = p;  //새로운 노드를 이전 노드의 링크 필드에 연결 
		//(p_prev는 바로 앞에서 할당된 구조체를 가리킴)

		p->link = NULL;  //새로운 노드의 링크 필드를 NULL로 설정
		//현재 처리하는 구조체가 연결리스트의 마지막노드라는 것을 의미하기 위해 link를 NULL로 설정
		p_prev = p;  //현재 노드를 이전 노드로 대입
		//현재의 국조체가 이전의 구조체로 반복수행하도록 p를 p_prev에 대입
	}

	//연결 리스트에 들어 있는 데이터 출력
	p = list; //연결리스트의 첫 번째 노드를 찾기 위해 첫번째 노드를 가리키는 헤드포인터 list를 p에 대입
	while (p != NULL) { //p를 통해 첫번째 노드가 가지고 있는 정보를 화면에 출력하기 위해while문 수행 p가 NULL이 되면 종료
		printf("[%s, %d]", p->name, p->age);
		p = p->link; //두번째 노드를 출력하는것으로 첫번째 노드의 link에 두번째 노드의 주소를 저장하기위함

		if (p != NULL) //p가 null이 아니면 "->"문자열 출력
			printf(" -> ");
	}

	//할당된 동적 메모리 반납
	p = list;  //각 노드별로 수행하기 위해 포인터p에 헤드포인터list값을 복사
	while (p != NULL) { //p=null일 경우, 즉 마지막 노드에 도달할때까지 메모리공간 반납
		p_next = p->link;  //p가 가리키는 메모리공간 모두 반납하면 p->link를 더이상 참조할 수 없으므로
		//메모리를 반납하기 전에 p->link를 p_next라는 포인터에 저장
		free(p); //free()함수를 이용하여 메모리 공간 반납
		p = p_next; //p_next를 p에 대입하여 다음 노드로 이동
	}
	return 0;
}