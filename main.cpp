#include <QCoreApplication>
#include <QDebug>
//    QStringList list;
//    list << "field1|9" << "field2|9(005)" << "field3|9(006)" << "field4|9(008)" << "field5|9(01)" << "field6|9(02)" << "field7|9(02)V9(02)" << "field8|9(03)" << "field9|9(03)V99" << "field10|9(04)" << "field11|9(04)V99" << "field12|9(05)" << "field13|9(06)" << "field14|9(07)" << "field15|9(08)" << "field16|9(08)V999" << "field17|9(09)" << "field18|9(1)" << "field19|9(10)" << "field20|9(12)" << "field21|9(2)" << "field22|9(3)" << "field23|9(3)V9(2)" << "field24|9(3)V9(4)" << "field25|9(4)" << "field26|9(4)V9(2)" << "field27|9(4)V99" << "field28|9(5)" << "field29|9(5)V9(3)" << "field30|9(6)" << "field31|9(7)V999" << "field32|9(8)" << "field33|99" << "field34|9999" << "field35|99V99" << "field36|99V9999" << "field37|99V999999" << "field38|S999V99" << "field39|X" << "field40|X(01)" << "field41|X(02)" << "field42|X(026)" << "field43|X(029)" << "field44|X(03)" << "field45|X(04)" << "field46|X(05)" << "field47|X(06)" << "field48|X(066)" << "field49|X(07)" << "field50|X(08)" << "field51|X(09)" << "field52|X(092)" << "field53|X(1)" << "field54|X(10)" << "field55|X(102)" << "field56|X(103)" << "field57|X(106)" << "field58|X(107)" << "field59|X(11)" << "field60|X(111)" << "field61|X(113)" << "field62|X(116)" << "field63|X(12)" << "field64|X(120)" << "field65|X(123)" << "field66|X(124)" << "field67|X(13)" << "field68|X(14)" << "field69|X(15)" << "field70|X(16)" << "field71|X(17)" << "field72|X(18)" << "field73|X(19)" << "field74|X(2)" << "field75|X(20)" << "field76|X(21)" << "field77|X(23)" << "field78|X(24)" << "field79|X(25)" << "field80|X(26)" << "field81|X(27)" << "field82|X(28)" << "field83|X(29)" << "field84|X(3)" << "field85|X(30)" << "field86|X(32)" << "field87|X(33)" << "field88|X(34)" << "field89|X(35)" << "field90|X(36)" << "field91|X(37)" << "field92|X(38)" << "field93|X(39)" << "field94|X(4)" << "field95|X(40)" << "field96|X(42)" << "field97|X(43)" << "field98|X(44)" << "field99|X(45)" << "field100|X(46)" << "field101|X(48)" << "field102|X(49)" << "field103|X(50)" << "field104|X(51)" << "field105|X(53)" << "field106|X(54)" << "field107|X(56)" << "field108|X(6)" << "field109|X(60)" << "field110|X(63)" << "field111|X(64)" << "field112|X(68)" << "field113|X(69)" << "field114|X(71)" << "field115|X(72)" << "field116|X(74)" << "field117|X(75)" << "field118|X(77)" << "field119|X(78)" << "field120|X(8)" << "field121|X(80)" << "field122|X(86)" << "field123|X(87)" << "field124|X(89)" << "field125|X(92)" << "field126|X(96)" << "field127|X(97)" << "field128|X(99)" << "field129|XXXX";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char *str_replace(char *orig, char *rep, char *with);
char** str_split(char* a_str, const char a_delim);
void printSplit(char *str, char *delim, char* result[]);

struct record
{
   unsigned short id;
   char data_type[15];
   unsigned short integer_length;
   unsigned short decimal_length;
};

