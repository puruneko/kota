#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int board[8][8];

int janken();																	//�{�[�h�̏��������s���A�W�����P���Ő�s��U�����߂�
int hantei(int m, int n, int me, int turning);									//�n���ꂽ���W�̏c�E���E�E������΂߁E�E�オ��΂߂𒲂ׁA�����ɒu���邩�𔻒肷��
int check(int tmp[], int type, int m, int n, int me, int center, int turning);		//�n���ꂽ�z��𔻒肵�A���ۂɂЂ�����Ԃ��ihantei�֐��̍�Ƃ̈�j
void show_board();																//�{�[�h�̗l�q������
int end(int turn);																//�I���̔���ƁA���肪�p�X���邵���Ȃ���ԂȂ̂��𔻒肷��

int main()
{
	int turn;		//�ǂ���̃^�[���Ȃ̂����
	int tmp;		//���͂����l���ꎞ�I�Ɋi�[
	int m, n;		//���͂������W
	int pass = 0;		//�p�X�t���O(1)���Q�[���I���t���O(2)
	int x, y;		//�Q�[���I�����ɁA�S�Ă̍��W�𒲂ׂ�ۂɗp����ϐ�
	int count1 = 0;		//�v���C���[�P�̋�̐�
	int count2 = 0;		//�v���C���[�Q�̋�̐�

	printf("�`�`�`�I�Z���`�`�`\n\n");

	//�{�[�h�̏��������s���A�W�����P���Ő�s��U�����߂�
	turn = janken();

	do
	{
		//�p�X�t���O�������Ă��Ȃ��Ȃ�΁A�^�[���̓���ւ�������
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
			printf("\n����͒u���Ȃ��̂ŁA������x���Ȃ��̃^�[���ł��B\n\n");
		}

		if (turn == 1)
		{
			printf("\n�`�`�`���v���C���[�P���`�`�`\n\n");
			show_board();
		}
		else if (turn == 2)
		{
			printf("\n�`�`�`���v���C���[�Q���`�`�`\n\n");
			show_board();
		}
		do
		{
			printf("�ǂ��ɒu���܂����H(�����F00)\n");
			printf("�@�c�F");
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
				printf("1�`8�̒l����͂��Ă�������\n\n");
				continue;
			}
			printf("�@���F");
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
				printf("1�`8�̒l����͂��Ă�������\n\n");
				continue;
			}
		} while ((board[m][n] != 0) || ((hantei(m, n, turn, 1)) == 8));

	} while ((pass = end(turn)) == 0);

	//��𐔂��āA���s�𔻒�
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

	printf("�����ʔ��\��\n");
	printf("�v���C���[�P�F%d\n", count1);
	printf("�v���C���[�Q�F%d\n\n", count2);

	if (count1 > count2)
	{
		printf("\n�v���C���[�P�̏����ł��I\n");
	}
	else if (count1 < count2)
	{
		printf("\n�v���C���[�Q�̏����ł��I\n");
	}
	else if (count1 == count2)
	{
		printf("���_�ł��I\n");
	}

	return 0;
}


int janken()
{
	int player;
	int computer;
	int m, n;

	//�{�[�h�̏�����
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

	//�W�����P��
	printf("��s��U���W�����P���Ō��߂܂��B\n");
	printf("����`�񂯁`��E�E�E\n");

	do
	{
		do
		{
			printf("�����o���܂����H�i�O�[�F�P�@�`���L�F�Q�@�p�[�F�R�j>");
			scanf("%d", &player);
		} while ((player != 1) && (player != 2) && (player != 3));

		srand(time(NULL));
		computer = rand() % 3 + 1;

		printf("�ۂ�����\n\n");
		printf("�@�v���C���[�F");
		if (player == 1)
		{
			printf("�O�[\n");
		}
		if (player == 2)
		{
			printf("�`���L\n");
		}
		if (player == 3)
		{
			printf("�p�[\n");
		}
		printf("�@�R���s���[�^�F");
		if (computer == 1)
		{
			printf("�O�[\n");
		}
		if (computer == 2)
		{
			printf("�`���L\n");
		}
		if (computer == 3)
		{
			printf("�p�[\n");
		}

		if (player == computer)
		{
			printf("���`�����ł��偙\n");
			continue;
		}
	} while (player == computer);

	if (((player == 1) && (computer == 2)) || ((player == 2) && (computer == 3)) || ((player == 3) && (computer == 1)))
	{
		printf("\n�v���C���[�P�̏����I\n�v���C���[�P����s�ō����ł�\n");

		return 2;
	}
	if (((player == 2) && (computer == 1)) || ((player == 3) && (computer == 2)) || ((player == 1) && (computer == 3)))
	{
		printf("\n�v���C���[�Q�̏����I\n�v���C���[�Q����s�Ŕ����ł�\n");
		return 1;
	}
}

