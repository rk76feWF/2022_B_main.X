#include "user.h"

int enqueue(queue_t *que, data_t enq_data)
{
    // エラー処理
    if (que->num >= QUEUE_SIZE)
        return -1;

    que->data[(que->head + que->num) % QUEUE_SIZE] = enq_data;
    que->num++;

    return 0;
}

int dequeue(queue_t *que, data_t *deq_data)
{
    // エラー処理
    if (que->num <= 0)
        return -1;

    *deq_data = que->data[que->head];
    que->head = (que->head + 1) % QUEUE_SIZE;
    que->num--;

    return 0;
}
