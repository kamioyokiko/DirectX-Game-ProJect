#include"Common.h"

#define ENEMY_NUM 5

//일반적
class Enemy :public entity {

public :
	Enemy();
	~Enemy();
	bool bShow; // 보이는지 체크
	bool show(); // 보여주기
	void hide(); // 충돌시 파괴
	void active(); // 버튼 누를시 총알 발사
	bool check_collision(float x, float y); // 충돌체크

	bool Enemy_Hit = false; //피격시 파괴되는 애니메이션 도구

	void init(float x, float y);
	void fire();
	void move();
	bool Visible;
};



//특수적(호밍)
class NewEnemy :public entity {

public:

	NewEnemy();
	~NewEnemy();

	bool up;
	bool down;
	bool moving; //이동
	bool stop; // 정지
	void Uping(); // 위쪽
	void downing(); // 아래쪽
	void Stopping(); // 정지시키는 것처럼

	bool bShow; // 보이는지 체크
	bool show(); // 보여주기
	void hide(); // 충돌시 파괴
	void active(); // 버튼 누를시 총알 발사
	bool check_collision(float x, float y); // 충돌체크

	void init(float x, float y);
	void fire();
	void move();
	bool Visible;

	bool NewEnemy_Hit = false; //피격시 파괴되는 애니메이션 도구
};




//통과불가 오브젝트
class Mushroom:public entity {

public:

	Mushroom();
	~Mushroom();

	bool up;
	bool down;
	bool moving; //이동
	bool stop; // 정지
	void Uping(); // 위쪽
	void downing(); // 아래쪽
	void Stopping(); // 정지시키는 것처럼

	bool bShow; // 보이는지 체크
	bool show(); // 보여주기
	void hide(); // 충돌시 파괴
	void active(); // 버튼 누를시 총알 발사
	bool check_collision(float x, float y); // 충돌체크


	void init(float x, float y);
	void fire();
	void move();
	bool Visible;
};




//보스
class BossEnemy :public entity {

public:
	BossEnemy();
	~BossEnemy();

	bool move_check = false;

	bool bShow; // 보이는지 체크
	bool show(); // 보여주기
	void hide(); // 충돌시 파괴
	void active(); // 버튼 누를시 총알 발사
	bool check_collision(float x, float y); // 충돌체크

	void init(float x, float y);
	void fire();
	void move(float x, float y);
	bool Visible;
	bool Boss_Check = false;
	bool Boss_Exist = false;

	bool BossEnemy_Hit = false; //피격시 파괴되는 애니메이션 도구
};
