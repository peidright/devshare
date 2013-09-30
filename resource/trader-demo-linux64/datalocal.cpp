#include "datalocal.h"
#include "sqlite3.h"
#include "config.h"
#include "assert.h"

string g_db_name="local.sdb";

int callback(void *,int count, char **row,char **titles)
{
	for(int i=0;i<count;i++){
		cout<<"title= "<<titles[i]<<"value= "<<row[i]<<endl;
	}
	return 0;
}
datalocal::datalocal()
{
	int ret;
	char                  *error = 0;
	ret = sqlite3_open(g_db_name.c_str(), &this->db); 
	if(ret==-1) {
		cout<<"localdb create error"<<endl; 
	} else {
		cout<<"localdb init ok"<<endl;
	}

	ret = sqlite3_exec(this->db, "drop  table trader", 0,0, &error );
	ret = sqlite3_exec(this->db, "create table trader(username char(32), password char(32))", 0,0, &error );
	//assert(ret==0);
	if(ret!=SQLITE_OK) {
		printf("%s\n",error);
	}

	ret=sqlite3_exec(this->db,"insert into trader values ('aaa','bbb')",callback,NULL,&error);
	ret=sqlite3_exec(this->db,"select * from trader",callback,NULL,&error);
	assert(ret== SQLITE_OK);
	sqlite3_close(this->db);
}