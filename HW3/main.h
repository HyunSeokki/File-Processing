#include "Member.h"
#include "Lecture.h"
#include "Purchase.h"
#include "recfile.h"
#include "indfile.h"
#include "buffile.h"
#include "tindbuff.h"
#include "textind.h"
#include "btnode.h"
#include "btree.h"
#include "indbuff.h"
#include "indnode.h"
#include "simpind.h"
#include "btree.h"
#include "btree.cpp"
#include "btnode.h"
#include "btnode.cpp"
#include <fstream>

using namespace std;

bool make_flag = false;
Purchase* purchase_arr = new Purchase[1200];
int mem_num = 0, lec_num = 0, pur_num = 0;
const int BTreeSize = 4;
BTree <char> bt(BTreeSize);
char world_key;

void LecturePurchaseSystem();
void Make_indexfile(int, int);
int InsertPurchase(char *RecordId);
int DeleteKey();
int UpdatePurchase();