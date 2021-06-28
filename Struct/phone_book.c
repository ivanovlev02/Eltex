#define N 50

#include <stdio.h>

struct phone_book {
	char first_name[20];
	char last_name[30];
	char number[11];
} pb[N];

int menu();
void add_pb();
void search_pb();
void look_pb();
void delete_pb();

int main(void) {
	
	int count;

	do {
		count = menu();
		switch(count){
			case 1:
				add_pb();
				break;
			case 2: 
				search_pb();
				break;
			case 3:
				look_pb();
				break;
			case 4: 
				delete_pb();
				break;
			default:
				printf("\nGoodBye!\n");
				break;
		}
	} while(count != 5);
	return 0;
}


int menu(){
	int count;
	printf("\n1. Add\n2. Search\n3. Look\n4. Delete\n5. Exit\n");
	scanf("%d", &count);
	return count;
}


void add_pb(void){

	char search[20];
	int t;
	
	printf("\nAdd:\n");
        
	for(t = 0; pb[t].first_name[0] && t < N; ++t);
        
	if(t != N) {
	        printf("\nFirst name: ");
	        fgets(pb[t].first_name, 100, stdin);
	        fgets(pb[t].first_name, 100, stdin);
	        printf("Last name: ");
	        fgets(pb[t].last_name, 100, stdin);
	        printf("Number: ");
	        fgets(pb[t].number, 100, stdin);
	} else {
	        printf("\nThe list's full!\n");
        }
}

void search_pb(void){

	char search[20];
	
	printf("\nPlease enter your first name, last name or phone number:\n");
	fgets(search, 100, stdin);
	fgets(search, 100, stdin);
	
	for(int i = 0; i < N; i++){
		if((strcmp(search, pb[i].first_name) == 0) ||
		   (strcmp(search, pb[i].last_name) == 0) ||
		   (strcmp(search, pb[i].number) == 0)){
			printf("\nFound");
			printf("\nFirst name: %s", pb[i].first_name);
			printf("Last Name: %s", pb[i].last_name);
			printf("Number: %s", pb[i].number);
			printf("\n");
		}
	}
}

void look_pb(void){

	printf("\nContacts added to the phone book:\n");

	for(int t = 0; t < N; ++t){
		if(pb[t].first_name[0]){
			printf("\nFirst name: %s", pb[t].first_name);
			printf("Last name: %s", pb[t].last_name);
			printf("Number: %s", pb[t].number);
			printf("\n");
		}
	}
}

void delete_pb(void){

	char search[20];

	printf("\nPlease enter your first name, last name or phone number:\n");
	fgets(search, 100, stdin);
	fgets(search, 100, stdin);
	
	for(int i = 0; i < N; i++){
		if((strcmp(search, pb[i].first_name) == 0) ||
		   (strcmp(search, pb[i].last_name) == 0) ||
		   (strcmp(search, pb[i].number) == 0)){
			pb[i].first_name[0] = '\0';
			pb[i].last_name[0] = '\0';
			pb[i].number[0] = '\0';
		}
	}
}