int hantei(int m, int n, int me, int turning)
{
	int tmp[8];		//�n���ꂽ���W�̏c�E���E�E������΂߁E�E�オ��΂߂��i�[����z��
	int i, k, j = 0;		//�z��Ɋi�[����ۂɗp����ϐ�
	int error = 0;		//�G���[��(error == 8 ���ƒu���Ȃ�)
	int center;

	//�c�̃`�F�b�N
	for (i = 0; i < 8; i++)
	{
		tmp[i] = board[i][n];
	}
	center = m;

	error += check(tmp, 1, m, n, me, center, turning);

	//���̃`�F�b�N
	for (i = 0; i < 8; i++)
	{
		tmp[i] = board[m][i];
	}
	center = n;

	error += check(tmp, 2, m, n, me, center, turning);

	//�E������΂߂̃`�F�b�N
	i = 8;
	// (x, y) = (n - 8,m - 8)�̍��W����E������Ɉړ����A�{�[�h���ɏ��߂ē���ʒu�����
	while (((m - i) < 0) || ((n - i) < 0))
	{
		i--;
	}
	//�z��tmp�ւ̊i�[
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
	//tmp[7]�܂Ŗ��܂��ĂȂ��ꍇ�́A3���i�[
	for (k = j; k < 8; k++)
	{
		tmp[k] = 3;
	}

	error += check(tmp, 3, m, n, me, center, turning);

	//�E�オ��΂߂̃`�F�b�N
	i = 8;
	// (x, y) = (n - 8,m + 8)�̍��W����E�オ�肪��Ɉړ����A�{�[�h���ɏ��߂ē���ʒu�����
	while (((m + i) >= 8) || ((n - i) < 0))
	{
		i--;
	}

	for (k = 0; k < 8; k++)
	{
		tmp[k] = 9;
	}

	//�z��tmp�ւ̊i�[
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
	//tmp[7]�܂Ŗ��܂��ĂȂ��ꍇ�́A3���i�[
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

	//�ǂ���̃v���C���[�ɂ��Ή��ł���悤�ɂ���
	if (me == 1)
	{
		you = 2;
	}
	else if (me == 2)
	{
		you = 1;
	}

	//�n���ꂽ�z��get_tmp[]�̐擪�A�h���X����A�z��tmp�֊i�[
	for (i = 0; i < 8; i++)
	{
		tmp[i] = *get_tmp;
		get_tmp++;
	}

	//�����̃`�F�b�N
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

	//�E���̃`�F�b�N
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


	//turning�t���O�������Ă���Ȃ�΁A���ۂɃ{�[�h���Ђ�����Ԃ�
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

	printf("  �P�Q�R�S�T�U�V�W\n");
	for (y = 0; y < 8; y++)
	{
		printf("%d ", y + 1);
		for (x = 0; x < 8; x++)
		{
			if (board[y][x] == 0)
			{
				printf("��");
			}
			else if (board[y][x] == 1)
			{
				printf("��");
			}
			else if (board[y][x] == 2)
			{
				printf("��");
			}
		}
		printf(" %d\n", y + 1);
	}
	printf("  �P�Q�R�S�T�U�V�W\n\n");
}

int end(int me)
{
	int x, y;
	int you_pass = 0;		//���肪�u���Ȃ��ʒu�̐�
	int me_pass = 0;		//�������u���Ȃ��ʒu�̐�
	int you;

	//�ǂ���̃v���C���[�ɂ��Ή��ł���悤�ɂ���
	if (me == 1)
	{
		you = 2;
	}
	else if (me == 2)
	{
		you = 1;
	}

	//����
	for (y = 0;y < 8; y++)
	{
		for (x = 0; x < 8; x++)
		{

			//���肪�u����ꏊ�Ȃ�0��Ԃ��āA����I��
			if ((board[y][x] == 0) && ((hantei(y, x, you, 0)) != 8))
			{
				printf("(%d,%d) = %d\n", y + 1, x + 1, board[y][x]);
				return 0;
			}
			//���肪�u���Ȃ��ꏊ�Ȃ�ϐ�you_pass��1�𑫂��āA����p��
			else
			{
				you_pass++;
			}
			//�������u����ꏊ�Ȃ牽�������A����p��
			if ((hantei(y, x, me, 0)) != 8)
			{
			}
			//�������u���Ȃ��ꏊ�Ȃ�A�ϐ�me_pass��1�𑫂��āA����p��
			else
			{
				me_pass++;
			}
		}
	}

	//������������ǂ��ɂ��u���Ȃ��ꍇ�A�Q�[���I���t���O(2)��Ԃ�
	if ((you_pass == 64) && (me_pass == 64))
	{
		return 2;
	}
	//����͂ǂ��ɂ��u���Ȃ��ꍇ�A�p�X�t���O(1)��Ԃ�
	else if ((you_pass == 64) && (me_pass != 64))
	{
		return 1;
	}
	//�Q�[���𑱂�����ꍇ�A���̃t���O�����Ă���0��Ԃ�
	else
	{
		return 0;
	}
}

