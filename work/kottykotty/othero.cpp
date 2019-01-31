#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int board[8][8];

int janken();																	//ボードの初期化を行い、ジャンケンで先行後攻を決める
int hantei(int m, int n, int me, int turning);									//渡された座標の縦・横・右下がり斜め・右上がり斜めを調べ、そこに置けるかを判定する
int check(int tmp[], int type, int m, int n, int me, int center, int turning);		//渡された配列を判定し、実際にひっくり返す（hantei関数の作業の一つ）
void show_board();																//ボードの様子を見る
int end(int turn);																//終了の判定と、相手がパスするしかない状態なのかを判定する

int main()
{
	int turn;		//どちらのターンなのか区別
	int tmp;		//入力した値を一時的に格納
	int m, n;		//入力した座標
	int pass = 0;		//パスフラグ(1)かつゲーム終了フラグ(2)
	int x, y;		//ゲーム終了時に、全ての座標を調べる際に用いる変数
	int count1 = 0;		//プレイヤー１の駒の数
	int count2 = 0;		//プレイヤー２の駒の数

	printf("～～～オセロ～～～\n\n");

	//ボードの初期化を行い、ジャンケンで先行後攻を決める
	turn = janken();

	do
	{
		//パスフラグが立っていないならば、ターンの入れ替えをする
		if (pass == 0)
		{
			if (turn == 1)
			{
				turn = 2;
			}
			else if (turn == 2)
			{
				turn = 1;
			}
		}
		else if (pass == 1)
		{
			printf("\n相手は置けないので、もう一度あなたのターンです。\n\n");
		}

		if (turn == 1)
		{
			printf("\n～～～○プレイヤー１○～～～\n\n");
			show_board();
		}
		else if (turn == 2)
		{
			printf("\n～～～●プレイヤー２●～～～\n\n");
			show_board();
		}
		do
		{
			printf("どこに置きますか？(訂正：00)\n");
			printf("　縦：");
			scanf("%d", &tmp);
			while (getchar() != '\n')
			{
			}
			if ((tmp > 0) && (tmp <= 8))
			{
				m = tmp - 1;
			}
			else
			{
				printf("1～8の値を入力してください\n\n");
				continue;
			}
			printf("　横：");
			scanf("%d", &tmp);
			if (tmp == 00)
			{
				continue;
			}
			while (getchar() != '\n')
			{
			}
			if ((tmp > 0) && (tmp <= 8))
			{
				n = tmp - 1;
			}
			else
			{
				printf("1～8の値を入力してください\n\n");
				continue;
			}
		} while ((board[m][n] != 0) || ((hantei(m, n, turn, 1)) == 8));

	} while ((pass = end(turn)) == 0);

	//駒を数えて、勝敗を判定
	for (y = 0; y < 8; y++)
	{
		for (x = 0; x < 8; x++)
		{
			if (board[y][x] == 1)
			{
				count1++;
			}
			else if (board[y][x] == 2)
			{
				count2++;
			}
		}
	}

	printf("＜結果発表＞\n");
	printf("プレイヤー１：%d\n", count1);
	printf("プレイヤー２：%d\n\n", count2);

	if (count1 > count2)
	{
		printf("\nプレイヤー１の勝ちです！\n");
	}
	else if (count1 < count2)
	{
		printf("\nプレイヤー２の勝ちです！\n");
	}
	else if (count1 == count2)
	{
		printf("同点です！\n");
	}

	return 0;
}


