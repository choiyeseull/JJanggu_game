#include <bangtal>
#include <ctime>
using namespace bangtal;

ObjectID startButton, startButton2, endButton, howtoplayButton;
ObjectID jjang_gu, huni, yuri, cheolsu, maenggu, stone_maenggu;	//맹구 뛰는거 추가해야함
ObjectID howtoplay, howtodo2, howtodo3, howtodo4, howtodo5;
ObjectID continue1, continue2, continue3, continue4;
ObjectID replay1, replay2, replay3, replay4;
ObjectID warp, click_maenggu;
SceneID final_stage, score_ground;
SceneID startscene, startwithtitle, scene1, scene2, scene3, scene4, scene5;
SceneID scene2_1, scene3_1, scene4_1, scene5_1;

SoundID startsound, bgm, peace, hunibgm, yuribgm, cheolsubgm, final_bgm;
SoundID win, hit, clicksound, chocob_sound,move_glass,change_outil, pick_stone;
TimerID start, menu, play_timer;

int minute = 0; 
int sec = 0;

int jjang_guX = 400, jjang_guY = 50, meX = 0;
int now_scene = 1;
int direct=0;
bool all_pass[4] = { 0, };	//all_pass[0] = 훈이, all_pass[1] = 유리, all_pass[2] = 철수

//1. 훈이게임
ObjectID gameground, parischae, hand, bug[40], ministart1;
SceneID success1, fail1;
TimerID bug_time, huni_timer;
int bugX[40], bugY[40], what_bug[40];
int outil = 0; //파리채 = 1, 손 = 2
int catch_bug = 0, bug_count = 0, wrong = 0;

//2. 유리게임
ObjectID notattack, attack, ministart2, arrow[8];
SceneID success2, fail2;
TimerID arrow_timer, show_attack;
int count = 0;
int arrow_number[8] = { 0, };
int turn = 0;

//3. 철수게임
SceneID gameground3, success3, fail3;
ObjectID ministart3, rewrite, submit;
ObjectID number[10];	//노란색숫자
ObjectID express[5];	//철수가 임으로 생성하는 식 저장 (두자리수)*(두자리수)
ObjectID click[4];		//짱구가 노란숫자 4개 클릭
int first = 0, second = 0, answer;	//first * second = answer
int now = 0; //짱구가 지금 몇개 클릭했냐
int click_number[4];
int count3 = 0;	//몇번 맞췄냐


//4. 맹구게임
SceneID gameground4, success4;
ObjectID ministart4, fail4;

SceneID bg1, bg2, bg3, bg4, bg5, bg6;	//돌찾는 배경
ObjectID glass1, glass2, glass3, glass4, glass5;	//돋보기 5개
ObjectID here1, here3, here5, here6;			//돌 숨겨져있는 곳
ObjectID fake1, fake3, fake5, fake6;
ObjectID stone1, stone3, stone5, stone6;	//돌
ObjectID back1, back2, back3, back5, back6, back_game;	//되돌아가기

SceneID showcase;
ObjectID check;	//돌 수집 현황
ObjectID Ston1, Ston2, Ston3, Ston4;

ObjectID chocoB1, chocoB2, chocoB3, chocoB4;
TimerID choco;
int stone_count = 0;
bool heart[4] = { 0, }; //초코비 찾으면 증가

ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown)
{
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);
	if (shown) {
		showObject(object);
	}
	return object;
}

