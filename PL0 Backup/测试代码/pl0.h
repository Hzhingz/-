                         /*PL/0 编译系统C版本头文件 pl0.h*/
//*******************
//此范围为修改的地方
//*******************

//*************************************
# define norw 26		//关键字增加
//*************************************

# define txmax 100               /*名字表容量*/
# define nmax  14                /*number的最大位数*/
# define al 10                   /*符号的最大长度*/
# define amax 2047               /*地址上界*/
# define levmax 3                /*最大允许过程嵌套声明层数[0，lexmax]*/
# define cxmax 500               /*最多的虚拟机代码数*/
/*符号*/
enum symbol{
nul,    ident,     number,     plus,     minus,
times,   slash,   oddsym,   eql,     neq,
lss,     leq,      gtr,     geq,     lparen,
rparen,  comma,   semicolon,period,  becomes,
beginsym, endsym, ifsym,    thensym,  whilesym,
writesym, readsym,  dosym,  callsym,  constsym,
varsym,  procsym,
elsesym, repeatsym, untilsym, returnsym, 
forsym,tosym,downtosym,//增加for语句关键字
addbecomes,//运算符+=
minusbecomes,//运算符-=
timesbecomes,//运算符*=
slashbecomes,//运算符/=
incsym,//运算符++
decsym,//运算符--
lepa,//数组的左括号[
ripa,//数组的右括号]
mod,//取余
};

//****************************************************************
//此数组是为了词法分析输出保留字而建立的
char *symout[] = {
	"nul",    "ident",     "number",     "plus",     "minus",
	 "times",   "slash",   "oddsym",   "eql",     "neq",
"lss",     "leq",      "gtr",     "geq",     "lparen",
"rparen",  "comma",   "semicolon","period",  "becomes",
"beginsym", "endsym", "ifsym",    "thensym",  "whilesym",
"writesym", "readsym",  "dosym",  "callsym",  "constsym",
"varsym",  "procsym","elsesym","repeatsym","untilsym","returnsym",
"forsym","stepsym","tosym","downtosym",
"addbecomes","minusbecomes","timesbecomes","slashbecomes","inc","dec","lepa","ripa","mod"
};
//****************************************************************
#define symnum 44		
//****************************************************************
//错误原因说明字符数组
char *errortxt[]=
{
	//错误原因																	出错编号
	"",																			//0没有使用
	"常数说明中的\"=\"写成\":=\"",												//1
	"常数说明中的\"=\"后应是数字",												//2
	"常数说明中的标识符后应是\"=\"",											//3
	"const,var,procedure后应为标识符",											//4
	"漏掉了\",\"或者\";\"",														//5
	"过程说明后的符号不正确（应是语句开始符，或过程定义符）",					//6
	"应是语句开始符",															//7
	"repeat语句缺少\"until\"",											    	//8
	"程序结尾丢了句号\".\"",													//9
	"语句之间漏了\";\"",														//10
	"标识符未说明",																//11
	"赋值语句中，赋值号左部标识符属性应是变量",									//12
	"赋值语句左部标识符后应是赋值号\":=\"、\"+=\"、\"-=\"、\"*=\"、\"/=\"",		//13
	"call后应为标识符",															//14
	"call后标识符属性应为过程",													//15
	"条件语句中丢了\"then\"",													//16
	"丢了\"end\"或者\";\"",														//17
	"while型循环语句中丢了\"do\"",												//18
	"for语句后跟赋值语句，赋值语句左部是变量，缺少变量",						//19
	"运算符不是关系运算符",														//20
	"表达式内标识符属性不能是过程",												//21
	"表达式中漏掉右括号",														//22
	"因子后的非法符号",															//23
	"表达式的开始符不正确",														//24
	"数组下标定义不符合规定，应为常量",											//25
	"数组缺少右中括号\"]\"",													//26
	"数组变量后跟着\"[\"",														//27
	"数组下标越界",																//28
	"for语句中缺少了\"do\"",													//29
	"数字的长度太长",															//30
	"数超出规定的界限",															//31
	"当前分程序所在层层次超过规定的最大层次",									//32
	"read和write语句中，缺少右括号\")\"",										//33
	"read和write语句中，缺少左括号",											//34
	"read语句中，()里必须是标识符"												//35
};

