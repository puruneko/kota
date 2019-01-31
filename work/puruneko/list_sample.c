#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ルール
// 1. コンパイラの組み込みGCは使わない（mallocで確保したメモリは全て管理する）
// 2. リスト操作関数内でmain側から渡されたポインタの位置を変化させない（関数内のローカル変数を使う）
// 3. リストは双方向とし、循環型とする（mainで持っている変数に先頭を保持させる）
// 4. リスト操作関数は、どの位置のポインタを指定されても正しく動くように実装する
// 5. 空のリストは作れない

typedef int type_;

typedef struct list_name
{
    type_ elem;
    struct list_name* prev;
    struct list_name* next;
} ListName;


ListName* ver_name = NULL;


ListName* get_new(type_ elem)
{
    ListName* new_list = (ListName*)malloc(sizeof(ListName));
    new_list->elem = elem;
    new_list->next = NULL;
    new_list->prev = NULL;
    return new_list;
}

ListName* get_first(ListName* list_)
{
    if (list_ == NULL)
    {
        return NULL;
    }
    ListName* tmp = list_;
    while(tmp->prev != NULL)
    {
        tmp = tmp->prev;
    }
    return tmp;
}

ListName* get_last(ListName* list_)
{
    if (list_ == NULL)
    {
        return NULL;
    }
    ListName* tmp = list_;
    while(tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    return tmp;
}

int get_length(ListName* list_)
{
    int len = -1;
    if (list_ != NULL)
    {
        ListName* tmp;
        tmp = get_first(list_);
        for (len = 1; tmp->next != NULL; len++)
        {
            tmp = tmp->next;
        }
    }
    return len;
}

void show_mono(ListName* list_)
{
    if (list_ != NULL)
    {
        printf("[%010d] %010d, %010d, %010d\n", (int)list_, list_->elem, (int)(list_->prev), (int)(list_->next));
    }
}

void show(ListName* list_)
{
    printf("start show.\n");
    if (list_ != NULL)
    {
        ListName* tmp = get_first(list_);
        int len = get_length(tmp);
        int i;
        for (i = 0; i < len; i++)
        {
            show_mono(tmp);
            tmp = tmp->next;
        }
    }
    else
    {
        printf("NULL\n");
    }
    printf("end show.\n");
}

ListName* get_at(ListName* list_, int index)
{
    if (list_ == NULL)
    {
        return NULL;
    }
    ListName* tmp = get_first(list_);
    int i;
    for (i = 0; i < index; i++)
    {
        tmp = tmp->next;
        if (tmp == NULL)
        {
            return NULL;
        }
    }
    return tmp;
}

void add(ListName* added, ListName* prev, ListName* next)
{
    if (added != NULL && (prev != NULL || next != NULL))
    {
        printf("@add prev\n");
        show_mono(prev);
        printf("@add next\n");
        show_mono(next);
        added->next = next;
        added->prev = prev;
        if (prev != NULL)
        {
            prev->next = added;
        }
        if (next != NULL)
        {
            next->prev = added;
        }
        printf("@add added\n");
        show(added);
    }
}

ListName* insert(ListName* list_, type_ elem, int index)
{
    if (list_ != NULL)
    {
        ListName* tmp = list_;
        ListName* list_new = get_new(elem);
        int len = get_length(tmp);
        if (index > len)
        {
            return NULL;
        }
        else if (index == len)
        {
            tmp = get_last(tmp);
            add(list_new, tmp, NULL);
        }
        else if (index == 0)
        {
            tmp = get_first(tmp);
            add(list_new, NULL, tmp);
        }
        else
        {
            tmp = get_at(tmp, index);
            ListName* next = tmp;
            ListName* prev = tmp->prev;
            add(list_new, next, prev);
        }
    }
    return list_;
}

void append(ListName* list_, type_ elem)
{
    if (list_ != NULL)
    {
        int len = get_length(list_);
        list_ = insert(list_, elem, len);
    }
}

void prepend(ListName* list_, type_ elem)
{
    if (list_ != NULL)
    {
        list_ = insert(list_, elem, 0);
    }
}

void delete(ListName* list_)
{
    if (list_ != NULL)
    {
        ListName* tmp = list_;
        if (list_->prev != NULL && list_->next != NULL)
        {
            list_->prev->next = list_->next;
            list_->next->prev = list_->prev;
            list_ = list_->next;
        }
        else if (list_->prev == NULL && list_->next != NULL)
        {
            list_->next->prev = NULL;
            list_ = list_->next;
        }
        else if (list_->prev != NULL && list_->next == NULL)
        {
            list_->prev->next = NULL;
            list_ = list_->prev;
        }
        free(tmp);
    }
}

void delete_at(ListName* list_, int index)
{
    delete(get_at(list_, index));
}

void pop(ListName* list_)
{
    delete(get_last(list_));
}

void pop_left(ListName* list_)
{
    delete(get_first(list_));
}

void destroy(ListName** plist_)
{
    ListName* list_ = *plist_;
    if (list_ != NULL)
    {
        list_ = get_first(list_);
        ListName* next = list_->next;
        while(next->next != NULL)
        {
            free(next->prev);
            next->prev = NULL;
            next = next->next;
        }
        free(next);
    }
    *plist_ = NULL;
}

int main()
{
    ListName* a = get_new(500);
    int i;
    printf("a aims at [%d]\n", (int)(a));
    for (i = 0; i < 3; i++)
    {
        printf("==== append %d ====\n", i);
        append(a, (i+6)*100 );
        printf("a aims at [%d]\n", (int)(a));
        printf("@main result\n");
        show(a);
        printf("********\n");
    }
    printf("----------\n");
    for (i = 0; i < 3; i++)
    {
        printf("==== prepend %d ====\n", i);
        prepend(a, (4-i)*100 );
        printf("a aims at [%d]\n", (int)(a));
        printf("@main result\n");
        show(a);
        printf("********\n");
    }
    printf("----------\n");
    
    printf("@main result after processing.\n");
    show(a);
    
    destroy(&a);
    printf("@main result after destroy\n");
    show_mono(a);
    show(a);

    return 0;
}