#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

typedef struct  {
    int* data;
    size_t len;
    int head;
    int tail;
}deque; 

/*
#define deque_init(type, size_t len) ({\
    type* p = (type*)malloc(len*sizeof(type)); \
    if (!p) return (deque){0x0, len, 0, 0};\
    return (deque){p, len, 0, 0};\
})
#define deque_init_m(type, len) do{(deque){(type*)malloc(len*sizeof(type)), len, 0, 0};}while(0);
*/

deque deque_init(size_t len) {
    return (deque){(int*)malloc(len*sizeof(int)), len, 0, 0};
}

#define deque_expansion(q) do{\
    int *new_data = realloc(q->data, 2*q->len*sizeof(int));\
    if (!new_data) \
        printf("expansion failed\n");\
    q->data = new_data;\
}while(0);


void deque_push(deque* q, int v) {
    q->data[q->tail++] = v;
    if (q->head < q->tail) {
        if (q->tail==q->len) { 
            if (q->head==0) { /* need expand data twice*/
                deque_expansion(q);
                q->len = 2*q->len;
            }
            else {
                q->tail = 0;
            }
        }
    }
    else if (q->tail==q->head) { /* tail < head */  
        deque_expansion(q);      /* expand data twice*/
        /* 
         * copy the [0, tail) to end of [head, q->len) 
         * move the [head, tail+q->len) to [0, q->len) 
         */
        memcpy(&q->data[q->len], q->data, sizeof(int)*q->tail);
        memmove(q->data, &q->data[q->head], sizeof(int)*q->len);

        q->head = 0;
        q->tail = q->len;
        q->len = 2*q->len;
    }
}
// bool deque_popable(deque* q) { return q->head!=q->tail; }
#define deque_popable(q) ({q->head!=q->tail;})
int deque_pop(deque* q) {
    int t = q->data[q->head++];
    if (q->head == q->len) { 
        q->head = 0;
    }

    /* 
     * if the count drop below 25% of the length,
     * shrink the length to its half 
     */
    return t;
}

int deque_count(deque* q) {
    int t = q->tail- q->head;
    if (t>=0) 
        return t;
    else
        return q->len + t;
}

void deque_free(deque* q) {
    if (!q->data) return; 
    free(q->data);
    q->data = 0x0;
    q->len = q->head = q->tail = 0;
}

void deque_str(deque *q) 
{
    printf("deque->");
    if (q->head < q->tail) {
        for( int *t = &q->data[q->head]; 
                  t < &q->data[q->tail]; ++t) {
            printf("%d->", *t);
        }
    }
    else if (q->head>= q->tail) {
        assert(q->head!=q->tail);
        for( int *t = &q->data[q->head]; 
                  t < &q->data[q->len]; ++t) {
            printf("%d->", *t);
        }
        for (int *t = q->data;
                  t < &q->data[q->tail]; ++t) {
            printf("%d->", *t);
        }
    }
    printf("\n");
}

void dequeUT(void) 
{
/* TEST CASE 1 */
    deque q = deque_init(6);
    deque_push(&q, 1);
    deque_push(&q, 2);
    deque_push(&q, 3);
    deque_push(&q, 4);
    deque_push(&q, 5);
    assert( deque_count(&q)==5 && q.head==0 && q.tail==5 );
    deque_push(&q, 6);
    assert( deque_count(&q)==6 && q.head==0 && q.tail==6 );
    int d1=0;
    d1 = deque_pop(&q);
    assert( deque_count(&q)==5 && q.head==1 && q.tail==6 && d1==1 );
    deque_push(&q, 7);
    assert( deque_count(&q)==6 && q.head==1 && q.tail==7 );
    deque_push(&q, 8);
    assert( deque_count(&q)==7 && q.head==1 && q.tail==8 );
    deque_str(&q);
    deque_free(&q);

/* TEST CASE 2 */

    deque q1 = deque_init(3);
    deque_push(&q1, 1);
    deque_push(&q1, 2);
    d1 = deque_pop(&q1);
    assert( deque_count(&q1)==1 && q1.head==1 && q1.tail==2 );
    deque_push(&q1, 3);
    assert( deque_count(&q1)==2 && q1.head==1 && q1.tail==0 );
    deque_push(&q1, 4);
    assert( deque_count(&q1)==3 && q1.head==0 && q1.tail==3 && q1.len == 6);
    deque_push(&q1, 5);
    assert( deque_count(&q1)==4 && q1.head==0 && q1.tail==4 );

    int d2 = 0;
    d2 = deque_pop(&q1);
    assert( deque_count(&q1)==3 && q1.head==1 && q1.tail==4 && d2==2);
    deque_push(&q1, 6);
    assert( deque_count(&q1)==4 && q1.head==1 && q1.tail==5 );
    deque_push(&q1, 7);
    assert( deque_count(&q1)==5 && q1.head==1 && q1.tail==0 );
    deque_push(&q1, 8);
    assert( deque_count(&q1)==6 && q1.head==0 && q1.tail==6 );

    int d3 = 0;
    d3 = deque_pop(&q1);
    assert( deque_count(&q1)==5 && q1.head==1 && q1.tail==6 && d3==3);
    deque_push(&q1, 9);
    assert( deque_count(&q1)==6 && q1.head==1 && q1.tail==7 && q1.len==12);
    deque_push(&q1, 10);
    assert( deque_count(&q1)==7 && q1.head==1 && q1.tail==8 && q1.len==12);
    deque_str(&q1);
    deque_free(&q1);
    printf("QUEUE TEST DONE\n");
}

int main(void) {
    dequeUT();
    return 0;
}
