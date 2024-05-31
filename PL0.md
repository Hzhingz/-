# 编译原理实验报告

## 一、实验目的与要求

	对PL/0作以下修改和扩充，并使用测试用例验证：

	（1）修改单词：不等号# 改为 != ，只有！符号为非法单词，同时#成为非法符号。
	（2）增加单词(只实现词法分析部分)：
	保留字 ELSE，FOR，TO，CHAR，FLOAT
	运算符 *=，/=，++，--
	注释符 //，/*，*/
	（3）增加IF条件语句的ELSE子句（实现语法语义目标代码），要求：写出相关文法或语法图，分析语法语义目标代码的实现。
    （4）扩充语句（Pascal的FOR语句）（实现语法语义目标代码）:FOR <变量>:=<表达式>TO<表达式>DO<语句>
	要求：写出相关文法或语法图，分析语法语义目标代码的实现。

## 二、实验环境与工具 

	1、源语言：PL/0语言，PL/0语言是PASCAL语言的子集，它的编译程序是一个编译解析执行系统，后缀名为.PL0；
	2、目标语言：生成文件后缀为*.COD的目标代码 
	3、实现平台：Borland C++ Builder 6 
	4、运行平台：Windows 10 64位 

## 三、结构流程

### （1）PL/0 语言编译器 

PL/0语言可看成是PASCAL语言的子集，它的编译程序是一个。编译解释执行系统。PL/0的目标程序为假想栈式计算机的汇编语言，与具体计算机无关。

![](jiegou.png)

## 四、实验过程