int janken()
{
	int player;
	int computer;
	int m, n;

	//ボードの初期化
	for (m = 0; m < 8; m++)
	{
		for (n = 0; n < 8; n++)
		{
			board[m][n] = 0;
		}
	}
	board[3][3] = 2;
	board[4][4] = 2;
	board[3][4] = 1;
	board[4][3] = 1;

	//ジャンケン
	printf("先行後攻をジャンケンで決めます。\n");
	printf("じゃ～んけ～ん・・・\n");

	do
	{
		do
		{
			printf("何を出しますか？（グー：１　チョキ：２　パー：３）>");
			scanf("%d", &player);
		} while ((player != 1) && (player != 2) && (player != 3));

		srand(time(NULL));
		computer = rand() % 3 + 1;

		printf("ぽいっ☆\n\n");
		printf("　プレイヤー：");
		if (player == 1)
		{
			printf("グー\n");
		}
		if (player == 2)
		{
			printf("チョキ\n");
		}
		if (player == 3)
		{
			printf("パー\n");
		}
		printf("　コンピュータ：");
		if (computer == 1)
		{
			printf("グー\n");
		}
		if (computer == 2)
		{
			printf("チョキ\n");
		}
		if (computer == 3)
		{
			printf("パー\n");
		}

		if (player == computer)
		{
			printf("あ～いこでしょ☆\n");
			continue;
		}
	} while (player == computer);

	if (((player == 1) && (computer == 2)) || ((player == 2) && (computer == 3)) || ((player == 3) && (computer == 1)))
	{
		printf("\nプレイヤー１の勝ち！\nプレイヤー１が先行で黒○です\n");

		return 2;
	}
	if (((player == 2) && (computer == 1)) || ((player == 3) && (computer == 2)) || ((player == 1) && (computer == 3)))
	{
		printf("\nプレイヤー２の勝ち！\nプレイヤー２が先行で白●です\n");
		return 1;
	}
}

int hantei(int m, int n, int me, int turning)
{
	int tmp[8];		//渡された座標の縦・横・右下がり斜め・右上がり斜めを格納する配列
	int i, k, j = 0;		//配列に格納する際に用いる変数
	int error = 0;		//エラー数(error == 8 だと置けない)
	int center;

	//縦のチェック
	for (i = 0; i < 8; i++)
	{
		tmp[i] = board[i][n];
	}
	center = m;

	error += check(tmp, 1, m, n, me, center, turning);

	//横のチェック
	for (i = 0; i < 8; i++)
	{
		tmp[i] = board[m][i];
	}
	center = n;

	error += check(tmp, 2, m, n, me, center, turning);

	//右下がり斜めのチェック
	i = 8;
	// (x, y) = (n - 8,m - 8)の座標から右下がりに移動し、ボード内に初めて入る位置を特定
	while (((m - i) < 0) || ((n - i) < 0))
	{
		i--;
	}
	//配列tmpへの格納
	do
	{
		tmp[j] = board[m - i][n - i];
		if (i == 0)
		{
			center = j;
		}
		i--;
		j++;
	} while (((m - i) < 8) && ((n - i) < 8));
	//tmp[7]まで埋まってない場合は、3を格納
	for (k = j; k < 8; k++)
	{
		tmp[k] = 3;
	}

	error += check(tmp, 3, m, n, me, center, turning);

	//右上がり斜めのチェック
	i = 8;
	// (x, y) = (n - 8,m + 8)の座標から右上がりがりに移動し、ボード内に初めて入る位置を特定
	while (((m + i) >= 8) || ((n - i) < 0))
	{
		i--;
	}

	for (k = 0; k < 8; k++)
	{
		tmp[k] = 9;
	}

	//配列tmpへの格納
	j = 0;
	do
	{
		tmp[j] = board[m + i][n - i];
		if (i == 0)
		{
			center = j;
		}
		i--;
		j++;
	} while (((m + i) >= 0) && ((n - i) < 8));
	//tmp[7]まで埋まってない場合は、3を格納
	for (k = j; k < 8; k++)
	{
		tmp[k] = 3;
	}

	error += check(tmp, 4, m, n, me, center, turning);

	return error;
}

