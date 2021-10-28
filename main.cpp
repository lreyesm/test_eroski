//////////////////////////////////// Includes section /////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
///////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////// Types definitions ////////////////////////////////////////////
typedef enum {NUMERIC = 1, DECIMAL, ALPHA_NUMERIC} DataType;
typedef struct record
{
    unsigned short id = 0;
    DataType data_type = NUMERIC;
    unsigned short integer_length = 0;
    unsigned short decimal_length = 0;
} RecordType;
///////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////// Function prototypes //////////////////////////////////////////
void            menu(void);
void            choice1(RecordType *, unsigned short);
void            choice2(RecordType *, unsigned short);
void            choice3(RecordType *, unsigned short);
void            choice4(RecordType *, unsigned short);
char            *str_replace(char *orig, char *rep, char *with, unsigned int *count_matches);
void            str_split(char *str, char *delim, char* result[]);
void            printRecord(struct record record);
unsigned int    getIntLength(char *str);
unsigned int    getFloatLength(char *str);
unsigned int    getStringLength(char *str);
void            sortByType(RecordType *records, unsigned short size);
void            sortByIntegerLength(RecordType *records, unsigned short size);
void            sortByFloatingLength(RecordType *records, unsigned short size);
////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////// Global variables //////////////////////////////////////////////
unsigned char choice = 0;
////////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * @brief brief description 
 * Main function loads file in the root directory of the Project,
 * parses its content and saves the data in array of records, then
 * waits for the user input selection
 * @return {int}  : Returns 0
 */
int main()
{
    FILE *in_file  = fopen("data.txt", "r");
    // test for files not existing.
    if (in_file == NULL)
    {
        printf("Error! Could"
                ""
                " not open file\n");
        exit(-1); // must include stdlib.h
    }
    else{
        //File opened successfully
        unsigned int index = 0;
        char *s;
        char **data = NULL;
        data = (char**)malloc(sizeof(char*) * 100);
        while(fscanf(in_file,"%s", s) != EOF)
        {
//            if(s){
                data[index] = (char *)(malloc((strlen(s) + 1)*sizeof (char*)));
                strcpy(data[index], s);
                index++;
                data = (char**)(realloc(data, (index+1)*sizeof(*data)));
//            }
        }
        fclose(in_file);

        unsigned short i = 0;
        const unsigned short SIZE = index; //129 original size
        RecordType *records = (struct record *)(malloc((SIZE)*sizeof (struct record)));
        for(i = 0; i < SIZE; i++){
            if (strstr(data[i], "|") != NULL) { //Checks if the string contains the split pattern
                char * str = (char *)(malloc(strlen(data[i]) + 1));
                strcpy(str, data[i]);
                char delim[] = "|";
                char *split_data[2];
                unsigned int matches = 0;
                str_split(str, delim, split_data);
                char *s_id = split_data[0];
                char *s_data = split_data[1];
                if (strstr(s_id, "field") != NULL) {
                    s_id = str_replace(split_data[0], "field", "", &matches);
                }
                int num = (int) strtol(s_id, (char **)NULL, 10);  //Convert to int
                records[i].id = num;
                if(strstr(s_data, "X") != NULL){ //String type
                    records[i].data_type = ALPHA_NUMERIC;
                    unsigned int size = getStringLength(s_data);
                }
                else if(strstr(s_data, "V") != NULL){ //String type
                    records[i].data_type = DECIMAL;
                    unsigned int size = getIntLength(s_data);
                    records[i].integer_length = size;
                    unsigned int matches = 0;
                    s_data = str_replace(s_data, "9", "", &matches);
                    size = getFloatLength(s_data);
                    records[i].decimal_length = size;
                }
                else if(strstr(s_data, "9") != NULL){
                    records[i].data_type = NUMERIC;
                    unsigned int size = getIntLength(s_data);
                    records[i].integer_length = size;
                }
                free(str);
            }
        }
        free(data);

        while (choice != '5'){
            menu();
            if (choice =='0')
                continue;
            else if (choice =='1'){
                choice = 0;
                choice1(records, SIZE);
            }
            else if (choice =='2'){
                choice = 0;
                choice2(records, SIZE);
            }
            else if (choice =='3'){
                choice = 0;
                choice3(records, SIZE);
            }
            else if (choice =='4'){
                choice = 0;
                choice4(records, SIZE);
            }
            else if (choice =='5')
                break;
            else{
                if(choice != '\n'){
                    printf("Invalid character.\n\n", choice);
                }
            }
        };
    }
    exit(-1);
    return 0;
}
    

//////////////////////////////////// Function implementations //////////////////////////////////////
/**
 * @brief brief description 
 * Received records and prints the array
 * @param  {RecordType*} records : Pointer to the records to print
 * @param  {unsigned} short      : The size of the array of records
 */
