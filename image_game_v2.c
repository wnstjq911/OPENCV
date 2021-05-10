#include <iostream>
#include <thread>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <random>
#include <Windows.h>
#include <stdio.h>


// 커버 이미지 크기
#define COVER_IMAGE_ROW 1200  // 가로
#define COVER_IMAGE_COL 900  // 세로

// 리사이징 이미지 크기
#define RE_IMAGE_ROW 150
#define RE_IMAGE_COL 150

// 상태 정의
#define QUESTION 5
#define apple 1
#define banana 2
#define IDLE 3
#define GOOD 6
#define Rtry 7
#define FINISH 8
#define SHIT 9

using std::thread;
using namespace cv;
using namespace std;

Mat rotate(Mat rotate_out);
int random(int check);
Mat copy(Mat copyrotation, Mat copyrotation2, Mat cover_image, int num);
void draw(Mat cover_image2);
void point();


// 가로 세로 선 그리기 배열
int draw_row_ary[7] = { 10, 181, 352, 523, 695, 865, 1037 };
int draw_col_ary[5] = { 45, 218, 391, 564, 737 };

int draw_ary[5][7] = { 0 };

// 과일들의 배치된 좌표 값 배열
int Apple[2][35];
int Banana[2][35];

int mouse_left, mouse_right;
int state;
int question_state = apple;
int answer_state = IDLE;
int delays = 0;
int apple_count=0;
int banana_count;
int row_i, col_i;

int life_ = 35;

Mat cover_image2(COVER_IMAGE_COL, COVER_IMAGE_ROW, CV_8UC3, Scalar(255, 255, 255));
Mat cover_image(COVER_IMAGE_COL, COVER_IMAGE_ROW, CV_8UC3, Scalar(255, 255, 255));
Mat bg_image(COVER_IMAGE_COL, COVER_IMAGE_ROW, CV_8UC3, Scalar(255, 255, 255));

Mat apple_rotation, banana_rotation;
Mat cross_small;
Mat banana_cross_small;
Mat life5 = imread("C://Users//user//Desktop//준섭//opencv//life.jpg");
Mat life1 = imread("C://Users//user//Desktop//준섭//opencv//life1.jpg");
Mat life2 = imread("C://Users//user//Desktop//준섭//opencv//life2.jpg");
Mat life3 = imread("C://Users//user//Desktop//준섭//opencv//life3.jpg");
Mat life4 = imread("C://Users//user//Desktop//준섭//opencv//life4.jpg");
Mat life0 = imread("C://Users//user//Desktop//준섭//opencv//life0.jpg");
Mat life  = imread("C://Users//user//Desktop//준섭//opencv//life.jpg");
Mat cross = imread("C://Users//user//Desktop//준섭//opencv//cross.png");

