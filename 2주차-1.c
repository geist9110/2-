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
void MainMenu(int* selection); // 메인 메뉴 호출
void SwitchingConsoleCursor(bool flag, int size); // 커서의 크기와 보이는걸 조정
void GotoXY(int _x, int _y);
void select_user(void);
void UserListLoad(void);
void TypeMode(int* selection2);
void EnglishTest(int* selection2, int* selection3);

int main(void)
{
	int selection = 1;
	int* selection_address = &selection;
	system("title Typing Tester"); // 제목
	system("mode con:cols=100 lines=30"); // 화면 크기
	SwitchingConsoleCursor(false, 1); // 커서 숨김

	while (1) {
		system("cls");
		MainMenu(selection_address);
	}
}

void MainMenu(int* selection) {

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

void select_user(void) { // select user 시작시
	int selection2 = 1, check, col = 0, quit = 1;
	int* selection2_address = &selection2;
	int start_string;
	int line_width = 100;
	char title[] = "S E L C T  U S E R";
	char design1[] = "========================================";
	char temp[100];
	int i = 1, j = 6;

	FILE* fp = fopen("user list.txt", "r");
	while (fgets(temp, 100, fp) != NULL) {
		col++;
	}
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	while (quit) { // 마지막에서 한번더 밑으로 누르면 메인 메뉴로 돌아감
		system("cls");
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
			if (i == selection2) {
				PrintString(hStdOut, WHITE_BG, "");
				GotoXY(35, j);
				printf("%d. %s", i, temp);
				PrintString(hStdOut, YELLOW, "");
			}
			else {
				GotoXY(35, j);
				printf("%d. %s", i, temp);
			}
			i++;
			j++;
		}
		if (col + 1 == selection2) { // 마지막 Quit 추가
			PrintString(hStdOut, WHITE_BG, "");
			GotoXY(35, j++);
			printf("%d. Quit", i++);
			PrintString(hStdOut, YELLOW, "");
		}
		else {
			GotoXY(35, j++);
			printf("%d. Quit", i++);
		}
		fclose(fp);
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
					if (selection2 > col + 1) selection2 = col + 1;
					break;
				}
				break;
			}
			else if (check == 13) {
				if (selection2 == col + 1) {
					quit = 0;
				}
				else {
					TypeMode(selection2_address);
					quit = 0;
				}
			}
			break;
		}
	}
}

void UserListLoad(void) { // 실험용 내역 생성
	char name1[] = "LEE\n";
	char name2[] = "HAN\n";
	char name3[] = "PARK\n";

	char Esong1[] = "So what we get drunk, So what we get smoke weed\n";
	char Esong2[] = "We're just having fun, We don't care who sees\n";
	char Esong3[] = "So what we go out\n";
	char Esong4[] = "That's how it's supposed to be\n";
	char Esong5[] = "Living young and wild and free\n";

	char Hsong1[] = "어두운 불빛아래 촛불 하나 와인 잔에 담긴 약속하나\n";
	char Hsong2[] = "항상 너의 곁에서 널 지켜줄거야 날 믿어준 너였잖아\n";
	char Hsong3[] = "나 바라는 건 오직 하나 영원한 행복을 꿈꾸지만\n";
	char Hsong4[] = "화려하지 않아도 꿈같진 않아도 너만 있어주면 돼\n";
	char Hsong5[] = "걱정 마, 언제나 이 순간을 잊지 않을게\n";

	FILE* fa = fopen("user list.txt", "w");
	fputs(name1, fa);
	fputs(name2, fa);
	fputs(name3, fa);
	fclose(fa);

	FILE* fb = fopen("english test.txt", "w");
	fputs(Esong1, fb);
	fputs(Esong2, fb);
	fputs(Esong3, fb);
	fputs(Esong4, fb);
	fputs(Esong5, fb);
	fclose(fb);

	FILE* fc = fopen("korean test.txt", "w");
	fputs(Hsong1, fc);
	fputs(Hsong2, fc);
	fputs(Hsong3, fc);
	fputs(Hsong4, fc);
	fputs(Hsong5, fc);
	fclose(fc);

	system("cls");
	printf("easter egg");
	system("pause");
}

void TypeMode(int* selection2) {
	int start_string;
	int line_width = 100;
	char title[] = "M O D E  S E L E C T";
	int selection3 = 1;
	int* selection3_address = &selection3;
	int quit = 1;
	int check;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	while (quit) {
		system("cls");
		start_string = (line_width / 2) - (strlen(title) / 2);
		GotoXY(start_string, 2);
		PrintString(hStdOut, GREEN, title);
		PrintString(hStdOut, YELLOW, "");

		if (selection3 == 1) {
			PrintString(hStdOut, WHITE_BG, "");
			GotoXY(start_string, 4);
			printf("1. 한글");
			PrintString(hStdOut, YELLOW, "");
		}
		else {
			GotoXY(start_string, 4);
			printf("1. 한글");
		}

		if (selection3 == 2) {
			PrintString(hStdOut, WHITE_BG, "");
			GotoXY(start_string, 5);
			printf("2. ENGLISH");
			PrintString(hStdOut, YELLOW, "");
		}
		else {
			GotoXY(start_string, 5);
			printf("2. ENGLISH");
		}

		if (selection3 == 3) {
			PrintString(hStdOut, WHITE_BG, "");
			GotoXY(start_string, 6);
			printf("3. Quit");
			PrintString(hStdOut, YELLOW, "");
		}
		else {
			GotoXY(start_string, 6);
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
					EnglishTest(selection3_address, selection3_address);
				}
			}
			break;
		}

	}
}

void EnglishTest(int* selection2, int* selection3) {
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

	SwitchingConsoleCursor(true, 1); // 커서 보이게 함
	FILE* fp = fopen("english test.txt", "r");
	fgets(temp1, 100, fp);
	fgets(temp2, 100, fp);
	fgets(temp3, 100, fp);
	fgets(temp4, 100, fp);
	fgets(temp5, 100, fp);
	fclose(fp);

	int start_string;
	int line_width = 100;
	char title[] = "E N G L I S H  T E S T";
	char Song[] = "Y O U N G ,  W I L D  A N D  F R E E";
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);


	system("cls");
	PrintString(hStdOut, GREEN, "");
	start_string = (line_width / 2) - (strlen(title) / 2);
	GotoXY(start_string, 2);
	printf("%s", title);
	start_string = (line_width / 2) - (strlen(Song) / 2);
	GotoXY(start_string, 3);
	printf("%s\n", Song);

	GotoXY(3, 10);
	printf("%s", temp1);

	GotoXY(3, 13);
	printf("%s", temp2);

	GotoXY(3, 16);
	printf("%s", temp3);

	GotoXY(3, 19);
	printf("%s", temp4);

	GotoXY(3, 22);
	printf("%s", temp5);

	GotoXY(3, 11);
	scanf("%s", &answer1[95]);

	GotoXY(3, 14);
	scanf("%s", &answer2[95]);

	GotoXY(3, 17);
	scanf("%s", &answer3[95]);

	GotoXY(3, 20);
	scanf("%s", &answer4[95]);

	GotoXY(3, 23);
	scanf("%s", &answer5[95]);

	GotoXY(3, 29);
	system("pause");
	SwitchingConsoleCursor(false, 1); // 커서 숨김
}