void choice1(RecordType * records, unsigned short size){
    unsigned short i = 0;
    for(i = 0; i < size; i++){
        printRecord(records[i]);
    }
}
/**
 * @brief brief description
 * Received records, they are ordered by type and then prints them
 * @param  {RecordType*} records : Pointer to the records to print
 * @param  {unsigned} short      : The size of the array of records
 */
void choice2(RecordType * records, unsigned short size){
    sortByType(records, size);
    unsigned short i = 0;
    for(i = 0; i < size; i++){
        printRecord(records[i]);
    }
}
/**
 * @brief brief description
 * Received records, they are ordered by its integer's length and then prints them
 * @param  {RecordType*} records : Pointer to the records to print
 * @param  {unsigned} short      : The size of the array of records
 */
void choice3(RecordType * records, unsigned short size){
    sortByIntegerLength(records, size);
    unsigned short i = 0;
    for(i = 0; i < size; i++){
        printRecord(records[i]);
    }
}
/**
 * @brief brief description
 * Received records, they are ordered by its decimal's length and then prints them
 * @param  {RecordType*} records : Pointer to the records to print
 * @param  {unsigned} short      : The size of the array of records
 */
void choice4(RecordType * records, unsigned short size){
    sortByFloatingLength(records, size);
    unsigned short i = 0;
    for(i = 0; i < size; i++){
        printRecord(records[i]);
    }
}
/**
 * @brief brief description
 * Shows a menu and waits for the selection of the user
 * @param  {void} undefined : Receives nothing
 */
void menu(void) {
    if(choice != '\n'){
        printf("\nMenu:\n\n");
        printf("1) Print the content of the file.\n");
        printf("2) Print ordered by (NUMERIC, DECIMAL, ALPHANUMERIC).\n");
        printf("3) Print ordered by integer size.\n");
        printf("4) Print ordered by decimal size.\n");
        printf("Choose any of the above, or enter 5 to quit.\n\n");
    }
    scanf("%c", &choice);
}
/**
 * @brief brief description
 * This function sorts the array of records by type of data
 * @param  {unsigned} short : The size of the array of records
 * @param  {struct*} record : Pointer to records to sort
 */
void sortByType(RecordType *records, unsigned short size){
    unsigned short i, j;
    for(i = 0; i < size - 1; i++){
        for(j = 0; j < size - i - 1; j++){
            struct record tempRecord;
            if (records[j].data_type > records[j+1].data_type) //Increasing order
            {
                tempRecord = records[j];
                records[j]   = records[j+1];
                records[j+1] = tempRecord;
            }
        }
    }
}
/**
 * @brief brief description
 * This function sorts the array of records by its integer's length
 * @param  {struct*} record : The size of the array of records
 * @param  {unsigned} short : Pointer to records to sort
 */
void sortByIntegerLength(RecordType *records, unsigned short size){
    unsigned short i, j;
    for(i = 0; i < size - 1; i++){
        for(j = 0; j < size - i - 1; j++){
            struct record tempRecord;
            if (records[j].integer_length > records[j+1].integer_length) //Increasing order
            {
                tempRecord = records[j];
                records[j]   = records[j+1];
                records[j+1] = tempRecord;
            }
        }
    }
}
/**
 * @brief brief description
 * This function sorts the array of records by its decimal's length
 * @param  {struct*} record : The size of the array of records
 * @param  {unsigned} short : Pointer to records to sort
 */
void sortByFloatingLength(RecordType *records, unsigned short size){
    unsigned short i, j;
    for(i = 0; i < size - 1; i++){
        for(j = 0; j < size - i - 1; j++){
            struct record tempRecord;
            if (records[j].decimal_length > records[j+1].decimal_length) //Increasing order
            {
                tempRecord = records[j];
                records[j]   = records[j+1];
                records[j+1] = tempRecord;
            }
        }
    }
}
/**
 * @brief brief description
 * This function received string and gets the amount of the integers
 * @param  {char*} str_original : Pointer to the string
 * @return {unsigned}           : Returns the amount of the integers
 */