int check(int get_tmp[], int type, int m, int n, int me, int center, int turning)
{
	int you;
	int i, j, x;
	int error = 0;
	int tmp[8];

	//どちらのプレイヤーにも対応できるようにする
	if (me == 1)
	{
		you = 2;
	}
	else if (me == 2)
	{
		you = 1;
	}

	//渡された配列get_tmp[]の先頭アドレスから、配列tmpへ格納
	for (i = 0; i < 8; i++)
	{
		tmp[i] = *get_tmp;
		get_tmp++;
	}

	//左側のチェック
	if (tmp[center - 1] == you)
	{
		i = center - 2;
		while ((tmp[i] == you) && (i >= 0))
		{
			i--;
		}
		if ((tmp[i] == me) && (i >= 0))
		{
			for (x = i + 1; x <= center; x++)
			{
				tmp[x] = me;
			}
		}
		else
		{
			error++;
		}
	}
	else
	{
		error++;
	}

	//右側のチェック
	if (tmp[center + 1] == you)
	{
		i = center + 2;
		while ((tmp[i] == you) && (i < 8))
		{
			i++;
		}
		if ((tmp[i] == me) && (i < 8))
		{
			for (x = i - 1; x >= center; x--)
			{
				tmp[x] = me;
			}
		}
		else
		{
			error++;
		}
	}
	else
	{
		error++;
	}


	//turningフラグが立っているならば、実際にボードをひっくり返す
	if (turning == 1)
	{
		if (error != 2)
		{
			if (type == 1)
			{
				for (i = 0; i < 8; i++)
				{
					board[i][n] = tmp[i];
				}
			}
			else if (type == 2)
			{
				for (i = 0; i < 8; i++)
				{
					board[m][i] = tmp[i];
				}
			}
			else if (type == 3)
			{
				i = 8;
				while (((m - i) < 0) || ((n - i) < 0))
				{
					i--;
				}
				j = 0;
				do
				{
					board[m - i][n - i] = tmp[j];
					i--;
					j++;
				} while (((m - i) < 8) && ((n - i) < 8) && (tmp[j] != 3));
			}
			else if (type == 4)
			{
				i = 8;
				while (((m + i) >= 8) || ((n - i) < 0))
				{
					i--;
				}
				j = 0;
				do
				{
					board[m + i][n - i] = tmp[j];
					i--;
					j++;
				} while (((m + i) >= 0) && ((n - i) < 8) && (tmp[j] != 3));
			}
		}
	}

	return error;
}

void show_board()
{
	int x, y;

	printf("  １２３４５６７８\n");
	for (y = 0; y < 8; y++)
	{
		printf("%d ", y + 1);
		for (x = 0; x < 8; x++)
		{
			if (board[y][x] == 0)
			{
				printf("□");
			}
			else if (board[y][x] == 1)
			{
				printf("○");
			}
			else if (board[y][x] == 2)
			{
				printf("●");
			}
		}
		printf(" %d\n", y + 1);
	}
	printf("  １２３４５６７８\n\n");
}

int end(int me)
{
	int x, y;
	int you_pass = 0;		//相手が置けない位置の数
	int me_pass = 0;		//自分が置けない位置の数
	int you;

	//どちらのプレイヤーにも対応できるようにする
	if (me == 1)
	{
		you = 2;
	}
	else if (me == 2)
	{
		you = 1;
	}

	//判定
	for (y = 0;y < 8; y++)
	{
		for (x = 0; x < 8; x++)
		{

			//相手が置ける場所なら0を返して、判定終了
			if ((board[y][x] == 0) && ((hantei(y, x, you, 0)) != 8))
			{
				printf("(%d,%d) = %d\n", y + 1, x + 1, board[y][x]);
				return 0;
			}
			//相手が置けない場所なら変数you_passに1を足して、判定継続
			else
			{
				you_pass++;
			}
			//自分が置ける場所なら何もぜず、判定継続
			if ((hantei(y, x, me, 0)) != 8)
			{
			}
			//自分が置けない場所なら、変数me_passに1を足して、判定継続
			else
			{
				me_pass++;
			}
		}
	}

	//自分も相手もどこにも置けない場合、ゲーム終了フラグ(2)を返す
	if ((you_pass == 64) && (me_pass == 64))
	{
		return 2;
	}
	//相手はどこにも置けない場合、パスフラグ(1)を返す
	else if ((you_pass == 64) && (me_pass != 64))
	{
		return 1;
	}
	//ゲームを続けられる場合、何のフラグも立てずに0を返す
	else
	{
		return 0;
	}
}

