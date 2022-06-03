#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data
{
       char type[50];
       int qty;
       struct data *next;
       struct data *prev;
}*curr, *head, *tail;

void push_depan(char type[], int qty)
{
       curr = (struct data*)malloc(sizeof(struct data));
       strcpy(curr->type, type);
       curr->qty = qty;

       if(head == NULL) 
       {
              head = tail = curr;
       }
       else
       {
              curr->next = head;
              head->prev = curr;
              head = curr;
       }
       tail->next = NULL;
       head->prev = NULL;
}

int display()
{
       int idx = 0;
       puts("            --- ORDER LIST ---          \n");
       puts("-------+-----------------------+----------");
       puts("| No.  | Nama Menu Pesanan     | jumlah |");
       puts("-------+-----------------------+----------");
      
       if(head != NULL) 
       {
              curr = head;
              while(curr != NULL)
              {
                     printf("| %d | %s | %d |\n", idx+1, curr->type, curr->qty);
                     curr = curr->next;
                     idx++;
              }
       }
       puts("-------+-----------------------+-----------");
       getchar();
       return idx;
}

void addOrder()
{
       if(curr == head)
       {
              head = head->next;
              free(curr);
              if(head != NULL)
              {
                     head->prev = NULL;
              }
       }
       else if(curr == tail)
       {
              curr = tail;
              tail = tail->prev;
              free(curr);
              tail->next = NULL;
       }
       else
       {
              struct data *temp;
              temp = head;
              while(temp->next != curr)
              {
                     temp = temp->next;
              }

              curr->next->prev = curr->prev;
              temp->next = curr->next;
              free(curr);
       }
}

int main()
{
       int choose;

       do
       {
              do
              {
                     system("cls");
                     puts("     Cafe Metime      ");
                     puts(" ====================\n");
                     puts(" 1. Lihat List Pesanan");
                     puts(" 2. Tambah Pesanan");
                     puts(" 3. Ambil Pesanan");
                     puts(" 4. keluar");
                     printf(" >> Masukkan pilihanmu : ");
                     scanf("%d", &choose); fflush(stdin);
              }
              while(choose < 1 || choose > 4);
             
              system("cls");

              switch(choose)
              {
              case 1:
                     display();
                     break;

              case 2:
                     char type[50];
                     int qty;

                     do
                     {
                           printf(" Masukkan Makanan/Minuman Yang Diinginkan : ");
                           scanf("%[^\n]", type); fflush(stdin);
                     }
                     while(strlen(type) < 3 || strlen(type) > 30);

                     do
                     {
                           printf(" Masukkan Jumlah Pesanan: ");
                           scanf("%d", &qty); fflush(stdin);
                     }
                     while(qty < 1 || qty > 20);
                     printf("Pesanan Berhasil Ditambahkan");
                     push_depan(type, qty);
                     getchar();
                     break;

              case 3:
                     int posisi;
                     int total = display();

                     do
                     {
                           printf("Masukkan Nomor Pesanan: ", total);
                           scanf("%d", &posisi); fflush(stdin);
                     }
                     while(posisi < 1 || posisi > total);

                     curr = head;
                     for(int i = 1 ; i < posisi ; i++)
                     {
                           curr = curr->next;
                     }

                     addOrder();
                     printf("Sukses Mengambil Pesanan");
                     getchar();
                     break;
              }
       }while(choose != 4);
       return 0;
}
