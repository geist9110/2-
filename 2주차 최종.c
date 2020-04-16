#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define RED         (FOREGROUND_RED | FOREGROUND_INTENSITY) // 색 조정용
#define GREEN       (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define BLUE        (FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define YELLOW      (RED | GREEN)
#define PUPLE		(RED | BLUE)
#define WHITE		(RED | BLUE | GREEN)
#define SKYBLUE     (GREEN | BLUE)
#define RED_BG      (BACKGROUND_RED | BACKGROUND_INTENSITY)
#define BLUE_BG     (BACKGROUND_BLUE | BACKGROUND_INTENSITY)
#define GREEN_BG    (BACKGROUND_GREEN | BACKGROUND_INTENSITY)
#define WHITE_BG    (RED_BG | GREEN_BG | BLUE_BG)

void PrintString(HANDLE hStdOut, WORD Attribute, LPCSTR str);
void MainMenu(int* selection, int* roop); // 메인 메뉴 호출
void SwitchingConsoleCursor(bool flag, int size); // 커서의 크기와 보이는걸 조정
void GotoXY(int _x, int _y);
void select_user(void); // 타자연습 유저 선택
void UserListLoad(void); // 기존 유저 목록 불러옴
void TypeMode(int selection2); // 타자연습 한,영 모드
void Test(int selection2, int selection3); // 타자연습 실행
void Result(int selection2, int selection3, float raptime, float average); // 마지막 결론창 도출, txt파일에 결론 입력
void AddNewUser(int* col_2); // 유저 추가
void DeleteNewUser(int* col_2); // 유저 삭제
void EditUser(int* col); // 유저 조작
int CheckName(char* name); // 이름의 존재 여부 확인
void About(void);
void PrintAllList(void);
void SearchList(void);

int main(void)
{
	int selection = 1;
	int* selection_address = &selection;

	int roop = 1;
	int* roop_address = &roop;
	system("title Typing Tester"); // 제목
	system("mode con:cols=100 lines=30"); // 화면 크기
	SwitchingConsoleCursor(false, 1); // 커서 숨김

	while (roop) {
		system("cls");
		MainMenu(selection_address, roop_address);
	}
}