Mat banana_cross = imread("C://Users//user//Desktop//준섭//opencv//banana_cross.png");

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	
	if (event == EVENT_LBUTTONDOWN)
	{
		cout << "왼쪽 마우스 버튼 클릭.. 좌표 = (" << x << ", " << y << ")" << endl;
		int temp  = -2000;
		int temp2 = -2000;

		for (int i = 0; i < 7; i++)
		{
			temp = draw_row_ary[i] - x;
			if (temp > 0)
			{
				if(i>0)
				temp = draw_row_ary[i - 1] - x;
				row_i = i - 1;
				break;
			}
			row_i = i;
		}
		for (int i = 0; i < 5; i++)
		{
			temp2 = draw_col_ary[i] - y;
			if (temp2 > 0)
			{
				if(i>0)
				temp2 = draw_col_ary[i - 1] - y;
				col_i = i - 1;
				break;
			}
			col_i = i;
		}



		printf("temp = %d , temp2 = %d\n",temp, temp2);

		for (int i = 0; i < 35; i++)
		{

			if ((x != 0 && y != 0) && (Apple[0][i] <= x && x <= (Apple[0][i] + 150)) && (Apple[1][i] <= y && y <= (Apple[1][i] + 150)))
			{
				printf("GOOD\n");
				printf("apple_count : %d\n",apple_count);
				apple_rotation.copyTo(cover_image2(Rect(draw_row_ary[row_i], draw_col_ary[col_i], apple_rotation.cols, apple_rotation.rows)));

				draw(cover_image2);
				imshow("covered_image", cover_image2);
				apple_count--;
				
				break;
			}
			//else if ((x != 0 && y != 0) && (Banana[0][i] <= x && x <= (Banana[0][i] + 150)) && (Banana[1][i] <= y && y <= (Banana[1][i] + 150)))
			//{
			//	life_--;
			//	printf("Banana OOPS LIFE =%d \n", life_);
			//					printf("x= %d, y= %d", x, y);
			//	if (life_ % 35 == 0)
			//		//printf("OOPS LIFE =%d \n", life_);
			//	if (life_ == 0) life = life4;
			//	else if (life_ >70 &&life_ < -35) life = life3;
			//	else if (life_ == -70) life = life2;
			//	else if (life_ == -105) life = life1;
			//	else if (life_ == -140) { life = life0; apple_count = 0; }
			//	else if (life_ < -140) { life = life5; }

			//	life.copyTo(cover_image(Rect(985, 0, life.cols, life.rows)));
			//	life.copyTo(cover_image2(Rect(985, 0, life.cols, life.rows)));

			//	resize(banana_cross, banana_cross_small, Size(RE_IMAGE_ROW, RE_IMAGE_COL));
			//	banana_cross_small.copyTo(cover_image2(Rect(draw_row_ary[row_i], draw_col_ary[col_i], 150, 150)));
			//	draw(cover_image2);
			//	imshow("covered_image", cover_image2);

			//}
			else  if ((x != 0 && y != 0) && (Apple[0][i] > x || x > (Apple[0][i] + 150)) && (Apple[1][i] > y || y > (Apple[1][i] + 150)))
			{

				life_--;
				printf("x= %d, y= %d", x, y);
				printf("OOPS LIFE =%d \n", life_);

					if (life_ == 0) life = life4;
					else if (life_ > -70 && life_ < -35) { life = life3; }
					else if (-105 < life_ && life_ < -70) { life = life2; }
					else if (-140 < life_ && life_ < -105) { life = life1; }
					else if (life_ == -140) { life = life0; apple_count = 0; }
					

				life.copyTo(cover_image(Rect(985, 0, life.cols, life.rows)));
				life.copyTo(cover_image2(Rect(985, 0, life.cols, life.rows)));

				resize(cross, cross_small, Size(RE_IMAGE_ROW, RE_IMAGE_COL));	
				cross_small.copyTo(cover_image2(Rect(draw_row_ary[row_i], draw_col_ary[col_i], cross_small.cols, cross_small.rows)));
				draw(cover_image2);
				imshow("covered_image", cover_image2);
			}
		}

	}
}
int main(int ac, char** av)
{
	int event;

	Mat img_apple = imread("C://Users//user//Desktop//준섭//opencv//apple.jpg");
	Mat img_banana = imread("C://Users//user//Desktop//준섭//opencv//banana.jpg");
	Mat Question_banana = imread("C://Users//user//Desktop//준섭//opencv//Question_banana.jpg");
	Mat Question_apple = imread("C://Users//user//Desktop//준섭//opencv//Question_apple.png");
	Mat Question_location = imread("C://Users//user//Desktop//준섭//opencv//Question_location.png");

	
	Mat img_roi_apple, img_roi_banana;
	Mat img_small_apple, img_small_banana;


	VideoCapture count("C://Users//user//Desktop//준섭//opencv//Countdown_321.mp4");
	Mat Mat_count(COVER_IMAGE_COL, COVER_IMAGE_ROW, CV_8UC3, Scalar(255, 255, 255));
	Mat resize_image;

	// 관심 영역 따기
	img_roi_apple = img_apple(Rect(Point(130, 100), Point(544, 522)));
	img_roi_banana = img_banana(Rect(Point(39, 15), Point(603, 410)));

	// 리사이징
	resize(img_roi_apple, img_small_apple, Size(RE_IMAGE_ROW, RE_IMAGE_COL));
	resize(img_roi_banana, img_small_banana, Size(RE_IMAGE_ROW, RE_IMAGE_COL));



	//while (1)
	//{
	//	count >> Mat_count;

	//	resize(Mat_count, resize_image, Size(1200, 900));
	//	if (resize_image.empty())
	//	{
	//		printf("empty image");
	//	}
	//	imshow("covered_image", resize_image);
	//
	//	if (waitKey(25) == 27)
	//		break;
	//}



	while (1) {

		life.copyTo(cover_image(Rect(985, 0, life.cols, life.rows)));
		life.copyTo(cover_image2(Rect(985, 0, life.cols, life.rows)));

		Question_location.copyTo(cover_image(Rect(450, 0, Question_location.cols, Question_location.rows)));
		draw(cover_image);

		apple_rotation = rotate(img_small_apple);			// 회전 된 반환 값 각각을 받아옴
		banana_rotation = rotate(img_small_banana);			// 회전 된 반환 값 각각을 받아옴
		cover_image = copy(apple_rotation, banana_rotation, cover_image, 3);


		imshow("covered_image", cover_image);  // 과일들 난수 배치

		// 두번째 빈공간 생성 -> (문제 풀 수 있는 두번째 MAT 생성)
		waitKey(500);

		while (1) {
			setMouseCallback("covered_image", CallBackFunc, NULL); // 왼쪽 마우스 클릭 좌표 확인

			Question_apple.copyTo(cover_image2(Rect(470, 0, Question_apple.cols, Question_apple.rows)));

			draw(cover_image2);
			life.copyTo(cover_image(Rect(985, 0, life.cols, life.rows)));
			imshow("covered_image", cover_image2);		
			waitKey(3500);

			
			if (apple_count <= 0 || banana_count <= 0)
			{
				//if (life_ < -140) { life = life5; }
				life_ = 35;
				cover_image = Scalar(255,255,255);
				cover_image2 = Scalar(255,255,255);
				break;
			}
		}

		life.copyTo(cover_image(Rect(985, 0, life.cols, life.rows)));
		life.copyTo(cover_image2(Rect(985, 0, life.cols, life.rows)));

		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 7; j++)
				draw_ary[i][j] = 0;

		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 35; j++){
				Apple[i][j] = 0;
				Banana[i][j] = 0;
			}

	}

	
	return 0;
}

