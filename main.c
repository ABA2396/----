#include "main.h"

void main()
{
    init();   // ��ʼ������
    while (1) // ��ѭ��
    {
        key_down();    // �жϰ����Ƿ���
        reset_show();  // ����������ʾ��ֵ
    }
}
