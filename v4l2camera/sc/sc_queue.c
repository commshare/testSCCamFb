#include <assert.h> //for assert
#include<stdlib.h> //for malloc free
  #include <string.h> //for memset

#include "sc_queue.h"
#include"sc_log.h"

//#define CLEAR(x) memset(&(x), 0, sizeof(x))
static
int queue_init(sc_queue_t **q){

	(*q)=(sc_queue_t *)malloc(sizeof(sc_queue_t));
	if(*q){
		memset((*q),0,sizeof(sc_queue_t));
		return 0;
	}else{
	  (*q)=NULL;
	  return -1;
	}
}
sc_queue_t *queue_new(int size){
    sc_queue_t * q=NULL;
	if(queue_init(&q)==0){
		q->size=size;/*�����д�С���޵�*/
		q->level=0;
		q->head=q->tail=NULL;/*�Ӳ��Ӷ�һ����*/
		LOGD("queue new OK");
	}else
		LOGD("queue new FAIL");
	return q;
}
void queue_delete(sc_queue_t *q){
	if(q){
		memset(q,0,sizeof(sc_queue_t));
		free(q);
		q=NULL;
	}
}

int queue_empty(sc_queue_t *q){
	assert(q!=NULL);
	if(q->level==0)
		return 1;
	else
		return 0;
}
int queue_full(sc_queue_t *q){
	assert(q!=NULL);
	if(q->level==q->size)
		return 1;
	else
		return 0;
}


int queue_pushback(sc_queue_t * q, sc_pkt * pkt){
	//assert(q!=NULL && pkt!=NULL);
	if(q==NULL || pkt==NULL){
		LOGE("QUEUE PUSHBACK FAIL FOR EXCEPTION!");
		return -1;
	}
	if(queue_full(q))
	{
		LOGD("queue is full,cannot pushback");
		return -1;
	}

    sc_entry_t *entry=NULL;
    entry=(sc_entry_t *)malloc(sizeof(sc_entry_t));
	memset(entry,0,sizeof(sc_entry_t));
	entry->
	if(q->head==NULL){
		LOGD("first time pushback");
		/*head��tailһֱû������ڴ氡����ôtai�ļ�������û�ڴ�ģ�Ҳ���޷���ֵ��ʹ��*/
		q->head=q->tail=entry; /*����tail��NULL������ᱨ��*/
		/*�����ڸı�entry��prev��next*/
		//q->head->next=NULL;
		//q->head->prev=NULL;
	}
	q->tail->next=entry;
	q->tail->next->prev=q->tail;
	q->tail=entry;
	q->tail->next=NULL;
	q->level+=1;
	return 0;
}

int queue_popfront(sc_queue_t * q, sc_pkt **pkt){
	if(q!=NULL){
		if(queue_empty(q)){
			LOGE("queue is empty ,popfront FAIL");
			return -1;
		}
		(*pkt)=q->head->pkt;
		sc_entry_t *next=q->head->next;
		//if(next)/*��Ȼ�Ѿ����ǿյģ���ônext�϶����ǿյĶ԰�*/
		{
			next->
			q->head=next;
			q->level-=1;
			/*���pop���ǲ��ǿ���*/
			if(q->level==0){
				q->head=q->tail=NULL;
				q->head->prev=NULL;
				q->head->next=NULL;
			}
		}
		return 0;
	}else{
		LOGE("Q IS NULL ,pop front queue fail");
		return -1;
	}
}