### （一）修改单词：不等号# 改为 != ，只有！符号为非法单词，同时#成为非法符号。


        else  /* THE FOLLOWING TWO CHECK WERE ADDED
		         BECAUSE ASCII DOES NOT HAVE A SINGLE CHARACTER FOR <= OR >= */
		    if (CH=='<') {
			  GetCh();
			  if (CH=='=') { SYM=LEQ; GetCh(); }
			  else if (CH=='>') {SYM=NEQ; GetCh(); }
			  else SYM=LSS;
			}
			else
			  if (CH=='>') {
			    GetCh();
				if (CH=='=') { SYM=GEQ; GetCh(); }
				else SYM=GTR;

### （二）增加单词(只实现词法分析部分)：
####1.保留字 ELSE，FOR，TO，CHAR，FLOAT
####2.运算符 *=，/=，++，--
####3.注释符 //，/*，*/

**首先参照已有的保留字，进行相应的命名和添加规范，再将新增的保留字添加对应的保留字的集合中。具体实现的语句如下所示：**

	typedef enum  { NUL, IDENT, NUMBER, PLUS, MINUS, TIMES,
		            SLASH, ODDSYM, EQL, NEQ, LSS, LEQ, GTR, GEQ,
		            LPAREN, RPAREN, COMMA, SEMICOLON, PERIOD,
		            BECOMES, BEGINSYM, ENDSYM, IFSYM, THENSYM,
		            WHILESYM, WRITESYM, READSYM, DOSYM, CALLSYM,
		            CONSTSYM, VARSYM, PROCSYM, PROGSYM,
		            // 实验内容：增加 else、for 等保留字
		            ELSESYM, FORSYM, TOSYM, CHARSYM, FLOATSYM,
		            // 实验内容：增加运算符 *=, /=
		            MULEQUALSYM, DIVEQUALSYM, ANDSYM, ORSYM, GATESYM,
		            // 增加 ++ 与 --
		            INCSYM, DECSYM
	        } SYMBOL;
	char *SYMOUT[] = {"NUL", "IDENT", "NUMBER", "PLUS", "MINUS", "TIMES",
		    "SLASH", "ODDSYM", "EQL", "NEQ", "LSS", "LEQ", "GTR", "GEQ",
		    "LPAREN", "RPAREN", "COMMA", "SEMICOLON", "PERIOD",
		    "BECOMES", "BEGINSYM", "ENDSYM", "IFSYM", "THENSYM",
		    "WHILESYM", "WRITESYM", "READSYM", "DOSYM", "CALLSYM",
		    "CONSTSYM", "VARSYM", "PROCSYM", "PROGSYM",
		    // 增加 保留字
		    "ELSESYM", "FORSYM", "TOSYM", "CHARSYM", "FLOATSYM",
		    // 增加 运算符
		    "MULEQUALSYM", "DIVEQUALSYM", "ANDSYM", "ORSYM", "GATESYM",
		    // 增加 ++ 与 --
		    "INCSYM", "DECSYM"
		     };


**将新增的保留字按照字母表升序的方式添加，运算符参照已有的运算符来进行添加，注意好符号与SYM的对应。具体实现的语句如下所示：** 

	strcpy(KWORD[ 1], "AND");		strcpy(KWORD[ 2],"BEGIN");    
	  strcpy(KWORD[ 3], "CALL");	strcpy(KWORD[ 4],"CHAR");
	  strcpy(KWORD[ 5],"CONST");    strcpy(KWORD[ 6], "DEC"); //  --
	  strcpy(KWORD[ 7], "DIVEQUAL");    strcpy(KWORD[ 8],"DO");
	  strcpy(KWORD[ 9], "ELSE");	strcpy(KWORD[ 10],"END");
	  strcpy(KWORD[11], "FLOAT");	strcpy(KWORD[12], "FOR");	
                  strcpy(KWORD[13], "GATE");
	  strcpy(KWORD[14], "INC"); //  ++
	  strcpy(KWORD[15], "IF");		strcpy(KWORD[16], "MULEQUAL");
	  strcpy(KWORD[17], "ODD");     strcpy(KWORD[18], "OR");
	  strcpy(KWORD[19],"PROCEDURE");   strcpy(KWORD[20],"PROGRAM");
	  strcpy(KWORD[21], "READ");	      strcpy(KWORD[22],"THEN");
	  strcpy(KWORD[23],"TO");           strcpy(KWORD[24],"VAR");
	  strcpy(KWORD[25], "WHILE");   strcpy(KWORD[26],"WRITE");
	  // 设置保留字符号
	  WSYM[ 1]=ANDSYM;		WSYM[ 2]=BEGINSYM;
	  WSYM[ 3]=CALLSYM;		WSYM[ 4]=CHARSYM;
	  WSYM[ 5]=CONSTSYM;		WSYM[ 6]=DECSYM;
	  WSYM[ 7]=DIVEQUALSYM;		WSYM[ 8]=DOSYM;
	  WSYM[ 9]=ELSESYM;		WSYM[ 10]=ENDSYM;
	  WSYM[11]=FLOATSYM;		WSYM[12]=FORSYM;
	  WSYM[13]=GATESYM;		WSYM[14]=INCSYM;
	  WSYM[15]=IFSYM;			WSYM[16]=MULEQUALSYM;
	  WSYM[17]=ODDSYM;		WSYM[18]=ORSYM;
	  WSYM[19]=PROCSYM;		WSYM[20]=PROGSYM;
	  WSYM[21]=READSYM;		WSYM[22]=THENSYM;
	  WSYM[23]=TOSYM;	WSYM[24]=VARSYM;
	  WSYM[25]=WHILESYM;	WSYM[26]=WRITESYM;

**修改 void GetSym() 函数，添加'//' （'/ /'） 注释符识别新增的运算符需要被编译器识别，必须满足编译器做词法分析时，能够正确得到对于的SYM，因此在GetSym()函数中在相应位置增加相应的运算符分析判断，具体实现如下面所示的语句：**

		else
          if (CH=='!') {
	    GetCh();
		if (CH=='=') { SYM=NEQ; GetCh(); }
		else SYM=NUL;
			  }
			else
			  if (CH=='/') {
			  	GetCh();
			  	if (CH=='='){ SYM=DIVEQUALSYM; GetCh();}
			  	
			else if (CH=='*') { 		// 过滤/* */注释
			  		i = 0;
			  		do {
			  			GetCh();
			  			if(CH=='*') {
			  				i=1;
			  			} else if (CH=='/') {
			  				if (i==1) { // 确保最后一个/前的*
			  					i=2;	
			  				}
			  			} else {
			  				i=0;
			  			}
			  		} while(i!=2); // 循环跳过
			  		GetCh();
			  	}
			  	else if(CH == '/') { 		// '//' 单行注释
			  		i = CX; // 记录当前行号
			  		while(CC!=LL) {
			  			GetCh();
			  		}
			  		GetCh();
			  	}
			  	else SYM=SLASH;
			  }
			else
			  if (CH=='&') {
			  	GetCh();
			  	SYM=ANDSYM;
			  }
			else
			  if (CH=='|') {
			  	GetCh();
			  	if (CH=='|'){ SYM=ORSYM; GetCh(); }
			  	else Error(19);
			  }
			else
			  if (CH=='!') {
			  	GetCh();
			  	if (CH=='=') {SYM=NEQ; GetCh(); }
			  	else SYM=GATESYM;
			  }
			else
			  if (CH=='+') {	// 运算符 '++'
			  	GetCh();
			  	if (CH=='+') {SYM=INCSYM; GetCh(); }
			  	else SYM=PLUS;
			  }
			else 
			  if (CH=='-') {
			  	GetCh();
			  	if (CH=='-') {SYM=DECSYM; GetCh(); }
			  	else SYM=MINUS;
			  }
			  else { SYM=SSYM[CH]; GetCh(); }
	} /*GetSym()*/

	EXPRESSION(FSYS, LEV, TX);
			if(TEMP==MULEQUALSYM) {
				// 实现 *=
				GEN(OPR, 0, 4);
			}
			else if(TEMP==DIVEQUALSYM) {
				// 实现 /=
				GEN(OPR, 0, 5);
			}
