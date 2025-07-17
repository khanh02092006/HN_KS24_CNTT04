#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef  struct Request
{
    int id;
    char issue[100];
    int priority;

}Request;
typedef  struct node
{
  Request data;
    struct node *next;
}node;
typedef  struct queue
{

    node *front;
    node *rear;

}queue;
void initQueue(queue *q)
{
    q->front = q->rear = NULL;
}
int isQueueEmpty(queue *q)
{
    return q->front == NULL;
}
void enQueue(queue *q, Request data)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->data = data;
    newnode->next = NULL;
    if(isQueueEmpty(q))
    {
        q->front = q->rear= newnode;
    } else
    {
        q->rear->next = newnode;
        q->rear = newnode;
    }

}
void printQueue(queue *q)
{
    if(isQueueEmpty(q))
    {
        printf("Queue is empty\n");
        return;
    }
    node *temp = q->front;
    while(temp != NULL)
    {
        printf("%d\t|%s\n", temp->data.id, temp->data.issue);
        temp = temp->next;
    }

}
int main(void)
{
    queue HIGHQUEUE , LOWQUEUE;
    initQueue(&LOWQUEUE);
    initQueue(&HIGHQUEUE);
    int choice;
    do
    {
        printf("\n======= REQUEST SYSTE====\n");
        printf("1. Gui yeu cau ho tro\n");
        printf("2. Xu ly yeu cau\n");
        printf("3. Xem yeu cau gan nhat can xu ly\n");
        printf("4. Hien thi toan bo yeu cau\n");
        printf("5. Thoat\n");
        printf("Chon: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
            case 1:
            Request r;
            printf(" nhap ID ");
            scanf("%d", &r.id);
            getchar();
            printf(" nhat issue ");
            fgets(r.issue, 100, stdin);
            r.issue[strcspn(r.issue, "\n")] = 0;
            printf(" nhap muc do uu tien");
            scanf("%d", &r.priority);
            getchar();
            if (r.priority==1)
            {
                enQueue(&HIGHQUEUE, r);
            }else
            {
                enQueue(&LOWQUEUE, r);
            }
            printf(" thanh cong");
            break;
            case 2:
            break;
            case 3:
            break;
            case 4:
            printQueue(&LOWQUEUE);

            break;
            case 5:
            printf(" thoat\n");
            break;
            default:
            printf(" lua chon khong hop le");
            break;

        }

    }while(choice != 5);
    return 0;
}