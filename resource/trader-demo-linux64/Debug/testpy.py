import sys
import sqlite3
import time
sys.path.append('./');
print ("ggggg");
if 1==1:
    print ("i fuck you");
db = sqlite3.connect('local.sdb',uri=True);
cu=db.cursor();
cu.execute("select * from  instrument"); 
print( cu.fetchall()); 
time.sleep(10);
cu.execute("select * from  instrument"); 
print( cu.fetchall()); 
