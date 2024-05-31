                         /*PL/0 ����ϵͳC�汾ͷ�ļ� pl0.h*/
//*******************
//�˷�ΧΪ�޸ĵĵط�
//*******************

//*************************************
# define norw 26		//�ؼ�������
//*************************************

# define txmax 100               /*���ֱ�����*/
# define nmax  14                /*number�����λ��*/
# define al 10                   /*���ŵ���󳤶�*/
# define amax 2047               /*��ַ�Ͻ�*/
# define levmax 3                /*����������Ƕ����������[0��lexmax]*/
# define cxmax 500               /*���������������*/
/*����*/
enum symbol{
nul,    ident,     number,     plus,     minus,
times,   slash,   oddsym,   eql,     neq,
lss,     leq,      gtr,     geq,     lparen,
rparen,  comma,   semicolon,period,  becomes,
beginsym, endsym, ifsym,    thensym,  whilesym,
writesym, readsym,  dosym,  callsym,  constsym,
varsym,  procsym,
elsesym, repeatsym, untilsym, returnsym, 
forsym,tosym,downtosym,//����for���ؼ���
addbecomes,//�����+=
minusbecomes,//�����-=
timesbecomes,//�����*=
slashbecomes,//�����/=
incsym,//�����++
decsym,//�����--
lepa,//�����������[
ripa,//�����������]
mod,//ȡ��
};

//****************************************************************
//��������Ϊ�˴ʷ�������������ֶ�������
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
//����ԭ��˵���ַ�����
char *errortxt[]=
{
	//����ԭ��																	������
	"",																			//0û��ʹ��
	"����˵���е�\"=\"д��\":=\"",												//1
	"����˵���е�\"=\"��Ӧ������",												//2
	"����˵���еı�ʶ����Ӧ��\"=\"",											//3
	"const,var,procedure��ӦΪ��ʶ��",											//4
	"©����\",\"����\";\"",														//5
	"����˵����ķ��Ų���ȷ��Ӧ����俪ʼ��������̶������",					//6
	"Ӧ����俪ʼ��",															//7
	"repeat���ȱ��\"until\"",											    	//8
	"�����β���˾��\".\"",													//9
	"���֮��©��\";\"",														//10
	"��ʶ��δ˵��",																//11
	"��ֵ����У���ֵ���󲿱�ʶ������Ӧ�Ǳ���",									//12
	"��ֵ����󲿱�ʶ����Ӧ�Ǹ�ֵ��\":=\"��\"+=\"��\"-=\"��\"*=\"��\"/=\"",		//13
	"call��ӦΪ��ʶ��",															//14
	"call���ʶ������ӦΪ����",													//15
	"��������ж���\"then\"",													//16
	"����\"end\"����\";\"",														//17
	"while��ѭ������ж���\"do\"",												//18
	"for�������ֵ��䣬��ֵ������Ǳ�����ȱ�ٱ���",						//19
	"��������ǹ�ϵ�����",														//20
	"���ʽ�ڱ�ʶ�����Բ����ǹ���",												//21
	"���ʽ��©��������",														//22
	"���Ӻ�ķǷ�����",															//23
	"���ʽ�Ŀ�ʼ������ȷ",														//24
	"�����±궨�岻���Ϲ涨��ӦΪ����",											//25
	"����ȱ����������\"]\"",													//26
	"������������\"[\"",														//27
	"�����±�Խ��",																//28
	"for�����ȱ����\"do\"",													//29
	"���ֵĳ���̫��",															//30
	"�������涨�Ľ���",															//31
	"��ǰ�ֳ������ڲ��γ����涨�������",									//32
	"read��write����У�ȱ��������\")\"",										//33
	"read��write����У�ȱ��������",											//34
	"read����У�()������Ǳ�ʶ��"												//35
};

/*--��ʶ������������--*/
enum object{
   constant,
   variable,
   procedur,
   array,
};
/*---���������ָ�������---*/
enum fct{
lit, opr,  lod,  sto,  cal,  inte,  jmp,  jpc, 
gar,//����ջ����ƫ�Ƶ�ַ��������ȡֵ���µ�ջ��
sar,//���ݴ�ջ����ƫ�Ƶ�ַ��ջ����ֵ��������
shd,//��ջ����ֵ���Ƶ���ջ����ջ����ջ������ջ����Ϊջ��
del,//��ջ��
jud,//�ж������±�Ϸ���
tra,//��������±귶Χ��ջ��gendo(tra,0,�����±����ֵ);
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
   char name[al];                            /*����*/
   enum object kind;                         /*���ͣ�const��var��array or procedure*/
   int val;                                  /*��ֵ����constʹ��*/
   int level;                                /*�����㣬��const��ʹ��*/
   int adr;                                  /*��ַ����const��ʹ��*/
   int size;                                 /*��Ҫ������������ռ䣬��procedureʹ��*/
};
struct tablestruct table[txmax];             /*���ֱ�*/
FILE * fin;
FILE* fout;
char fname[al];
int err;                                       /*���������*/
/*�������лᷢ��fatal errorʱ�����أ�1��֪�������ĺ����������˳�����*/
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

        