###（三）增加IF条件语句的ELSE子句（实现语法语义目标代码）

![](else.png)
	
// 增加else子句

			GetSym();
			CONDITION(SymSetUnion(SymSetNew(THENSYM,DOSYM),FSYS),LEV,TX);
			if (SYM==THENSYM) GetSym();
			else Error(16);
			CX1=CX;  GEN(JPC,0,0);
			STATEMENT(SymSetUnion(SymSetNew(ELSESYM),FSYS),LEV,TX);
			if (SYM==SEMICOLON) GetSym();
			else Error(5);	// 漏掉分号
			if (SYM!=ELSESYM) {
				CODE[CX1].A=CX;
			}
			else {
				GetSym();	// 读取单词
				CX2=CX; //保存无条件跳转指令的地址，等待结束指令地址的回填
				GEN(JMP, 0, 0); //把ELSE首地址回填给JPC条件转移指令跳转的地址
				CODE[CX1].A=CX;
				// 执行语句
				STATEMENT(SymSetUnion(SymSetNew(ELSESYM), FSYS), LEV, TX); 
				CODE[CX2].A=CX; // 结束指令的地址回填到无条件跳转的地址
			}
			// STATEMENT(FSYS,LEV,TX); 
			// CODE[CX1].A=CX;
			break;

###(四)扩充语句（Pascal的FOR语句）（实现语法语义目标代码）:FOR <变量>:=<表达式>TO<表达式>DO<语句>

**for语句打的语句语发图如下**
![](fortodo.png)

首先，词法分析部分增加关键字
在SYMBOL里增加FORSYM, TOSYM, TOSYM

