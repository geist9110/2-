#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include<stdbool.h>

#define RED         (FOREGROUND_RED | FOREGROUND_INTENSITY) // 색 조정용
#define GREEN       (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define BLUE        (FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define YELLOW      (RED | GREEN)
#define PUPLE		(RED | BLUE)
#define RED_BG      (BACKGROUND_RED | BACKGROUND_INTENSITY)
#define BLUE_BG     (BACKGROUND_BLUE | BACKGROUND_INTENSITY)
#define GREEN_BG    (BACKGROUND_GREEN | BACKGROUND_INTENSITY)
#define WHITE_BG    (RED_BG | GREEN_BG | BLUE_BG)

void PrintString(HANDLE hStdOut, WORD Attribute, LPCSTR str);
void design(int* start_string, char* text);
void MainMenu(int* selection); // 메인 메뉴 호출
void SwitchingConsoleCursor(bool flag, int size); // 커서의 크기와 보이는걸 조정
void GotoXY(int _x, int _y);
void select_user(void);
void UserListLoad(void);

int main(void)
{
	int selection = 1;
	int* selection_address = &selection;
	system("title Typing Tester"); // 제목
	system("mode con:cols=100 lines=30"); // 화면 크기
	SwitchingConsoleCursor(false, 1); // 커서 숨김
	UserListLoad();

	while (1) {
		system("cls");
		MainMenu(selection_address);
	}
}

void MainMenu(int* selection) {

	int end = 70;
	char* insert[100];
	int line_width = 100; // cmd 길이
	int* start_string;
	int check;

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

	GotoXY(start_string, 8);
	PrintString(hStdOut, YELLOW, menubar);

	design(start_string, "┃            ***MAIN MENU***            ┃\n");
	design(start_string, "┃                                       ┃\n");
	if (*selection == 1) {
		GotoXY(start_string, 11);
		printf("┃  ");
		PrintString(hStdOut, WHITE_BG, "<1> Select User");
		GotoXY(end, 11);
		PrintString(hStdOut, YELLOW, "┃");

	}
	else {
		design(start_string, "┃  <1> Select User                      ┃\n");
	}
	design(start_string, "┃                                       ┃\n");
	if (*selection == 2) {
		GotoXY(start_string, 13);
		printf("┃  ");
		PrintString(hStdOut, WHITE_BG, "<2> Statistics");
		GotoXY(end, 13);
		PrintString(hStdOut, YELLOW, "┃");

	}
	else {
		design(start_string, "┃  <2> Statistics                       ┃\n");
	}
	design(start_string, "┃                                       ┃\n");
	if (*selection == 3) {
		GotoXY(start_string, 15);
		printf("┃  ");
		PrintString(hStdOut, WHITE_BG, "<3> View User Records");
		GotoXY(end, 15);
		PrintString(hStdOut, YELLOW, "┃");

	}
	else {
		design(start_string, "┃  <3> View User Records                ┃\n");
	}
	design(start_string, "┃                                       ┃\n");
	if (*selection == 4) {
		GotoXY(start_string, 17);
		printf("┃  ");
		PrintString(hStdOut, WHITE_BG, "<4> About");
		GotoXY(end, 17);
		PrintString(hStdOut, YELLOW, "┃");

	}
	else {
		design(start_string, "┃  <4> About                            ┃\n");
	}
	design(start_string, "┃                                       ┃\n");
	if (*selection == 5) {
		GotoXY(start_string, 19);
		printf("┃  ");
		PrintString(hStdOut, WHITE_BG, "<5> Quit");
		GotoXY(end, 19);
		PrintString(hStdOut, YELLOW, "┃");

	}
	else {
		design(start_string, "┃  <5> Quit                             ┃\n");
	}
	design(start_string, "┃                                       ┃\n");
	design(start_string, "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n\n");

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
				system("cls");
				printf("4\n");
				system("pause");
				break;

			case 5:
				system("cls");
				printf("5\n");
				system("pause");
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
			system("cls");
			printf("4\n");
			system("pause");
			break;

		case 53:
			system("cls");
			printf("5\n");
			system("pause");
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

void design(int* start_string, char* text) {
	int i;
	for (i = 0; i < start_string; i++) printf(" ");
	printf("%s", text);
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

void select_user(void) { // select user 시작시
	int start_string;
	int line_width = 100;
	char title[] = "S E L C T  U S E R";
	char design1[] = "========================================";
	char temp[100];
	int i = 0, j = 6;

	system("cls");
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	FILE* fp = fopen("user list.txt", "r");

	start_string = (line_width / 2) - (strlen(title) / 2);
	GotoXY(start_string, 3);

	PrintString(hStdOut, GREEN, title);

	start_string = (line_width / 2) - (strlen(design1) / 2);
	GotoXY(start_string, 2);
	printf(design1);
	GotoXY(start_string, 4);
	printf("%s\n", design1);


	PrintString(hStdOut, YELLOW, "");
	while (fgets(temp, 100, fp) != NULL) {
		GotoXY(35, j);
		printf("%d. %s", i + 1, temp);
		i++;
		j++;
	}
	fclose(fp);
	printf("\n");
	system("pause");
}

void UserListLoad(void) {
	char name1[] = "LEE\n";
	char name2[] = "HAN\n";
	FILE* fp = fopen("user list.txt", "w");
	fputs(name1, fp);
	fputs(name2, fp);
	fclose(fp);
}