#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    char phone_number[50];
    char email[50];
} User;

int main() {
    User* user_ptr_list[100];
    FILE *fp = NULL;

    fp = fopen("data.dat", "r");
    if (fp == NULL) {
        return 1;
    }

    User* user = NULL;
    int i = 0;
    while ((user = (User*)malloc(sizeof(User))) && (fscanf(fp,"%s %s %s\n", user->name, user->phone_number, user->email) != EOF))
    {
        printf("in while %s %s %s\n", user->name, user->phone_number, user->email); 
        user_ptr_list[i] = user;
        i++;
    }

    fclose(fp);

    fp = fopen("data.dat", "w");

    printf("random after w: %s %s %s\n", user_ptr_list[0]->name, user_ptr_list[0]->phone_number, user_ptr_list[0]->email); 

    User *newUser= (User*)malloc(sizeof(User));   
    strcpy(newUser->name, "7");  
    strcpy(newUser->phone_number, "8");  
    strcpy(newUser->email, "9");
    printf("insert newUser: %s %s %s\n", newUser->name, newUser->phone_number, newUser->email); 

    user_ptr_list[i] = newUser;
    i += 1;

    int j = 0;
    for (int j = 0; j < i; j++) {
        fprintf(fp, "%s %s %s\n", user_ptr_list[j]->name, user_ptr_list[j]->phone_number, user_ptr_list[j]->email);
    }

    fclose(fp);

    system("pause");
    return 0;
}
 