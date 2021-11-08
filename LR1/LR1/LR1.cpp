#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef int Data;
typedef struct Node Node;

struct Node {
    
    int s; // начальный номер вершины (стартовый)
    int c; // конечный номер вершины (финишный)
    int v; //"вес" пути
    Node* next; // указатель на след. элемент
};

struct item { //структура для описания элемента карты
    int s, c; //начальный и конечный узлы
    int v; //"вес" пути
};
void print(Node* list);
void set_edge(Node** plist, int s, int c, int v);
int isEmpty(Node* list);
Data pop(Node** list);
Data deleteLastNode(Node** plist);
//int* searchByKey(Node* list, int key);
int find(Node* list, int s, int c);
void step(Node* list, int s, int f, int p);

const int m = 22; //количество путей по графу
const int n = 9; //количество вершин графа

struct item map[m] = { //все пути, нумерация узлов с нуля
 {0,1,1}, {0,2,1}, {2,3,1}, {1,4,1}, {2,4,1},
 {4,5,1}, {4,7,1}, {5,6,1}, {6,7,1}
};

int road[n]; //номера узлов текущей "дороги"
bool incl[n]; //true, если i-ая вершина включена в путь
int way[n]; //искомый самый короткий путь
int waylen; //его длина
int start, finish; //начальная и конечная вершины
bool found;
int len; //найденный "вес" маршрута
int c_len; //текущий "вес" маршрута



int find(Node* list, int s, int c) { //вес пути из s и c или 0, если пути нет
    int index = 1;
    for (Node* p = list; p != NULL; p = p->next) {
        
        if (p->s == s && p->c == c ||
            p->s == c && p->c == s) return p->v;
        index++;
    }
    
    return 0;
}
void step(Node* list, int s, int f, int p) { //рекурсивный поиск шага пути
    int c; //номер вершины, куда делаем шаг
    if (s == f) { //путь найден
        found = true; //поставить флажок "найдено"
        len = c_len; //запомнить общий вес пути
        waylen = p; //запомнить длину пути (количество узлов)
        for (int i = 0; i < waylen; i++) way[i] = road[i]; //запомнить сам путь
    }
    else { //выбор очередной точки
        for (c = 0; c < n; c++) { //проверяем все вершины
            int w = find(list, s, c); //есть ли путь из s в c
            if (w && !incl[c] && (len == 0 || c_len + w < len)) { //нужная точка не включена?
                road[p] = c; //включить точку в путь
                incl[c] = true; //пометить как включенную
                c_len += w; //учесть в общем весе пути
                step(list, c, f, p + 1); //вызвать себя для поиска следующей точки
                road[p] = 0; //вернуть всё как было
                incl[c] = false;
                c_len -= w;
            }
        }
    }
}

