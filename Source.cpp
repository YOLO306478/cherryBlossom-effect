#include <stdio.h>
#include <easyx.h>
#include <time.h>
#include<math.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define NUM 100



struct Blossom
{
	int x, y;//當前座標
	bool state;//是否存在
	IMAGE img;
	int anglex;
	double width, height;
	int oldx;

	Blossom();
	void init();
	void fall(int i);
};



Blossom::Blossom()//初始化櫻花
{
	x = 0, y = 0, anglex = 0, oldx = 0;
	width = 0, height = 0;
	state = 0;

}

void Blossom::init()//初始化櫻花
{
	x = rand() % 1000 + 1600;//隨機設置櫻花x座標
	oldx = x;
	y = -50 - rand() % 600;//隨機y座標
	anglex = rand() % 360;
	width = 20 * cos(3.14159265359 * anglex / 180);
	height = 20 * sin(3.14159265359 * anglex / 180);
	loadimage(&img, "1.png", 20, 20);
	putimage(x, y, &img, SRCPAINT);//放出櫻花
	state = 1;//設置該櫻花狀態為存在

}



void Blossom::fall(int i)//下落櫻花
{

	if (anglex >= 365)//超出365度
	{
		width = 20;
		height = 0;
		anglex = 0;
	}
	if (anglex >= 275)
	{
		loadimage(&img, "2.png", (int)width + 2, abs((int)height) + 2);
	}
	else if (anglex >= 175)
	{
		loadimage(&img, "4.png", abs((int)width) + 2, abs((int)height) + 2);
		x = oldx - abs((int)width);
	}
	else if (anglex >= 85)
	{
		loadimage(&img, "3.png", abs((int)width) + 2, (int)height + 2);
		x = oldx - abs((int)width);
	}
	else
	{
		loadimage(&img, "1.png", (int)width + 2, (int)height + 2);
	}
	putimage(x, y, &img, SRCPAINT);//放出新位置的櫻花

	//4種移動速度
	switch (i % 4)
	{
	case 0:
		oldx -= 3;
		y += 2;
		break;
	case 1:
		oldx -= 2;
		y += 1;
		break;
	case 2:
		oldx -= 2;
		y += 2;
		break;
	case 3:
		oldx -= 2;
		y += 2;
		break;
	}

	x = oldx;
	double width0 = width;//原寬度
	double height0 = height;//原高度
	int deltaAngle = i % 3 + 2;//旋轉角度

	width = width0 * cos(3.14159265359 * deltaAngle / 180) - height0 * sin(3.14159265359 * deltaAngle / 180);
	height = width0 * sin(3.14159265359 * deltaAngle / 180) + height0 * cos(3.14159265359 * deltaAngle / 180);
	anglex += deltaAngle;
	if (oldx < 100 || y > 1000)//當櫻花超出範圍
		state = 0;//設置櫻花狀態為不存在
}

int main()
{
	srand((unsigned)time(0));
	initgraph(1600, 1000);//開啟視窗(1600,1000)
	setorigin(-200, -110);//修正原點位置

	IMAGE background;


	/*	int ps = 0;
		double width0 = 25, height0 = 0;
		double width1 = 25, height1 = 0;
		int degree = 5;
		int i = 0;
		int x = 500;
		putimage(500, 500, &img2);
		while (1)
		{
			if (i == 73)
			{
				width1 = 25;
				height1 = 0;
				i = 0;
			}
			if (i >= 55)
			{
				loadimage(&img2, "1.png", abs((int)width1) + 1, 25);
				x = 500;
			}
			else if(i >= 37)
			{
				loadimage(&img2, "3.png", abs((int)width1) + 1, 25);
				x = 500 - abs((int)width1);
			}
			else if (i >= 19)
			{
				loadimage(&img2, "3.png", abs((int)width1) + 1, 25);
				x = 500 - abs((int)width1);
			}
			else
			{
				loadimage(&img2, "1.png", abs((int)width1) + 1, 25);
				x = 500;
			}
			BeginBatchDraw();
			putimage(x, 500, &img2);
			EndBatchDraw();
			printf("%f\n", width1);
			Sleep(100);
			cleardevice();
			width0 = width1;
			height0 = height1;
			width1 = width0 * cos(3.14159265359 * degree/180) - height0 * sin(3.14159265359 * degree/180);
			height1 = width0 * sin(3.14159265359 * degree / 180) + height0 * cos(3.14159265359 * degree / 180);
			i++;
		}
	*/
	loadimage(&background, "backgroung.png", 1920, 1030);//加載背景
	waveOutSetVolume(0, 0x4FFF4FFF);//調整背景音樂音量
	mciSendString("open tsuki.mp3 alias BGM", 0, 0, 0);  //mci: media control surface,開啟背景音樂
	mciSendString("play BGM repeat", 0, 0, 0);//重複撥放音樂


	//settextstyle(20,0,"新細明體");
	int t1 = GetTickCount(), t2;//宣告t1,t2
	Blossom p[NUM];
	int angle = 4;

	for (int i = 0; i < NUM; i++)
		p[i].init();//初始化櫻花

	while (1)
	{

		t2 = GetTickCount();//獲得當前時間
		if (t2 - t1 >= 20)//每20ms刷新一次
		{
			BeginBatchDraw();//以雙緩衝防止閃爍
			putimage(0, 100, &background);//放出背景
			for (int i = 0; i < NUM; i++)
			{
				if (p[i].state == 0)//當該櫻花狀態為不存在
					p[i].init();//初始化櫻花
				p[i].fall(i);//下落櫻花
			}
			EndBatchDraw();
			t1 = t2;
		}
	}

	return 0;
}

