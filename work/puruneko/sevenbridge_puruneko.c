#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>

#define __TRUE__ 1
#define __FALSE__ 0

#define PLAYER_NUMBER 4
#define SUIT_NUMBER 4
#define CARD_NUMBER_PER_SUIT 13
#define GAMESET_NUMBER 3

typedef int boolean;

typedef struct card
{
	int number;
	int suit;
	// ssssnnnnnnnnnnnnn のint型にしようか迷い中
	// ↓↓ 案 ↓↓
	// スペード = 0001、クラブ = 0010、ハート = 0100、ダイヤ = 1000
	// （ハート2 = 01000000000000010 = 32770）
	// （ダイヤ1,3,5 = 10000000000010101 = 65557）
	// （これならint型の配列でデッキ・手札・メルド領域が扱える）
} Card;

typedef struct cards
{
	Card card;
	Card* prev;
	Card* next;
} Cards;

typedef struct cards_list
{
	Cards cards;
	Cards* prev;
	Cards* next;
} CardsList;

typedef struct player_information
{
	int id;
	int category;
	Cards* hand;
	boolean meld_done_flag;
	int point;
} Playerinformation;

// プロトタイプ宣言（業務関数）
// 命名規則：create->メモリ確保、 free->メモリ解放、 you->ユーザ入力、 疑問形->論理値返却
Playerinformation* create_player_information(int id, int category);
boolean is_game_over(int count, int set);
int* create_full_deck(int suit_num, int card_num);
CardsList* create_meld_field();
Cards* create_hand(int* deck);
boolean is_round_going_on(Cards* hand, int count);
void show_field(Card* grave, CardsList* meld_field);
void show_player(Playerinformation* player);
int get_available_options(Cards* hand, Card* grave, CardsList* meld_field);
int what_action_do_you_select(int flag);
boolean can_pong(int flag);
boolean is_action_pong(int flag);
void pong(Cards* hand, Card* grave, CardsList* meld_field);
boolean can_qi(int flag);
boolean is_action_qi(int flag);
void qi(Cards* hand, Card* grave, CardsList* meld_field);
void draw_card(int* deck, Cards* hand);
boolean can_meld(int flag);
boolean is_action_meld(int flag);
void meld(Cards* hand, CardsList* meld_field);
boolean can_tag(int flag);
boolean is_action_tag(int flag);
void tag(Cards* hand, CardsList* meld_field);
Card* what_card_do_you_discard(Cards* hand, Cards* graves);
int get_card_number(Cards* cards);
int* create_deck(Cards* resource);
int calc_point(Cards* hand);
void free_deck(int* deck);
void free_meld_field(CardsList* meld_field);
void free_hand(Cards* hand);
int* calc_rank(Playerinformation* players[], int player_number); 
void free_player(Playerinformation* player);

// プロトタイプ宣言（内部関数）
void* next_list();
int get_nth_bit(int bit, int nth);

