/********************************************/
/* InputBox.h */
/********************************************/
BOOL _InitInputBox(HWND hParent); // ��ѡ�������ڵ���InputBox����֮ǰ��õ���һ�¸ú�����
// �ú����ǳ�ʼ��InputBox,��Ҫ���Ǵ���һ�������ھ����
void _SetNumber(BOOL fIsNumber); // ��ѡ���ú���������Editֻ����������
void _SetLowerCase(BOOL fIsLowerCase); // ��ѡ���ú���������Editֻ������Сд��ĸ
void _SetUpperCase(BOOL fIsUpperCase); // ��ѡ���ú���������Editֻ�������д��ĸ
void _SetMaxLine(unsigned int nLineSize); // ��ѡ���ú���������Edit������������ַ�����Ĭ�������256���ַ������ܳ����������

/*********************************************************/
/* InputBox���� */
/* lpWndMsg ; ��ѡ������������ʾ�û� */
/* lpWndTitle ; ��ѡ����, ���öԻ���Ĭ�ϱ��� */
/* lpDefValue ; ��ѡ����������EditĬ��ֵ */
/* xPos ; ��ѡ���������Ϊ������д��� */
/* yPos ; ��ѡ���������Ϊ������д��� */
/* lpHelpFile ; ��ѡ��������*.hlp�����ļ� */
/* nHelpIndex ; ��ѡ�����������������lpHelpFile������ */
/* ; �����������Help�ļ������� */
/* ��������ɹ�������һ��char *ָ�룬�����û���������� */
/*********************************************************/
char *_InputBox(char *lpWndMsg,
char *lpWndTitle = "����!",
char *lpDefValue = "",
int xPos = 0,
int yPos = 0,
char *lpHelpFile = "",
int nHelpIndex = 0);

#define InputBox _InputBox
#define SetNumber _SetNumber
#define InitInputBox _InitInputBox
#define SetLowerCase _SetLowerCase
#define SetUpperCase _SetUpperCase
#define SetMaxLine _SetMaxLine
