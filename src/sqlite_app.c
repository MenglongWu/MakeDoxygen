#include <stdio.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  printf("count = %d\n",argc);
  for(i=0; i<argc; i++){ 
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

int main(int argc, char **argv){
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

  if( argc!=3 ){
    fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT\n", argv[0]);
    return -1;
  }
  rc = sqlite3_open(argv[1], &db);
  if( rc ){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return -1;
  }
  rc = sqlite3_exec(db, argv[2], callback, 0, &zErrMsg);

  if( rc!=SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }

  int index;
  char **dbResult;
  int nRow,nColumn;
  char *errMsg = NULL;
  int result;

  result = sqlite3_get_table(db,argv[2], &dbResult, &nRow, &nColumn, &errMsg);
  if( SQLITE_OK == result ) {
    printf("row %d col %d\n", nRow, nColumn);

    printf("0 ----: %s\n", dbResult[0]);
    index = nColumn; //前面说过 dbResult 前面第一行数据是字段名称，从 nColumn 索引开始才是真正的数据

    printf( "查到%d条记录\n", nRow );

    for(  int i = 0; i < nRow ; i++ )

    {

      printf( "第 %d 条记录\n", i+1 ); 

      for( int j = 0 ; j < nColumn; j++ )

      {

             printf( "index %d 字段名:%s   ß> 字段值:%s\n", index,  dbResult[j], dbResult [index] );

             ++index; // dbResult 的字段值是连续的，从第0索引到第 nColumn - 1索引都是字段名称，从第 nColumn 索引开始，后面都是字段值，它把一个二维的表（传统的行列表示法）用一个扁平的形式来表示

      }

      printf( "-------\n" );

    }

  }



  sqlite3_close(db);
  return 0;
}