/*--标识符的类型属性--*/
enum object{
   constant,
   variable,
   procedur,
   array,
};
/*---虚拟机代码指令操作码---*/
enum fct{
lit, opr,  lod,  sto,  cal,  inte,  jmp,  jpc, 
gar,//根据栈顶的偏移地址从数组中取值到新的栈顶
sar,//根据次栈顶的偏移地址把栈顶的值存入数组
shd,//将栈顶的值下移到次栈顶，栈顶出栈，即次栈顶成为栈顶
del,//出栈顶
jud,//判断数组下标合法性
tra,//将数组的下标范围入栈，gendo(tra,0,数组下标最大值);
};
#define fctnum 14
/*--------------*/
struct instruction
{
  enum fct f;
  int l;
  int a;
};

FILE * fas;
FILE * fa;
FILE * fa1;
FILE * fa2;

bool tableswitch;
bool listswitch;
char ch;
enum symbol sym;
char id[al+1];
int  num;
int  arraysize;
int cc,ll;
int cx;
char line[81];
char a[al+1];
struct instruction code[cxmax];
char word[norw][al];
enum symbol wsym[norw];
enum symbol ssym[256];
char mnemonic[fctnum][5];
bool declbegsys[symnum];
bool statbegsys[symnum];
bool facbegsys[symnum];
/*------------------------------*/

struct tablestruct
{
   char name[al];                            /*名字*/
   enum object kind;                         /*类型：const，var，array or procedure*/
   int val;                                  /*数值，仅const使用*/
   int level;                                /*所处层，仅const不使用*/
   int adr;                                  /*地址，仅const不使用*/
   int size;                                 /*需要分配的数据区空间，仅procedure使用*/
};
struct tablestruct table[txmax];             /*名字表*/
FILE * fin;
FILE* fout;
char fname[al];
int err;                                       /*错误计数器*/
/*当函数中会发生fatal error时，返回－1告知调用它的函数，最终退出程序*/
#define getsymdo                              if(-1==getsym())return -1
#define getchdo                               if(-1==getch())return -1
#define testdo(a,b,c)                         if(-1==test(a,b,c))return -1
#define gendo(a,b,c)                          if(-1==gen(a,b,c))return -1
#define expressiondo(a,b,c)                   if(-1==expression(a,b,c))return -1
#define factordo(a,b,c)                       if(-1==factor(a,b,c))return -1
#define termdo(a,b,c)                         if(-1==term(a,b,c))return -1
#define conditiondo(a,b,c)                    if(-1==condition(a,b,c))return -1
#define statementdo(a,b,c)                    if(-1==statement(a,b,c))return -1
#define constdeclarationdo(a,b,c)             if(-1==constdeclaration(a,b,c))return -1
#define vardeclarationdo(a,b,c)               if(-1==vardeclaration(a,b,c))return -1
void error(int n);
int getsym();
int getch();
void init();
int gen(enum fct x,int y,int z);
int test(bool*s1,bool*s2,int n);
int inset(int e,bool*s);
int addset(bool*sr,bool*s1,bool*s2,int n);
int subset(bool*sr,bool*s1,bool*s2,int n);
int mulset(bool*sr,bool*s1,bool*s2,int n);
int block(int lev,int tx,bool* fsys);
void interpret();
int factor(bool* fsys,int* ptx,int lev);
int term(bool*fsys,int*ptx,int lev);
int condition(bool*fsys,int*ptx,int lev);
int expression(bool*fsys,int*ptx,int lev);
int statement(bool*fsys,int*ptx,int lev);
void listcode(int cx0);
int vardeclaration(int* ptx,int lev, int* pdx);
int constdeclaration(int* ptx,int lev, int* pdx);
int position(char* idt,int tx);
void enter(enum object k,int* ptx,int lev,int* pdx);
int base(int l,int* s,int b);

        