其次，修改STATEMENT，代码如下：

		case FORSYM:
			// 检测到 for 子句
			GetSym();
			if(SYM!=IDENT) {
				Error(13); // 判断是否为变量符号
			}
			else {
				i = POSITION(ID, TX);
				if (i==0) Error(11);
				else if (TABLE[i].KIND!=VARSYM) {
					// 赋值语句中，赋值左部标识符是变量
					i=0;
				}
				GetSym();
				if(SYM!=BECOMES) {
					Error(13);
				} else {
					GetSym();
					EXPRESSION(SymSetUnion(SymSetNew(TOSYM, CHARSYM, DOSYM), FSYS), LEV, TX);
					if (i != 0) {
						GEN(STO, LEV-TABLE[i].vp.LEVEL, TABLE[i].vp.ADR); // 保持初值
					}
					CX1=CX;
					GEN(JMP, 0, 0);
					CX1=CX; // 保持循环开始点
					if (SYM!=CHARSYM) {
						Error(19); 
					} else {
						GetSym();
						EXPRESSION(SymSetUnion(SymSetNew(TOSYM, CHARSYM, DOSYM), FSYS), LEV, TX);
						GEN(LOD, LEV-TABLE[i].vp.LEVEL, TABLE[i].vp.ADR); // 将循环变量放到栈顶
						GEN(OPR, 0, 2);
						GEN(STO, LEV-TABLE[i].vp.LEVEL, TABLE[i].vp.ADR); // 将栈顶的值放入循环变量
						if(SYM!=TOSYM) {
							Error(19); 
						} else {
							CODE[CX1-1].A=CX; 
							GetSym();
							EXPRESSION(SymSetUnion(SymSetNew(TOSYM, CHARSYM, DOSYM), FSYS), LEV, TX);
							GEN(LOD, LEV-TABLE[i].vp.LEVEL, TABLE[i].vp.ADR);
							GEN(OPR, 0, 12);
							CX2=CX;
							GEN(JPC, 0, 0);
							if (SYM==DOSYM) {
								GetSym();
								STATEMENT(FSYS, LEV, TX);
								GEN(JMP, 0, CX1);
								CODE[CX2].A=CX;
							} else {
								Error(19); // 没有读取到 do
							}
						}
					}
				}
			}
			break;

### 五、关于测试用例说明

####（1）运行界面
![](form1.png)

![](form2.png)

####(2)测试用例E01

	PROGRAM EX01;
	VAR A,B,C;
	BEGIN
	A:=88;
	B:=1;
    C:=A+B*(3+B);
    WRITE(C);
    ELSE;
    FOR;
    TO;
    CHAR;
    FLOAT;
     *=;
    /=;
     ++;
     --;
    //;
    END.

实验截图
![](E01.png)
![](E01COD.png)

####(3)ELSE测试

	var a,b; 
    begin
    a:=7;
    b:=6;
    if a<b
    then
    write(a) 
    else
    write(b);
    end.

![](test01.png)
![](test02.png)

####(4)FOR语句测试

	PROGRAM EX01;
	VAR X,SUM;
	BEGIN
	  SUM:=1; 
	  FOR X:=1
	  CHAR 1
	  TO 10
	  DO BEGIN 
      WRITE(SUM);
	  END;
	;
	END.

实验截图
![](FORTO01.png)
![](FORTO.png)

## 七、心得体会

总的来说，课内实验 部分还是让我获益匪浅的。通过完成 “PL0编译器扩充” 这个实验 让我对编译原理这门课程有了深刻的了解，包括如何进行词法分析，语法分析，语义分析等过程等。平日里看起来非常普通的编译器其实背后隐藏着很多知识。

对于实验内容来说，增添保留字和运算符以及修改单词是很基本的操作。只要明白词法分析的过程就很容易完成，对于ELSE语句的添加，更多的是体现在ELSE语句体的语义分析上面，这个需要我们对语义衔接跳转回调的理解。

我较为全面系统的理解了编译原理程序构造的原理和基本实现方法。自己对修改的方案比较满意，在扩充功能上去实现自己希望PL0能具备的功能。在条件选择和循环的语句扩展上比较有心得，增加了FOR语句。实现了++以及++等扩展功能。印象比较深刻的是一维数组的扩展，扩展此功能时，我先设计方案，明确需要修改的地方。然而虽然思路明确，但扩展时却出现了很多意想不到的问题，结果花费了大量的时间调试，再加上找参考书，咨询同学，还是顺利完成了这项扩展功能。

本次实验设计，除了能把书本的知识转化为实际应用，增加课外知识：提高自己的编程能力；熟悉 C++Builder6.0的基本应用；锻炼了自己的思维，编写程序时的逻辑性与耐心，提高自己的设计能力与计划能力。
本次课程设计让我收获良多，以后要继续学习，不断钻研，努力掌握更多的专业知识，成为一个技术型人才。