//player 위치 변경 함수
void locate(int numero) {
	switch(numero){
	case 1 :
		if (direct == 0) {
			locateObject(jjang_gu, scene1, jjang_guX, jjang_guY);
			locateObject(huni, scene1, jjang_guX - 80, jjang_guY);
			locateObject(yuri, scene1, jjang_guX - 160, jjang_guY);
			locateObject(cheolsu, scene1, jjang_guX - 240, jjang_guY);
			locateObject(maenggu, scene1, jjang_guX - 320, jjang_guY);
		}
		else {
			locateObject(jjang_gu, scene1, jjang_guX, jjang_guY);
			locateObject(huni, scene1, jjang_guX + 80, jjang_guY);
			locateObject(yuri, scene1, jjang_guX + 160, jjang_guY);
			locateObject(cheolsu, scene1, jjang_guX + 240, jjang_guY);
			locateObject(maenggu, scene1, jjang_guX + 320, jjang_guY);
		}
		break;

	case 2:
		if (direct == 0) {
			locateObject(jjang_gu, scene2, jjang_guX, jjang_guY);
			locateObject(huni, scene2, jjang_guX - 80, jjang_guY);
			locateObject(yuri, scene2, jjang_guX - 160, jjang_guY);
			locateObject(cheolsu, scene2, jjang_guX - 240, jjang_guY);
			locateObject(maenggu, scene2, jjang_guX - 320, jjang_guY);
		}
		else {
			locateObject(jjang_gu, scene2, jjang_guX, jjang_guY);
			locateObject(huni, scene2, jjang_guX + 80, jjang_guY);
			locateObject(yuri, scene2, jjang_guX + 160, jjang_guY);
			locateObject(cheolsu, scene2, jjang_guX + 240, jjang_guY);
			locateObject(maenggu, scene2, jjang_guX + 320, jjang_guY);
		}
		break;

	case 3 :
		if (direct == 0) {
			locateObject(jjang_gu, scene3, jjang_guX, jjang_guY);
			locateObject(huni, scene3, jjang_guX - 80, jjang_guY);
			locateObject(yuri, scene3, jjang_guX - 160, jjang_guY);
			locateObject(cheolsu, scene3, jjang_guX - 240, jjang_guY);
			locateObject(maenggu, scene3, jjang_guX - 320, jjang_guY);
		}
		else {
			locateObject(jjang_gu, scene3, jjang_guX, jjang_guY);
			locateObject(huni, scene3, jjang_guX + 80, jjang_guY);
			locateObject(yuri, scene3, jjang_guX + 160, jjang_guY);
			locateObject(cheolsu, scene3, jjang_guX + 240, jjang_guY);
			locateObject(maenggu, scene3, jjang_guX + 320, jjang_guY);
		}
		break;
	case 4 :
		if (direct == 0) {
			locateObject(jjang_gu, scene4, jjang_guX, jjang_guY);
			locateObject(huni, scene4, jjang_guX - 80, jjang_guY);
			locateObject(yuri, scene4, jjang_guX - 160, jjang_guY);
			locateObject(cheolsu, scene4, jjang_guX - 240, jjang_guY);
			locateObject(maenggu, scene4, jjang_guX - 320, jjang_guY);
		}
		else {
			locateObject(jjang_gu, scene4, jjang_guX, jjang_guY);
			locateObject(huni, scene4, jjang_guX + 80, jjang_guY);
			locateObject(yuri, scene4, jjang_guX + 160, jjang_guY);
			locateObject(cheolsu, scene4, jjang_guX + 240, jjang_guY);
			locateObject(maenggu, scene4, jjang_guX + 320, jjang_guY);
		}
		break;
	case 5 :	//맹구, 유치원
		if (direct == 0) {
			locateObject(jjang_gu, scene5, jjang_guX, jjang_guY);
			locateObject(huni, scene5, jjang_guX - 80, jjang_guY);
			locateObject(yuri, scene5, jjang_guX - 160, jjang_guY);
			locateObject(cheolsu, scene5, jjang_guX - 240, jjang_guY);
			locateObject(maenggu, scene5, jjang_guX - 320, jjang_guY);
		}
		else {
			locateObject(jjang_gu, scene5, jjang_guX, jjang_guY);
			locateObject(huni, scene5, jjang_guX + 80, jjang_guY);
			locateObject(yuri, scene5, jjang_guX + 160, jjang_guY);
			locateObject(cheolsu, scene5, jjang_guX + 240, jjang_guY);
			locateObject(maenggu, scene5, jjang_guX + 320, jjang_guY);
		}
		break;
	case 6 :
		if (direct == 0) {
			locateObject(jjang_gu, final_stage, jjang_guX, jjang_guY);
			locateObject(huni, final_stage, jjang_guX - 80, jjang_guY);
			locateObject(yuri, final_stage, jjang_guX - 160, jjang_guY);
			locateObject(cheolsu, final_stage, jjang_guX - 240, jjang_guY);
			locateObject(maenggu, final_stage, jjang_guX - 320, jjang_guY);
		}
		else {
			locateObject(jjang_gu, final_stage, jjang_guX, jjang_guY);
			locateObject(huni, final_stage, jjang_guX + 80, jjang_guY);
			locateObject(yuri, final_stage, jjang_guX + 160, jjang_guY);
			locateObject(cheolsu, final_stage, jjang_guX + 240, jjang_guY);
			locateObject(maenggu, final_stage, jjang_guX + 320, jjang_guY);
		}
		break;


	}
	
}
void check_move() {		//player가 화면 밖에서 움직이지 않도록 체크하는 함수
	if (jjang_guX + meX < 0){}
	else{
		switch (now_scene) {
		case 1:
			jjang_guX += meX;
			if (jjang_guX > 1280) {	
				enterScene(scene2);
				now_scene = 2; jjang_guX = 30;
				locate(2);
			}
			else {
				locate(1);
			}
			break;
		case 2:
			jjang_guX += meX;
			if (jjang_guX > 1280) {
				enterScene(scene3);
				now_scene = 3; jjang_guX = 30;
				locate(3);
			}
			else if(jjang_guX < 30) {	//뒤로 가면
				enterScene(scene1);
				now_scene = 1; jjang_guX = 1200;
				locate(1);
			}
			else {
				locate(2);
			}
			break;
		case 3:
			jjang_guX += meX;
			if (jjang_guX > 1280) {
				enterScene(scene4);
				now_scene = 4; jjang_guX = 30;
				locate(4);
			}
			else if (jjang_guX < 30) {	//뒤로 가면
				enterScene(scene2);
				now_scene = 2; jjang_guX = 1200;
				locate(2);
			}
			else {
				locate(3);
			}
			break;
		case 4:
			jjang_guX += meX;
			if (jjang_guX > 1280) {
				enterScene(scene5);
				now_scene = 5; jjang_guX = 30;
				locate(5);
			}
			else if (jjang_guX < 30) {	//뒤로 가면
				enterScene(scene3);
				now_scene = 3; jjang_guX = 1200;
				locate(3);
			}
			else {
				locate(4);
			}
			break;
		case 5:
			jjang_guX += meX;
			if (jjang_guX < 30) {	//뒤로 가면
				enterScene(scene4);
				now_scene = 4; jjang_guX = 1200;
				locate(4);
			} 
			else if (jjang_guX > 1280) {
				enterScene(final_stage);
				now_scene = 6; jjang_guX = 30;
				locate(6);
			}
			else{
				jjang_guX += meX;
				locate(5);
			}
			break;
		case 6 :
			jjang_guX += meX;
			if (jjang_guX < 30) {	//뒤로 가면
				enterScene(scene5);
				now_scene = 5; jjang_guX = 1200;
				locate(5);
			}
			else if (jjang_guX > 1180) { jjang_guX = 1170; }
			else {
				if (all_pass[0] == true || all_pass[1] == true || all_pass[2] == true || all_pass[3] == true) {
					showObject(warp);
				}
				jjang_guX += meX;
				locate(6);
			}
			break;

		}

	}
}