Mat rotate(Mat rotate_out)
{
	int rd_row = random(1);
	int rd_col = random(2);
	
	Mat rotation; // 회전할 이미지
	Point2f pt(rotate_out.cols / 2., rotate_out.rows / 2.); //Point2f 로 회전시킬 이미지의 중심 설정 (정중앙)
	int p = random(3);
	Mat r = getRotationMatrix2D(pt, p, 1); // 사진 회전시키기 (사진 중앙값, 회전값, 사진 비율) 
	warpAffine(rotate_out, rotation, r, Size(rotate_out.cols, rotate_out.rows), INTER_LINEAR, BORDER_CONSTANT, Scalar(255, 255, 255)); //설정해준 값을 회전시켜줌

	
	return rotation;
}

int random(int check)
{
	// 랜덤 수 만들기
	random_device rd;
	mt19937 gen(rd());

	if (check == 1)
	{
		uniform_int_distribution<int> dis(0, COVER_IMAGE_ROW - RE_IMAGE_ROW);
		return dis(gen);
	}
	else if (check == 2)
	{
		uniform_int_distribution<int> dis(0, COVER_IMAGE_COL - RE_IMAGE_COL);
		return dis(gen);
	}
	else if (check == 3)
	{
		uniform_int_distribution<int> dis(0, 360);
		return dis(gen);
	}
	else if (check == 4) // 가로 배열의 인덱스 값  
	{
		uniform_int_distribution<int> dis(0, 6);
		return dis(gen);
	}
	else if (check == 5) //세로 배열의 인덱스 값 
	{
		uniform_int_distribution<int> dis(0, 4);
		return dis(gen);
	}
	else if (check == 6) // apple, banana 랜덤 
	{
		uniform_int_distribution<int> dis(1, 2);
		return dis(gen);
	}

}
Mat copy(Mat copy_rotation, Mat copy_rotation2, Mat cover_image, int num)
{
	int i=0;
	int raw, col;
	int check;

	while (i<8) {

		 raw = random(4);
		 col = random(5);
		 
		 check = random(6);
		 

		 if (check == 1)
		 {
			 if (draw_ary[col][raw] == 0) {
				 draw_ary[col][raw] = 1;
				 Apple[0][i] = draw_row_ary[raw];
				 Apple[1][i] = draw_col_ary[col];
				 apple_count++;
				 cout << "apple 좌표 = (" << draw_row_ary[raw] << ", " << draw_col_ary[col] << ")" << endl;
				 copy_rotation.copyTo(cover_image(Rect(draw_row_ary[raw], draw_col_ary[col], copy_rotation.cols, copy_rotation.rows)));

			 }
			 else if (draw_ary[col][raw] != 0)
				 continue;
		}
		else if (check == 2)
		{
			if (draw_ary[col][raw] == 0){

				draw_ary[col][raw] = 2;

				Banana[0][i] = draw_row_ary[raw];
				Banana[1][i] = draw_col_ary[col];

				banana_count++;
				cout << "banana 좌표 = (" << draw_row_ary[raw] << ", " << draw_col_ary[col] << ")" << endl;
				copy_rotation2.copyTo(cover_image(Rect(draw_row_ary[raw], draw_col_ary[col], copy_rotation2.cols, copy_rotation2.rows)));
			}
			else if (draw_ary[col][raw] != 0)
				continue;
		}
		 
			i++;
	}

	for(int i =0; i<5; i++){
		for(int j=0; j<7; j++)
		printf("%d ",draw_ary[i][j]);
		//printf("draw_ary[%d][%d]=%d ", i, j, draw_ary[i][j]);
		printf("\n");
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 35; j++)
		printf("%d ", Apple[i][j]);
		//printf("draw_ary[%d][%d]=%d ", i, j, draw_ary[i][j]);
		printf("\n");
	}
	return cover_image;

}
void draw(Mat cover_image2)
{
	Point pt1(0, 35), pt2(1200, 35);
	Point pt3(0, 727), pt4(1200, 727);
	Point pt5(0, 554), pt6(1200, 554);
	Point pt7(0, 381), pt8(1200, 381);
	Point pt9(0, 208), pt10(1200, 208);

	line(cover_image2, pt1, pt2, Scalar(0, 0, 0), 1);
	line(cover_image2, pt3, pt4, Scalar(0, 0, 0), 1);
	line(cover_image2, pt5, pt6, Scalar(0, 0, 0), 1);
	line(cover_image2, pt7, pt8, Scalar(0, 0, 0), 1);
	line(cover_image2, pt9, pt10, Scalar(0, 0, 0), 1);


	Point pit1(171, 35), pit2(171, 900);
	Point pit3(342, 35), pit4(342, 900);
	Point pit5(513, 35), pit6(513, 900);
	Point pit7(685, 35), pit8(685, 900);
	Point pit9(855, 35), pit10(855, 900);
	Point pit11(1027, 35), pit12(1027, 900);

	line(cover_image2, pit1, pit2, Scalar(0, 0, 0), 1);
	line(cover_image2, pit3, pit4, Scalar(0, 0, 0), 1);
	line(cover_image2, pit5, pit6, Scalar(0, 0, 0), 1);
	line(cover_image2, pit7, pit8, Scalar(0, 0, 0), 1);
	line(cover_image2, pit9, pit10, Scalar(0, 0, 0), 1);
	line(cover_image2, pit11, pit12, Scalar(0, 0, 0), 1);

}
void point()
{
	printf("hello, world!!!\n");
}