void MainMenu(int* selection, int* roop) {

	int line_width = 100; // cmd 길이
	int start_string, check; // start_string : 문자열 위치 조정, check : _getch()함수 값 받아올때 사용
	int i = 8; // 메뉴 그림 첫번째 행 8번 행에서 시작
	int end = 70; // 메뉴 그림 그릴때 마지막 열

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	char title[] = "▶ T Y P I N G  T E S T E R ◀";
	start_string = (line_width / 2) - (strlen(title) / 2); // 타이틀 가운데 정렬
	GotoXY(start_string, 1);
	PrintString(hStdOut, GREEN, title);

	PrintString(hStdOut, PUPLE, "\n >> Press the arrow keys: ↑ or ↓ to navigate the option."); // 텍스트를 보라색으로
	printf(" >> Press <ENTER> key to accept an option.\n");
	printf(" >> [OR] Press the number keys to select your choice.");


	char menubar[] = "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
	start_string = (line_width / 2) - (strlen(menubar) / 4);

	GotoXY(start_string, i), PrintString(hStdOut, YELLOW, menubar), i++; // 8
	GotoXY(start_string, i), printf("┃            ***MAIN MENU***            ┃"), i++; // 9
	GotoXY(start_string, i), printf("┃                                       ┃"), i++; // 10
	if (*selection == 1) { // 11
		GotoXY(start_string, i);
		printf("┃  ");
		PrintString(hStdOut, WHITE_BG, "<1> Select User");
		GotoXY(end, i);
		PrintString(hStdOut, YELLOW, "┃"), i++;
	}
	else { // 11
		GotoXY(start_string, i), printf("┃  <1> Select User                      ┃"), i++;
	}
	GotoXY(start_string, i), printf("┃                                       ┃"), i++; // 12
	if (*selection == 2) { // 13
		GotoXY(start_string, i);
		printf("┃  ");
		PrintString(hStdOut, WHITE_BG, "<2> Statistics");
		GotoXY(end, i);
		PrintString(hStdOut, YELLOW, "┃"), i++;

	}
	else { // 13
		GotoXY(start_string, i), printf("┃  <2> Statistics                       ┃"), i++;
	}
	GotoXY(start_string, i), printf("┃                                       ┃"), i++; // 14
	if (*selection == 3) { // 15
		GotoXY(start_string, i);
		printf("┃  ");
		PrintString(hStdOut, WHITE_BG, "<3> View User Records");
		GotoXY(end, i);
		PrintString(hStdOut, YELLOW, "┃"), i++;
	}
	else {
		GotoXY(start_string, i), printf("┃  <3> View User Records                ┃"), i++; // 15
	}
	GotoXY(start_string, i), printf("┃                                       ┃"), i++; // 16
	if (*selection == 4) { // 17
		GotoXY(start_string, i);
		printf("┃  ");
		PrintString(hStdOut, WHITE_BG, "<4> About");
		GotoXY(end, i);
		PrintString(hStdOut, YELLOW, "┃"), i++;
	}
	else { // 17
		GotoXY(start_string, i), printf("┃  <4> About                            ┃"), i++;
	}
	GotoXY(start_string, i), printf("┃                                       ┃"), i++; // 18
	if (*selection == 5) { // 19
		GotoXY(start_string, i);
		printf("┃  ");
		PrintString(hStdOut, WHITE_BG, "<5> Quit");
		GotoXY(end, i);
		PrintString(hStdOut, YELLOW, "┃"), i++;
	}
	else { // 19
		GotoXY(start_string, i), printf("┃  <5> Quit                             ┃"), i++;
	}
	GotoXY(start_string, i), printf("┃                                       ┃"), i++; // 20
	GotoXY(start_string, i), printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"); // 21

	while (1) { // 입력값에 따른 처리
		check = _getch();

		if (check == 224) {
			check = _getch();
			switch (check) {
			case 72:
				*selection -= 1;
				if (*selection < 1) *selection = 1;
				break;

			case 80:
				*selection += 1;
				if (*selection > 5) *selection = 5;
				break;
			}
			break;
		}

		else if (check == 13) {
			switch (*selection) {
			case 1:
				select_user();
				break;

			case 2:
				PrintAllList();
				break;

			case 3:
				SearchList();
				break;

			case 4:
				About();
				break;

			case 5:
				*roop = 0;
				break;
			}
			break;
		}

		switch (check) {
		case 49:
			select_user();
			break;

		case 50:
			PrintAllList();
			break;

		case 51:
			SearchList();
			break;

		case 52:
			About();
			break;

		case 53:
			*roop = 0;
			break;

		case 48:
			UserListLoad();
			break;
		}
		break;
	}
}

void PrintString(HANDLE hStdOut, WORD Attribute, LPCSTR str) // 글자 색칠하는 함수
{
	SetConsoleTextAttribute(hStdOut, Attribute);
	puts(str);
}