//1. 훈이게임
void create_bug() {
	int x, y;
	char name[200];	//경로저장
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 40; i++) {	// 총 벌레 40마리
		x = rand() % 5000;	//시작 위치
		y = rand() % 350;

		bugX[i] = 1280 + x;
		bugY[i] = 200 + y;
		what_bug[i] = 1 + rand() % 2;
		sprintf_s(name, "Image/hunigame/%d.png", what_bug[i]);
		bug[i] = createObject(name, scene2_1, bugX[i], bugY[i], true);
		scaleObject(bug[i], 0.4f);

	}
}
void how_many_catch(int num) {
	if (num == 20) {	//20마리잡아야함
		stopTimer(bug_time);
		enterScene(success1);
		stopSound(hunibgm);
		playSound(win);
		stopTimer(huni_timer);
		hideTimer();
		all_pass[0] = true;
		showMessage("20마리 잡기 성공! 훈이와 같이 유리네 집으로 가자!");
		showObject(huni);
	}
}

//2. 유리게임

void create_arrow() {
	char name[200];

	//1,2,3,4 화살표있음
	for (int i = 0; i < 8; i++) {
		arrow_number[i] = 1 + rand() % 4;

		sprintf_s(name, "Image/yurigame/%d.png", arrow_number[i]);

		arrow[i] = createObject(name, scene3_1, 570 + 80 * i, 100, true);
		scaleObject(arrow[i], 0.3f);
	}
}
void arrow_check() {
	if (turn == 8) {
		if (count < 4) {
			for (int i = 0; i < 8; i++) {
				hideObject(arrow[i]);
				turn = 0;	
			}
			count++;
			create_arrow();
		}
		else {
			//5번 성공
			enterScene(success2);
			stopSound(yuribgm);
			playSound(win);
			all_pass[1] = true;
			stopTimer(arrow_timer);
			showMessage("5번 성공! 유리와 같이 철수네 집으로 가자!");
			showObject(yuri);
		}
	}
	
}

//3. 철수게임
void createnumber() {		//짱구가 눌러야할 노란 숫자 생성
	char path[200];
	for (int i = 0; i < 10; i++) {
		sprintf_s(path, "Image/chulsugame/%d.png", i);
		number[i] = createObject(path, gameground3, 590 + (i*60), 100, true);
	}
}
void make_number(int th) {
	int num;
	char path[200];
	num = 1 + rand() % 30;	//1 ~ 30 생성
	sprintf_s(path, "Image/chulsugame/c%d.png", num / 10);
	if(num/10 != 0){
		express[th-1] = createObject(path, gameground3, 520 + (50 * th), 390, true); //scaleObject(express[2], 0.9f);
	}
	sprintf_s(path, "Image/chulsugame/c%d.png", num % 10);
	express[th] = createObject(path, gameground3, 570 + (50 * th), 390, true);
	if (th == 1) {
		first = num;
	}
	else {
		second = num;
	} 
}
void make_express() {	//랜덤 식 생성
	
	make_number(1);	//firsrt생성
	make_number(4);	//second생성

	//1. 곱셈할건지 덧셈할건지
	int kind = rand() % 2;
	
	if (kind == 0) {	// 0 나오면 곱셈
		express[2] = createObject("Image/chulsugame/x.png", gameground3, 670, 400, true); //scaleObject(express[2], 0.9f);
		answer = first * second;
	}
	else {
		express[2] = createObject("Image/chulsugame/+.png", gameground3, 670, 400, true); //scaleObject(express[2], 0.9f);	
		answer = first + second;
	}
}
void renew() {
	
	if (count3 < 5) {
		now = 0;
		answer = 0;
		for (int i = 0; i < 4; i++) {
			hideObject(click[i]);
			click_number[i] = 0;
		}
		for (int i = 0; i < 5; i++) {
			hideObject(express[i]);
		}
		make_express();	//철수 new식
	}
	else {
		enterScene(success3);
		stopSound(cheolsubgm);
		playSound(win);
		all_pass[2] = true;
		showMessage("5번 맞추기 성공! 다같이 맹구 만나러 떡잎유치원으로 가자!");
		showObject(cheolsu);

	}
}
void answer_compare() {	//맞았으면 1반환 틀렸으면 0반환
	int position = now-1;
	int nombre = 0;	//짱구가 누른거 숫자로 변환해서 저장
	for (int i = 0; i < now; i++) {
		nombre += click_number[i] * pow(10, position);
		position--;
	}
	if (answer == nombre) {
		count3++;
		renew();
	}
	else {
		stopSound(cheolsubgm);
		enterScene(fail3);
	}
}