int main(int argc, char *argv[])
{  QCoreApplication a(argc, argv);


    const unsigned short SIZE = 129;
    struct record records[SIZE];

    char *data[] = {"field1|9","field2|9(005)","field3|9(006)","field4|9(008)","field5|9(01)","field6|9(02)","field7|9(02)V9(02)","field8|9(03)","field9|9(03)V99","field10|9(04)","field11|9(04)V99","field12|9(05)","field13|9(06)","field14|9(07)","field15|9(08)","field16|9(08)V999","field17|9(09)","field18|9(1)","field19|9(10)","field20|9(12)","field21|9(2)","field22|9(3)","field23|9(3)V9(2)","field24|9(3)V9(4)","field25|9(4)","field26|9(4)V9(2)","field27|9(4)V99","field28|9(5)","field29|9(5)V9(3)","field30|9(6)","field31|9(7)V999","field32|9(8)","field33|99","field34|9999","field35|99V99","field36|99V9999","field37|99V999999","field38|S999V99","field39|X","field40|X(01)","field41|X(02)","field42|X(026)","field43|X(029)","field44|X(03)","field45|X(04)","field46|X(05)","field47|X(06)","field48|X(066)","field49|X(07)","field50|X(08)","field51|X(09)","field52|X(092)","field53|X(1)","field54|X(10)","field55|X(102)","field56|X(103)","field57|X(106)","field58|X(107)","field59|X(11)","field60|X(111)","field61|X(113)","field62|X(116)","field63|X(12)","field64|X(120)","field65|X(123)","field66|X(124)","field67|X(13)","field68|X(14)","field69|X(15)","field70|X(16)","field71|X(17)","field72|X(18)","field73|X(19)","field74|X(2)","field75|X(20)","field76|X(21)","field77|X(23)","field78|X(24)","field79|X(25)","field80|X(26)","field81|X(27)","field82|X(28)","field83|X(29)","field84|X(3)","field85|X(30)","field86|X(32)","field87|X(33)","field88|X(34)","field89|X(35)","field90|X(36)","field91|X(37)","field92|X(38)","field93|X(39)","field94|X(4)","field95|X(40)","field96|X(42)","field97|X(43)","field98|X(44)","field99|X(45)","field100|X(46)","field101|X(48)","field102|X(49)","field103|X(50)","field104|X(51)","field105|X(53)","field106|X(54)","field107|X(56)","field108|X(6)","field109|X(60)","field110|X(63)","field111|X(64)","field112|X(68)","field113|X(69)","field114|X(71)","field115|X(72)","field116|X(74)","field117|X(75)","field118|X(77)","field119|X(78)","field120|X(8)","field121|X(80)","field122|X(86)","field123|X(87)","field124|X(89)","field125|X(92)","field126|X(96)","field127|X(97)","field128|X(99)","field129|XXXX"};

    unsigned short i;

    char str[] = "strtok needs|to be called several times to split a string";
    char delim[] = "|";

    char *split_data[2];
    printSplit(str, delim, split_data);

    qDebug() << "string 1: "<< split_data[0] <<endl;

    for(i = 0; i < SIZE; i++){

//        records[i].id =

//        char ** split = str_split(data[i], '|');
//        qDebug() << "string 1: "<< split[0] <<endl;
//        qDebug() << "string 2: "<< split[1] <<endl;
//        qDebug() <<endl << endl;

//        QString s = str_replace(data[i], "field1", "--");
//        qDebug() << "string: "<< s <<endl;

//        printf("%d record:  %s\n", i,data[i]);
    }
    return a.exec();
}


char *str_replace(char *orig, char *rep, char *with) {
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

void printSplit(char *str, char *delim, char* result[]){

        int init_size = strlen(str);

        unsigned int i = 0;

        char *ptr = strtok(str, delim);
        result[i] = ptr;
        i++;
        while(ptr != NULL)
        {
            printf("'%s'\n", ptr);
            ptr = strtok(NULL, delim);
            if(i < 2){
                result[i] = ptr;
            }
            i++;


        }
        /* This loop will show that there are zeroes in the str after tokenizing */
//        for (int i = 0; i < init_size; i++)
//        {
//            printf("%d ", str[i]); /* Convert the character to integer, in this case
//                                   the character's ASCII equivalent */
//        }

}
char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = (char **)(malloc(sizeof(char*) * count));

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}





