#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위는 내림차순, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];
char postfixExp[MAX_EXPRESSION_SIZE];
char postfixStack[MAX_STACK_SIZE];
int evalStack[MAX_STACK_SIZE];

int postfixStackTop = -1;
int evalStackTop = -1;

int evalResult = 0;

void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	char command;
	do{
		printf("[----------------- [Cho Daehyeon] [2016039075] -----------------]\n");
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;


}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop()
{
	char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x;
}

int evalPop()
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */

void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	char *exp = infixExp;	// infixExp에서 문자 차례로 가져옴
	char x;		// 가져온 문자 저장하는 변수

	while(*exp != '\0')
	{
		if(getPriority(*exp) == operand)	// 읽은 문자가 숫자일 때
		{
			x = *exp;		// exp로 읽은 숫자 변수 x에 저장
        	charCat(&x);	// postfixExp에 x에 저장된 숫자 복사
		}
        else if(getPriority(*exp) == lparen) {	// 읽은 문자가 (일때

        	postfixPush(*exp);		// postfixStack에 exp로 읽은 문자 저장
        }
        else if(getPriority(*exp) == rparen)	// 읽은 문자가 )일때
        {
        	while((x = postfixPop()) != '(') {
        		charCat(&x);					// 스택에서 (까지 저장된 문자 pop해서 postfixExp에 저장
        	}
        }
        else
        {	/* exp로 읽은 문자가 postfixStack의 top문자보다 우선순위가 낮을 때 */
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))	
            {
            	x = postfixPop();	// postfixStack에서 pop해온 문자를 postfixExp에 저장
            	charCat(&x);
            }
            postfixPush(*exp);	// exp로 읽은 문자를 postfixStack에 push
        }
        exp++;
	}

    while(postfixStackTop != -1)
    {
    	x = postfixPop();
    	charCat(&x);
    }

}

void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}
void evaluation()
{
	int opr1, opr2, i;

	int length = strlen(postfixExp);	// postfixExp에 저장된 문자열 길이 구하기
	char symbol;		// postfixExp의 문자를 하나씩 가져와서 저장하는 변수
	evalStackTop = -1;	// evalStack의 Top -1로 초기화

	for(i = 0; i < length; i++)
	{
		symbol = postfixExp[i];
		if(getToken(symbol) == operand) {	// postfixExp에서 가져온 문자가 숫자일 때
			evalPush(symbol - '0');			// ascii 문자값 48을 빼서 숫자 얻기
		}
		else {		// postfixExp에서 가져운 문자가 연산자일 때
			opr2 = evalPop();	// 첫 번째 숫자 pop
			opr1 = evalPop();	// 두 번째 숫자 pop
			switch(getToken(symbol)) {
			case plus: evalPush(opr1 + opr2); break;	// 가져온 문자가 +일 때
			case minus: evalPush(opr1 - opr2); break;	// 가져온 문자가 -일 때
			case times: evalPush(opr1 * opr2); break;	// 가져온 문자가 *일 때
			case divide: evalPush(opr1 / opr2); break;	// 가져온 문자가 /일 때
			default: break;
			}
		}
	}
	evalResult = evalPop();		// 계산 결과 pop 
}