//4. 맹구게임
void check_stone_number() {
	if (stone_count == 4) {
		playSound(win);
		stopSound(peace);
		enterScene(success4);
	}
}
void count_heart() {
	int count = 0;
	for (int i = 0; i < 4; i++) {
		if (heart[i] == true) {
			count++;
			if (count == 3) {
				//타이머
				startTimer(choco);
				
			}
		}
	}
}

/// /////////////////////////////////////////////////////////////////////////////////////////////////////// 콜백함수

void keyboardCallback(KeyCode code, KeyState state) {
	
	if (code == 83) { //right
		meX += (state == KeyState::KEYBOARD_PRESSED ? 40 : -40);
		setObjectImage(jjang_gu, "Image/짱구.png");
		setObjectImage(huni, "Image/훈이.png");
		setObjectImage(yuri, "Image/유리.png");
		setObjectImage(cheolsu, "Image/철수.png");
		setObjectImage(maenggu, "Image/맹구.png");
		direct = 0;
		check_move();
	}
	else if (code == 82) {  //left
		meX -= (state == KeyState::KEYBOARD_PRESSED ? 30 : -30);
		setObjectImage(jjang_gu, "Image/짱구뒤.png");
		setObjectImage(huni, "Image/훈이뒤.png");
		setObjectImage(yuri, "Image/유리뒤.png");
		setObjectImage(cheolsu, "Image/철수뒤.png");
		setObjectImage(maenggu, "Image/맹구뒤.png");
		direct = 1;
		check_move();
	}
	else if (code == 84) {   //up
		switch (now_scene) {
		case 2:
			if (jjang_guX > 400 && jjang_guX < 450) {
				if (all_pass[0] == true) {
					showMessage("이미 훈이를 데리고 나왔습니다 \n 왼쪽으로 이동하세요!");
				}
				else {
					enterScene(scene2_1);
				}
			} break;
		case 3:
			if (jjang_guX > 100 && jjang_guX < 200) {
				if (all_pass[1] == true) {
					showMessage("이미 유리를 데리고 나왔습니다 \n 왼쪽으로 이동하세요!");
				}
				else {
					enterScene(scene3_1);
				}
			} break;
		case 4:
			if (jjang_guX > 400 && jjang_guX < 450) {
				if (all_pass[2] == true) {
					showMessage("이미 철수를 데리고 나왔습니다 \n 왼쪽으로 이동하세요!");
				}
				else {
					enterScene(scene4_1);
				}
			} break;
		case 6 :
			if (jjang_guX > 900 && jjang_guX < 950) {
				stopSound(bgm);
				playSound(final_bgm);
				enterScene(score_ground);
				stopTimer(play_timer);

				char min[200];
				sprintf_s(min, " 걸린시간 : %d 분 ~ %d분 사이", minute, minute+1);
				showMessage(min);
			}
		}
	}
	//2. 유리게임
	else if (code == 23) {	
		if (state == KeyState::KEYBOARD_PRESSED) {
			if (arrow_number[turn] == 1) {	
				setObjectImage(arrow[turn], "Image/yurigame/5.png");	
				showObject(attack); startTimer(show_attack);
				turn++;
				arrow_check();
			}
			else {
				stopSound(yuribgm);
				enterScene(fail2);
				stopTimer(arrow_timer);
			}
		}	
	}
	else if (code == 4) {
		if (state == KeyState::KEYBOARD_PRESSED) {
			if (arrow_number[turn] == 2) {
				setObjectImage(arrow[turn], "Image/yurigame/6.png");
				showObject(attack); startTimer(show_attack);
				turn++; 
				arrow_check();
			}
			else {
				stopSound(yuribgm);
				enterScene(fail2);
				stopTimer(arrow_timer);
			}
		}
	}
	else if (code == 19) {
		if (state == KeyState::KEYBOARD_PRESSED) {
			if (arrow_number[turn] == 3) {
				setObjectImage(arrow[turn], "Image/yurigame/7.png");
				showObject(attack); startTimer(show_attack);
				turn++;
				arrow_check();
			}
			else {
				enterScene(fail2);
				stopSound(yuribgm);
				stopTimer(arrow_timer);
			}
		}
	}
	else if (code == 1) {
		if (state == KeyState::KEYBOARD_PRESSED) {
			if (arrow_number[turn] == 4) {
				setObjectImage(arrow[turn], "Image/yurigame/8.png");
				showObject(attack); startTimer(show_attack);
				turn++;
				arrow_check();
			}
			else {
				stopSound(yuribgm);
				enterScene(fail2);
				stopTimer(arrow_timer);
			}
		}
	}
}
void timerCallback(TimerID timer) {
	if (timer == start) {
		enterScene(startwithtitle);
	}
	if (timer == menu) {
		showObject(startButton);
		showObject(endButton);
		showObject(howtoplayButton);
	}
	if (timer == huni_timer) {
		stopSound(hunibgm);
		enterScene(fail1);
	}
	if (timer == bug_time) {
		for (int i = 0; i < 30; i++) {
			bugX[i] -= 10;
			locateObject(bug[i], scene2_1, bugX[i], bugY[i]);
			if (bugX[i] < 600) {
				hideObject(bug[i]);
			}
		}
		setTimer(bug_time, 0.05f);
		startTimer(bug_time);
	}
	if (timer == arrow_timer) {	//몇초 안에 패스해야함
		enterScene(fail2);
		showMessage("시간초과");
	}
	if (timer == show_attack) {
		playSound(hit);
		hideObject(attack);
		setTimer(show_attack,0.3f);
	}
	if (timer == choco) {
		enterScene(fail4);
	}
	if (timer == play_timer) {
		
		minute++;

		setTimer(play_timer, 60.f);
		startTimer(play_timer);
	}
}
void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	
	if (object == startButton|| object == startButton2) {
		playSound(clicksound);
		hideObject(startButton);
		enterScene(scene1);
		playSound(bgm);
	}
	if (object == endButton) {
		playSound(clicksound);
		endGame();
	}
	if (object == howtoplayButton) {
		playSound(clicksound);
		enterScene(howtoplay);
	}
	if (object == replay1) {	//1. 훈이게임 replay
		playSound(clicksound);
		hideObject(gameground);
		hideObject(parischae);
		hideObject(hand);
		
		enterScene(scene2_1);
		showObject(howtodo2);
		showObject(ministart1);
		
		for(int i = 0; i < 30; i++) {
			hideObject(bug[i]);
			bugX[i] = 0;
			bugY[i] = 0;
			what_bug[i]=0;
		}		
		outil = 0; //파리채 = 1, 손 = 2
		catch_bug = 0, bug_count = 0, wrong = 0;
		
		setTimer(bug_time, 0.05f);
		setTimer(huni_timer, 25.0f);
		
	}

	//1. 훈이 게임
	if (object == ministart1) {
		playSound(clicksound);
		stopSound(bgm);
		playSound(hunibgm);
		hideObject(ministart1);
		hideObject(howtodo2);
		showObject(gameground);
		showObject(parischae);
		showObject(hand);

		create_bug();
		startTimer(bug_time);
		startTimer(huni_timer);
		showTimer(huni_timer);
	}
	if (object == hand) {
		playSound(change_outil);
		outil = 2;
		scaleObject(hand, 1.5f);
		scaleObject(parischae, 1.0f);
	}
	if (object == parischae) {
		playSound(change_outil);
		outil = 1;
		scaleObject(parischae, 1.5f);
		scaleObject(hand, 1.0f);
	}
	for (int i = 0; i < 30; i++) {
		if (object == bug[i]) {	//1. 파리채, 2. 손
			if (what_bug[i] == 1) {
				if (outil == 1) {
					catch_bug++;
					how_many_catch(catch_bug);
					hideObject(bug[i]);
				}
				else {
					stopTimer(huni_timer); hideTimer();
					stopTimer(bug_time); 
					enterScene(fail1);
					stopSound(hunibgm);
				}
			}
			else if (what_bug[i] == 2) {
				if (outil == 2) {
					catch_bug++;
					how_many_catch(catch_bug);
					hideObject(bug[i]);
				}
				else {
					stopTimer(huni_timer); hideTimer();
					stopTimer(bug_time);
					enterScene(fail1);
					stopSound(hunibgm);
				}
			}

		}
	}
	if (object == continue1) {
		stopSound(win);
		playSound(clicksound);
		enterScene(scene2);
		playSound(bgm);
	}
	////////////////////////////////////////////////////////////////////////////////////////
	if (object == replay2) {		//2. 유리게임 replay
		playSound(clicksound);
		hideObject(notattack);
		hideTimer();
		setTimer(arrow_timer, 20.0f);
		enterScene(scene3_1);
		showObject(howtodo3);
		showObject(ministart2);
		for (int i = 0; i < 8; i++) {
			arrow_number[i] = 0;
			hideObject(arrow[i]);
		}
		count = 0;
		turn = 0;
	}

	//2. 유리게임
	if (object == ministart2) {
		stopSound(bgm);
		playSound(clicksound);
		playSound(yuribgm);
		hideObject(ministart2);
		hideObject(howtodo3);
		showObject(notattack);

		create_arrow();
		startTimer(arrow_timer);
		showTimer(arrow_timer);
	}
	if (object == continue2) {
		stopSound(win);
		playSound(clicksound);
		hideTimer();
		enterScene(scene3);
		playSound(bgm);
	}
	///////////////////////////////////////////////////////////////////////////////////////////
	if (object == replay3) {	//3. 철수게임 replay
		playSound(clicksound);
		enterScene(scene4_1);
		showObject(ministart3);
		showObject(howtodo4);
		first = 0; second = 0; answer = 0;
		now = 0; 
		count3 = 0;	
		for (int i = 0; i < 5; i++) {
			hideObject(click_number[i]);
			hideObject(express[i]);	
			hideObject(click[i]);	
		}
		
	}

	//3. 철수게임
	if (object == ministart3) {
		stopSound(bgm);
		playSound(clicksound);
		playSound(cheolsubgm);
		hideObject(ministart3);
		hideObject(howtodo4);
		enterScene(gameground3);

		createnumber();	//노란색 숫자
		make_express();	//철수 식
	}
	for (int i = 0; i < 10; i++) {
		if (object == number[i]) {
			char path[200];
			if (now < 4) {
				sprintf_s(path, "Image/chulsugame/%d.png", i);
				click[now] = createObject(path, gameground3, 950 + (50 * now), 420, true);
				click_number[now] = i;

				now++;
			}
		}
	}
	if (object == submit) {
		playSound(clicksound);
		answer_compare();	//답이랑 비교
	}
	if (object == rewrite) {
		playSound(clicksound);
		now = 0;
		answer = 0;
		for (int i = 0; i < 4; i++) {
			hideObject(click[i]);
			click_number[i] = 0;
		}

	}
	if (object == continue3) {
		stopSound(win);
		playSound(clicksound);
		enterScene(scene4);
		playSound(bgm);
	}

	///////////////////////////////////////////////////////////////////////////////////////

	//4. 맹구게임
	if (object == stone_maenggu) {
		
		if (all_pass[0] == false || all_pass[1] == false || all_pass[2] == false) {
			showMessage("누가 안온거 같은데? \n 내 게임은 다 같이 해야 성공할 수 있다구!");
		}
		else {
			hideObject(click_maenggu);
			enterScene(scene5_1);
		}
	}
	if (object == ministart4) {
		playSound(clicksound);
		enterScene(bg4);
		stopSound(bgm);
		playSound(peace);
	}
	if (object == glass1) {
		playSound(move_glass);
		enterScene(bg2);
	}
	if (object == glass2) {
		playSound(move_glass);
		enterScene(bg1);
	}
	if (object == glass3) {
		playSound(move_glass);
		enterScene(bg3);
	}
	if (object == glass4) {
		playSound(move_glass);
		enterScene(bg5);
	}
	if (object == glass5) {
		playSound(move_glass);
		enterScene(bg6);
	}

	//닭치우기
	if (object == here3) {
		if (action == MouseAction::MOUSE_DRAG_RIGHT) {
			showObject(stone3);
			locateObject(here3, bg3, 550, 200);
		}
		else if (action == MouseAction::MOUSE_DRAG_LEFT) {
			showObject(stone3);
			locateObject(here3, bg3, 450, 200);
		}
	}
	if (object == stone3) {
		playSound(pick_stone); pickObject(stone3);
		showObject(Ston1);
		stone_count++;
		check_stone_number();
	}

	//모래사장클릭하기
	if (object == here1) {
		showObject(stone1);
	}
	if (object == stone1) {
		playSound(pick_stone); pickObject(stone1);
		showObject(Ston2);
		stone_count++;
		check_stone_number();
	}

	//세면대 클릭하기
	if (object == here5) {
		showObject(stone5);
	}
	if (object == stone5) {
		playSound(pick_stone); pickObject(stone5);
		showObject(Ston3);
		stone_count++;
		check_stone_number();
	}

	if (object == here6) {
		if (action == MouseAction::MOUSE_DRAG_RIGHT) {
			showObject(stone6);
			locateObject(here6, bg6, 940, 430);
		}
		else if (action == MouseAction::MOUSE_DRAG_LEFT) {
			showObject(stone6);
			locateObject(here6, bg6, 840, 430);
		}
	}
	if (object == stone6) {
		playSound(pick_stone); pickObject(stone6);
		showObject(Ston4);
		stone_count++;
		check_stone_number();
	}

	if (object == fake1) {
		playSound(chocob_sound); showObject(chocoB1);
		heart[0] = true; count_heart();
	}
	if (object == fake3) {
		playSound(chocob_sound); showObject(chocoB2);
		heart[1] = true; count_heart();
	}
	if (object == fake5) {
		playSound(chocob_sound); showObject(chocoB3);
		heart[2] = true; count_heart();
	}
	if (object == fake6) {
		playSound(chocob_sound); showObject(chocoB4);
		heart[3] = true; count_heart();
	}
	
	if (object == continue4) {	//맹구 성공 continue
		stopSound(win);
		playSound(clicksound);
		all_pass[3] = true;
		enterScene(scene5);
		hideObject(stone_maenggu);
		showObject(maenggu);
		playSound(bgm);
	}

	//되돌아가기
	if (object == back1 || object == back2 || object == back_game) {
		playSound(move_glass);
		enterScene(bg4);
	}
	if (object == back3 || object == back5) {
		playSound(move_glass);
		enterScene(bg2);
	}
	if (object == back6) {
		playSound(move_glass);
		enterScene(bg5);
	}
	if (object == check) {
		playSound(clicksound);
		enterScene(showcase);
	}
}


