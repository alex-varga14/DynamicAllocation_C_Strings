#include "DynamicCStrings.h"

//Function prototypes
void test_copying(void);
void test_appending(void);
void test_truncating(void);

//Conditional compilation to test each function
int main(void) {
	#if 1
		test_copying();
	#endif
		
	#if 1
		test_truncating();
	#endif
		
	#if 1
		test_appending();
	#endif
    return 0;
}

//Function that dynamically allocates an empty string to heap
void create_empty_string (String *str) {
    
    if(str -> dynamic_storage != NULL)
        free(str -> dynamic_storage);
    
    str -> dynamic_storage = malloc (sizeof(char) * 1);
    if(str ->dynamic_storage == NULL) {
        printf("malloc failed ...\n");
        exit(1);
    }
    
    str -> dynamic_storage[0] = '\0';
    str -> length = 0;
}

//two different methods in twofunctions to dynamically copy strings
void String_cpy(String *dest, const char* source) {
    
    if(dest -> dynamic_storage != NULL){
        free(dest->dynamic_storage);
        dest ->dynamic_storage = NULL;
    }
    
    if(source != NULL || source [0] != '\0' ) {
        // allocate storate space equal to length of source plus one for '\0'
        dest -> dynamic_storage = malloc(strlen(source)+1);
        if(dest -> dynamic_storage == NULL){
            printf("malloc failed: Memory was unavailable...\n");
            exit(1);
        }
        
        strcpy(dest -> dynamic_storage , source);
        dest -> length = (int)strlen(source);
    }
}

void String_copy(String *dest, const String* source) {
    if(dest -> dynamic_storage != NULL){
        free(dest->dynamic_storage);
        dest->dynamic_storage = NULL;
    }
    
    if(source ->dynamic_storage != NULL) {
        // allocate storate space equal to length of source plus one for '\0'
        dest -> dynamic_storage = malloc(strlen(source->dynamic_storage)+1);
        if(dest -> dynamic_storage == NULL){
            printf("malloc failed: Memory was unavailable...\n");
            exit(1);
        }
        
        strcpy(dest -> dynamic_storage , source ->dynamic_storage);
        dest -> length = source -> length;
    }
}

//Function to display string to terminal
void display_String(const String* s){
    if(s -> length > 0)
        printf("%s      %zu\n", s->dynamic_storage, s -> length);
    else
        printf("%s      %zu\n", "String is empty", s -> length);
}

//Function to append to string on heap
void String_append(String *dest, const String* source){
    if(source->dynamic_storage == NULL ||dest->dynamic_storage == NULL) // checks if either string is empty
		return;
	unsigned long int newlength = dest -> length + source -> length; // new length of appended memory
	char * newstorage =  malloc (newlength+1); //creating new memory allocation to store values
	if (newstorage == NULL){// checks for proper construction of newstorage
		printf("Memory not available...");
		exit(1);
	}
	strcpy(newstorage, dest->dynamic_storage); // copies values of dest into newstorage
	strcat(newstorage, source->dynamic_storage);//appends values of source to newstorage
	
	if(dest->dynamic_storage != NULL){ // checks if dest->dynamic_storage is NULL and if not it frees all memory
		free(dest->dynamic_storage);
	}
	dest->dynamic_storage = newstorage; // assigns memory of newstorage with new length to dest->dynamic_storage
	dest->length = newlength; // assigns new length of newstorage to dest->length
}

//Function to truncate to string on heap
void String_truncate(String *dest, int new_length){
    assert(new_length >= 0);
	if(dest->length <= new_length){ // checks if new length is equal or less to old length
		return;
	}
	char * newstorage = malloc(new_length+1); // creating new memory allocation to store values of dest wihtin new_length
	if(newstorage == NULL){ // checks for proper construction of newstorage
		printf("Malloc has failed to allocate memory...");
		exit(1);
	}
	int i;
	for(i = 0; i < new_length; i++){ // loops through dest.dynamic_storage values and assigns them into the newstorage elements according to new length
		newstorage[i] = dest->dynamic_storage[i];
	}
	newstorage[i] = '\0'; 
	
	if(dest->dynamic_storage != NULL){ // checks if dest->dynamic_storage is NULL and if not it frees all memory
		free(dest->dynamic_storage);
	}
	dest->dynamic_storage = newstorage; // assigns memory of newstorage with new length to dest->dynamic_storage
	dest->length = new_length; // assigns new length of newstorage to dest->length			
}