unsigned int getIntLength(char *str_original){
    unsigned int size = 0;
    char * str = (char *)(malloc(strlen(str_original) + 1));
    strcpy(str, str_original);
    if(str && strstr(str, "9(") != NULL){
        char *split_data[2];
        str_split(str, "9(", split_data);
        if(split_data[1] && strstr(split_data[1], ")") != NULL){
            str_split(split_data[1], ")", split_data);
            char *s_amount = split_data[0];
            size = (int) strtol(s_amount, (char **)NULL, 10);
        }
        if(split_data[0] && strstr(split_data[0], ")") != NULL){
            str_split(split_data[0], ")", split_data);
            char *s_amount = split_data[0];
            size = (int) strtol(s_amount, (char **)NULL, 10);
        }
    }
    else{
        while (str && strstr(str, "9") != NULL) {
            unsigned int matches = 0;
            str = str_replace(str, "9", "", &matches);
            size = matches;
        }
    }
    free(str);
    return size;
}
/**
 * @brief brief description
 * This function received string and gets the amount of the decimals
 * @param  {char*} str_original : Pointer to the string
 * @return {unsigned}           : Returns the amount of the integers
 */
unsigned int getFloatLength(char *str_original){
    unsigned int size = 0;
    char * str = (char *)(malloc(strlen(str_original) + 1));
    strcpy(str, str_original);
    if(str && strstr(str, "V(") != NULL){
        char *split_data[2];
        str_split(str, "V(", split_data);
        if(split_data[1] && strstr(split_data[1], ")") != NULL){
            str_split(split_data[1], ")", split_data);
            char *s_amount = split_data[0];
            size = (int) strtol(s_amount, (char **)NULL, 10);
        }
        if(split_data[0] && strstr(split_data[0], ")") != NULL){
            str_split(split_data[0], ")", split_data);
            char *s_amount = split_data[0];
            size = (int) strtol(s_amount, (char **)NULL, 10);
        }
    }
    else{
        while (str && strstr(str, "V") != NULL) {
            unsigned int matches = 0;
            str = str_replace(str, "V", "", &matches);
            size = matches;
        }
    }
    free(str);
    return size;
}
/**
 * @brief brief description
 * This function received string and gets the amount of the alphanumeric characters
 * @param  {char*} str_original : Pointer to the string
 * @return {unsigned}           : Returns the amount of the integers
 */
unsigned int getStringLength(char *str_original){
    unsigned int size = 0;
    char * str = (char *)(malloc(strlen(str_original) + 1));
    strcpy(str, str_original);
    if(str && strstr(str, "X(") != NULL){
        char *split_data[2];
        str_split(str, "X(", split_data);
        if(split_data[1] && strstr(split_data[1], ")") != NULL){
            str_split(split_data[1], ")", split_data);
            char *s_amount = split_data[0];
            size = (int) strtol(s_amount, (char **)NULL, 10);
        }
        if(split_data[0] && strstr(split_data[0], ")") != NULL){
            str_split(split_data[0], ")", split_data);
            char *s_amount = split_data[0];
            size = (int) strtol(s_amount, (char **)NULL, 10);
        }
    }
    else{
        while (str && strstr(str, "X") != NULL) {
            unsigned int matches = 0;
            str = str_replace(str, "X", "", &matches);
            size = matches;
        }
    }
    free(str);
    return size;
}
/**
 * @brief brief description
 * This function receives a record type and prints it
 * @param  {struct} record : Record type to print
 */
void printRecord(RecordType record){
    printf("\nRecord\n");
    printf("id             : %d\n", record.id);
    printf("data_type      : %s\n", (record.data_type==NUMERIC)?
                "NUMERIC":(record.data_type==DECIMAL)?
                    "DECIMAL":(record.data_type==ALPHA_NUMERIC)?
                        "ALPHA_NUMERIC": "unknow");
    printf("integer_length : %d\n", record.integer_length);
    printf("decimal_length : %d\n\n", record.decimal_length);
}
/**
 * @brief brief description
 * This function replaces a pattern on the original string with a replacement string
 * and count the amount of matches in the original string
 * @param  {char*} orig    : Pointer to the original string
 * @param  {char*} rep     : Pointer to the string to replace
 * @param  {char*} with    : Pointer to the replacement string
 * @param  {unsigned*} int : Pointer to the amount of matches
 */
char *str_replace(char *orig, char *rep, char *with, unsigned int *count_matches) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements
    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);
    // count the number of replacements needed
    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }
    *count_matches = count;
    tmp = result = (char *)(malloc(strlen(orig) + (len_with - len_rep) * count + 1));
    if (!result)
        return NULL;
    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}
/**
 * @brief brief description
 * This function splits the string in two parts
 * @param  {char*} str       : Pointer to the string to split
 * @param  {char*} delim     : Pointer to the string splitter pattern
 * @param  {char* []} result : Pointer to the string array splitted parts 
 */
void str_split(char *str, char *delim, char* result[]){
    //        int init_size = strlen(str);
    unsigned int i = 0;
    char *ptr = strtok(str, delim);
    result[i] = ptr;
    i++;
    while(ptr != NULL)
    {
        ptr = strtok(NULL, delim);
        if(i < 2){
            result[i] = ptr;
        }
        i++;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////





