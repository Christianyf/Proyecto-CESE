#include <stdio.h>
#include <sqlite3.h> 
#include <stdlib.h>

//$gcc test.c -l sqlite3 para compilar

typedef struct{
	sqlite3		*db;
	char		*zErrMsg;
	int			rc;
	char		*sql;
	const char	*dato;
}data_db;

data_db base_users;
//char *sql;
//----------------------------------------------------------
void create_db(data_db * data, const char* name);
void create_table(data_db * data,char* sql_dat,const char* name);
void insert_user(data_db * data,char* sql_dat,const char* name);
void print_user(data_db * data,char* sql_dat,const char* name);//es lo mismo que select user
void delete_user(data_db * data,char* sql_dat,const char* name);


static int callback_create_table(void *NotUsed, int argc, char **argv, char **azColName);
static int callback_insert_user(void *NotUsed, int argc, char **argv, char **azColName);
static int callback_print(void *data, int argc, char **argv, char **azColName);
static int callback_delete(void *data, int argc, char **argv, char **azColName);
//----------------------------------------------------------
//-----------------------------------------------------------
const char* name="base_users.db";
const char* dato = "Funcion llamada";

	
char *sql = "CREATE TABLE USER("  \
			"ID INT PRIMARY KEY     NOT NULL," \
			"NOMBRE         TEXT    NOT NULL," \
			"PASSWORD       INT    NOT NULL," \
			"DATA           INT );";
			
char *sql_user = "INSERT INTO USER (ID,NOMBRE,PASSWORD,DATA) "  \
         "VALUES (1, 'Mark', 1234, 1);";
         
char *sql_print_user = "SELECT * from USER";

char  *sql_delete = "DELETE from USER where ID=3; " \
         "SELECT * from USER";
//-----------------------------------------------------------
//-----------------------------------------------------------
int main (int argc, char* argv[])
{
	//create_db(&base_users,name);
	//create_table(&base_users,sql,name);
	//insert_user(&base_users,sql_user,name);
	base_users.dato=dato;
	print_user(&base_users,sql_print_user,name);
	//delete_user(&base_users,sql_delete,name);

return 0;
}
//------------------------------------------------------------
void create_db(data_db * data,const char* name)
{
	data->rc=sqlite3_open(name, &data->db);
	
	if( data->rc )
	{
	      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(data->db));
	      return;
	} 
	else {
      		fprintf(stderr, "Opened database successfully\n");
   	}
   		
   sqlite3_close(data->db);
return;
}
//-----------------------------------------------------------

void create_table(data_db * data,char* sql_dat,const char* name)
{
	//si ya existe la tabla da error
	//debe abrirse primero la db antes de escribir la tabla, luego no olvidar cerrar
	data->rc=sqlite3_open(name, &data->db);
	
	if( data->rc )
	{
	      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(data->db));
	      return;
	} 
	else {
      		fprintf(stderr, "Opened database successfully\n");
   	}
   	
   	
	data->rc = sqlite3_exec(data->db, sql_dat, callback_create_table, 0, &data->zErrMsg);
	
	
   
   if( data->rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", data->zErrMsg);
      sqlite3_free(&data->zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
   sqlite3_close(data->db);
}
//-----------------------------------------------------------

static int callback_create_table(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}
//----------------------------------------------------------
void insert_user(data_db * data,char* sql_dat,const char* name)
{
	//si ya existe el usuario da error
	//debe abrirse primero la db antes de escribir la tabla, luego no olvidar cerrar
	data->rc=sqlite3_open(name, &data->db);
	
	if( data->rc )
	{
	      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(data->db));
	      return;
	} 
	else {
      		fprintf(stderr, "Opened database successfully\n");
   	}
   	
   	data->rc = sqlite3_exec(data->db, sql_dat, callback_insert_user, 0, &data->zErrMsg);
   	
   if( data->rc  != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", data->zErrMsg);
      sqlite3_free(data->zErrMsg);
   } else {
      fprintf(stdout, "Records created successfully\n");
   }
   sqlite3_close(data->db);
	
}
//---------------------------------------------------------
static int callback_insert_user(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}
//---------------------------------------------------------
void print_user(data_db * data,char* sql_dat,const char* name)
{
		data->rc=sqlite3_open(name, &data->db);
	
	if( data->rc )
	{
	      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(data->db));
	      return;
	} 
	else {
      		fprintf(stderr, "Opened database successfully\n");
   	}
   	
   	data->rc = sqlite3_exec(data->db, sql_print_user, callback_print, (void *)data->dato, &data->zErrMsg);
   	
   if( data->rc  != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", data->zErrMsg);
      sqlite3_free(data->zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(data->db);
}
//---------------------------------------------------------
static int callback_print(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   
   for(i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   
   printf("\n");
   return 0;
}
//---------------------------------------------------------
void delete_user(data_db * data,char* sql_dat,const char* name)
{
	//no da error si no hay el elemento
	data->rc=sqlite3_open(name, &data->db);
	
	if( data->rc )
	{
	      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(data->db));
	      return;
	} 
	else {
      		fprintf(stderr, "Opened database successfully\n");
   	}
   	
   	data->rc = sqlite3_exec(data->db, sql_delete, callback_delete, (void *)data->dato, &data->zErrMsg);
   	
   if( data->rc  != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", data->zErrMsg);
      sqlite3_free(data->zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(data->db);
}
//----------------------------------------------------------
static int callback_delete(void *data, int argc, char **argv, char **azColName) {
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

