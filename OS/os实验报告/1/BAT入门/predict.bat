@Echo Off
:next
Set /p date=please input your birthday(exp. 20010101)


Set year=%date:~0,4%
Set monthday=%date:~4,4%
Set month=%date:~4,2%
Set day=%date:~6,2%

if "%month%" GTR "12" (
echo "�����ʽ����,����������"
goto next
)
if "%day%" GTR "31" (
echo "�����ʽ����,����������"
goto next)


Set /a mod=%year%%%12
 
if %mod%==0 Echo ������
if %mod%==1 Echo ������
if %mod%==2 Echo ������
if %mod%==3 Echo ������
if %mod%==4 Echo ������
if %mod%==5 Echo ����ţ
if %mod%==6 Echo ������
if %mod%==7 Echo ������
if %mod%==8 Echo ������
if %mod%==9 Echo ������
if %mod%==10 Echo ������
if %mod%==11 Echo ������
 
 
 
if "%monthday%" LEQ "0119" echo ħЫ��
if "%monthday%" GEQ "0120" if "%monthday%" LEQ "0218" echo ˮƿ��
if "%monthday%" GEQ "0219" if "%monthday%" LEQ "0320" echo ˫����
if "%monthday%" GEQ "0321" if "%monthday%" LEQ "0419" echo ������
if "%monthday%" GEQ "0420" if "%monthday%" LEQ "0520" echo ��ţ��
if "%monthday%" GEQ "0521" if "%monthday%" LEQ "0621" echo ˫����
if "%monthday%" GEQ "0622" if "%monthday%" LEQ "0722" echo ��з��
if "%monthday%" GEQ "0723" if "%monthday%" LEQ "0822" echo ʨ����
if "%monthday%" GEQ "0823" if "%monthday%" LEQ "0922" echo ��Ů��
if "%monthday%" GEQ "0923" if "%monthday%" LEQ "1023" echo �����
if "%monthday%" GEQ "1024" if "%monthday%" LEQ "1122" echo ��Ы��
if "%monthday%" GEQ "1123" if "%monthday%" LEQ "1221" echo ��Ы��
if "%monthday%" GEQ "1222" echo ħЫ��
goto next
Pause