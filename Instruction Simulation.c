int                 x;                  //  全局变量

int Test(void);                         //  函数原型

int
main(void)
{
    int             y;                  //  局部自动变量
    
    y = Test();
    return (x - y);
}