int main() {

    setlocale(LC_ALL, "Russian");
    system("color F0");
    Node* list = NULL;

    int x = 0;
    int value = 0;

    set_edge(&list, 1, 5, 1);
    set_edge(&list, 1, 6, 2);
    set_edge(&list, 1, 9, 2);
    set_edge(&list, 1, 8, 4);

    set_edge(&list, 2, 1, 3);
    set_edge(&list, 2, 3, 4);

    set_edge(&list, 3, 4, 5);
    set_edge(&list, 3, 5, 6);

    set_edge(&list, 4, 8, 7);
    set_edge(&list, 4, 7, 8);

    set_edge(&list, 5, 8, 9);
    set_edge(&list, 5, 7, 10);

    set_edge(&list, 6, 8, 11);
    set_edge(&list, 6, 7, 12);

    set_edge(&list, 7, 1, 13);
    set_edge(&list, 7, 2, 14);
    set_edge(&list, 7, 9, 15);

    set_edge(&list, 8, 3, 16);
    set_edge(&list, 8, 2, 17);
    set_edge(&list, 8, 9, 18);

    set_edge(&list, 9, 4, 19);
    set_edge(&list, 9, 6, 20);

    //Инициализация данных:
    for (int i = 0; i < n; i++) {
        road[i] = way[i] = 0; incl[i] = false;
    }
    len = c_len = waylen = 0;

    start = 1; //начало пути - нумерация с 0
    finish = 8; //конец пути - нумерация с 0
    road[0] = start; //первую точку внесли в маршрут
    incl[start] = true; //и пометили как включённую
    found = false; //но путь пока не найден
    step(list, start, finish, 1); //ищем вторую точку

    if (found) {
        cout << "Way is";
        for (int i = 0; i < waylen; i++) cout << " " << way[i];
        cout << ", weight is " << len;
    }
    else cout << "Way not found!";
    cout << endl;
    
    
    

    do
    {
        printf("1. Добавить вершину в граф\n");
        printf("2. Удалить элемент из конца списка\n");
        printf("3. Вывести список\n");
        printf("4. Удалить весь список\n");
        printf("5. Поиск элемента\n");
        printf("0. Выйти\n");
        printf("\nНомер операции > "); scanf_s("%d", &x);
        switch (x)
        {
        case 1:

            printf("Значение > "); scanf_s("%d", &value);
            //set_edge(&list, 78, 32);
            //print(list);
            break;
        case 2:
            /*deleteLastNode(&list);
            printf("pop %d :\n", d);
            print(list);*/
            break;
        case 3:
            print(list);
            break;
        case 4:
            
            while (!isEmpty(list)) {
                Data d = pop(&list);
                printf("pop %d :\n", d);
            }
            printf("Empty: %s\n", isEmpty(list) ? "YES" : "NO");
            break;
        case 5:
            printf("Значение > "); scanf_s("%d", &value);
            //int* Arr = searchByKey(list, value);
            break;
        }
    } while (x != 0);

    printf("\n");

    return 0;
}


Data pop(Node** plist) { // удаляет первый элемент

    Node* p = *plist;
    Data res = p->s;
    *plist = p->next;
    free(p);

    return res;
}

Data deleteLastNode(Node** plist) //7.	Удаление элемента из конца списка
{
    Node* toDelete, * secondLastNode;
    if (plist == NULL)
    {
        printf("List is already empty.");
        return 0;
    }
    else
    {
        toDelete = *plist;
        secondLastNode = *plist;

        /* меняем указатель до тех пор, пока не дойдем до конца */
        while (toDelete->next != NULL)
        {
            secondLastNode = toDelete;
            toDelete = toDelete->next;
        }

        if (toDelete == *plist)
        {
            *plist = NULL;
        }
        else
        {
            /* разрываем связь предпоследнего элемента с последним*/
            secondLastNode->next = NULL;
        }
        Data res = toDelete->s;
        /* освобождаем память */
        free(toDelete);
        return res;
    }
}
int isEmpty(Node* list) { // проверка на пустоту списка
    return list == NULL;
}
void print(Node* list) { // вывести на экран
    int index = 0;
    for (Node* p = list; p != NULL; p = p->next) {
        printf("[%d] = %d, %d, %d\n", index, p->s, p->c, p->v);
        index++;
    }

    printf("\n");
}
/*int* searchByKey(Node* list, int key) { // найти индекс элемента
    int overlap = 0;
    for (Node* p = list; p != NULL; p = p->next) {
        if (p->data == key) {
            overlap++;

        }
    }
    printf("\n");
    int index = -1;
    int count = 0;
    int query = 0;
    int* Arr = new int[overlap];
    for (Node* p = list; p != NULL; p = p->next) {
        if (p->data == key) {

            index = query;
            count++;
            Arr[count] = index;
            printf("Ключ %d поиска найден. Индекс равен %d\n", key, index);
        }
        query++;
    }
    if (index == -1) {
        printf("Ключ %d поиска не найден\n", key);
    }
    return Arr;
}*/
void set_edge(Node** plist, int s, int c, int v) { // положить элемент в начало
    Node* p = (struct Node*)malloc(sizeof(Node));
    p->s = s;
    p->c = c;
    p->v = v;
    p->next = *plist;
    *plist = p;
}