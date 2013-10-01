#include "datalocal.h"
#include "sqlite3.h"
#include "config.h"
#include "assert.h"
#include <map>
#include <vector>
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

	ret=sqlite3_exec(this->db, "drop table instrument",0,0,&error);
	ret=sqlite3_exec(this->db,"create table instrument(name char(32), product char(32), status  interger ,ctime integer)",0,0,&error);
	if(ret!=SQLITE_OK) {
		printf("%s\n",error);
	}
	assert(ret==SQLITE_OK);
	ret=sqlite3_exec(this->db, "insert into instrument values('cu1401','cu',1,1380629713)",0,0,&error);
	//ret=sqlite3_exec(this->db,"drop table ",0,0,&error);
	//sqlite3_close(this->db);
}

int get_product_callback(void *arg,int count, char **row,char **titles)
{
	for(int i=0;i<count;i++){
		cout<<"title= "<<titles[i]<<"value= "<<row[i]<<endl;
	}
	return 0;
}
int general_callback(void *arg, int count, char **row, char **titles)
{
	vector< map<string,string> > *v=(vector< map<string,string> > *)arg;
	map<string,string> m;

	for(int i=0;i<count;i++){
		cout<<"title= "<<titles[i]<<"value= "<<row[i]<<endl;
		m[titles[i]]=row[i];
	}
	v->push_back(m);
	return 0;
}

void datalocal:: get_product_list(vector<string> *product_list)
{
	int ret;
	char                  *error = 0;
	vector< map<string,string> > rows;
	vector< map<string,string> >::iterator rows_it;
	ret=sqlite3_exec(this->db,"select name, product, status,ctime from instrument",general_callback,&rows,&error);
	for(rows_it=rows.begin();rows_it!=rows.end();rows_it++) {
		(*rows_it)["name"];
		product_list->push_back((*rows_it)["name"]);
	}
}



datalocal::~datalocal()
{
	sqlite3_close(this->db);
	this->db=NULL;
}


