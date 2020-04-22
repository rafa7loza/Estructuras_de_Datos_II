#define FILL_SIZE 30
#define FIELD_SIZE_A 13
#define FIELD_SIZE_B 12
#define NUM_SIZE 5
#define TIME_FORMAT_SIZE 8
#define BUFFER 80

#define REGISTER_SIZE 64

#define NEW_REGISTER '1'
#define READ_FROM_FILE '2'
#define EXIT '7'
#define FIND '3'
#define SHOW_KEYS '4'
#define FIND_BY_SECONDARY '5'
#define SHOW_SECONDARY_INDEX '6'

#define FIND_NAME '1'
#define FIND_CITY '2'
#define FIND_NATIONALITY '3'


#define PRINT_INDEX 'p'
#define FILL_CHAR '*'

#define INDEX_SIZE 100
#define INDEX_REGISTER 16

#define SECONDARY_INDEX_REGISTER (FIELD_SIZE_A+sizeof(int))

#define EXTENSION ".dat"

#define NAME "_sk_name"
#define CITY "_sk_city"
#define NATIONALITY "_sk_nationality"

#define debug(str) printf("Debug: ** %s **\n", str)
#define clean while ((getchar()) != '\n')

/**

1
nombre 1
domicilio 1
ciudad 1
mexicano 1
1:11:11

2
nombre 2
domicilio 2
ciudad 2
mexicano 2
2:22:22

13
nombre 13
domicilio 13
ciudad 13
mexicano 13
0:00:00

4
nombre 4
domicilio 4
ciudad 4
mexicano 4
0:00:00

14
nombre 14
domicilio 14
ciudad 14
mexicano 14
0:00:00



0101
Juan
olimpica 45
Guadalajara
mexicano
0:49:00

1010
Alonso
Revolucion 200
Zapopan
Aleman
1:00:20

0300
Pedro
Olimpica 21
Guadalajara
mexicano
0:56:00

*/