void SwitchingConsoleCursor(bool flag, int size)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = size;
	cursorInfo.bVisible = flag;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void GotoXY(int _x, int _y)
{
	COORD pos = { _x, _y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void select_user(void) { // <=> userselectmenu
	int selection2 = 1, check, col = 0, quit = 1, for_design = 10;
	int* col_address = &col;
	int line_width = 100;
	char title[] = "S E L C T  U S E R";
	char design1[] = "━━━━━━━━━━━━━━━━━━━━";
	char temp[100];
	int i = 1, j = 6;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	FILE* fa = fopen("user list.txt", "r");
	while (fgets(temp, 100, fa) != NULL) {
		col++;
	}

while (quit) { // 마지막에서 한번더 밑으로 누르면 메인 메뉴로 돌아감

	system("cls");

	GotoXY(for_design + 1, 3);
	PrintString(hStdOut, YELLOW, title);

	GotoXY(for_design, 2);
	printf("%s", design1);
	GotoXY(for_design, 4);
	printf("%s", design1);

	FILE* fp = fopen("user list.txt", "r");
	PrintString(hStdOut, YELLOW, "");

	while (fgets(temp, 100, fp) != NULL) {
		if (i == selection2) {
			PrintString(hStdOut, WHITE_BG, "");
			GotoXY(for_design, j);
			printf("%d. %s", i, temp);
			PrintString(hStdOut, YELLOW, "");
		}
		else {
			GotoXY(for_design, j);
			printf("%d. %s", i, temp);
		}
		i++;
		j += 2;
	}
	fclose(fp);

	if (col + 1 == selection2) {
		PrintString(hStdOut, WHITE_BG, "");
		GotoXY(for_design, j);
		printf("%d. Edit user", i++);
		PrintString(hStdOut, YELLOW, "");
	}
	else {
		GotoXY(for_design, j);
		printf("%d. Edit user", i++);
	}

	if (col + 2 == selection2) {
		PrintString(hStdOut, WHITE_BG, "");
		GotoXY(for_design, j + 2);
		printf("%d. Quit", i++);
		PrintString(hStdOut, YELLOW, "");
	}
	else {
		GotoXY(for_design, j + 2);
		printf("%d. Quit", i++);
	}
	i = 1, j = 6;

	while (1) { // selection2의 값을 방향키로 바꿈
		check = _getch();

		if (check == 224) {
			check = _getch();
			switch (check) {
			case 72: // up
				selection2 -= 1;
				if (selection2 < 1) selection2 = 1;
				break;

			case 80: // down
				selection2 += 1;
				if (selection2 > col + 2) selection2 = col + 2;
				break;
			}
			break;
		}
		else if (check == 13) {
			if (selection2 == col + 2) {
				quit = 0;
			}
			else if (selection2 == col + 1) {
				EditUser(col_address);
			}
			else {
				TypeMode(selection2);
				quit = 0;
			}
		}
		break;
	}
}
}

void TypeMode(int selection2) { // <=> listLesson()
	int for_design = 10, row = 6;
	char design1[] = "━━━━━━━━━━━━━━━━━━━━━";
	int line_width = 100;
	char title[] = "M O D E  S E L E C T";
	char ModeTitle [100] ;
	int selection3 = 1;
	int quit = 1;
	int check, col = 0, col_2, i, j = 1, k;
	int l = 0;
	char temp[100];

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	FILE* fb = fopen("test.txt", "r");
	while (fgets(temp, 100, fb) != NULL) {
		col++;
	}
	fclose(fb);

	col_2 = col / 7;

	while (quit) {
		system("cls");
		GotoXY(for_design + 1, 3);
		PrintString(hStdOut, YELLOW, title);
		GotoXY(for_design, 2);
		printf("%s", design1);
		GotoXY(for_design, 4);
		printf("%s", design1);

		row = 6;
		j = 1;

		for (i = 0; i < col_2; i++) {
			FILE* fa = fopen("test.txt", "r");

			for (k = 0; k < i * 8; k++) {
				fgets(temp, 100, fa);
			}

			fgets(temp, 100, fa); // 첫번째

			if (selection3 == j) { // 두번째 입력

				PrintString(hStdOut, WHITE_BG, "");
				GotoXY(for_design, row);
				printf("%d. %s", i+1, temp);
				PrintString(hStdOut, YELLOW, "");
			}
			else {
				GotoXY(for_design, row);
				printf("%d. %s", i+1, temp);
			
			fgets(temp, 100, fa);
			fgets(temp, 100, fa); // 두번째
			fgets(temp, 100, fa); // 세번째
			fgets(temp, 100, fa); // 네번째
			fgets(temp, 100, fa); // 다섯번째
			fgets(temp, 100, fa); // 여섯번째
			fgets(temp, 100, fa); // 일곱번째
			}
			row += 2;
			j++;
			fclose(fa);
		}

		if (selection3 == col_2 + 1) {
			PrintString(hStdOut, WHITE_BG, "");
			GotoXY(for_design, row);
			printf("%d. Quit", col_2 + 1);
			PrintString(hStdOut, YELLOW, "");
		}
		else {
			GotoXY(for_design, row);
			printf("%d. Quit", col_2 + 1);
		}

		while (1) { // selection2의 값을 방향키로 바꿈
			check = _getch();

			if (check == 224) {
				check = _getch();
				switch (check) {
				case 72: // up
					selection3 -= 1;
					if (selection3 < 1) selection3 = 1;
					break;

				case 80: // down
					selection3 += 1;
					if (selection3 > col_2 + 1) selection3 = col_2 + 1;
					break;
				}
				break;
			}
			else if (check == 13) {
				if (selection3 == col_2 + 1) {
					quit = 0;
				}
				else {
					quit = 0;
					Test(selection2, selection3);
				}
			}
			break;
		}

	}
}

void Test(int selection2, int selection3) { // <=> begin session

	int for_design = 10, row = 3, i;
	char design1[] = "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
	char song[100];
	char title[100];
	char temp1[100]; // 첫째 줄
	char temp2[100];
	char temp3[100];
	char temp4[100];
	char temp5[100];
	char answer1[100];
	char answer2[100];
	char answer3[100];
	char answer4[100];
	char answer5[100];

	float average; // 평균 계산용
	float Count = 0; // 맞는거 계산용
	float StrCount = 0; // 문자열 계산용
	int SpaceCount = 0; // 문자열 속 단어 계산용
	double t0, t1, RapTime; // 시간 세는 용도
	int line_width = 100;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");


	PrintString(hStdOut, YELLOW, "");


	FILE* fp = fopen("test.txt", "r");

	for (i = 0; i < (8 * (selection3-1)); i++) {
		fgets(temp1, 100, fp);
	}

	fgets(title, 100, fp);
	fgets(song, 100, fp);
	fgets(temp1, 100, fp);
	fgets(temp2, 100, fp);
	fgets(temp3, 100, fp);
	fgets(temp4, 100, fp);
	fgets(temp5, 100, fp);
	fclose(fp);

	GotoXY(for_design+1, row);
	printf("%s", title);
	GotoXY(for_design+1, row + 1);
	printf("%s", song);
	GotoXY(for_design, row - 1);
	printf("%s", design1);
	GotoXY(for_design, row + 2);
	printf("%s", design1);

	if (selection3 == 2) Count = -2; // 오차율 보정

	PrintString(hStdOut, SKYBLUE, "");
	GotoXY(for_design, 10);
	printf("%s", temp1);
	GotoXY(for_design, 13);
	printf("%s", temp2);
	GotoXY(for_design, 16);
	printf("%s", temp3);
	GotoXY(for_design, 19);
	printf("%s", temp4);
	GotoXY(for_design, 22);
	printf("%s", temp5);

	PrintString(hStdOut, WHITE, "");
	t0 = GetTickCount64(); // 시작 시간

	getchar();// 오류 보정
	SwitchingConsoleCursor(true, 1); // 커서 보이게 함
	GotoXY(for_design, 11);
	scanf("%[^\n]s", &answer1);
	getchar();// 오류 보정
	GotoXY(for_design, 14);
	scanf("%[^\n]s", &answer2);
	getchar();
	GotoXY(for_design, 17);
	scanf("%[^\n]s", &answer3);
	getchar();
	GotoXY(for_design, 20);
	scanf("%[^\n]s", &answer4);
	getchar();
	GotoXY(for_design, 23);
	scanf("%[^\n]s", &answer5);
	getchar();

	t1 = GetTickCount64(); // 끝난 시간

	strcat(answer1, "\n");
	strcat(answer2, "\n");
	strcat(answer3, "\n");
	strcat(answer4, "\n");
	strcat(answer5, "\n");

	for (i = 0; i < 100; i++) { // 오류 세기
		if (temp1[i] != answer1[i]) {
			Count++;
		}
		if (temp2[i] != answer2[i]) {
			Count++;
		}
		if (temp3[i] != answer3[i]) {
			Count++;
		}
		if (temp4[i] != answer4[i]) {
			Count++;
		}
		if (temp5[i] != answer5[i]) {
			Count++;
		}
	}

	StrCount = strlen(temp1) + strlen(temp2) + strlen(temp3) + strlen(temp4) + strlen(temp5);
	average = ((StrCount - Count) * 100) / StrCount;

	RapTime = (t1 - t0) / 1000;

	SwitchingConsoleCursor(false, 1); // 커서 숨김
	_getch(); // 다음 화면 대기

	Result(selection2, selection3, RapTime, average);
}

void Result(int selection2, int selection3, float raptime, float average) {
	char name[100], lesson[100];
	char for_design = 10, row = 3;
	char design1[] = "━━━━━━━━━━━━━";
	int i;
	int WPM, AllStrCount = 0;
	char buffer[33]; // 문자열로 변환 시키는 용도
	char Date[30], Time[30];
	char temp[100], str_count[100];
	int col = 0, col_2, k;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");


	GotoXY(for_design + 1, row);
	PrintString(hStdOut, YELLOW, "R E S U L T");
	GotoXY(for_design, row - 1);
	printf("%s", design1);
	GotoXY(for_design, row + 1);
	printf("%s", design1);

	FILE* fa = fopen("user list.txt", "r"); // selection2를 이용해 name 값 받아오기
	for (i = 0; i < selection2; i++) {
		fgets(name, 100, fa);
	}
	fclose(fa);

	FILE* fc = fopen("test.txt", "r");
	while (fgets(temp, 100, fc) != NULL) {
		col++;
	}
	fclose(fc);

	col_2 = col / 2;

	for (i = 0; i < col_2; i++) {
		FILE* fb = fopen("test.txt", "r");

		for (k = 0; k < i * 8; k++) {
			fgets(temp, 100, fb);
		}

		fgets(lesson, 100, fb); // 레슨 값
		fgets(temp, 100, fb); 
		fgets(temp, 100, fb);
		fgets(temp, 100, fb);
		fgets(temp, 100, fb);
		fgets(temp, 100, fb);
		fgets(temp, 100, fb);
		fgets(str_count, 100, fb); // str 카운트
	}
	fclose(fa);

	AllStrCount = atoi(str_count);

	WPM = (AllStrCount * 60) / raptime;

	struct tm* now;
	time_t now_t;

	time(&now_t);
	now = localtime(&now_t);

	_itoa(now->tm_mon, buffer, 10); // 날짜 문자열 화
	strcpy(Date, buffer);
	strcat(Date, "m/");
	_itoa(now->tm_mday, buffer, 10);
	strcat(Date, buffer);
	strcat(Date, "d/");
	_itoa(now->tm_year + 1900, buffer, 10);
	strcat(Date, buffer);
	strcat(Date, "y\n");

	_itoa(now->tm_hour, buffer, 10);
	strcpy(Time, "[");
	strcat(Time, buffer);
	strcat(Time, "h:");
	_itoa(now->tm_min, buffer, 10);
	strcat(Time, buffer);
	strcat(Time, "m:");
	_itoa(now->tm_sec, buffer, 10);
	strcat(Time, buffer);
	strcat(Time, "s]\n");

	GotoXY(for_design, row + 3);
	printf("Name : %s", name);
	GotoXY(for_design, row + 5);
	printf("Lesson title : %s", lesson);
	GotoXY(for_design, row + 7);
	printf("Duration : %0.2f seconds\n", raptime);
	GotoXY(for_design, row + 9);
	printf("Gross Speed : %d WPM\n", WPM);
	GotoXY(for_design, row + 11);
	printf("Accuracy : %0.2f%%\n", average);
	GotoXY(for_design, row + 13);
	printf("Date : %d, %d, %d\n", now->tm_mon + 1, now->tm_mday, now->tm_year + 1900);
	GotoXY(for_design, row + 15);
	printf("Time : [%dh:%dm:%ds]", now->tm_hour, now->tm_min, now->tm_sec);

	FILE* fb = fopen("statistics.txt", "a");
	fputs(name, fb);
	fputs(lesson, fb);
	_gcvt(raptime, 6, buffer);
	fputs(buffer, fb);
	fputs("\n", fb);
	_itoa(WPM, buffer, 10);
	fputs(buffer, fb);
	fputs("\n", fb);
	_gcvt(average, 6, buffer);
	fputs(buffer, fb);
	fputs("\n", fb);
	fputs(Date, fb);
	fputs(Time, fb);

	fclose(fb);
	_getch();
}

void UserListLoad(void) { // 실험용 내역 생성

	char name[] = "LHG\nHYJ\n";

	char song1[] = "KOREAN TEST\n아 로 하\n어두운 불빛아래 촛불 하나 와인 잔에 담긴 약속하나\n항상 너의 곁에서 널 지켜줄거야 날 믿어준 너였잖아\n나 바라는 건 오직 하나 영원한 행복을 꿈꾸지만\n화려하지 않아도 꿈같진 않아도 너만 있어주면 돼\n걱정 마, 언제나 이 순간을 잊지 않을게\n37\n";
	char song2[] = "ENGLISH TEST\nY O U N G ,  W I L D  A N D  F R E E\nSo what we get drunk, So what we get smoke weed\nWe're just having fun, We don't care who sees\nSo what we go out\nThat's how it's supposed to be\nLiving young and wild and free\n40\n";

	char LeeIf[] = "LHG\nENGLISH TEST\n32.594\n73\n100.\n3m/16d/2020y\n[21h:9m:31s]\n";
	char HanIf[] = "HYJ\nENGLISH TEST\n31.123\n78\n100.\n3m/16d/2020y\n[19h:8m:33s]\n";

	FILE* fa = fopen("user list.txt", "w");
	fputs(name, fa);
	fclose(fa);

	FILE* fb = fopen("test.txt", "w");
	fputs(song1, fb);
	fputs(song2, fb);
	fclose(fb);

	FILE* fc = fopen("statistics.txt", "w");
	fputs(LeeIf, fc);
	fputs(HanIf, fc);
	fclose(fc);

	int for_design = 10, row = 3;
	char design1[] = "━━━━━━━━━━━━━━━━━";
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	GotoXY(for_design + 1, row);
	PrintString(hStdOut, YELLOW, "U S E R  L I S T");
	GotoXY(for_design, row - 1);
	printf("%s", design1);
	GotoXY(for_design, row + 1);
	printf("%s", design1);

	GotoXY(for_design, row + 3);
	printf("유저 리스트와 타자 연습 리스트가 생성되었습니다.");
	_getch();

}

void EditUser(int* col) {

	int col_2 = *col;
	int* col_2_address = &col_2;
	int selection = 1;
	int check;
	int for_design = 10, row = 3;
	char design1[] = "━━━━━━━━━━━━━━━━━";
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	while (1) { // 입력값에 따른 처리
		system("cls");

		GotoXY(for_design+1, row);
		PrintString(hStdOut, YELLOW, "E D I T  U S E R");
		GotoXY(for_design, row-1);
		printf("%s", design1);
		GotoXY(for_design, row+1);
		printf("%s", design1);

		if (selection == 1) {
			GotoXY(for_design, row + 3);
			PrintString(hStdOut, WHITE_BG, "1. Add new user");
			PrintString(hStdOut, YELLOW, "");
		}
		else {
			GotoXY(for_design, row + 3);
			printf("1. Add new user");
		}

		if (selection == 2) {
			GotoXY(for_design, row + 5);
			PrintString(hStdOut, WHITE_BG, "2. Delete user");
			PrintString(hStdOut, YELLOW, "");
		}
		else {
			GotoXY(for_design, row + 5);
			printf("2. Delete user");
		}

		if (selection == 3) {
			GotoXY(for_design, row + 7);
			PrintString(hStdOut, WHITE_BG, "3. Quit");
			PrintString(hStdOut, YELLOW, "");
		}
		else {
			GotoXY(for_design, row + 7);
			printf("3. Quit");
		}

		check = _getch();

		if (check == 224) {
			check = _getch();
			switch (check) {
			case 72:
				selection -= 1;
				if (selection < 1) selection = 1;
				break;

			case 80:
				selection += 1;
				if (selection > 3) selection = 3;
				break;
			}
		}

		else if (check == 13) {
			switch (selection) {
			case 1:
				AddNewUser(col_2_address);
				*col = col_2;
				break;

			case 2:
				DeleteNewUser(col_2_address);
				*col = col_2;
				break;

			case 3:
				break;
			}
			break;
		}

	}
}

void AddNewUser(int* col_2) {
	char name[100];
	char* name_address = &name;
	int for_design = 10, row = 3;
	char design1[] = "━━━━━━━━━━━━━━━━━━━━━━━━━━━";

	system("cls");
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	GotoXY(for_design + 1, row);
	PrintString(hStdOut, YELLOW, "A D D  N E W  U S E R");
	GotoXY(for_design, row - 1);
	printf("%s", design1);
	GotoXY(for_design, row + 1);
	printf("%s", design1);

	SwitchingConsoleCursor(true, 1); // 커서 생성
	GotoXY(for_design, row + 3);
	printf("Name : ");
	scanf("%s", &name);
	SwitchingConsoleCursor(false, 1); // 커서 숨김

	if (!CheckName(name_address)) { // 이름이 없다면 실행
		FILE* fa = fopen("user list.txt", "a");
		fputs(name, fa);
		fputs("\n", fa);
		fclose(fa);
		GotoXY(for_design, row + 5);
		printf("%s has been entered successfully", name);
		_getch();
		*col_2 += 1;
	}

	else {
		GotoXY(for_design, row + 5);
		printf("%s already exist", name);
		_getch();
	}
}

void DeleteNewUser(int* col_2) {
	char temp[100], name[100], check[100];
	char* name_address = &name;
	int i = 0, j = 0, k = 1, col = 0;
	int for_design = 10, row = 3;
	char design1[] = "━━━━━━━━━━━━━━━━━━━";
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	GotoXY(for_design + 1, row);
	PrintString(hStdOut, YELLOW, "D E L T E  U S E R");
	GotoXY(for_design, row - 1);
	printf("%s", design1);
	GotoXY(for_design, row + 1);
	printf("%s", design1);

	SwitchingConsoleCursor(true, 1); // 커서 생성
	GotoXY(for_design, row + 3);
	printf("Name : ");
	scanf("%s", name);
	SwitchingConsoleCursor(false, 1); // 커서 숨김

	if (CheckName(name_address)) { // 이름이 있다면 실행

		strcpy(check, name);
		strcat(check, "\n");
		FILE* fa = fopen("temp.txt", "w"); // temp 초기화
		fclose(fa);

		FILE* fb = fopen("user list.txt", "r");
		while (fgets(temp, 100, fb) != NULL) {
			col++;
		}
		fclose(fb);

		for (i; i < col; i++) { // 찾는 이름 제외한 나머지를 temp로 복사

			FILE* fc = fopen("user list.txt", "r"); // contact.txt의 각 행의 문자열을 가져옴
			for (j = 0; j < k; j++) {
				fgets(temp, 100, fc);
			}

			if (!strcmp(temp, check)) { // check 와 contact를 비교
				fclose(fc);
			}

			else {
				fclose(fc);
				FILE* fd = fopen("temp.txt", "a"); // 가져온 문자열을 임시 파일에 집어넣음
				fputs(temp, fd);
				fclose(fd);
			}
			k += 1;
		}

		k = 1, i = 0; // k와 i 초기화
		FILE* fe = fopen("user list.txt", "w"); // contact list 초기화
		fclose(fe);

		for (i; i < col - 1; i++) { // temp.txt에서 user list.txt로 이동

			FILE* ff = fopen("temp.txt", "r"); // temp.txt의 각 행의 문자열을 가져옴
			for (j = 0; j < k; j++) {
				fgets(temp, 100, ff);
			}
			fclose(ff);

			FILE* fg = fopen("user list.txt", "a"); // 가져온 문자열을 임시 파일에 집어넣음
			fputs(temp, fg);
			fclose(fg);

			k += 1;
		}

		GotoXY(for_design, row + 5);
		printf("%s has been deleted successfully", name);
		*col_2 -= 1;
		_getch();
	}
	else {
		GotoXY(for_design, row + 5);
		printf("%s does not exist", name);
		_getch();
	}
}

int CheckName(char* name) { // user.txt에 name값이 있는지 없는지 확인
	char temp[100];
	char check[100];

	strcpy(check, name);
	strcat(check, "\n"); // strcmp를 위해서 \n를 더해줌

	FILE* ff = fopen("user list.txt", "r"); // user.txt의 행의 개수 세기
	while (fgets(temp, 100, ff) != NULL) {
		if (!strcmp(temp, check)) {
			return 1;
		}
	}
	fclose(ff);
}

void About(void) {

	int for_design = 10, row = 3;
	char design1[] = "━━━━━━━━━━";
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	GotoXY(for_design + 1, row);
	PrintString(hStdOut, YELLOW, "A B O U T");
	GotoXY(for_design, row - 1);
	printf("%s", design1);
	GotoXY(for_design, row + 1);
	printf("%s", design1);

	GotoXY(for_design, row + 3);
	printf("정보보호 119 2주차 7분반 한연재, 이현기");
	GotoXY(for_design, row + 5);
	printf("메인 메뉴에서 0번키를 누르면 타자 연습용 텍스트 파일과 유저 목록이 생성 됩니다.");
	_getch();
}

void PrintAllList(void) {

	system("cls");
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	char buffer[200];
	int i, k = 5, col = 0, col_2;
	int for_design = 10, row = 3;
	char design1[] = "━━━━━━━━━━━━━━━━━━━━";

	GotoXY(for_design + 1, row);
	PrintString(hStdOut, YELLOW, "S T A T I S T I C S");
	GotoXY(for_design, row - 1);
	printf("%s", design1);
	GotoXY(for_design, row + 1);
	printf("%s", design1);

	GotoXY(for_design, row + 3);
	printf("Sn");

	GotoXY(for_design + 3, row + 3);
	printf("Name");

	GotoXY(for_design + 11, row + 3);
	printf("Lesson");

	GotoXY(for_design + 25, row + 3);
	printf("Duration");

	GotoXY(for_design + 35, row + 3);
	printf("WPM");

	GotoXY(for_design + 40, row + 3);
	printf("Accuracy");

	GotoXY(for_design + 50, row + 3);
	printf("Date");

	GotoXY(for_design + 66, row + 3);
	printf("Time");

	GotoXY(for_design, row + 4);
	printf("%s%s%s%s", design1, design1, design1, design1);
	
	FILE* ff = fopen("statistics.txt", "r");
	while (fgets(buffer, 100, ff) != NULL) {
		col++;
	}
	fclose(ff);

	col_2 = col / 7;

	FILE* fa = fopen("statistics.txt", "r");

	for (i = 0; i < col_2; i++) {
		GotoXY(for_design, k + 3); // Sn
		printf("%d", i + 1);

		GotoXY(for_design + 3, k + 3);
		fgets(buffer, 200, fa); // name
		printf("%s", buffer);

		GotoXY(for_design + 11, k + 3); //Lesson
		fgets(buffer, 200, fa);
		printf("%s", buffer);
		
		GotoXY(for_design + 25, k + 3); // Duration
		fgets(buffer, 200, fa);
		printf("%s", buffer);

		GotoXY(for_design + 35, k + 3); //Wpm
		fgets(buffer, 200, fa);
		printf("%s", buffer);

		GotoXY(for_design + 40, k + 3); //Accuracy
		fgets(buffer, 200, fa);
		printf("%s", buffer);

		GotoXY(for_design + 50, k + 3); // Date
		fgets(buffer, 200, fa);
		printf("%s", buffer);

		GotoXY(for_design + 66, k + 3); // time
		fgets(buffer, 200, fa);
		printf("%s", buffer);

		k++;
	}
	fclose(fa);
	_getch();
}

void SearchList(void) {
	char name[100];
	char temp[100];
	int col = 0, i, j = 7, k = 1;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	int for_design = 10, row = 3;
	char design1[] = "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
	char design2[] = "━━━━━━━━━━━━━━━━━━━━";

	system("cls");

	GotoXY(for_design + 1, row);
	PrintString(hStdOut, YELLOW, "V I E W  U S E R  R E C O R D S");
	GotoXY(for_design, row-1);
	printf("%s", design1);
	GotoXY(for_design, row + 1);
	printf("%s", design1);

	GotoXY(for_design, row + 3);
	printf("Finding name : ");
	scanf("%s", name);
	strcat(name, "\n");

	GotoXY(for_design, row + 5);
	printf("Sn");

	GotoXY(for_design + 3, row + 5);
	printf("Name");

	GotoXY(for_design + 11, row + 5);
	printf("Lesson");

	GotoXY(for_design + 25, row + 5);
	printf("Duration");

	GotoXY(for_design + 35, row + 5);
	printf("WPM");

	GotoXY(for_design + 40, row + 5);
	printf("Accuracy");

	GotoXY(for_design + 50, row + 5);
	printf("Date");

	GotoXY(for_design + 66, row + 5);
	printf("Time");

	GotoXY(for_design, row + 6);
	printf("%s%s%s%s", design2, design2, design2, design2);


	FILE* fa = fopen("statistics.txt", "r");
	while (fgets(temp, 100, fa) != NULL) {
		col++;
	}
	fclose(fa);

	FILE* ff = fopen("statistics.txt", "r");
	for (i = 0; i < col; i++) {
		fgets(temp, 100, ff);

		if (!strcmp(name, temp)) {
			GotoXY(for_design, row + j); // sn
			printf("%d", k);

			GotoXY(for_design + 3, row + j);
			printf("%s", temp);

			fgets(temp, 100, ff);  // lesson
			GotoXY(for_design + 11, row + j);
			printf("%s", temp);

			fgets(temp, 100, ff);  // duration
			GotoXY(for_design + 25, row + j);
			printf("%s", temp);

			fgets(temp, 100, ff);  // Wpm
			GotoXY(for_design + 35, row + j);
			printf("%s", temp);

			fgets(temp, 100, ff);  // accuracy
			GotoXY(for_design + 40, row + j);
			printf("%s", temp);

			fgets(temp, 100, ff);  // date
			GotoXY(for_design + 50, row + j);
			printf("%s", temp);

			fgets(temp, 100, ff);  // time
			GotoXY(for_design + 66, row + j);
			printf("%s", temp);

			fgets(temp, 100, ff);  // dummy

			j++;
			k++;
		}
	}
	_getch();
}