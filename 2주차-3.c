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
void UserListLoad(void); // 이스터에그 기존 유저 목록 불러옴
void TypeMode(int selection2); // 타자연습 한,영 모드
void Test(int selection2, int selection3); // 타자연습 실행
void Result(int selection2, int selection3, float raptime, float average); // 마지막 결론창 도출, txt파일에 결론 입력
void AddNewUser(int* col_2); // 유저 추가
void DeleteNewUser(int* col_2); // 유저 삭제
void EditUser(int* col); // 유저 조작
int CheckName(char* name); // 이름의 존재 여부 확인
void About(void);

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
				system("cls");
				printf("2\n");
				system("pause");
				break;

			case 3:
				system("cls");
				printf("3\n");
				system("pause");
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
			system("cls");
			printf("2\n");
			system("pause");
			break;

		case 51:
			system("cls");
			printf("3\n");
			system("pause");
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
		printf("%s",design1);
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
	int selection3 = 1;
	int quit = 1;
	int check;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	while (quit) {
		system("cls");
		GotoXY(for_design + 1, 3);
		PrintString(hStdOut, YELLOW, title);
		GotoXY(for_design, 2);
		printf("%s", design1);
		GotoXY(for_design, 4);
		printf("%s", design1);

		if (selection3 == 1) {
			PrintString(hStdOut, WHITE_BG, "");
			GotoXY(for_design, row);
			printf("1. 한글");
			PrintString(hStdOut, YELLOW, "");
		}
		else {
			GotoXY(for_design, row);
			printf("1. 한글");
		}

		if (selection3 == 2) {
			PrintString(hStdOut, WHITE_BG, "");
			GotoXY(for_design, row + 2);
			printf("2. ENGLISH");
			PrintString(hStdOut, YELLOW, "");
		}
		else {
			GotoXY(for_design, row + 2);
			printf("2. ENGLISH");
		}

		if (selection3 == 3) {
			PrintString(hStdOut, WHITE_BG, "");
			GotoXY(for_design, row + 4);
			printf("3. Quit");
			PrintString(hStdOut, YELLOW, "");
		}
		else {
			GotoXY(for_design, row + 4);
			printf("3. Quit");
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
					if (selection3 > 3) selection3 = 3;
					break;
				}
				break;
			}
			else if (check == 13) {
				if (selection3 == 3) {
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
	char design1[] = "━━━━━━━━━━━━━━━━━━━━━━";
	char design2[] = "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";
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
	char title1[] = "K O R E A N  T E S T";
	char title2[] = "E N G L I S H  T E S T";
	char Song1[] = "아 로 하";
	char Song2[] = "Y O U N G ,  W I L D  A N D  F R E E";
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");


	PrintString(hStdOut, YELLOW, "");

	if (selection3 == 1) { // 한글
		FILE* fp = fopen("test.txt", "r");
		fgets(temp1, 100, fp);
		fgets(temp2, 100, fp);
		fgets(temp3, 100, fp);
		fgets(temp4, 100, fp);
		fgets(temp5, 100, fp);
		fclose(fp);

		GotoXY(for_design+1, row);
		printf("%s", title1);
		GotoXY(for_design+1, row + 1);
		printf("%s", Song1);
		GotoXY(for_design, row - 1);
		printf("%s", design1);
		GotoXY(for_design, row + 2);
		printf("%s", design1);
		SpaceCount = 37;
	}

	else if (selection3 == 2) { // 영어

		FILE* fp = fopen("test.txt", "r");
		for (i = 0; i < 5; i++) {
			fgets(temp1, 100, fp);
		}
		fgets(temp1, 100, fp);
		fgets(temp2, 100, fp);
		fgets(temp3, 100, fp);
		fgets(temp4, 100, fp);
		fgets(temp5, 100, fp);
		fclose(fp);

		GotoXY(for_design+1, row);
		printf("%s", title2);
		GotoXY(for_design+1, row + 1);
		printf("%s", Song2);
		GotoXY(for_design, row - 1);
		printf("%s", design2);
		GotoXY(for_design, row + 2);
		printf("%s", design2);
		SpaceCount = 40;
		Count = -2; // 오차율 보정
	}

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


	getchar(); // 오류 보정
	t0 = GetTickCount64(); // 시작 시간
	SwitchingConsoleCursor(true, 1); // 커서 보이게 함

	PrintString(hStdOut, WHITE, "");
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
	char name[50], lesson[20];
	char for_design = 10, row = 3;
	char design1[] = "━━━━━━━━━━━━━";
	int i;
	int WPM, AllStrCount = 0;
	char buffer[33]; // 문자열로 변환 시키는 용도
	char Date[30], Time[30];

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
		fgets(name, 50, fa);
	}
	fclose(fa);

	if (selection3 == 1) {
		strcpy(lesson, "한글\n");
		AllStrCount = 37;
	}
	else if (selection3 == 2) {
		strcpy(lesson, "English\n");
		AllStrCount = 40;
	}

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

	char name1[] = "LEE\n";
	char name2[] = "HAN\n";
	char name3[] = "PARK\n";

	char song1[] = "어두운 불빛아래 촛불 하나 와인 잔에 담긴 약속하나\n";
	char song2[] = "항상 너의 곁에서 널 지켜줄거야 날 믿어준 너였잖아\n";
	char song3[] = "나 바라는 건 오직 하나 영원한 행복을 꿈꾸지만\n";
	char song4[] = "화려하지 않아도 꿈같진 않아도 너만 있어주면 돼\n";
	char song5[] = "걱정 마, 언제나 이 순간을 잊지 않을게\n";
	char song6[] = "So what we get drunk, So what we get smoke weed\n";
	char song7[] = "We're just having fun, We don't care who sees\n";
	char song8[] = "So what we go out\n";
	char song9[] = "That's how it's supposed to be\n";
	char song10[] = "Living young and wild and free\n";

	FILE* fa = fopen("user list.txt", "w");
	fputs(name1, fa);
	fputs(name2, fa);
	fputs(name3, fa);
	fclose(fa);

	FILE* fb = fopen("test.txt", "w");
	fputs(song1, fb);
	fputs(song2, fb);
	fputs(song3, fb);
	fputs(song4, fb);
	fputs(song5, fb);
	fputs(song6, fb);
	fputs(song7, fb);
	fputs(song8, fb);
	fputs(song9, fb);
	fputs(song10, fb);

	fclose(fb);

	int for_design = 10, row = 3;
	char design1[] = "━━━━━━━━━━━━━━━━━━━";
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	GotoXY(for_design + 1, row);
	PrintString(hStdOut, YELLOW, "E A S T E R  E G G");
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