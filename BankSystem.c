#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
/***********银行系统*******
    简单实现银行的:  查看余额、存钱、取钱

     查看Bank.txt 是否已经创建，没有就创建并设置初始余额为： 50(可自行修改)
     1.查看余额
     2.存钱
     3.取钱
    -1：退出
*/
#define initMoney 50
void initBank(); // 初始化，创建一个 Bank.txt 用于存储余额
void See();      // 查看余额    打印Money()的返回值
int Money();     // 返回余额
void Save();     // 存钱
void ability();  // 功能实现

void main()
{
    initBank();
    printf("\n\n\n\t\t\t\tWelcome to the Bank system!\n");
    printf("\n\n\t\t\t\tplease input:\n\t\t\t\t\t'1' : Check your balance\n\t\t\t\t\t'2' : save Money\n\t\t\t\t\t'3' : Withdraw Money");
    ability();
}
// 初始化，创建一个 Bank.txt 用于存储余额
void initBank()
{

    // 等于-1则文件不存在   #include <unistd.h>
    if ((access("Bank.txt", F_OK)) == -1)
    {
        FILE *fp;
        // 判断是否有这个文件，有就打开，没有创建打开
        if (!(fp = fopen("Bank.txt", "w")))
        { //wt+ 打开或建立一个文件
            printf("cannot open the file\n");
            exit(1); //退出
        }
        // 文件存入整数50
        putw(initMoney, fp);
        fclose(fp);
    }
}
// 查看余额
void See()
{

    printf("\t\t\t\tYour balance is:  %d\n", Money());
}
// 存钱
void Save()
{
    FILE *fp;
    char ch;
    int money;
    // 先存储文件内原有的钱
    int i = Money();
    //若文件存在，则清除原文件内容后写入；否则，新建文件后写入
    if (!(fp = fopen("Bank.txt", "r+")))
    { //wt+ 打开或建立一个文件
        printf("cannot open the file\n");
        exit(1); //退出
    }

    printf("\t\t\t\tHow much do you want to deposit: \n\t\t\t\t");
    scanf("%d", &money);
    while (money < 0)
    {
        printf("\t\t\t\tPlease enter the correct number!\n\t\t\t\t");
        scanf("%d", &money);
    }

    printf("\t\t\t\tYour balance is:  %d", i + money);
    money += i;
    putw(money, fp);

    printf("\n");
    fclose(fp); //关闭文件
}
// 取钱
void Withdraw()
{
    // 对文件只读
    FILE *fp;
    int dSee;
    int i = Money();
    if (!(fp = fopen("Bank.txt", "r+")))
    {
        printf("cannot open the file\n");
        exit(1); //退出
    }

    printf("\t\t\t\tHow much do you want to withdraw: \n\t\t\t\t");
    scanf("%d", &dSee);
    while (dSee > i)
    {
        printf("\t\t\t\tplease input again:\n\t\t\t\t");
        scanf("%d", &dSee);
    }

    i -= dSee;
    putw(i, fp);
    printf("\t\t\t\tyour balance is: %d", i);
    fclose(fp); //关闭文件
}
// 功能实现
void ability()
{
    // 创建银行文件
    int num;
    do
    {
        printf("\n\n\t\t\t\tWhat service do you want: ");
        scanf("%d", &num);
        // 只要不输入 -1，就不退出
        switch (num)
        {
        case -1:
            printf("\t\t\t\texit Bank.txt System!\n");
            exit(-1);
            break;
        case 1:
            Money();
            break;
        case 2:
            Save();
            break;
        case 3:
            Withdraw();
            break;
        default:
            printf("\t\t\t\tThe number you entered is wrong. Please re-enter it!\n");
            printf("\t\t\t\t");
            ability();
        }

    } while (num != -1);
}
// 返回余额
int Money()
{

    FILE *fp;
    int ch;
    // 对文件只读
    if (!(fp = fopen("Bank.txt", "r")))
    {
        printf("cannot open the file\n");
        exit(1); //退出
    }
    int i = getw(fp);
    printf("\t\t\t\tYour balance is:  %d\n", i);
    fclose(fp); //关闭文件
    return i;
}