//Test the copy function
void test_copying(void){
    printf("\nTesting String_cpy and String_copy started: \n");
    
    String st1 = {NULL, 0};
    String st2 = {NULL, 0};
    String st3 = {NULL, 0};
    String st4 = {NULL, 0};
    
    // The following four lines creates instances of STring with valid
    // c-strings of length zero. Means it allocates one element for the
    //dynamic_storage and initializes that element with '\0'.
    create_empty_string(&st1);
    create_empty_string(&st2);
    create_empty_string(&st3);
    create_empty_string(&st4);
    
    display_String(&st1);     // displays: String is empty      0
    display_String(&st2);     // displays: String is empty      0
    display_String(&st3);     // displays: String is empty      0
    display_String(&st4);     // displays: String is empty      0
    
    //copies "William Shakespeare" int the string_stirage in object st1
    String_cpy(&st1, "William Shakespeare");
    display_String(&st1);
    
    String_cpy(&st2, "Aaron was Here!!!!");
    display_String(&st2);
    
    String_cpy(&st3, "But now he is in Italy");
    display_String(&st3);
    
    String_copy(&st1, &st4);
    display_String(&st1);
    
    String_cpy(&st2, "");
    display_String(&st2);
    
    String_copy(&st2, &st3);
    display_String(&st2);
    
    create_empty_string(&st2);
    display_String(&st1);
    
    printf("\nTesting String_cpy and String_copy finished...\n");
    printf("------------------------------------------------------------\n");
}

//Test the append function
void test_appending(void) {
    printf("\nTesting String_append started: \n");
    
    String st1 = {NULL, 0};
    String st2 = {NULL, 0};
    String st3 = {NULL, 0};
    String st4 = {NULL, 0};
    
    create_empty_string(&st1); // creates an empty object with a valid c-string
    create_empty_string(&st2); // creates an empty object with a valid c-string
    create_empty_string(&st3); // creates an empty object with a valid c-string
    create_empty_string(&st4); // creates an empty object with a valid c-string
    
    String_cpy(&st1, "Aaron was Here. ");
    display_String(&st1);
    
    String_cpy(&st2, "He left a few minutes ago.");
    display_String(&st2);
    
    String_append(&st4, &st3);
    display_String(&st4);
    
    String_append(&st1, &st2);
    display_String(&st1);
    
    create_empty_string(&st1);
    display_String(&st1);
    
    String_cpy(&st1, "GET THE BALL ROLLING");
    display_String(&st1);
    
    String_cpy(&st2, "!");
    String_append(&st1, &st2);
    display_String(&st1);
    
    String_append(&st1, &st4);
    display_String(&st1);
    
    printf("\nTesting String_append finished...\n");
    printf("------------------------------------------------------------\n");
}

//Test the truncate function
void test_truncating (void) {
    printf("\nTesting String_truncate started: \n");
    
    String st1 = {NULL, 0};
    String_cpy(&st1, "Computer Engineering.");
    display_String(&st1);
    
    String_truncate(&st1, 8);
    display_String(&st1);
    
    String_truncate(&st1, 3);
    display_String(&st1);
    
    String_truncate(&st1, 7);
    display_String(&st1);
    
    String_truncate(&st1, 1);
    display_String(&st1);
    
    String_truncate(&st1, 0);
    display_String(&st1);
    
    String_cpy(&st1, "Truncate done Successfully.");
    display_String(&st1);
    
    printf("\nTesting String_truncate finished... \n");
    printf("------------------------------------------------------------\n");
}