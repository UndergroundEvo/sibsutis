#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>

const int N=10;
using namespace std;


struct spis{
    int data;
    spis *next;
};


void Q(spis *&head, spis *&tail){
	spis *p,*pp;
	   system("cls");
	for (int i=1; i<=N; i++){
		p=new spis;
		p->next=NULL;
        p->data=i;
	    if (head) tail->next=p;
	    else head=p;
	    tail=p;	
	    
	    for (pp=head; pp->next; pp=pp->next)
	    cout<<pp->data<<' ';
	    cout<<'\n';
	    for (pp=head; pp->next; pp=pp->next)
	    cout<<"  ";
	    cout<<'^';
	    cout<<'\n';
	    for (pp=head; pp->next; pp=pp->next)
	    cout<<"  ";
	    cout<<p->data<<' ';
	    getch();
	       system("cls");
    }
	 for (pp=head; pp; pp=pp->next)
	    cout<<pp->data<<' ';
	       	system("pause");
	       	system("cls");
	
for (int i=1; i<=N; i++, head=head->next){
     cout<<"  ";
        for (p=head->next; p; p=p->next)
        cout<<p->data<<' ';
        cout<<'\n';
		cout<<'v'<<'\n'<<head->data<<'\n';
		getch();
		system("cls");
	}
		system("pause");	       	
	
	       	
}


void Stack(spis *&head){
    system("cls");
	spis *pp,*p;
	for (int i=1; i<=N; i++, head=pp){
        
        cout<<"  ";
        for (p=head; p; p=p->next)
        cout<<p->data<<' ';
        cout<<'\n';
		pp=new spis;
		pp->data=i;
		cout<<'^'<<'\n'<<pp->data<<'\n';
		pp->next=head;
		getch();
		system("cls");
	}
	 for (p=head; p; p=p->next)
        cout<<p->data<<' ';
	system("pause");
	system("cls");
	
	
for (int i=1; i<=N; i++, head=head->next){
     cout<<"  ";
        for (p=head->next; p; p=p->next)
        cout<<p->data<<' ';
        cout<<'\n';
		cout<<'v'<<'\n'<<head->data<<'\n';
		getch();
		system("cls");
	}
		system("pause");
	
}


int main(){
    int k;
    spis *head=NULL,*head2=NULL,*tail=NULL;
    while (1){
        system("cls");
        cout<<"1-„пэк\n2-„почередь\n3-„пыход\n";
        cin>>k;
        if (k==1) Stack(head);
        if (k==2) Q(head2,tail);
        if (k==3) return 3;
}
    
    
return 0;
}
    
