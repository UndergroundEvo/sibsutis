#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <time.h>

using namespace std;

const int N=20;


class spis {
	public: int data;
	spis *next;
};



/*void FillStack(spis *&head, int n){
    int A[n];
	spis *pp,*p;
	for (int i=0; i<n; i++, head=pp){
        A[i]=rand()%10;
		pp=new spis;
		pp->data=A[i]*A[i];
		pp->next=head;
	}
}

void FillIncQ(spis *&head, spis *&tail){
	spis *p;
	int n;
	

	for (int i=1; i<=10; i++){
		p=new spis;
		p->next=NULL;
	   p->data=i;
	    if (head) tail->next=p;
	    else head=p;
	    tail=p;	
	}
}*/

void FillQ(spis *&head, spis *&tail){
	spis *p;
int A[N];
	for (int i=0; i<N; i++){
        A[i]=rand()%20;
		p=new spis;
		p->next=NULL;
        p->data=A[i]*A[i];
	    if (head) tail->next=p;
	    else head=p;
	    tail=p;	
	}
}



/*int CheckSum(spis *head){
	int sum=0;
	for (head; head; head=head->next)
	sum+=head->data;
	return sum;
}

int RunNumber(spis *head){
	int num=1;
	if (head==NULL) {printf("Empty ErrorCode:"); return -1;}
	for (head; head->next; head=head->next)
	if (head->data>head->next->data) num++;
	return num;
}*/



void Print(spis *head){
	if (head==NULL) printf("Queue are Empty");
	for (head; head; head=head->next)
	printf("%d ",head->data);
}

int FreeSpis(spis *&head){
	spis *p;
	while (head){
	 p=head;
     head=p->next;
     delete p;
}
printf("list was deleted");
}


void AddInQ(spis *head){
	spis *p;
	int n;
	cout<<"Add After:";
    cin>>n;
	for (int i=1; i<n; i++)
	head=head->next;
		p=new spis;		cout<<"Add :";
	    cin>>p->data;
	    p->next=head->next;
	    head->next=p;
}

void DeleteFromQ(spis *&head){
	spis *temp=head,*p;
	int n;
	
	cout<<"\nDelete Namber:";
    cin>>n;
    if (n==1) {p=head->next;
    delete (temp);
    head=p;}
    else{
    
	for (int i=2; i<n; i++)
	temp=temp->next;
		p=temp->next->next;
	delete(temp->next);
	temp->next=p;}
}

void MoveInQ(spis *&head){
	spis *temp,*p=head,*pp=head;
	int n,k;

	cout<<"\nMove Namber:";
    cin>>n;
    cout<<"\nAfter Namber:";
    cin>>k;
    
    if (n==1) {
    for (int i=1; i<k; i++)
    pp=pp->next;
    temp=head;
    cout<<p->data<<" "<<pp->data<<" "<<temp->data;
    
    head=head->next;
    temp->next=pp->next;
    pp->next=temp;
        
        }
    else{
    
    
  	for (int i=2; i<n; i++)
  	p=p->next;
  	for (int i=1; i<k; i++)
	pp=pp->next;
	temp=p->next;
	cout<<p->data<<" "<<pp->data<<" "<<temp->data;
	

	
	p->next=temp->next;
	temp->next=pp->next;
	pp->next=temp;
}
  	
  
}

int LengthQ(spis *head){
    int l=0;
	if (head==NULL) {printf("Queue are Empty"); return 0;}
	for (head; head; head=head->next)
	l++;
	return l;
}
void DeleteRepeat(spis *head){
	spis *p=head,*temp;
	int f=0,A[N],j,l=1,n,i;
	A[0]=head->data;
	for (p; p->next; 1){
        
        for (j=0; j<l; j++)
            if (p->next->data==A[j]){
                temp=p->next;
                p->next=p->next->next;
                delete(temp); f=1;
                break;}
            if (0==f){
            A[l++]=p->next->data;
            p=p->next;
            }
        f=0;

    }
}

int main(){
    
short menu;
    int i,j,k,n;
    spis *head=NULL, *tail=NULL;
    	printf("1-Print\n2-FillQ\n3-DeleteFromQ\n4-AddInQ\n5-MoveInQ\n6-DeleteRepeat\n7-LengthQ\n0-FreeSpis\n\n");
    while(1){

cout<<"\n";
	menu=getch();
	  srand(time(NULL));
	switch(menu){
	case 27:return 0;
	case 49:Print(head);  break;
	case 50:FillQ(head,tail); break;
	case 51:DeleteFromQ(head); break;
	case 52:AddInQ(head); break;
	case 53:MoveInQ(head); break;
	case 54:DeleteRepeat(head); break;	
    case 55:cout<<"\nLengthQ="<<LengthQ(head); break;
	case 48:FreeSpis(head); break;		
		cout<<"\n";
							
}
}
return 0;
}
    