// メイン関数
int main()
{
	// プログラム初期化設定
	int itr_tmp;
	Cards* hand;

	int* deck;
	CardsList* meld_field;
	Card* grave;
	Cards* graves;

	Playerinformation* players[PLAYER_NUMBER];

	int gameset_count;
	int voiddeck_count;
	int flag_available; //付け札順子(32)、付け札刻子(16)、メルド順子(8)、メルド刻子(4)、チー(2)、ポン(1)
	int flag_action;

	// ゲーム初期化設定
	gameset_count = 1;
	for (itr_tmp = 0; itr_tmp < PLAYER_NUMBER; itr_tmp++)
	{
		players[itr_tmp] = create_player_information(itr_tmp);
	}

	// ゲームセットカウントループ
	while (is_game_over(gameset_count,GAMESET_NUMBER))
	{
		// 場を初期化する
        deck = create_full_deck(SUIT_NUMBER, CARD_NUMBER_PER_SUIT);
		meld_field = create_meld_field();
		voiddeck_count = 1;

		// カード配る
		for (itr = 0; itr < PLAYER_NUMBER; itr++)
		{
			players[itr]->hand = create_hand(deck);
		}

		// ゲームメインループ
		while (is_round_going_on(hands, voiddeck_count))
		{
			// プレイヤー交代処理
			player = players[(player + 1) % PLAYER_NUMBER];

			// 画面表示
			show_field(grave, meld_field);
			show_player(player);

			// ポン・チーの要否確認
			flag_available = get_available_options(player->hand, grave, meld_field);
			flag_action = what_action_do_you_select(flag_available);

			// ポン
			if (can_pong(flag_available) && is_action_pong(flag_action))
			{
				pong(player->hand, grave, meld_field);
				grave = NULL;
			}
			// チー
			else if (can_qi(flag_available) && is_action_qi(flag_action))
			{
				qi(player->hand, meld_field);
				grave = NULL;
			}
			// ポン・チー出来ない／しない場合
			else
			{
				// ドロー
				draw_card(deck, player->hand);

				// メルド・付け札するしないループ
				while(__TRUE__)
				{
					// 画面表示
					show_field(grave, meld_field);
					show_player(player);

					// メルド・つけ札の可否確認
					flag_available = get_available_options(player->hand, grave, meld_field);

					// メルドもつけ札もできない
					if (!can_mald(flag_available) && !can_tag(flag_available))
					{
						break;
					}

					// メルド・付け札の選択
					flag_action = what_action_do_you_select(flag_available);

					// メルドもつけ札もしない
					if (!is_action_meld(flag_action) && !is_action_tag(flag_action))
					{
						break;
					}
					// 何かする
					else
					{
						// メルド処理
						if (can_meld(flag_available) && is_action_meld(flag_action))
						{
							meld(player, meld_field);
						}
						// 付け札処理
						else if (can_tag(flag_available) && is_action_tag(flag_action))
						{
							tag(player->hand, meld_field);
						}
					}
				}
			}

			// 画面表示
			show_field(grave, meld_field);
			show_player(player);

			// 捨て札処理
			grave = what_card_do_you_discard(player->hand);

			// 山札の確認
			if (get_card_number(deck) <= 0)
			{
				free_deck(deck);
				deck = create_deck(players);
				grave = NULL;
				voiddeck_count++;
			}
		}

		// 点数計算
		for (itr = 0; itr < PLAYER_NUMBER; itr++)
		{
			players[itr]->point += calc_point(players[itr]->hand);
		}

		// ゲームセットの終了処理
		free_deck(deck);
		free_meld_field(meld_field);
		for (itr_tmp = 0; itr_tmp < PLAYER_NUMBER; itr_tmp++)
		{
			free_hand(players[itr_tmp]->hand);
		}
		gameset_count++;
	}

	// 順位決定
    rank = calc_rank(players, PLAYER_NUMBER);

	// 終了処理
	for (itr_tmp = 0; itr_tmp < PLAYER_NUMBER; itr_tmp++)
	{
		free_player(players[itr_tmp]);
	}
    printf("");

}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

Cards* get_last_card(Cards* list_)
{
	Cards* cards = list_;
	while(cards->next != NULL)
	{
		cards = cards->next;
	}
	return cards;
}

void append_card(Cards* list_, Card* card)
{
	Cards* cards = (Cards*)malloc(sizeof(Cards));
	Cards* last_card = get_last_card(list_);
	cards->card = card;
	cards->prev = last_card;
	cards->next = NULL;
	last_card->next = cards;
}

void free_cards(Cards* list_)
{
	Cards* target = get_last_card(list_);
	Cards* prev = target->prev;
	while(target != NULL)
	{
		free(target);
		target = prev;
		if (target != NULL)
		{
			prev = target->prev;
		}
	}
}

CardsList* get_last_cards(CardsList* list_)
{
	CardsList* cardslist = list_;
	while(cardslist->next != NULL)
	{
		cardslist = cardslist->next;
	}
	return cardslist;
}

void append_cards(CardsList* list_, Cards* cards)
{
	CardsList* cardslist = (CardsList*)malloc(sizeof(CardsList));
	CardsList* last_cards = get_last_cards(list_);
	cardslist->card = cards;
	cardslist->prev = last_cards;
	cardslist->next = NULL;
	last_cards->next = cardslist;
}