int main() {
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	setMouseCallback(mouseCallback);
	setKeyboardCallback(keyboardCallback);
	setTimerCallback(timerCallback);
	

	startscene = createScene("시작화면", "Image/startscene.png");
	startwithtitle = createScene("시작화면", "Image/startwithtitle.png");
	howtoplay = createScene("게임방법", "Image/howtoplay.png");
	start = createTimer(2.f);
	menu = createTimer(5.f);
	play_timer = createTimer(60.0f);


	startsound = createSound("sound/startbgm.mp3");
	bgm = createSound("sound/배경음악.mp3");
	peace = createSound("sound/stonebgm.mp3");
	hunibgm = createSound("sound/hunibgm.mp3");
	yuribgm = createSound("sound/yuribgm.mp3");
	cheolsubgm = createSound("sound/철수 브금.mp3");
	win = createSound("sound/win.mp3");
	hit = createSound("sound/hit.mp3");
	clicksound = createSound("sound/click.wav");
	chocob_sound = createSound("sound/chocob_sound.mp3"); 
	move_glass = createSound("sound/move_glass.mp3");
	change_outil = createSound("sound/change_outil.wav"); 
	pick_stone = createSound("sound/pick_stone.wav");
	final_bgm = createSound("sound/finish_bgm.mp3");


	scene1 = createScene("1", "Image/background1.png");
	scene2 = createScene("2", "Image/background2.png");
	scene3 = createScene("3", "Image/background3.png");
	scene4 = createScene("4", "Image/background4.png");
	scene5 = createScene("5", "Image/background5.png");
	final_stage = createScene("warp", "Image/background6.png");
	score_ground = createScene("finish", "Image/scoreground.png");

	scene2_1 = createScene("2-1", "Image/ready2.png");
	scene3_1 = createScene("3-1", "Image/ready3.png");
	scene4_1 = createScene("4-1", "Image/ready4.png");
	scene5_1 = createScene("5-1", "Image/ready5.png");
	
	startButton = createObject("Image/start.png", startwithtitle, 430, 160, false);
	startButton2 = createObject("Image/ministart.png", howtoplay, 550, 50, true);
	howtoplayButton = createObject("image/howtoplaybutton.png", startwithtitle, 580, 160, false);
	endButton = createObject("image/end.png", startwithtitle, 730, 160, false);


	jjang_gu = createObject("Image/짱구.png", scene1, jjang_guX, jjang_guY, true); scaleObject(jjang_gu, (float)0.25);
	huni = createObject("Image/훈이.png", scene1, jjang_guX - 80, jjang_guY, false); scaleObject(huni, (float)0.25);
	yuri = createObject("Image/유리.png", scene1, jjang_guX - 160, jjang_guY, false); scaleObject(yuri, (float)0.35);
	cheolsu = createObject("Image/철수.png", scene1, jjang_guX-240, jjang_guY, false); scaleObject(cheolsu, (float)0.25);
	maenggu = createObject("Image/맹구.png", scene1, jjang_guX - 320, jjang_guY, false); scaleObject(maenggu, (float)0.25);
	stone_maenggu = createObject("Image/maenggugame/돌줍는맹구.png", scene5, 400, 55, true); scaleObject(stone_maenggu, (float)0.5);

	howtodo2 = createObject("Image/hunigame/howtodo2.png", scene2_1, 550, 200, true);	//가로 690 훈이
	howtodo3 = createObject("Image/yurigame/howtodo3.png", scene3_1, 550, 200, true);	// 유리
	howtodo4 = createObject("Image/chulsugame/howtodo4.png", scene4_1, 550, 200, true);		//철수
	howtodo5 = createObject("Image/maenggugame/howto5.png", scene5_1, 300, 100, true);	//맹구

	ministart1 = createObject("Image/ministart.png", scene2_1, 800, 100, true);
	ministart2 = createObject("Image/ministart.png", scene3_1, 800, 100, true);
	ministart3 = createObject("Image/ministart.png", scene4_1, 800, 100, true);
	ministart4 = createObject("Image/ministart.png", scene5_1, 550, 40, true);

	//1. 훈이게임
	success1 = createScene("s1", "Image/hunigame/success1.png");
	fail1 = createScene("f1", "Image/hunigame/fail1.png");
	gameground = createObject("Image/hunigame/gameground.png", scene2_1, 550, 150, false);
	parischae = createObject("Image/hunigame/파리채.png", scene2_1, 750, 50, false);
	hand = createObject("Image/hunigame/손.png", scene2_1, 910, 50, false);

	bug_time = createTimer(0.01f);
	huni_timer = createTimer(25.0f);
	
	//2. 유리게임
	success2 = createScene("s2", "Image/yurigame/success.png");
	fail2 = createScene("f2", "Image/yurigame/fail.png");
	notattack= createObject("Image/yurigame/notattack.png", scene3_1, 570, 260, false);
	attack = createObject("Image/yurigame/attack.png", scene3_1, 570, 260, false);
	arrow_timer = createTimer(20.0f);
	show_attack = createTimer(0.002f);

	//3. 철수게임
	success3 = createScene("s3", "Image/chulsugame/success.png");
	fail3 = createScene("f3", "Image/chulsugame/fail.png");
	gameground3 = createScene("play","Image/chulsugame/gameground.png");
	rewrite = createObject("Image/chulsugame/다시선택.png", gameground3, 900, 350, true);
	submit = createObject("Image/chulsugame/확인.png", gameground3, 1060, 350, true);
	
	//4. 맹구게임

	bg1 = createScene("m1", "Image/maenggugame/1.png");
	bg2 = createScene("m2", "Image/maenggugame/2.png");
	bg3 = createScene("m3", "Image/maenggugame/3.png");
	bg4 = createScene("m4", "Image/maenggugame/4.png");
	bg5 = createScene("m5", "Image/maenggugame/5.png");
	bg6 = createScene("m6", "Image/maenggugame/6.png");

	success4 = createScene("success", "Image/maenggugame/success.png");
	fail4 = createScene("fail", "Image/maenggugame/fail.png");

	//돋보기
	glass1 = createObject("Image/maenggugame/돋보기.png", bg4, 300, 150, true);	
	glass2 = createObject("Image/maenggugame/돋보기.png", bg4, 900, 300, true); 
	glass3 = createObject("Image/maenggugame/돋보기.png", bg2, 300, 250, true); 
	glass4 = createObject("Image/maenggugame/돋보기.png", bg2, 600, 150, true); 
	glass5 = createObject("Image/maenggugame/돋보기.png", bg5, 300, 250, true); 

	//돌시작
	here1 = createObject("Image/maenggugame/1_move.png", bg1,100, 210,true);	//모래사장
	stone1 = createObject("Image/maenggugame/stone1.png", bg1, 200, 250, false);
	stone3 = createObject("Image/maenggugame/stone3.png", bg3, 500, 200, false);	//닭 뒤에 돌
	here3 = createObject("Image/maenggugame/3_move.png", bg3, 500, 200, true);	//닭
	here5 = createObject("Image/maenggugame/5_move.png", bg5, 825, 150, true);	//세면대
	stone5 = createObject("Image/maenggugame/stone5.png", bg5, 840, 160, false);	
	stone6 = createObject("Image/maenggugame/stone6.png", bg6, 890, 430, false);	//액자 뒤에 돌
	here6 = createObject("Image/maenggugame/6_move.png", bg6, 890, 430, true);	//액자
	
	//초코비시작
	fake1 = createObject("image/maenggugame/1_fail.png", bg1, 405, 305, true);	//말
	chocoB1 = createObject("image/maenggugame/초코비.png", bg1, 405, 305, false);
	fake3 = createObject("image/maenggugame/3_fail.png", bg3, 605, 130, true);	//풀
	chocoB2 = createObject("image/maenggugame/초코비.png", bg3, 605, 130, false);
	fake5 = createObject("image/maenggugame/5_fail.png", bg5, 735, 150, true);	//세면대
	chocoB3 = createObject("image/maenggugame/초코비.png", bg5, 735, 150, false);
	fake6 = createObject("image/maenggugame/6_fail.png", bg6, 830, 225, true);	//상자
	chocoB4 = createObject("image/maenggugame/초코비.png", bg6, 830, 225, false);

	choco = createTimer(0.6f);

	//돌수집현황버튼
	check = createObject("Image/maenggugame/check.png", bg4, 1050, 50, true);
	showcase = createScene("case", "Image/maenggugame/case.png");

	Ston1 = createObject("image/maenggugame/돌1.png", showcase, 290, 190, false);	
	Ston2 = createObject("image/maenggugame/돌2.png", showcase, 290, 380, false);	//pass
	Ston3 = createObject("image/maenggugame/돌3.png", showcase, 600, 300, false);	//pass
	Ston4 = createObject("image/maenggugame/돌4.png", showcase, 840, 390, false);	//pass

	//뒤로가기
	back1 = createObject("Image/maenggugame/back.png", bg1, 600, 50, true);
	back2 = createObject("Image/maenggugame/back.png", bg2, 600, 50, true);
	back3 = createObject("Image/maenggugame/back.png", bg3, 600, 50, true);
	back5 = createObject("Image/maenggugame/back.png", bg5, 600, 50, true);
	back6 = createObject("Image/maenggugame/back.png", bg6, 600, 50, true);
	back_game = createObject("image/maenggugame/back.png", showcase, 600, 50, true);

	//////////////////////////////////////////////////////////////////////////////////////////////////

	replay1 = createObject("Image/replay.png", fail1, 785, 270, true);
	replay2 = createObject("Image/replay.png", fail2, 785, 300, true);
	replay3 = createObject("Image/replay.png", fail3, 785, 370, true);
	replay4 = createObject("Image/replay.png", fail4, 550, 40, true);

	continue1 = createObject("Image/continue.png", success1, 785, 270, true);
	continue2 = createObject("Image/continue.png", success2, 785, 300, true);
	continue3 = createObject("Image/continue.png", success3, 785, 370, true);
	continue4 = createObject("Image/continue.png", success4, 520, 250, true);
	
	

	warp = createObject("Image/warp.png", final_stage, 900, 50, false );
	click_maenggu = createObject("Image/click.png", scene5, 350, 170, true);

	startTimer(start);
	startTimer(menu);
	startTimer(play_timer);
	playSound(startsound);
	
	
	startGame(startscene);
	
}